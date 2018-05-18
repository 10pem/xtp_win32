// API
#include "xtp_trader_api.h"

// ϵͳ
#ifdef WIN32
#include "stdafx.h"
#endif
#include <string>
#include <queue>
#include <vector>

// BOOST
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python��װ
#include <boost/python/def.hpp>		//python��װ
#include <boost/python/dict.hpp>	//python��װ
#include <boost/python/list.hpp>	//python��װ
#include <boost/python/object.hpp>	//python��װ
#include <boost/python.hpp>			//python��װ
#include <boost/thread.hpp>			//������е��̹߳���
#include <boost/bind.hpp>			//������е��̹߳���

// �����ռ�
using namespace std;
using namespace boost::python;
using namespace boost;

// ����
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

// API�еĲ������
/// GILȫ����
class PyLock
{
public:
	// ��ȡGIL
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}
	// ���������ͷ�ȫ����
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}

private:
	PyGILState_STATE gil_state;
};

/// ����ṹ��
struct Task
{
	int task_name;		// �ص�������Ӧ�ĳ���
	void *task_data;	// ���ݽṹ��
	void *task_error;	// ����ṹ��
	int task_id;		// ����id
	bool task_last;		// �Ƿ�Ϊ����
	uint64_t task_session;		// �Ự��
};

/// �̰߳�ȫ�Ķ���
template<typename Data>
class ConcurrentQueue
{
private:
	queue<Data> the_queue;		// ����
	mutable mutex the_mutex;	// boost������
	condition_variable the_condition_variable;	// ֪ͨ
public:
	// �����µ�����
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);		// �����
		the_queue.push(data);
		lock.unlock();
		the_condition_variable.notify_one();
	}

	// �������Ƿ�Ϊ��
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);		// �����
		return the_queue.empty();
	}

	// ȡ������
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);
		while (the_queue.empty())
		{
			the_condition_variable.wait(lock);	// �����̵߳ȴ�
		}

		Data popped_value = the_queue.front();	// ��ȡ�����еĵ�һ��
		the_queue.pop();
		return popped_value;
	}
};

/// ��pyobj��ȡ���ݵĺ���
void getInt(dict d, string key, int* value);
void getDouble(dict d, string key, double* value);
void getStr(dict d, string key, char* value);


// TdApi
class TdApi : public XTP::API::TraderSpi
{
private:
	XTP::API::TraderApi* api;		// API��������
	thread *task_thread;			// �����߳�ָ��, ָ������Process��ָ��
	ConcurrentQueue<Task*> task_queue; // �������, �����е�������Task*

public:
	/// ���캯��
	TdApi()
	{
		function0<void> f = boost::bind(&TdApi::processTask, this);
		thread t(f);	// ��һ���߳����� processTask
		this->task_thread = &t;
	}

	/// ��������
	~TdApi()
	{

	}

	/// SPI �ص���������
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

	/// process����
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

	/// python�ص���������
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


	/// ������������
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

