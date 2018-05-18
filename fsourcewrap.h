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

