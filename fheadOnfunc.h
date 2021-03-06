virtual void OnDisconnected(int reason);
virtual void OnError(XTPRI *error_info);
virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last);
virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last);
virtual void OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count);
virtual void OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last);
virtual void OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last);
virtual void OnOrderBook(XTPOB *order_book);
virtual void OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last);
virtual void OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last);
virtual void OnTickByTick(XTPTBT *tbt_data);
virtual void OnSubscribeAllMarketData(XTPRI *error_info);
virtual void OnUnSubscribeAllMarketData(XTPRI *error_info);
virtual void OnSubscribeAllOrderBook(XTPRI *error_info);
virtual void OnUnSubscribeAllOrderBook(XTPRI *error_info);
virtual void OnSubscribeAllTickByTick(XTPRI *error_info);
virtual void OnUnSubscribeAllTickByTick(XTPRI *error_info);
virtual void OnQueryAllTickers(XTPQSI *ticker_info, XTPRI *error_info, bool is_last);
virtual void OnQueryTickersPriceInfo(XTPTPI *ticker_info, XTPRI *error_info, bool is_last);
