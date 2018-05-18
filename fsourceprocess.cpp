void MdApi::processDisconnected(Task *task)
{
	PyLock lock;
	this->onDisconnected(task->task_id);
	delete task;
}

void MdApi::processError(Task *task)
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

void MdApi::processSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onSubMarketData(data, error, task->task_last);
	delete task;
}

void MdApi::processUnSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onUnSubMarketData(data, error, task->task_last);
	delete task;
}

void MdApi::processDepthMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPMD *task_data = (XTPMD*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["last_price"] = task_data->last_price;
		data["pre_close_price"] = task_data->pre_close_price;
		data["open_price"] = task_data->open_price;
		data["high_price"] = task_data->high_price;
		data["low_price"] = task_data->low_price;
		data["close_price"] = task_data->close_price;
		data["pre_open_interest"] = task_data->pre_open_interest;
		data["open_interest"] = task_data->open_interest;
		data["pre_settlement_price"] = task_data->pre_settlement_price;
		data["settlement_price"] = task_data->settlement_price;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["pre_delta"] = task_data->pre_delta;
		data["curr_delta"] = task_data->curr_delta;
		data["data_time"] = task_data->data_time;
		data["qty"] = task_data->qty;
		data["turnover"] = task_data->turnover;
		data["avg_price"] = task_data->avg_price;
		data["trades_count"] = task_data->trades_count;
		data["ticker_status"] = task_data->ticker_status;
		data["total_bid_qty"] = task_data->total_bid_qty;
		data["total_ask_qty"] = task_data->total_ask_qty;
		data["ma_bid_price"] = task_data->ma_bid_price;
		data["ma_ask_price"] = task_data->ma_ask_price;
		data["ma_bond_bid_price"] = task_data->ma_bond_bid_price;
		data["ma_bond_ask_price"] = task_data->ma_bond_ask_price;
		data["yield_to_maturity"] = task_data->yield_to_maturity;
		data["iopv"] = task_data->iopv;
		data["etf_buy_count"] = task_data->etf_buy_count;
		data["etf_sell_count"] = task_data->etf_sell_count;
		data["etf_buy_qty"] = task_data->etf_buy_qty;
		data["etf_buy_money"] = task_data->etf_buy_money;
		data["etf_sell_qty"] = task_data->etf_sell_qty;
		data["etf_sell_money"] = task_data->etf_sell_money;
		data["total_warrant_exec_qty"] = task_data->total_warrant_exec_qty;
		data["warrant_lower_price"] = task_data->warrant_lower_price;
		data["warrant_upper_price"] = task_data->warrant_upper_price;
		data["cancel_buy_count"] = task_data->cancel_buy_count;
		data["cancel_sell_count"] = task_data->cancel_sell_count;
		data["cancel_buy_qty"] = task_data->cancel_buy_qty;
		data["cancel_sell_qty"] = task_data->cancel_sell_qty;
		data["cancel_buy_money"] = task_data->cancel_buy_money;
		data["cancel_sell_money"] = task_data->cancel_sell_money;
		data["total_buy_count"] = task_data->total_buy_count;
		data["total_sell_count"] = task_data->total_sell_count;
		data["duration_after_buy"] = task_data->duration_after_buy;
		data["duration_after_sell"] = task_data->duration_after_sell;
		data["num_bid_orders"] = task_data->num_bid_orders;
		data["num_ask_orders"] = task_data->num_ask_orders;
		data["exec_time"] = task_data->exec_time;
		data["is_market_closed"] = task_data->is_market_closed;
		data["total_position"] = task_data->total_position;
		data["pe_ratio1"] = task_data->pe_ratio1;
		data["pe_ratio2"] = task_data->pe_ratio2;

		boost::python::list bid;
		boost::python::list ask;
		boost::python::list bid_qty;
		boost::python::list ask_qty;

		for(int i=0; i<10; ++i)
		{
			bid.append(task_data->bid[i]);
			ask.append(task_data->ask[i]);
			bid_qty.append(task_data->bid_qty[i]);
			ask_qty.append(task_data->ask_qty[i]);
		}
		data["bid"] = bid;
		data["ask"] = ask;
		data["bid_qty"] = bid_qty;
		data["ask_qty"] = ask_qty;
		delete task->task_data;
	}

	this->onDepthMarketData(data);
	delete task;
}

void MdApi::processSubOrderBook(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onSubOrderBook(data, error, task->task_last);
	delete task;
}

void MdApi::processUnSubOrderBook(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onUnSubOrderBook(data, error, task->task_last);
	delete task;
}

void MdApi::processOrderBook(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPOB *task_data = (XTPOB*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["last_price"] = task_data->last_price;
		data["qty"] = task_data->qty;
		data["turnover"] = task_data->turnover;
		data["trades_count"] = task_data->trades_count;
		data["data_time"] = task_data->data_time;

		boost::python::list bid;
		boost::python::list ask;
		boost::python::list bid_qty;
		boost::python::list ask_qty;

		for(int i=0; i<10; ++i)
		{
			bid.append(task_data->bid[i]);
			ask.append(task_data->ask[i]);
			bid_qty.append(task_data->bid_qty[i]);
			ask_qty.append(task_data->ask_qty[i]);
		}
		data["bid"] = bid;
		data["ask"] = ask;
		data["bid_qty"] = bid_qty;
		data["ask_qty"] = ask_qty;
		delete task->task_data;
	}

	this->onOrderBook(data);
	delete task;
}

void MdApi::processSubTickByTick(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onSubTickByTick(data, error, task->task_last);
	delete task;
}

void MdApi::processUnSubTickByTick(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onUnSubTickByTick(data, error, task->task_last);
	delete task;
}

void MdApi::processTickByTick(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPTBT *task_data = (XTPTBT*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["seq"] = task_data->seq;
		data["data_time"] = task_data->data_time;
		data["type"] = (int) task_data->type;
		delete task->task_data;
	}

	this->onTickByTick(data);
	delete task;
}

void MdApi::processSubscribeAllMarketData(Task *task)
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

	this->onSubscribeAllMarketData(error);
	delete task;
}

void MdApi::processUnSubscribeAllMarketData(Task *task)
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

	this->onUnSubscribeAllMarketData(error);
	delete task;
}

void MdApi::processSubscribeAllOrderBook(Task *task)
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

	this->onSubscribeAllOrderBook(error);
	delete task;
}

void MdApi::processUnSubscribeAllOrderBook(Task *task)
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

	this->onUnSubscribeAllOrderBook(error);
	delete task;
}

void MdApi::processSubscribeAllTickByTick(Task *task)
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

	this->onSubscribeAllTickByTick(error);
	delete task;
}

void MdApi::processUnSubscribeAllTickByTick(Task *task)
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

	this->onUnSubscribeAllTickByTick(error);
	delete task;
}

void MdApi::processQueryAllTickers(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQSI *task_data = (XTPQSI*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["ticker_type"] = (int) task_data->ticker_type;
		data["pre_close_price"] = task_data->pre_close_price;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["price_tick"] = task_data->price_tick;
		data["buy_qty_unit"] = task_data->buy_qty_unit;
		data["sell_qty_unit"] = task_data->sell_qty_unit;
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

	this->onQueryAllTickers(data, error, task->task_last);
	delete task;
}

void MdApi::processQueryTickersPriceInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPTPI *task_data = (XTPTPI*) task->task_data;
		data["exchange_id"] = (int) task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["last_price"] = task_data->last_price;
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

	this->onQueryTickersPriceInfo(data, error, task->task_last);
	delete task;
}

