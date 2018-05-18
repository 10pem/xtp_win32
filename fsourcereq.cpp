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

MIGHT WRONG MdApi::getApiLastError()
{
	MIGHT WRONG i = this->api->GetApiLastError();
	return i;
}

void MdApi::setUDPBufferSize(int buff_size)
{
	this->api->SetUDPBufferSize(buff_size);
}

void MdApi::registerSpi(MIGHT WRONG spi)
{
	this->api->RegisterSpi(MIGHT WRONG);
}

void MdApi::setHeartBeatInterval(int interval)
{
	this->api->SetHeartBeatInterval(interval);
}

int MdApi::subscribeMarketData(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::unSubscribeMarketData(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->UnSubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::subscribeOrderBook(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->SubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::unSubscribeOrderBook(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->UnSubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::subscribeTickByTick(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->SubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::unSubscribeTickByTick(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
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
	int i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE) sock_type);
	return i;
}

int MdApi::logout()
{
	int i = this->api->Logout();
	return i;
}

int MdApi::queryAllTickers(int exchage_id)
{
	int i = this->api->QueryAllTickers((XTP_EXCHANGE_TYPE) exchage_id);
	return i;
}

int MdApi::queryTickersPriceInfo(string ticker, int exchage_id)
{
	char *buffer = (char*) ticker.c_str();
	char *myreq[1] = { buffer };
	int i = this->api->QueryTickersPriceInfo(myreq, 1, (XTP_EXCHANGE_TYPE)exchage_id);
	return i;
}

int MdApi::queryAllTickersPriceInfo()
{
	int i = this->api->QueryAllTickersPriceInfo();
	return i;
}

