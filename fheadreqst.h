void release();
string getTradingDay();
string getApiVersion();
MIGHT WRONG getApiLastError();
void setUDPBufferSize(int buff_size);
void registerSpi(MIGHT WRONG spi);
void setHeartBeatInterval(int interval);
int subscribeMarketData(string ticker, int exchage_id);
int unSubscribeMarketData(string ticker, int exchage_id);
int subscribeOrderBook(string ticker, int exchage_id);
int unSubscribeOrderBook(string ticker, int exchage_id);
int subscribeTickByTick(string ticker, int exchage_id);
int unSubscribeTickByTick(string ticker, int exchage_id);
int subscribeAllMarketData();
int unSubscribeAllMarketData();
int subscribeAllOrderBook();
int unSubscribeAllOrderBook();
int subscribeAllTickByTick();
int unSubscribeAllTickByTick();
int login(string ip, int port, string user, string password, int sock_type);
int logout();
int queryAllTickers(int exchage_id);
int queryTickersPriceInfo(string ticker, int exchage_id);
int queryAllTickersPriceInfo();
