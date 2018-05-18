//说明部分

//系统
#include "stdafx.h"
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python封装
#include <boost/python/def.hpp>		//python封装
#include <boost/python/dict.hpp>	//python封装
#include <boost/python/object.hpp>	//python封装
#include <boost/python.hpp>			//python封装
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能

//API
#include "xtp_quote_api.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

// 常量
#define ONDISCONNECTED 0
#define ONERROR 1
#define ONSUBMARKETDATA 2
#define ONUNSUBMARKETDATA 3
#define ONDEPTHMARKETDATA 4
#define ONSUBORDERBOOK 5
#define ONUNSUBORDERBOOK 6
#define ONORDERBOOK 7
#define ONSUBTICKBYTICK 8
#define ONUNSUBTICKBYTICK 9
#define ONTICKBYTICK 10
#define ONSUBSCRIBEALLMARKETDATA 11
#define ONUNSUBSCRIBEALLMARKETDATA 12
#define ONSUBSCRIBEALLORDERBOOK 13
#define ONUNSUBSCRIBEALLORDERBOOK 14
#define ONSUBSCRIBEALLTICKBYTICK 15
#define ONUNSUBSCRIBEALLTICKBYTICK 16
#define ONQUERYALLTICKERS 17
#define ONQUERYTICKERSPRICEINFO 18

// GIL全局锁
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//在某个函数方法中创建该对象时，获得GIL锁
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//在某个函数完成后销毁该对象时，解放GIL锁
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};

// 任务结构体
//任务结构体
struct Task
{
	int task_name;		//回调函数名称对应的常量
	void *task_data;	//数据结构体
	void *task_error;	//错误结构体
	int task_id;		//整数
	bool task_last;		//是否为最后返回
};

// 线程安全的队列
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//标准库队列
	mutable mutex the_mutex;							//boost互斥锁
	condition_variable the_condition_variable;			//boost条件变量

public:

	//存入新的任务
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				//获取互斥锁
		the_queue.push(data);							//向队列中存入数据
		lock.unlock();									//释放锁
		the_condition_variable.notify_one();			//通知正在阻塞等待的线程
	}

	//检查队列是否为空
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//取出
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//当队列为空时
		{
			the_condition_variable.wait(lock);			//等待条件变量通知
		}

		Data popped_value = the_queue.front();			//获取队列中的最后一个任务
		the_queue.pop();								//删除该任务
		return popped_value;							//返回该任务
	}

};

/// 从python字典获取特定类型键值的函数
//从字典中获取某个建值对应的整数，并赋值到请求结构体对象的值上
void getInt(dict d, string key, int* value);

//从字典中获取某个建值对应的整数，并赋值到请求结构体对象的值上
void getLong(dict d, string key, int* value);

//从字典中获取某个建值对应的浮点数，并赋值到请求结构体对象的值上
void getDouble(dict d, string key, double* value);

//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getString(dict d, string key, char* value);

// 从字典中取键值的函数


/// ----------------------------------------------------------------------
/// SPI 的实现
/// ----------------------------------------------------------------------
class MdApi : public XTP::API::QuoteSpi
{
private:
	XTP::API::QuoteApi *api;
	thread *task_thread;		// 工作线程指针,boost
	ConcurrentQueue<Task*> task_queue;		// 任务队列

public:
	MdApi()
	{
		function0<void> f = boost::bind(&MdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~MdApi()
	{
	}

	// API 回调函数 -- 推入任务队列
	virtual void OnDisconnected(int reason);
	virtual void OnError(XTPRI *error_info);
	virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last);
	virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last);
	virtual void OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count);
	virtual void OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last);
	virtual void OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last);
	virtual void OnOrderBook(XTPOB *order_book);
	virtual void OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last);
	virtual void OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last);
	virtual void OnTickByTick(XTPTBT *tbt_data);
	virtual void OnSubscribeAllMarketData(XTPRI *error_info);
	virtual void OnUnSubscribeAllMarketData(XTPRI *error_info);
	virtual void OnSubscribeAllOrderBook(XTPRI *error_info);
	virtual void OnUnSubscribeAllOrderBook(XTPRI *error_info);
	virtual void OnSubscribeAllTickByTick(XTPRI *error_info);
	virtual void OnUnSubscribeAllTickByTick(XTPRI *error_info);
	virtual void OnQueryAllTickers(XTPQSI *ticker_info, XTPRI *error_info, bool is_last);
	virtual void OnQueryTickersPriceInfo(XTPTPI *ticker_info, XTPRI *error_info, bool is_last);


	// 任务处理函数 -- 任务处理
	void processTask();
	void processDisconnected(Task *task);
	void processError(Task *task);
	void processSubMarketData(Task *task);
	void processUnSubMarketData(Task *task);
	void processDepthMarketData(Task *task);
	void processSubOrderBook(Task *task);
	void processUnSubOrderBook(Task *task);
	void processOrderBook(Task *task);
	void processSubTickByTick(Task *task);
	void processUnSubTickByTick(Task *task);
	void processTickByTick(Task *task);
	void processSubscribeAllMarketData(Task *task);
	void processUnSubscribeAllMarketData(Task *task);
	void processSubscribeAllOrderBook(Task *task);
	void processUnSubscribeAllOrderBook(Task *task);
	void processSubscribeAllTickByTick(Task *task);
	void processUnSubscribeAllTickByTick(Task *task);
	void processQueryAllTickers(Task *task);
	void processQueryTickersPriceInfo(Task *task);

	// 继承实现的回调函数 -- python继承实现
	virtual void onDisconnected(int reason){};
	virtual void onError(dict error){};
	virtual void onSubMarketData(dict data, dict error, bool last){};
	virtual void onUnSubMarketData(dict data, dict error, bool last){};
	virtual void onDepthMarketData(dict data){};
	virtual void onSubOrderBook(dict data, dict error, bool last){};
	virtual void onUnSubOrderBook(dict data, dict error, bool last){};
	virtual void onOrderBook(dict data){};
	virtual void onSubTickByTick(dict data, dict error, bool last){};
	virtual void onUnSubTickByTick(dict data, dict error, bool last){};
	virtual void onTickByTick(dict data){};
	virtual void onSubscribeAllMarketData(dict error){};
	virtual void onUnSubscribeAllMarketData(dict error){};
	virtual void onSubscribeAllOrderBook(dict error){};
	virtual void onUnSubscribeAllOrderBook(dict error){};
	virtual void onSubscribeAllTickByTick(dict error){};
	virtual void onUnSubscribeAllTickByTick(dict error){};
	virtual void onQueryAllTickers(dict data, dict error, bool last){};
	virtual void onQueryTickersPriceInfo(dict data, dict error, bool last){};


	// 主动函数
	int exit();
	void createQuoteApi(int client_id, string save_file_path);

	void release();
	string getTradingDay();
	string getApiVersion();
	dict getApiLastError();
	void setUDPBufferSize(int buff_size);
	void setHeartBeatInterval(int interval);
	int subscribeMarketData(string ticker, int exchage_id);
	int unSubscribeMarketData(string ticker, int exchage_id);
	int subscribeOrderBook(string ticker, int exchage_id);
	int unSubscribeOrderBook(string ticker, int exchage_id);
	int subscribeTickByTick(string ticker, int exchage_id);
	int unSubscribeTickByTick(string ticker, int exchage_id);
	int subscribeAllMarketData();
	int unSubscribeAllMarketData();
	int subscribeAllOrderBook();
	int unSubscribeAllOrderBook();
	int subscribeAllTickByTick();
	int unSubscribeAllTickByTick();
	int login(string ip, int port, string user, string password, int sock_type);
	int logout();
	int queryAllTickers(int exchage_id);
	int queryTickersPriceInfo(string ticker, int exchage_id);
	int queryAllTickersPriceInfo();
};