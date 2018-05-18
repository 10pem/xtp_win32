.def("release", &TdApiWrap::release)
.def("getTradingDay", &TdApiWrap::getTradingDay)
.def("registerSpi", &TdApiWrap::registerSpi)
.def("getApiLastError", &TdApiWrap::getApiLastError)
.def("getApiVersion", &TdApiWrap::getApiVersion)
.def("getClientIDByXTPID", &TdApiWrap::getClientIDByXTPID)
.def("getAccountByXTPID", &TdApiWrap::getAccountByXTPID)
.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
.def("setSoftwareVersion", &TdApiWrap::setSoftwareVersion)
.def("setSoftwareKey", &TdApiWrap::setSoftwareKey)
.def("setHeartBeatInterval", &TdApiWrap::setHeartBeatInterval)
.def("login", &TdApiWrap::login)
.def("logout", &TdApiWrap::logout)
.def("insertOrder", &TdApiWrap::insertOrder)
.def("cancelOrder", &TdApiWrap::cancelOrder)
.def("queryOrderByXTPID", &TdApiWrap::queryOrderByXTPID)
.def("queryOrders", &TdApiWrap::queryOrders)
.def("queryTradesByXTPID", &TdApiWrap::queryTradesByXTPID)
.def("queryTrades", &TdApiWrap::queryTrades)
.def("queryPosition", &TdApiWrap::queryPosition)
.def("queryAsset", &TdApiWrap::queryAsset)
.def("queryStructuredFund", &TdApiWrap::queryStructuredFund)
.def("fundTransfer", &TdApiWrap::fundTransfer)
.def("queryFundTransfer", &TdApiWrap::queryFundTransfer)
.def("queryETF", &TdApiWrap::queryETF)
.def("queryETFTickerBasket", &TdApiWrap::queryETFTickerBasket)
.def("queryIPOInfoList", &TdApiWrap::queryIPOInfoList)
.def("queryIPOQuotaInfo", &TdApiWrap::queryIPOQuotaInfo)