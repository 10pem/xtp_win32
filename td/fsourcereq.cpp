void TdApi::release()
{

	this->api->Release();
}

string TdApi::getTradingDay()
{
	string i = this->api->GetTradingDay();
	return i;
}

void TdApi::registerSpi(MIGHT WRONG spi)
{

	this->api->RegisterSpi(MIGHT WRONG);
}

MIGHT WRONG TdApi::getApiLastError()
{
	MIGHT WRONG i = this->api->GetApiLastError();
	return i;
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

	this->api->SubscribePublicTopic((XTP_TE_RESUME_TYPE) resume_type);
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
	uint64_t i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE) sock_type);
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
	myreq.market = (XTP_XXX_TYPE)market;

	getDouble(data, "price", &myreq.price);
	getDouble(data, "stop_price", &myreq.stop_price);
	getInt64(data, "quantity", &myreq.quantity);
	int price_type;
	getInt(data, "price_type", &price_type);
	myreq.price_type = (XTP_XXX_TYPE)price_type;

	int side;
	getInt(data, "side", &side);
	myreq.side = (XTP_XXX_TYPE)side;

	int business_type;
	getInt(data, "business_type", &business_type);
	myreq.business_type = (XTP_XXX_TYPE)business_type;

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
	myreq.exchange_id = (XTP_XXX_TYPE)exchange_id;

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
	getString(data, "password", myreq.password);
	getDouble(data, "amount", &myreq.amount);
	int transfer_type;
	getInt(data, "transfer_type", &transfer_type);
	myreq.transfer_type = (XTP_XXX_TYPE)transfer_type;

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
	myreq.market = (XTP_XXX_TYPE)market;

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
	myreq.market = (XTP_XXX_TYPE)market;

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

