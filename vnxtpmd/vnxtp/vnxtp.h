//˵������

//ϵͳ
#include "stdafx.h"
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python��װ
#include <boost/python/def.hpp>		//python��װ
#include <boost/python/dict.hpp>	//python��װ
#include <boost/python/object.hpp>	//python��װ
#include <boost/python.hpp>			//python��װ
#include <boost/thread.hpp>			//������е��̹߳���
#include <boost/bind.hpp>			//������е��̹߳���

//API
#include "xtp_quote_api.h"

//�����ռ�
using namespace std;
using namespace boost::python;
using namespace boost;

// ����
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

// GILȫ����
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//��ĳ�����������д����ö���ʱ�����GIL��
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//��ĳ��������ɺ����ٸö���ʱ�����GIL��
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};

// ����ṹ��
//����ṹ��
struct Task
{
	int task_name;		//�ص��������ƶ�Ӧ�ĳ���
	void *task_data;	//���ݽṹ��
	void *task_error;	//����ṹ��
	int task_id;		//����
	bool task_last;		//�Ƿ�Ϊ��󷵻�
};

// �̰߳�ȫ�Ķ���
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//��׼�����
	mutable mutex the_mutex;							//boost������
	condition_variable the_condition_variable;			//boost��������

public:

	//�����µ�����
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				//��ȡ������
		the_queue.push(data);							//������д�������
		lock.unlock();									//�ͷ���
		the_condition_variable.notify_one();			//֪ͨ���������ȴ����߳�
	}

	//�������Ƿ�Ϊ��
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//ȡ��
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//������Ϊ��ʱ
		{
			the_condition_variable.wait(lock);			//�ȴ���������֪ͨ
		}

		Data popped_value = the_queue.front();			//��ȡ�����е����һ������
		the_queue.pop();								//ɾ��������
		return popped_value;							//���ظ�����
	}

};

/// ��python�ֵ��ȡ�ض����ͼ�ֵ�ĺ���
//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getInt(dict d, string key, int* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getLong(dict d, string key, int* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ�ĸ�����������ֵ������ṹ������ֵ��
void getDouble(dict d, string key, double* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ���������ֵ������ṹ������ֵ��
void getString(dict d, string key, char* value);

// ���ֵ���ȡ��ֵ�ĺ���


/// ----------------------------------------------------------------------
/// SPI ��ʵ��
/// ----------------------------------------------------------------------
class MdApi : public XTP::API::QuoteSpi
{
private:
	XTP::API::QuoteApi *api;
	thread *task_thread;		// �����߳�ָ��,boost
	ConcurrentQueue<Task*> task_queue;		// �������

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

	// API �ص����� -- �����������
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


	// �������� -- ������
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

	// �̳�ʵ�ֵĻص����� -- python�̳�ʵ��
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


	// ��������
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