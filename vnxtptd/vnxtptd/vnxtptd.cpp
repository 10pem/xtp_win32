// vnxtptd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnxtptd.h"


// 从pyobj获取数据的函数
void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint64(dict d, string key, uint64_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint32(dict d, string key, uint32_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getInt64(dict d, string key, int64_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getDouble(dict d, string key, double *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<double> x(o);
		if (x.check())
		{
			*value = x();
		}
	}
};

void getString(dict d, string key, char* value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char* buffer = s.c_str();
			strcpy_s(value, strlen(buffer) + 1, buffer);
		}
	}
};


// c++回调函数实现--推入队列
void TdApi::OnDisconnected(uint64_t session_id, int reason)
{
	Task *task = new Task();
	task->task_name = ONDISCONNECTED;

	task->task_session = session_id;
	task->task_id = reason;
	this->task_queue.push(task);
}

void TdApi::OnError(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONERROR;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void TdApi::OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONORDEREVENT;

	if (order_info)
	{
		XTPOrderInfo *task_data = new XTPOrderInfo();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnTradeEvent(XTPTradeReport *trade_info, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONTRADEEVENT;

	if (trade_info)
	{
		XTPTradeReport *task_data = new XTPTradeReport();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONCANCELORDERERROR;

	if (cancel_info)
	{
		XTPOrderCancelInfo *task_data = new XTPOrderCancelInfo();
		*task_data = *cancel_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYORDER;

	if (order_info)
	{
		XTPQueryOrderRsp *task_data = new XTPQueryOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYTRADE;

	if (trade_info)
	{
		XTPQueryTradeRsp *task_data = new XTPQueryTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYPOSITION;

	if (position)
	{
		XTPQueryStkPositionRsp *task_data = new XTPQueryStkPositionRsp();
		*task_data = *position;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYASSET;

	if (asset)
	{
		XTPQueryAssetRsp *task_data = new XTPQueryAssetRsp();
		*task_data = *asset;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYSTRUCTUREDFUND;

	if (fund_info)
	{
		XTPStructuredFundInfo *task_data = new XTPStructuredFundInfo();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYFUNDTRANSFER;

	if (fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONFUNDTRANSFER;

	if (fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryETF(XTPQueryETFBaseRsp *etf_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYETF;

	if (etf_info)
	{
		XTPQueryETFBaseRsp *task_data = new XTPQueryETFBaseRsp();
		*task_data = *etf_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryETFBasket(XTPQueryETFComponentRsp *etf_component_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYETFBASKET;

	if (etf_component_info)
	{
		XTPQueryETFComponentRsp *task_data = new XTPQueryETFComponentRsp();
		*task_data = *etf_component_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryIPOInfoList(XTPQueryIPOTickerRsp *ipo_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYIPOINFOLIST;

	if (ipo_info)
	{
		XTPQueryIPOTickerRsp *task_data = new XTPQueryIPOTickerRsp();
		*task_data = *ipo_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

void TdApi::OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *quota_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task *task = new Task();
	task->task_name = ONQUERYIPOQUOTAINFO;

	if (quota_info)
	{
		XTPQueryIPOQuotaRsp *task_data = new XTPQueryIPOQuotaRsp();
		*task_data = *quota_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

// process函数实现--任务分发
void TdApi::processTask()
{
	while (1)
	{
		Task *task = this->task_queue.wait_and_pop();
		switch (task->task_name)
		{
		case ONDISCONNECTED:
		{
			this->processDisconnected(task);
			break;
		}

		case ONERROR:
		{
			this->processError(task);
			break;
		}

		case ONORDEREVENT:
		{
			this->processOrderEvent(task);
			break;
		}

		case ONTRADEEVENT:
		{
			this->processTradeEvent(task);
			break;
		}

		case ONCANCELORDERERROR:
		{
			this->processCancelOrderError(task);
			break;
		}

		case ONQUERYORDER:
		{
			this->processQueryOrder(task);
			break;
		}

		case ONQUERYTRADE:
		{
			this->processQueryTrade(task);
			break;
		}

		case ONQUERYPOSITION:
		{
			this->processQueryPosition(task);
			break;
		}

		case ONQUERYASSET:
		{
			this->processQueryAsset(task);
			break;
		}

		case ONQUERYSTRUCTUREDFUND:
		{
			this->processQueryStructuredFund(task);
			break;
		}

		case ONQUERYFUNDTRANSFER:
		{
			this->processQueryFundTransfer(task);
			break;
		}

		case ONFUNDTRANSFER:
		{
			this->processFundTransfer(task);
			break;
		}

		case ONQUERYETF:
		{
			this->processQueryETF(task);
			break;
		}

		case ONQUERYETFBASKET:
		{
			this->processQueryETFBasket(task);
			break;
		}

		case ONQUERYIPOINFOLIST:
		{
			this->processQueryIPOInfoList(task);
			break;
		}

		case ONQUERYIPOQUOTAINFO:
		{
			this->processQueryIPOQuotaInfo(task);
			break;
		}


		}
	}
}

void TdApi::processDisconnected(Task *task)
{
	PyLock lock;
	this->onDisconnected(task->task_session, task->task_id);
	delete task;
}

void TdApi::processError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onError(error);
	delete task;
}

void TdApi::processOrderEvent(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPOrderInfo *task_data = (XTPOrderInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["ticker"] = task_data->ticker;
		data["market"] = (int)task_data->market;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["price_type"] = (int)task_data->price_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onOrderEvent(data, error, task->task_session);
	delete task;
}

void TdApi::processTradeEvent(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPTradeReport *task_data = (XTPTradeReport*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["ticker"] = task_data->ticker;
		data["market"] = (int)task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = task_data->exec_id;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = task_data->order_exch_id;
		data["trade_type"] = task_data->trade_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["branch_pbu"] = task_data->branch_pbu;
		delete task->task_data;
	}

	this->onTradeEvent(data, task->task_session);
	delete task;
}

void TdApi::processCancelOrderError(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPOrderCancelInfo *task_data = (XTPOrderCancelInfo*)task->task_data;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onCancelOrderError(data, error, task->task_session);
	delete task;
}

void TdApi::processQueryOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryOrderRsp *task_data = (XTPQueryOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["ticker"] = task_data->ticker;
		data["market"] = (int)task_data->market;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["price_type"] = (int)task_data->price_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = task_data->order_local_id;
		data["order_status"] = (int)task_data->order_status;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["order_type"] = task_data->order_type;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryOrder(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryTradeRsp *task_data = (XTPQueryTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["ticker"] = task_data->ticker;
		data["market"] = (int)task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = task_data->exec_id;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = task_data->order_exch_id;
		data["trade_type"] = task_data->trade_type;
		data["side"] = (int)task_data->side;
		data["business_type"] = (int)task_data->business_type;
		data["branch_pbu"] = task_data->branch_pbu;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryTrade(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*)task->task_data;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["market"] = (int)task_data->market;
		data["total_qty"] = task_data->total_qty;
		data["sellable_qty"] = task_data->sellable_qty;
		data["avg_price"] = task_data->avg_price;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["yesterday_position"] = task_data->yesterday_position;
		data["purchase_redeemable_qty"] = task_data->purchase_redeemable_qty;

		boost::python::list unknown;

		for (int i = 0; i<10; ++i)
		{
			unknown.append(task_data->unknown[i]);
		}
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryPosition(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryAsset(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryAssetRsp *task_data = (XTPQueryAssetRsp*)task->task_data;
		data["total_asset"] = task_data->total_asset;
		data["buying_power"] = task_data->buying_power;
		data["security_asset"] = task_data->security_asset;
		data["fund_buy_amount"] = task_data->fund_buy_amount;
		data["fund_buy_fee"] = task_data->fund_buy_fee;
		data["fund_sell_amount"] = task_data->fund_sell_amount;
		data["fund_sell_fee"] = task_data->fund_sell_fee;
		data["withholding_amount"] = task_data->withholding_amount;
		data["account_type"] = (int)task_data->account_type;

		boost::python::list unknown;

		for (int i = 0; i<10; ++i)
		{
			unknown.append(task_data->unknown[i]);
		}
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryAsset(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryStructuredFund(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPStructuredFundInfo *task_data = (XTPStructuredFundInfo*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["sf_ticker"] = task_data->sf_ticker;
		data["sf_ticker_name"] = task_data->sf_ticker_name;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["split_merge_status"] = (int)task_data->split_merge_status;
		data["ratio"] = task_data->ratio;
		data["min_split_qty"] = task_data->min_split_qty;
		data["min_merge_qty"] = task_data->min_merge_qty;
		data["net_price"] = task_data->net_price;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryStructuredFund(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryFundTransfer(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onFundTransfer(data, error, task->task_session);
	delete task;
}

void TdApi::processQueryETF(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFBaseRsp *task_data = (XTPQueryETFBaseRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["etf"] = task_data->etf;
		data["subscribe_redemption_ticker"] = task_data->subscribe_redemption_ticker;
		data["unit"] = task_data->unit;
		data["subscribe_status"] = task_data->subscribe_status;
		data["redemption_status"] = task_data->redemption_status;
		data["max_cash_ratio"] = task_data->max_cash_ratio;
		data["estimate_amount"] = task_data->estimate_amount;
		data["cash_component"] = task_data->cash_component;
		data["net_value"] = task_data->net_value;
		data["total_amount"] = task_data->total_amount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryETF(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryETFBasket(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFComponentRsp *task_data = (XTPQueryETFComponentRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = task_data->ticker;
		data["component_ticker"] = task_data->component_ticker;
		data["component_name"] = task_data->component_name;
		data["quantity"] = task_data->quantity;
		data["component_market"] = (int)task_data->component_market;
		data["replace_type"] = (int)task_data->replace_type;
		data["premium_ratio"] = task_data->premium_ratio;
		data["amount"] = task_data->amount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryETFBasket(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryIPOInfoList(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOTickerRsp *task_data = (XTPQueryIPOTickerRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["price"] = task_data->price;
		data["unit"] = task_data->unit;
		data["qty_upper_limit"] = task_data->qty_upper_limit;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryIPOInfoList(data, error, task->task_last, task->task_session);
	delete task;
}

void TdApi::processQueryIPOQuotaInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOQuotaRsp *task_data = (XTPQueryIPOQuotaRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task_error;
	}

	this->onQueryIPOQuotaInfo(data, error, task->task_last, task->task_session);
	delete task;
}


// 主动函数实现 -- 调用c++接口的函数
void TdApi::createTraderApi(uint8_t clientid, string path)
{
	this->api->CreateTraderApi(clientid, path.c_str());
	this->api->RegisterSpi(this);
}

int TdApi::exit()
{
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
}

void TdApi::release()
{

	this->api->Release();
}

string TdApi::getTradingDay()
{
	string i = this->api->GetTradingDay();
	return i;
}


dict TdApi::getApiLastError()
{	
	dict error;
	XTPRI* i = this->api->GetApiLastError();
	error["error_id"] = i->error_id;
	error["error_msg"] = i->error_msg;
	return error;
}

string TdApi::getApiVersion()
{
	string i = this->api->GetApiVersion();
	return i;
}

uint8_t TdApi::getClientIDByXTPID(uint64_t order_xtp_id)
{
	uint8_t i = this->api->GetClientIDByXTPID(order_xtp_id);
	return i;
}

string TdApi::getAccountByXTPID(uint64_t order_xtp_id)
{
	string i = this->api->GetAccountByXTPID(order_xtp_id);
	return i;
}

void TdApi::subscribePublicTopic(int resume_type)
{

	this->api->SubscribePublicTopic((XTP_TE_RESUME_TYPE)resume_type);
}

void TdApi::setSoftwareVersion(string version)
{

	this->api->SetSoftwareVersion(version.c_str());
}

void TdApi::setSoftwareKey(string key)
{

	this->api->SetSoftwareKey(key.c_str());
}

void TdApi::setHeartBeatInterval(uint32_t interval)
{

	this->api->SetHeartBeatInterval(interval);
}

uint64_t TdApi::login(string ip, int port, string user, string password, int sock_type)
{
	uint64_t i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)sock_type);
	return i;
}

int TdApi::logout(uint64_t session_id)
{
	int i = this->api->Logout(session_id);
	return i;
}

uint64_t TdApi::insertOrder(dict data, uint64_t session_id)
{
	XTPOrderInsertInfo myreq = XTPOrderInsertInfo();
	memset(&myreq, 0, sizeof(myreq));

	getUint64(data, "order_xtp_id", &myreq.order_xtp_id);
	getUint32(data, "order_client_id", &myreq.order_client_id);
	getString(data, "ticker", myreq.ticker);
	int market;
	getInt(data, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;

	getDouble(data, "price", &myreq.price);
	getDouble(data, "stop_price", &myreq.stop_price);
	getInt64(data, "quantity", &myreq.quantity);
	int price_type;
	getInt(data, "price_type", &price_type);
	myreq.price_type = (XTP_PRICE_TYPE)price_type;

	int side;
	getInt(data, "side", &side);
	myreq.side = (XTP_SIDE_TYPE)side;

	int business_type;
	getInt(data, "business_type", &business_type);
	myreq.business_type = (XTP_BUSINESS_TYPE)business_type;

	uint64_t i = this->api->InsertOrder(&myreq, session_id);
	return i;
}

uint64_t TdApi::cancelOrder(uint64_t order_xtp_id, uint64_t session_id)
{
	uint64_t i = this->api->CancelOrder(order_xtp_id, session_id);
	return i;
}

int TdApi::queryOrderByXTPID(uint64_t order_xtp_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryOrderByXTPID(order_xtp_id, session_id, request_id);
	return i;
}

int TdApi::queryOrders(dict data, uint64_t session_id, int request_id)
{
	XTPQueryOrderReq myreq = XTPQueryOrderReq();
	memset(&myreq, 0, sizeof(myreq));

	getString(data, "ticker", myreq.ticker);
	getInt64(data, "begin_time", &myreq.begin_time);
	getInt64(data, "end_time", &myreq.end_time);
	int i = this->api->QueryOrders(&myreq, session_id, request_id);
	return i;
}

int TdApi::queryTradesByXTPID(uint64_t order_xtp_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryTradesByXTPID(order_xtp_id, session_id, request_id);
	return i;
}

int TdApi::queryTrades(dict data, uint64_t session_id, int request_id)
{
	XTPQueryTraderReq myreq = XTPQueryTraderReq();
	memset(&myreq, 0, sizeof(myreq));

	getString(data, "ticker", myreq.ticker);
	getInt64(data, "begin_time", &myreq.begin_time);
	getInt64(data, "end_time", &myreq.end_time);
	int i = this->api->QueryTrades(&myreq, session_id, request_id);
	return i;
}

int TdApi::queryPosition(string ticker, uint64_t session_id, int request_id)
{
	int i = this->api->QueryPosition(ticker.c_str(), session_id, request_id);
	return i;
}

int TdApi::queryAsset(uint64_t session_id, int request_id)
{
	int i = this->api->QueryAsset(session_id, request_id);
	return i;
}

int TdApi::queryStructuredFund(dict data, uint64_t session_id, int request_id)
{
	XTPQueryStructuredFundInfoReq myreq = XTPQueryStructuredFundInfoReq();
	memset(&myreq, 0, sizeof(myreq));

	int exchange_id;
	getInt(data, "exchange_id", &exchange_id);
	myreq.exchange_id = (XTP_EXCHANGE_TYPE)exchange_id;

	getString(data, "sf_ticker", myreq.sf_ticker);
	int i = this->api->QueryStructuredFund(&myreq, session_id, request_id);
	return i;
}

uint64_t TdApi::fundTransfer(dict data, uint64_t session_id)
{
	XTPFundTransferReq myreq = XTPFundTransferReq();
	memset(&myreq, 0, sizeof(myreq));

	getUint64(data, "serial_id", &myreq.serial_id);
	getString(data, "fund_account", myreq.fund_account);
	getString(data, "passward", myreq.password);
	getDouble(data, "amount", &myreq.amount);
	int transfer_type;
	getInt(data, "transfer_type", &transfer_type);
	myreq.transfer_type = (XTP_FUND_TRANSFER_TYPE)transfer_type;

	uint64_t i = this->api->FundTransfer(&myreq, session_id);
	return i;
}

int TdApi::queryFundTransfer(dict data, uint64_t session_id, int request_id)
{
	XTPQueryFundTransferLogReq myreq = XTPQueryFundTransferLogReq();
	memset(&myreq, 0, sizeof(myreq));

	getUint64(data, "serial_id", &myreq.serial_id);
	int i = this->api->QueryFundTransfer(&myreq, session_id, request_id);
	return i;
}

int TdApi::queryETF(dict data, uint64_t session_id, int request_id)
{
	XTPQueryETFBaseReq myreq = XTPQueryETFBaseReq();
	memset(&myreq, 0, sizeof(myreq));

	int market;
	getInt(data, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;

	getString(data, "ticker", myreq.ticker);
	int i = this->api->QueryETF(&myreq, session_id, request_id);
	return i;
}

int TdApi::queryETFTickerBasket(dict data, uint64_t session_id, int request_id)
{
	XTPQueryETFComponentReq myreq = XTPQueryETFComponentReq();
	memset(&myreq, 0, sizeof(myreq));

	int market;
	getInt(data, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;

	getString(data, "ticker", myreq.ticker);
	int i = this->api->QueryETFTickerBasket(&myreq, session_id, request_id);
	return i;
}

int TdApi::queryIPOInfoList(uint64_t session_id, int request_id)
{
	int i = this->api->QueryIPOInfoList(session_id, request_id);
	return i;
}

int TdApi::queryIPOQuotaInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryIPOQuotaInfo(session_id, request_id);
	return i;
}



// wrapper类
struct TdApiWrap : TdApi, wrapper<TdApi>
{
	virtual void onDisconnected(uint64_t session_id, int reason)
	{
		try
		{
			this->get_override("onDisconnected")(session_id, reason);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onError(dict error)
	{
		try
		{
			this->get_override("onError")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onOrderEvent(dict data, dict error, uint64_t session_id)
	{
		try
		{
			this->get_override("onOrderEvent")(data, error, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onTradeEvent(dict data, uint64_t session_id)
	{
		try
		{
			this->get_override("onTradeEvent")(data, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onCancelOrderError(dict data, dict error, uint64_t session_id)
	{
		try
		{
			this->get_override("onCancelOrderError")(data, error, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryOrder(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryOrder")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryTrade(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryTrade")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryPosition(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryPosition")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryAsset(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryAsset")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryStructuredFund(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryStructuredFund")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryFundTransfer(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryFundTransfer")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onFundTransfer(dict data, dict error, uint64_t session_id)
	{
		try
		{
			this->get_override("onFundTransfer")(data, error, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryETF(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryETF")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryETFBasket(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryETFBasket")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryIPOInfoList(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryIPOInfoList")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryIPOQuotaInfo(dict data, dict error, bool last, uint64_t session_id)
	{
		try
		{
			this->get_override("onQueryIPOQuotaInfo")(data, error, last, session_id);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}


};

// boost
BOOST_PYTHON_MODULE(vnxtptd)
{
	PyEval_InitThreads();		// 创建GIL锁

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("onDisconnected", pure_virtual(&TdApiWrap::onDisconnected))
		.def("onError", pure_virtual(&TdApiWrap::onError))
		.def("onOrderEvent", pure_virtual(&TdApiWrap::onOrderEvent))
		.def("onTradeEvent", pure_virtual(&TdApiWrap::onTradeEvent))
		.def("onCancelOrderError", pure_virtual(&TdApiWrap::onCancelOrderError))
		.def("onQueryOrder", pure_virtual(&TdApiWrap::onQueryOrder))
		.def("onQueryTrade", pure_virtual(&TdApiWrap::onQueryTrade))
		.def("onQueryPosition", pure_virtual(&TdApiWrap::onQueryPosition))
		.def("onQueryAsset", pure_virtual(&TdApiWrap::onQueryAsset))
		.def("onQueryStructuredFund", pure_virtual(&TdApiWrap::onQueryStructuredFund))
		.def("onQueryFundTransfer", pure_virtual(&TdApiWrap::onQueryFundTransfer))
		.def("onFundTransfer", pure_virtual(&TdApiWrap::onFundTransfer))
		.def("onQueryETF", pure_virtual(&TdApiWrap::onQueryETF))
		.def("onQueryETFBasket", pure_virtual(&TdApiWrap::onQueryETFBasket))
		.def("onQueryIPOInfoList", pure_virtual(&TdApiWrap::onQueryIPOInfoList))
		.def("onQueryIPOQuotaInfo", pure_virtual(&TdApiWrap::onQueryIPOQuotaInfo))

		.def("release", &TdApiWrap::release)
		.def("getTradingDay", &TdApiWrap::getTradingDay)
		.def("getApiLastError", &TdApiWrap::getApiLastError)
		.def("getApiVersion", &TdApiWrap::getApiVersion)
		.def("getClientIDByXTPID", &TdApiWrap::getClientIDByXTPID)
		.def("getAccountByXTPID", &TdApiWrap::getAccountByXTPID)
		.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
		.def("setSoftwareVersion", &TdApiWrap::setSoftwareVersion)
		.def("setSoftwareKey", &TdApiWrap::setSoftwareKey)
		.def("setHeartBeatInterval", &TdApiWrap::setHeartBeatInterval)
		.def("login", &TdApiWrap::login)
		.def("logout", &TdApiWrap::logout)
		.def("insertOrder", &TdApiWrap::insertOrder)
		.def("cancelOrder", &TdApiWrap::cancelOrder)
		.def("queryOrderByXTPID", &TdApiWrap::queryOrderByXTPID)
		.def("queryOrders", &TdApiWrap::queryOrders)
		.def("queryTradesByXTPID", &TdApiWrap::queryTradesByXTPID)
		.def("queryTrades", &TdApiWrap::queryTrades)
		.def("queryPosition", &TdApiWrap::queryPosition)
		.def("queryAsset", &TdApiWrap::queryAsset)
		.def("queryStructuredFund", &TdApiWrap::queryStructuredFund)
		.def("fundTransfer", &TdApiWrap::fundTransfer)
		.def("queryFundTransfer", &TdApiWrap::queryFundTransfer)
		.def("queryETF", &TdApiWrap::queryETF)
		.def("queryETFTickerBasket", &TdApiWrap::queryETFTickerBasket)
		.def("queryIPOInfoList", &TdApiWrap::queryIPOInfoList)
		.def("queryIPOQuotaInfo", &TdApiWrap::queryIPOQuotaInfo)
		;
};

