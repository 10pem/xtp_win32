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

