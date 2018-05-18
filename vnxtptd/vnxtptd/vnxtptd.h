// API
#include "xtp_trader_api.h"

// 系统
#ifdef WIN32
#include "stdafx.h"
#endif
#include <string>
#include <queue>
#include <vector>

// BOOST
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python封装
#include <boost/python/def.hpp>		//python封装
#include <boost/python/dict.hpp>	//python封装
#include <boost/python/list.hpp>	//python封装
#include <boost/python/object.hpp>	//python封装
#include <boost/python.hpp>			//python封装
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能

// 命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

// 常量
#define ONDISCONNECTED 0
#define ONERROR 1
#define ONORDEREVENT 2
#define ONTRADEEVENT 3
#define ONCANCELORDERERROR 4
#define ONQUERYORDER 5
#define ONQUERYTRADE 6
#define ONQUERYPOSITION 7
#define ONQUERYASSET 8
#define ONQUERYSTRUCTUREDFUND 9
#define ONQUERYFUNDTRANSFER 10
#define ONFUNDTRANSFER 11
#define ONQUERYETF 12
#define ONQUERYETFBASKET 13
#define ONQUERYIPOINFOLIST 14
#define ONQUERYIPOQUOTAINFO 15

// API中的部分组件
/// GIL全局锁
class PyLock
{
public:
	// 获取GIL
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}
	// 析构函数释放全局锁
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}

private:
	PyGILState_STATE gil_state;
};

/// 任务结构体
struct Task
{
	int task_name;		// 回调函数对应的常量
	void *task_data;	// 数据结构体
	void *task_error;	// 错误结构体
	int task_id;		// 请求id
	bool task_last;		// 是否为最后的
	uint64_t task_session;		// 会话号
};

/// 线程安全的队列
template<typename Data>
class ConcurrentQueue
{
private:
	queue<Data> the_queue;		// 队列
	mutable mutex the_mutex;	// boost互斥锁
	condition_variable the_condition_variable;	// 通知
public:
	// 存入新的任务
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);		// 获得锁
		the_queue.push(data);
		lock.unlock();
		the_condition_variable.notify_one();
	}

	// 检查队列是否为空
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);		// 获得所
		return the_queue.empty();
	}

	// 取出数据
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);
		while (the_queue.empty())
		{
			the_condition_variable.wait(lock);	// 阻塞线程等待
		}

		Data popped_value = the_queue.front();	// 获取队列中的第一个
		the_queue.pop();
		return popped_value;
	}
};

/// 从pyobj提取数据的函数
void getInt(dict d, string key, int* value);
void getDouble(dict d, string key, double* value);
void getStr(dict d, string key, char* value);


// TdApi
class TdApi : public XTP::API::TraderSpi
{
private:
	XTP::API::TraderApi* api;		// API工作对象
	thread *task_thread;			// 工作线程指针, 指向运行Process的指针
	ConcurrentQueue<Task*> task_queue; // 任务队列, 队列中的数据是Task*

public:
	/// 构造函数
	TdApi()
	{
		function0<void> f = boost::bind(&TdApi::processTask, this);
		thread t(f);	// 开一个线程运行 processTask
		this->task_thread = &t;
	}

	/// 析构函数
	~TdApi()
	{

	}

	/// SPI 回调函数声明
	virtual void OnDisconnected(uint64_t session_id, int reason);
	virtual void OnError(XTPRI *error_info);
	virtual void OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info, uint64_t session_id);
	virtual void OnTradeEvent(XTPTradeReport *trade_info, uint64_t session_id);
	virtual void OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info, uint64_t session_id);
	virtual void OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, uint64_t session_id);
	virtual void OnQueryETF(XTPQueryETFBaseRsp *etf_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryETFBasket(XTPQueryETFComponentRsp *etf_component_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryIPOInfoList(XTPQueryIPOTickerRsp *ipo_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);
	virtual void OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *quota_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id);

	/// process声明
	void processTask();
	void processDisconnected(Task *task);
	void processError(Task *task);
	void processOrderEvent(Task *task);
	void processTradeEvent(Task *task);
	void processCancelOrderError(Task *task);
	void processQueryOrder(Task *task);
	void processQueryTrade(Task *task);
	void processQueryPosition(Task *task);
	void processQueryAsset(Task *task);
	void processQueryStructuredFund(Task *task);
	void processQueryFundTransfer(Task *task);
	void processFundTransfer(Task *task);
	void processQueryETF(Task *task);
	void processQueryETFBasket(Task *task);
	void processQueryIPOInfoList(Task *task);
	void processQueryIPOQuotaInfo(Task *task);

	/// python回调函数声明
	virtual void onDisconnected(uint64_t session_id, int reason){};
	virtual void onError(dict error){};
	virtual void onOrderEvent(dict data, dict error, uint64_t session_id){};
	virtual void onTradeEvent(dict data, uint64_t session_id){};
	virtual void onCancelOrderError(dict data, dict error, uint64_t session_id){};
	virtual void onQueryOrder(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryTrade(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryPosition(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryAsset(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryStructuredFund(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryFundTransfer(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onFundTransfer(dict data, dict error, uint64_t session_id){};
	virtual void onQueryETF(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryETFBasket(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryIPOInfoList(dict data, dict error, bool last, uint64_t session_id){};
	virtual void onQueryIPOQuotaInfo(dict data, dict error, bool last, uint64_t session_id){};


	/// 主动函数声明
	void createTraderApi(uint8_t clientid, string path);
	int exit();
	void release();
	string getTradingDay();
	dict getApiLastError();
	string getApiVersion();
	uint8_t getClientIDByXTPID(uint64_t order_xtp_id);
	string getAccountByXTPID(uint64_t order_xtp_id);
	void subscribePublicTopic(int resume_type);
	void setSoftwareVersion(string version);
	void setSoftwareKey(string key);
	void setHeartBeatInterval(uint32_t interval);
	uint64_t login(string ip, int port, string user, string password, int sock_type);
	int logout(uint64_t session_id);
	uint64_t insertOrder(dict data, uint64_t session_id);
	uint64_t cancelOrder(uint64_t order_xtp_id, uint64_t session_id);
	int queryOrderByXTPID(uint64_t order_xtp_id, uint64_t session_id, int request_id);
	int queryOrders(dict data, uint64_t session_id, int request_id);
	int queryTradesByXTPID(uint64_t order_xtp_id, uint64_t session_id, int request_id);
	int queryTrades(dict data, uint64_t session_id, int request_id);
	int queryPosition(string ticker, uint64_t session_id, int request_id);
	int queryAsset(uint64_t session_id, int request_id);
	int queryStructuredFund(dict data, uint64_t session_id, int request_id);
	uint64_t fundTransfer(dict data, uint64_t session_id);
	int queryFundTransfer(dict data, uint64_t session_id, int request_id);
	int queryETF(dict data, uint64_t session_id, int request_id);
	int queryETFTickerBasket(dict data, uint64_t session_id, int request_id);
	int queryIPOInfoList(uint64_t session_id, int request_id);
	int queryIPOQuotaInfo(uint64_t session_id, int request_id);

};

