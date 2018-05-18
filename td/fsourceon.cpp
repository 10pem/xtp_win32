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

	if(error_info)
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

	if(order_info)
	{
		XTPOrderInfo *task_data = new XTPOrderInfo();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(trade_info)
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

	if(cancel_info)
	{
		XTPOrderCancelInfo *task_data = new XTPOrderCancelInfo();
		*task_data = *cancel_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(order_info)
	{
		XTPQueryOrderRsp *task_data = new XTPQueryOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(trade_info)
	{
		XTPQueryTradeRsp *task_data = new XTPQueryTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(position)
	{
		XTPQueryStkPositionRsp *task_data = new XTPQueryStkPositionRsp();
		*task_data = *position;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(asset)
	{
		XTPQueryAssetRsp *task_data = new XTPQueryAssetRsp();
		*task_data = *asset;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(fund_info)
	{
		XTPStructuredFundInfo *task_data = new XTPStructuredFundInfo();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(etf_info)
	{
		XTPQueryETFBaseRsp *task_data = new XTPQueryETFBaseRsp();
		*task_data = *etf_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(etf_component_info)
	{
		XTPQueryETFComponentRsp *task_data = new XTPQueryETFComponentRsp();
		*task_data = *etf_component_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(ipo_info)
	{
		XTPQueryIPOTickerRsp *task_data = new XTPQueryIPOTickerRsp();
		*task_data = *ipo_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(quota_info)
	{
		XTPQueryIPOQuotaRsp *task_data = new XTPQueryIPOQuotaRsp();
		*task_data = *quota_info;
		task->task_data = task_data;
	}

	if(error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	task->task_session = session_id;
	this->task_queue.push(task);
}

