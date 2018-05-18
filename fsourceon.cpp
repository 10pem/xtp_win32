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

	if(error_info)
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

	if(ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(market_data)
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

	if(ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(order_book)
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

	if(ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(tbt_data)
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

	if(error_info)
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

	if(error_info)
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

	if(error_info)
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

	if(error_info)
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

	if(error_info)
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

	if(error_info)
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

	if(ticker_info)
	{
		XTPQSI *task_data = new XTPQSI();
		*task_data = *ticker_info;
		task->task_data = task_data;
	}

	if(error_info)
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

	if(ticker_info)
	{
		XTPTPI *task_data = new XTPTPI();
		*task_data = *ticker_info;
		task->task_data = task_data;
	}

	if(error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
}

