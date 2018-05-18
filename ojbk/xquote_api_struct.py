#encoding: UTF-8

from collections import OrderedDict

structDict = {}
#########################################################################
###@author 中泰证券股份有限公司
###@file xquote_api_struct.h
###@brief 定义行情类相关数据结构
#########################################################################
###指定的合约
XTPSpecificTickerStruct = OrderedDict()
###交易所代码
XTPSpecificTickerStruct['exchange_id'] = "enum"
###合约代码（不包含交易所信息）例如"600000"，不带空格，以'\0'结尾
XTPSpecificTickerStruct['ticker'] = "string"
structDict['XTPSpecificTickerStruct'] = XTPSpecificTickerStruct




structDict['XTPST'] = XTPSpecificTickerStruct


###行情
XTPMarketDataStruct = OrderedDict()
## 代码
###交易所代码
XTPMarketDataStruct['exchange_id'] = "enum"
###合约代码（不包含交易所信息），不带空格，以'\0'结尾
XTPMarketDataStruct['ticker'] = "string"
## 股票等价格
###最新价
XTPMarketDataStruct['last_price'] = "float"
###昨收盘
XTPMarketDataStruct['pre_close_price'] = "float"
###今开盘
XTPMarketDataStruct['open_price'] = "float"
###最高价
XTPMarketDataStruct['high_price'] = "float"
###最低价
XTPMarketDataStruct['low_price'] = "float"
###今收盘
XTPMarketDataStruct['close_price'] = "float"
## 期货等数据
###昨持仓量（目前未填写）
XTPMarketDataStruct['pre_open_interest'] = "float"
###持仓量（目前未填写）
XTPMarketDataStruct['open_interest'] = "float"
###上次结算价（目前未填写）
XTPMarketDataStruct['pre_settlement_price'] = "float"
###本次结算价（目前未填写）
XTPMarketDataStruct['settlement_price'] = "float"
###涨停板价（目前未填写）
XTPMarketDataStruct['upper_limit_price'] = "float"
###跌停板价（目前未填写）
XTPMarketDataStruct['lower_limit_price'] = "float"
###昨虚实度（目前未填写）
XTPMarketDataStruct['pre_delta'] = "float"
###今虚实度（目前未填写）
XTPMarketDataStruct['curr_delta'] = "float"
### 时间类，格式为YYYYMMDDHHMMSSsss
XTPMarketDataStruct['data_time'] = "int64_t"
## 量额数据
###数量，为总成交量（单位股，与交易所一致）
XTPMarketDataStruct['qty'] = "int64_t"
###成交金额，为总成交金额（单位元，与交易所一致）
XTPMarketDataStruct['turnover'] = "float"
###当日均价=(turnover#qty)
XTPMarketDataStruct['avg_price'] = "float"
## 买卖盘
###十档申买价
XTPMarketDataStruct['bid[10]'] = "float"
###十档申卖价
XTPMarketDataStruct['ask[10]'] = "float"
###十档申买量
XTPMarketDataStruct['bid_qty[10]'] = "int64_t"
###十档申卖量
XTPMarketDataStruct['ask_qty[10]'] = "int64_t"
## 额外数据（以下数据目前未填写）
###成交笔数
XTPMarketDataStruct['trades_count'] = "int64_t"
###当前交易状态说明
XTPMarketDataStruct['ticker_status'] = "string"
###委托买入总量
XTPMarketDataStruct['total_bid_qty'] = "int64_t"
###委托卖出总量
XTPMarketDataStruct['total_ask_qty'] = "int64_t"
###加权平均委买价格
XTPMarketDataStruct['ma_bid_price'] = "float"
###加权平均委卖价格
XTPMarketDataStruct['ma_ask_price'] = "float"
###债券加权平均委买价格
XTPMarketDataStruct['ma_bond_bid_price'] = "float"
###债券加权平均委卖价格
XTPMarketDataStruct['ma_bond_ask_price'] = "float"
###债券到期收益率
XTPMarketDataStruct['yield_to_maturity'] = "float"
###ETF净值估值
XTPMarketDataStruct['iopv'] = "float"
###ETF申购笔数
XTPMarketDataStruct['etf_buy_count'] = "int32_t"
###ETF赎回笔数
XTPMarketDataStruct['etf_sell_count'] = "int32_t"
###ETF申购数量
XTPMarketDataStruct['etf_buy_qty'] = "float"
###ETF申购金额
XTPMarketDataStruct['etf_buy_money'] = "float"
###ETF赎回数量
XTPMarketDataStruct['etf_sell_qty'] = "float"
###ETF赎回金额
XTPMarketDataStruct['etf_sell_money'] = "float"
###权证执行的总数量
XTPMarketDataStruct['total_warrant_exec_qty'] = "float"
###权证跌停价格（元）
XTPMarketDataStruct['warrant_lower_price'] = "float"
###权证涨停价格（元）
XTPMarketDataStruct['warrant_upper_price'] = "float"
###买入撤单笔数
XTPMarketDataStruct['cancel_buy_count'] = "int32_t"
###卖出撤单笔数
XTPMarketDataStruct['cancel_sell_count'] = "int32_t"
###买入撤单数量
XTPMarketDataStruct['cancel_buy_qty'] = "float"
###卖出撤单数量
XTPMarketDataStruct['cancel_sell_qty'] = "float"
###买入撤单金额
XTPMarketDataStruct['cancel_buy_money'] = "float"
###卖出撤单金额
XTPMarketDataStruct['cancel_sell_money'] = "float"
###买入总笔数
XTPMarketDataStruct['total_buy_count'] = "int64_t"
###卖出总笔数
XTPMarketDataStruct['total_sell_count'] = "int64_t"
###买入委托成交最大等待时间
XTPMarketDataStruct['duration_after_buy'] = "int32_t"
###卖出委托成交最大等待时间
XTPMarketDataStruct['duration_after_sell'] = "int32_t"
###买方委托价位数
XTPMarketDataStruct['num_bid_orders'] = "int32_t"
###卖方委托价位数
XTPMarketDataStruct['num_ask_orders'] = "int32_t"
###成交时间（UA3113）
XTPMarketDataStruct['exec_time'] = "int32_t"
###闭市标志（UA103#UA104）
XTPMarketDataStruct['is_market_closed'] = "string"
###合约持仓量（UA103）
XTPMarketDataStruct['total_position'] = "float"
###市盈率1（UA103）
XTPMarketDataStruct['pe_ratio1'] = "float"
###市盈率2（UA103）
XTPMarketDataStruct['pe_ratio2'] = "float"
structDict['XTPMarketDataStruct'] = XTPMarketDataStruct




structDict['XTPMD'] = XTPMarketDataStruct


###股票行情静态信息
XTPQuoteStaticInfo = OrderedDict()
###交易所代码
XTPQuoteStaticInfo['exchange_id'] = "enum"
###合约代码（不包含交易所信息），不带空格，以'\0'结尾
XTPQuoteStaticInfo['ticker'] = "string"
### 合约名称
XTPQuoteStaticInfo['ticker_name'] = "string"
### 合约类型
XTPQuoteStaticInfo['ticker_type'] = "enum"
###昨收盘
XTPQuoteStaticInfo['pre_close_price'] = "float"
###涨停板价
XTPQuoteStaticInfo['upper_limit_price'] = "float"
###跌停板价
XTPQuoteStaticInfo['lower_limit_price'] = "float"
###最小变动价位
XTPQuoteStaticInfo['price_tick'] = "float"
### 合约最小交易量(买)
XTPQuoteStaticInfo['buy_qty_unit'] = "int32_t"
### 合约最小交易量(卖)
XTPQuoteStaticInfo['sell_qty_unit'] = "int32_t"
structDict['XTPQuoteStaticInfo'] = XTPQuoteStaticInfo




structDict['XTPQSI'] = XTPQuoteStaticInfo


###定单薄
OrderBookStruct = OrderedDict()
###交易所代码
OrderBookStruct['exchange_id'] = "enum"
###合约代码（不包含交易所信息），不带空格，以'\0'结尾
OrderBookStruct['ticker'] = "string"
###最新价
OrderBookStruct['last_price'] = "float"
###数量，为总成交量
OrderBookStruct['qty'] = "int64_t"
###成交金额，为总成交金额
OrderBookStruct['turnover'] = "float"
###成交笔数
OrderBookStruct['trades_count'] = "int64_t"
## 买卖盘
###十档申买价
OrderBookStruct['bid[10]'] = "float"
###十档申卖价
OrderBookStruct['ask[10]'] = "float"
###十档申买量
OrderBookStruct['bid_qty[10]'] = "int64_t"
###十档申卖量
OrderBookStruct['ask_qty[10]'] = "int64_t"
### 时间类
OrderBookStruct['data_time'] = "int64_t"
structDict['OrderBookStruct'] = OrderBookStruct




structDict['XTPOB'] = OrderBookStruct


################################## 逐笔数据
###逐笔委托(仅适用深交所)
XTPTickByTickEntrust = OrderedDict()
###频道代码
XTPTickByTickEntrust['channel_no'] = "int32_t"
###委托序号(在同一个channel_no内唯一，从1开始连续)
XTPTickByTickEntrust['seq'] = "int64_t"
###委托价格
XTPTickByTickEntrust['price'] = "float"
###委托数量
XTPTickByTickEntrust['qty'] = "int64_t"
###'1':买 '2':卖 'G':借入 'F':出借
XTPTickByTickEntrust['side'] = "string"
###订单类别: '1': 市价 '2': 限价 '3': 本方最优
XTPTickByTickEntrust['ord_type'] = "string"
structDict['XTPTickByTickEntrust'] = XTPTickByTickEntrust



###逐笔成交
XTPTickByTickTrade = OrderedDict()
###频道代码
XTPTickByTickTrade['channel_no'] = "int32_t"
###委托序号(在同一个channel_no内唯一，从1开始连续)
XTPTickByTickTrade['seq'] = "int64_t"
###成交价格
XTPTickByTickTrade['price'] = "float"
###成交量
XTPTickByTickTrade['qty'] = "int64_t"
###成交金额(仅适用上交所)
XTPTickByTickTrade['money'] = "float"
###买方订单号
XTPTickByTickTrade['bid_no'] = "int64_t"
###卖方订单号
XTPTickByTickTrade['ask_no'] = "int64_t"
### SH: 内外盘标识('B':主动买 'S':主动卖 'N':未知)
### SZ: 成交标识('4':撤 'F':成交)
XTPTickByTickTrade['trade_flag'] = "string"
structDict['XTPTickByTickTrade'] = XTPTickByTickTrade



###逐笔数据信息
XTPTickByTickStruct = OrderedDict()
###交易所代码
XTPTickByTickStruct['exchange_id'] = "enum"
###合约代码（不包含交易所信息），不带空格，以'\0'结尾
XTPTickByTickStruct['ticker'] = "string"
###预留
XTPTickByTickStruct['seq'] = "int64_t"
###委托时间 or 成交时间
XTPTickByTickStruct['data_time'] = "int64_t"
###委托 or 成交
XTPTickByTickStruct['type'] = "enum"
structDict['XTPTickByTickStruct'] = XTPTickByTickStruct



structDict['XTPTickByTickStruct'] = XTPTickByTickStruct




structDict['XTPTBT'] = XTPTickByTickStruct


###供查询的最新信息
XTPTickerPriceInfo = OrderedDict()
###交易所代码
XTPTickerPriceInfo['exchange_id'] = "enum"
###合约代码（不包含交易所信息），不带空格，以'\0'结尾
XTPTickerPriceInfo['ticker'] = "string"
###最新价
XTPTickerPriceInfo['last_price'] = "float"
structDict['XTPTickerPriceInfo'] = XTPTickerPriceInfo




structDict['XTPTPI'] = XTPTickerPriceInfo


