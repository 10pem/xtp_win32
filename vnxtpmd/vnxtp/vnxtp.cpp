// vnxtp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnxtp.h"

/// 从python的字典获取特定类型的键值的函数
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

void getLong(dict d, string key, long *value)
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

void getString(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
			strcpy_s(value, strlen(buffer) + 1, buffer);
		}
	}
};

/// c++回调函数
void MdApi::OnDisconnected(int reason)
{
	Task *task = new Task();
	task->task_name = ONDISCONNECTED;

	task->task_id = reason;
	this->task_queue.push(task);
}

void MdApi::OnError(XTPRI *error_info)
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

void MdApi::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONSUBMARKETDATA;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONUNSUBMARKETDATA;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
{
	Task *task = new Task();
	task->task_name = ONDEPTHMARKETDATA;

	if (market_data)
	{
		XTPMD *task_data = new XTPMD();
		*task_data = *market_data;
		task->task_data = task_data;
	}

	this->task_queue.push(task);
}

void MdApi::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONSUBORDERBOOK;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONUNSUBORDERBOOK;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnOrderBook(XTPOB *order_book)
{
	Task *task = new Task();
	task->task_name = ONORDERBOOK;

	if (order_book)
	{
		XTPOB *task_data = new XTPOB();
		*task_data = *order_book;
		task->task_data = task_data;
	}

	this->task_queue.push(task);
}

void MdApi::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONSUBTICKBYTICK;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONUNSUBTICKBYTICK;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnTickByTick(XTPTBT *tbt_data)
{
	Task *task = new Task();
	task->task_name = ONTICKBYTICK;

	if (tbt_data)
	{
		XTPTBT *task_data = new XTPTBT();
		*task_data = *tbt_data;
		task->task_data = task_data;
	}

	this->task_queue.push(task);
}

void MdApi::OnSubscribeAllMarketData(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONSUBSCRIBEALLMARKETDATA;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void MdApi::OnUnSubscribeAllMarketData(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONUNSUBSCRIBEALLMARKETDATA;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void MdApi::OnSubscribeAllOrderBook(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONSUBSCRIBEALLORDERBOOK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void MdApi::OnUnSubscribeAllOrderBook(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONUNSUBSCRIBEALLORDERBOOK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void MdApi::OnSubscribeAllTickByTick(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONSUBSCRIBEALLTICKBYTICK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void MdApi::OnUnSubscribeAllTickByTick(XTPRI *error_info)
{
	Task *task = new Task();
	task->task_name = ONUNSUBSCRIBEALLTICKBYTICK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void MdApi::OnQueryAllTickers(XTPQSI *ticker_info, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONQUERYALLTICKERS;

	if (ticker_info)
	{
		XTPQSI *task_data = new XTPQSI();
		*task_data = *ticker_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

void MdApi::OnQueryTickersPriceInfo(XTPTPI *ticker_info, XTPRI *error_info, bool is_last)
{
	Task *task = new Task();
	task->task_name = ONQUERYTICKERSPRICEINFO;

	if (ticker_info)
	{
		XTPTPI *task_data = new XTPTPI();
		*task_data = *ticker_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}


/// 任务处理函数
void MdApi::processTask()
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

			case ONSUBMARKETDATA:
			{
				this->processSubMarketData(task);
				break;
			}

			case ONUNSUBMARKETDATA:
			{
				this->processUnSubMarketData(task);
				break;
			}

			case ONDEPTHMARKETDATA:
			{
				this->processDepthMarketData(task);
				break;
			}

			case ONSUBORDERBOOK:
			{
				this->processSubOrderBook(task);
				break;
			}

			case ONUNSUBORDERBOOK:
			{
				this->processUnSubOrderBook(task);
				break;
			}

			case ONORDERBOOK:
			{
				this->processOrderBook(task);
				break;
			}

			case ONSUBTICKBYTICK:
			{
				this->processSubTickByTick(task);
				break;
			}

			case ONUNSUBTICKBYTICK:
			{
				this->processUnSubTickByTick(task);
				break;
			}

			case ONTICKBYTICK:
			{
				this->processTickByTick(task);
				break;
			}

			case ONSUBSCRIBEALLMARKETDATA:
			{
				this->processSubscribeAllMarketData(task);
				break;
			}

			case ONUNSUBSCRIBEALLMARKETDATA:
			{
				this->processUnSubscribeAllMarketData(task);
				break;
			}

			case ONSUBSCRIBEALLORDERBOOK:
			{
				this->processSubscribeAllOrderBook(task);
				break;
			}

			case ONUNSUBSCRIBEALLORDERBOOK:
			{
				this->processUnSubscribeAllOrderBook(task);
				break;
			}

			case ONSUBSCRIBEALLTICKBYTICK:
			{
				this->processSubscribeAllTickByTick(task);
				break;
			}

			case ONUNSUBSCRIBEALLTICKBYTICK:
			{
				this->processUnSubscribeAllTickByTick(task);
				break;
			}

			case ONQUERYALLTICKERS:
			{
				this->processQueryAllTickers(task);
				break;
			}

			case ONQUERYTICKERSPRICEINFO:
			{
				this->processQueryTickersPriceInfo(task);
				break;
			}


		};
	}
};

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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPMD *task_data = (XTPMD*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
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

		for (int i = 0; i<10; ++i)
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
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPOB *task_data = (XTPOB*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
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

		for (int i = 0; i<10; ++i)
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
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPTBT *task_data = (XTPTBT*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["seq"] = task_data->seq;
		data["data_time"] = task_data->data_time;
		data["type"] = (int)task_data->type;
		delete task->task_data;
		
		if (task_data->type == XTP_TBT_ENTRUST)
		{
			data["channel_no"] = task_data->entrust.channel_no;
			data["seq"] = task_data->entrust.seq;
			data["price"] = task_data->entrust.price;
			data["qty"] = task_data->entrust.qty;
			data["side"] = task_data->entrust.side;
			data["ord_type"] = task_data->entrust.ord_type;
		}
		else
		{
			data["channel_no"] = task_data->trade.channel_no;
			data["seq"] = task_data->trade.seq;
			data["price"] = task_data->trade.price;
			data["qty"] = task_data->trade.qty;
			data["money"] = task_data->trade.money;
			data["bid_no"] = task_data->trade.bid_no;
			data["ask_no"] = task_data->trade.ask_no;
			data["trade_flag"] = task_data->trade.trade_flag;
		}
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPQSI *task_data = (XTPQSI*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["ticker_type"] = (int)task_data->ticker_type;
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
		XTPRI *task_error = (XTPRI*)task->task_error;
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
		XTPTPI *task_data = (XTPTPI*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["last_price"] = task_data->last_price;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryTickersPriceInfo(data, error, task->task_last);
	delete task;
}





/// 主动函数
int MdApi::exit()
{
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;

	return 1;
}

void MdApi::createQuoteApi(int client_id, string path)
{
	this->api = XTP::API::QuoteApi::CreateQuoteApi(client_id, path.c_str());
	this->api->RegisterSpi(this);
}

void MdApi::release()
{
	this->api->Release();
}

string MdApi::getTradingDay()
{
	string i = this->api->GetTradingDay();
	return i;
}

string MdApi::getApiVersion()
{
	string i = this->api->GetApiVersion();
	return i;
}

dict MdApi::getApiLastError()
{
	dict data;
	XTPRI *error = this->api->GetApiLastError();
	data["error_id"] = error->error_id;
	data["error_msg"] = error->error_msg;
	return data;
}

void MdApi::setUDPBufferSize(int buff_size)
{
	this->api->SetUDPBufferSize(buff_size);
}


void MdApi::setHeartBeatInterval(int interval)
{
	this->api->SetHeartBeatInterval(interval);
}

int MdApi::subscribeMarketData(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::unSubscribeMarketData(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->UnSubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::subscribeOrderBook(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->SubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::unSubscribeOrderBook(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->UnSubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::subscribeTickByTick(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->SubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::unSubscribeTickByTick(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->UnSubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::subscribeAllMarketData()
{
	int i = this->api->SubscribeAllMarketData();
	return i;
}

int MdApi::unSubscribeAllMarketData()
{
	int i = this->api->UnSubscribeAllMarketData();
	return i;
}

int MdApi::subscribeAllOrderBook()
{
	int i = this->api->SubscribeAllOrderBook();
	return i;
}

int MdApi::unSubscribeAllOrderBook()
{
	int i = this->api->UnSubscribeAllOrderBook();
	return i;
}

int MdApi::subscribeAllTickByTick()
{
	int i = this->api->SubscribeAllTickByTick();
	return i;
}

int MdApi::unSubscribeAllTickByTick()
{
	int i = this->api->UnSubscribeAllTickByTick();
	return i;
}

int MdApi::login(string ip, int port, string user, string password, int sock_type)
{
	int i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)sock_type);
	return i;
}

int MdApi::logout()
{
	int i = this->api->Logout();
	return i;
}

int MdApi::queryAllTickers(int exchage_id)
{
	int i = this->api->QueryAllTickers((XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::queryTickersPriceInfo(string ticker, int exchage_id)
{
	char *buffer = (char*)ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->QueryTickersPriceInfo(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::queryAllTickersPriceInfo()
{
	int i = this->api->QueryAllTickersPriceInfo();
	return i;
}



/// boost封装
struct MdApiWrap : MdApi, wrapper <MdApi>
{
	virtual void onDisconnected(int reason)
	{
		try
		{
			this->get_override("onDisconnected")(reason);
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

	virtual void onSubMarketData(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onSubMarketData")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onUnSubMarketData(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onUnSubMarketData")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onDepthMarketData(dict data)
	{
		try
		{
			this->get_override("onDepthMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onSubOrderBook(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onSubOrderBook")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onUnSubOrderBook(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onUnSubOrderBook")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onOrderBook(dict data)
	{
		try
		{
			this->get_override("onOrderBook")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onSubTickByTick(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onSubTickByTick")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onUnSubTickByTick(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onUnSubTickByTick")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onTickByTick(dict data)
	{
		try
		{
			this->get_override("onTickByTick")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onSubscribeAllMarketData(dict error)
	{
		try
		{
			this->get_override("onSubscribeAllMarketData")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onUnSubscribeAllMarketData(dict error)
	{
		try
		{
			this->get_override("onUnSubscribeAllMarketData")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onSubscribeAllOrderBook(dict error)
	{
		try
		{
			this->get_override("onSubscribeAllOrderBook")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onUnSubscribeAllOrderBook(dict error)
	{
		try
		{
			this->get_override("onUnSubscribeAllOrderBook")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onSubscribeAllTickByTick(dict error)
	{
		try
		{
			this->get_override("onSubscribeAllTickByTick")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onUnSubscribeAllTickByTick(dict error)
	{
		try
		{
			this->get_override("onUnSubscribeAllTickByTick")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryAllTickers(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onQueryAllTickers")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}

	virtual void onQueryTickersPriceInfo(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onQueryTickersPriceInfo")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	}


};


BOOST_PYTHON_MODULE(vnxtpmd)
{
	PyEval_InitThreads();	// 先创建GIL锁

	class_<MdApiWrap, boost::noncopyable>("MdApi")
		.def("onDisconnected", pure_virtual(&MdApiWrap::onDisconnected))
		.def("onError", pure_virtual(&MdApiWrap::onError))
		.def("onSubMarketData", pure_virtual(&MdApiWrap::onSubMarketData))
		.def("onUnSubMarketData", pure_virtual(&MdApiWrap::onUnSubMarketData))
		.def("onDepthMarketData", pure_virtual(&MdApiWrap::onDepthMarketData))
		.def("onSubOrderBook", pure_virtual(&MdApiWrap::onSubOrderBook))
		.def("onUnSubOrderBook", pure_virtual(&MdApiWrap::onUnSubOrderBook))
		.def("onOrderBook", pure_virtual(&MdApiWrap::onOrderBook))
		.def("onSubTickByTick", pure_virtual(&MdApiWrap::onSubTickByTick))
		.def("onUnSubTickByTick", pure_virtual(&MdApiWrap::onUnSubTickByTick))
		.def("onTickByTick", pure_virtual(&MdApiWrap::onTickByTick))
		.def("onSubscribeAllMarketData", pure_virtual(&MdApiWrap::onSubscribeAllMarketData))
		.def("onUnSubscribeAllMarketData", pure_virtual(&MdApiWrap::onUnSubscribeAllMarketData))
		.def("onSubscribeAllOrderBook", pure_virtual(&MdApiWrap::onSubscribeAllOrderBook))
		.def("onUnSubscribeAllOrderBook", pure_virtual(&MdApiWrap::onUnSubscribeAllOrderBook))
		.def("onSubscribeAllTickByTick", pure_virtual(&MdApiWrap::onSubscribeAllTickByTick))
		.def("onUnSubscribeAllTickByTick", pure_virtual(&MdApiWrap::onUnSubscribeAllTickByTick))
		.def("onQueryAllTickers", pure_virtual(&MdApiWrap::onQueryAllTickers))
		.def("onQueryTickersPriceInfo", pure_virtual(&MdApiWrap::onQueryTickersPriceInfo))

		.def("exit", &MdApiWrap::exit)
		.def("createQuoteApi", &MdApiWrap::createQuoteApi)
		.def("release", &MdApiWrap::release)
		.def("getTradingDay", &MdApiWrap::getTradingDay)
		.def("getApiVersion", &MdApiWrap::getApiVersion)
		.def("getApiLastError", &MdApiWrap::getApiLastError)
		.def("setUDPBufferSize", &MdApiWrap::setUDPBufferSize)
		.def("setHeartBeatInterval", &MdApiWrap::setHeartBeatInterval)
		.def("subscribeMarketData", &MdApiWrap::subscribeMarketData)
		.def("unSubscribeMarketData", &MdApiWrap::unSubscribeMarketData)
		.def("subscribeOrderBook", &MdApiWrap::subscribeOrderBook)
		.def("unSubscribeOrderBook", &MdApiWrap::unSubscribeOrderBook)
		.def("subscribeTickByTick", &MdApiWrap::subscribeTickByTick)
		.def("unSubscribeTickByTick", &MdApiWrap::unSubscribeTickByTick)
		.def("subscribeAllMarketData", &MdApiWrap::subscribeAllMarketData)
		.def("unSubscribeAllMarketData", &MdApiWrap::unSubscribeAllMarketData)
		.def("subscribeAllOrderBook", &MdApiWrap::subscribeAllOrderBook)
		.def("unSubscribeAllOrderBook", &MdApiWrap::unSubscribeAllOrderBook)
		.def("subscribeAllTickByTick", &MdApiWrap::subscribeAllTickByTick)
		.def("unSubscribeAllTickByTick", &MdApiWrap::unSubscribeAllTickByTick)
		.def("login", &MdApiWrap::login)
		.def("logout", &MdApiWrap::logout)
		.def("queryAllTickers", &MdApiWrap::queryAllTickers)
		.def("queryTickersPriceInfo", &MdApiWrap::queryTickersPriceInfo)
		.def("queryAllTickersPriceInfo", &MdApiWrap::queryAllTickersPriceInfo)
		;
}