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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPOrderInfo *task_data = (XTPOrderInfo*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPTradeReport *task_data = (XTPTradeReport*) task->task_data;
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
		XTPOrderCancelInfo *task_data = (XTPOrderCancelInfo*) task->task_data;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryOrderRsp *task_data = (XTPQueryOrderRsp*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryTradeRsp *task_data = (XTPQueryTradeRsp*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*) task->task_data;
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

		for(int i=0; i<10; ++i)
		{
			unknown.append(task_data->unknown[i]);
		}
		data["unknown"] = unknown;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryAssetRsp *task_data = (XTPQueryAssetRsp*) task->task_data;
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

		for(int i=0; i<10; ++i)
		{
			unknown.append(task_data->unknown[i]);
		}
		data["unknown"] = unknown;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPStructuredFundInfo *task_data = (XTPStructuredFundInfo*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryETFBaseRsp *task_data = (XTPQueryETFBaseRsp*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryETFComponentRsp *task_data = (XTPQueryETFComponentRsp*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryIPOTickerRsp *task_data = (XTPQueryIPOTickerRsp*) task->task_data;
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
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
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
		XTPQueryIPOQuotaRsp *task_data = (XTPQueryIPOQuotaRsp*) task->task_data;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*) task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryIPOQuotaInfo(data, error, task->task_last, task->task_session);
	delete task;
}

