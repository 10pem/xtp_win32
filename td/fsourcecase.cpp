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

