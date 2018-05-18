#encoding: UTF-8

from collections import OrderedDict

structDict = {}


#########################################################################
###@author 中泰证券股份有限公司
###@file xoms_api_struct.h
###@brief 定义交易类相关数据结构
#########################################################################
##=====================客户端接口定义=================================
###新订单请求
XTPOrderInsertInfo = OrderedDict()
###XTP系统订单ID，无需用户填写，在XTP系统中唯一
XTPOrderInsertInfo['order_xtp_id'] = "uint64_t"
###报单引用，由客户自定义
XTPOrderInsertInfo['order_client_id'] = "uint32_t"
###合约代码 客户端请求不带空格，以'\0'结尾
XTPOrderInsertInfo['ticker'] = "string"
###交易市场
XTPOrderInsertInfo['market'] = "enum"
###价格
XTPOrderInsertInfo['price'] = "float"
###止损价（保留字段）
XTPOrderInsertInfo['stop_price'] = "float"
###数量(股票单位为股，逆回购单位为张)
XTPOrderInsertInfo['quantity'] = "int64_t"
###报单价格
XTPOrderInsertInfo['price_type'] = "enum"
###买卖方向
XTPOrderInsertInfo['side'] = "enum"
###业务类型
XTPOrderInsertInfo['business_type'] = "enum"
structDict['XTPOrderInsertInfo'] = XTPOrderInsertInfo



###撤单失败响应消息
XTPOrderCancelInfo = OrderedDict()
###撤单XTPID
XTPOrderCancelInfo['order_cancel_xtp_id'] = "uint64_t"
###原始订单XTPID
XTPOrderCancelInfo['order_xtp_id'] = "uint64_t"
structDict['XTPOrderCancelInfo'] = XTPOrderCancelInfo



###报单响应结构体
XTPOrderInfo = OrderedDict()
###XTP系统订单ID，在XTP系统中唯一
XTPOrderInfo['order_xtp_id'] = "uint64_t"
###报单引用，用户自定义
XTPOrderInfo['order_client_id'] = "uint32_t"
###报单操作引用，用户自定义（暂未使用）
XTPOrderInfo['order_cancel_client_id'] = "uint32_t"
###撤单在XTP系统中的id，在XTP系统中唯一
XTPOrderInfo['order_cancel_xtp_id'] = "uint64_t"
###合约代码
XTPOrderInfo['ticker'] = "string"
###交易市场
XTPOrderInfo['market'] = "enum"
###价格
XTPOrderInfo['price'] = "float"
###数量，此订单的报单数量
XTPOrderInfo['quantity'] = "int64_t"
###报单价格条件
XTPOrderInfo['price_type'] = "enum"
###买卖方向
XTPOrderInfo['side'] = "enum"
###业务类型
XTPOrderInfo['business_type'] = "enum"
###今成交数量，为此订单累计成交数量
XTPOrderInfo['qty_traded'] = "int64_t"
###剩余数量，当撤单成功时，表示撤单数量
XTPOrderInfo['qty_left'] = "int64_t"
###委托时间，格式为YYYYMMDDHHMMSSsss
XTPOrderInfo['insert_time'] = "int64_t"
###最后修改时间，格式为YYYYMMDDHHMMSSsss
XTPOrderInfo['update_time'] = "int64_t"
###撤销时间，格式为YYYYMMDDHHMMSSsss
XTPOrderInfo['cancel_time'] = "int64_t"
###成交金额，为此订单的成交总金额
XTPOrderInfo['trade_amount'] = "float"
###本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
XTPOrderInfo['order_local_id'] = "string"
###报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
XTPOrderInfo['order_status'] = "enum"
###报单提交状态，OMS内部使用，用户无需关心
XTPOrderInfo['order_submit_status'] = "enum"
###报单类型
XTPOrderInfo['order_type'] = "string"
structDict['XTPOrderInfo'] = XTPOrderInfo



###报单成交结构体
XTPTradeReport = OrderedDict()
###XTP系统订单ID，此成交回报相关的订单ID，在XTP系统中唯一
XTPTradeReport['order_xtp_id'] = "uint64_t"
###报单引用
XTPTradeReport['order_client_id'] = "uint32_t"
###合约代码
XTPTradeReport['ticker'] = "string"
###交易市场
XTPTradeReport['market'] = "enum"
###订单号，引入XTPID后，该字段实际和order_xtp_id重复。接口中暂时保留。
XTPTradeReport['local_order_id'] = "uint64_t"
###成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
XTPTradeReport['exec_id'] = "string"
###价格，此次成交的价格
XTPTradeReport['price'] = "float"
###数量，此次成交的数量，不是累计数量
XTPTradeReport['quantity'] = "int64_t"
###成交时间，格式为YYYYMMDDHHMMSSsss
XTPTradeReport['trade_time'] = "int64_t"
###成交金额，此次成交的总金额 = price*quantity
XTPTradeReport['trade_amount'] = "float"
###成交序号 --回报记录号，每个交易所唯一,report_index+market字段可以组成唯一标识表示成交回报
XTPTradeReport['report_index'] = "uint64_t"
###报单编号 --交易所单号，上交所为空，深交所有此字段
XTPTradeReport['order_exch_id'] = "string"
###成交类型  --成交回报中的执行类型
XTPTradeReport['trade_type'] = "string"
###买卖方向
XTPTradeReport['side'] = "enum"
###业务类型
XTPTradeReport['business_type'] = "enum"
###交易所交易员代码
XTPTradeReport['branch_pbu'] = "string"
structDict['XTPTradeReport'] = XTPTradeReport



##########################################################################
###报单查询
##########################################################################
###报单查询请求-条件查询
XTPQueryOrderReq = OrderedDict()
###证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
XTPQueryOrderReq['ticker'] = "string"
###格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
XTPQueryOrderReq['begin_time'] = "int64_t"
###格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
XTPQueryOrderReq['end_time'] = "int64_t"
structDict['XTPQueryOrderReq'] = XTPQueryOrderReq



###报单查询响应结构体
structDict['XTPQueryOrderRsp'] = XTPOrderInfo
##########################################################################
###成交回报查询
##########################################################################
###查询成交报告请求-根据执行编号查询（保留字段）
XTPQueryReportByExecIdReq = OrderedDict()
###XTP订单系统ID
XTPQueryReportByExecIdReq['order_xtp_id'] = "uint64_t"
###成交执行编号
XTPQueryReportByExecIdReq['exec_id'] = "string"
structDict['XTPQueryReportByExecIdReq'] = XTPQueryReportByExecIdReq



###查询成交回报请求-查询条件
XTPQueryTraderReq = OrderedDict()
###证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
XTPQueryTraderReq['ticker'] = "string"
###开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
XTPQueryTraderReq['begin_time'] = "int64_t"
###结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
XTPQueryTraderReq['end_time'] = "int64_t"
structDict['XTPQueryTraderReq'] = XTPQueryTraderReq



###成交回报查询响应结构体
structDict['XTPQueryTradeRsp'] = XTPTradeReport
##########################################################################
###账户资金查询响应结构体
##########################################################################
XTPQueryAssetRsp = OrderedDict()
###总资产(=可用资金 + 证券资产（目前为0）+ 预扣的资金)
XTPQueryAssetRsp['total_asset'] = "float"
###可用资金
XTPQueryAssetRsp['buying_power'] = "float"
###证券资产（保留字段，目前为0）
XTPQueryAssetRsp['security_asset'] = "float"
###累计买入成交证券占用资金
XTPQueryAssetRsp['fund_buy_amount'] = "float"
###累计买入成交交易费用
XTPQueryAssetRsp['fund_buy_fee'] = "float"
###累计卖出成交证券所得资金
XTPQueryAssetRsp['fund_sell_amount'] = "float"
###累计卖出成交交易费用
XTPQueryAssetRsp['fund_sell_fee'] = "float"
###XTP系统预扣的资金（包括购买卖股票时预扣的交易资金+预扣手续费）
XTPQueryAssetRsp['withholding_amount'] = "float"
###账户类型
XTPQueryAssetRsp['account_type'] = "enum"
###(保留字段)
XTPQueryAssetRsp['unknown[43]'] = "uint64_t"
structDict['XTPQueryAssetRsp'] = XTPQueryAssetRsp



##########################################################################
###查询股票持仓情况
##########################################################################
XTPQueryStkPositionRsp = OrderedDict()
###证券代码
XTPQueryStkPositionRsp['ticker'] = "string"
###证券名称
XTPQueryStkPositionRsp['ticker_name'] = "string"
###交易市场
XTPQueryStkPositionRsp['market'] = "enum"
###总持仓
XTPQueryStkPositionRsp['total_qty'] = "int64_t"
###可卖持仓
XTPQueryStkPositionRsp['sellable_qty'] = "int64_t"
###持仓成本
XTPQueryStkPositionRsp['avg_price'] = "float"
###浮动盈亏（保留字段）
XTPQueryStkPositionRsp['unrealized_pnl'] = "float"
###昨日持仓
XTPQueryStkPositionRsp['yesterday_position'] = "int64_t"
###今日申购赎回数量（申购和赎回数量不可能同时存在，因此可以共用一个字段）
XTPQueryStkPositionRsp['purchase_redeemable_qty'] = "int64_t"
###(保留字段)
XTPQueryStkPositionRsp['unknown[50]'] = "uint64_t"
structDict['XTPQueryStkPositionRsp'] = XTPQueryStkPositionRsp



#########################################################################
###资金内转流水通知
#########################################################################
XTPFundTransferNotice = OrderedDict()
###资金内转编号
XTPFundTransferNotice['serial_id'] = "uint64_t"
###内转类型
XTPFundTransferNotice['transfer_type'] = "enum"
###金额
XTPFundTransferNotice['amount'] = "float"
###操作结果
XTPFundTransferNotice['oper_status'] = "enum"
###操作时间
XTPFundTransferNotice['transfer_time'] = "uint64_t"
structDict['XTPFundTransferNotice'] = XTPFundTransferNotice



#########################################################################
###资金内转流水查询请求与响应
#########################################################################
XTPQueryFundTransferLogReq = OrderedDict()
###资金内转编号
XTPQueryFundTransferLogReq['serial_id'] = "uint64_t"
structDict['XTPQueryFundTransferLogReq'] = XTPQueryFundTransferLogReq



#########################################################################
###资金内转流水记录结构体
#########################################################################
structDict['XTPFundTransferLog'] = XTPFundTransferNotice
##########################################################################
###查询分级基金信息结构体
##########################################################################
XTPQueryStructuredFundInfoReq = OrderedDict()
XTPQueryStructuredFundInfoReq['exchange_id'] = "enum"
XTPQueryStructuredFundInfoReq['sf_ticker'] = "string"
structDict['XTPQueryStructuredFundInfoReq'] = XTPQueryStructuredFundInfoReq



##########################################################################
###查询分级基金信息响应结构体
##########################################################################
XTPStructuredFundInfo = OrderedDict()
XTPStructuredFundInfo['exchange_id'] = "enum"
XTPStructuredFundInfo['sf_ticker'] = "string"
XTPStructuredFundInfo['sf_ticker_name'] = "string"
XTPStructuredFundInfo['ticker'] = "string"
XTPStructuredFundInfo['ticker_name'] = "string"
XTPStructuredFundInfo['split_merge_status'] = "enum"
XTPStructuredFundInfo['ratio'] = "uint32_t"
XTPStructuredFundInfo['min_split_qty'] = "uint32_t"
XTPStructuredFundInfo['min_merge_qty'] = "uint32_t"
XTPStructuredFundInfo['net_price'] = "float"
structDict['XTPStructuredFundInfo'] = XTPStructuredFundInfo



##########################################################################
###查询股票ETF合约基本情况--请求结构体,
###请求参数为多条件参数:1,不填则返回所有市场的ETF合约信息。
###                  2,只填写market,返回该交易市场下结果
###                   3,填写market及ticker参数,只返回该etf信息。
##########################################################################
XTPQueryETFBaseReq = OrderedDict()
###交易市场
XTPQueryETFBaseReq['market'] = "enum"
###ETF买卖代码
XTPQueryETFBaseReq['ticker'] = "string"
structDict['XTPQueryETFBaseReq'] = XTPQueryETFBaseReq



##########################################################################
###查询股票ETF合约基本情况--响应结构体
##########################################################################
XTPQueryETFBaseRsp = OrderedDict()
XTPQueryETFBaseRsp['market'] = "enum"
XTPQueryETFBaseRsp['etf'] = "string"
XTPQueryETFBaseRsp['subscribe_redemption_ticker'] = "string"
XTPQueryETFBaseRsp['unit'] = "int32_t"
XTPQueryETFBaseRsp['subscribe_status'] = "int32_t"
XTPQueryETFBaseRsp['redemption_status'] = "int32_t"
XTPQueryETFBaseRsp['max_cash_ratio'] = "float"
XTPQueryETFBaseRsp['estimate_amount'] = "float"
XTPQueryETFBaseRsp['cash_component'] = "float"
XTPQueryETFBaseRsp['net_value'] = "float"
XTPQueryETFBaseRsp['total_amount'] = "float"
structDict['XTPQueryETFBaseRsp'] = XTPQueryETFBaseRsp



##########################################################################
###查询股票ETF合约成分股信息--请求结构体,请求参数为:交易市场+ETF买卖代码
##########################################################################
XTPQueryETFComponentReq = OrderedDict()
###交易市场
XTPQueryETFComponentReq['market'] = "enum"
###ETF买卖代码
XTPQueryETFComponentReq['ticker'] = "string"
structDict['XTPQueryETFComponentReq'] = XTPQueryETFComponentReq



##########################################################################
###查询股票ETF合约成分股信息--响应结构体
##########################################################################
XTPQueryETFComponentRsp = OrderedDict()
###交易市场
XTPQueryETFComponentRsp['market'] = "enum"
###ETF代码
XTPQueryETFComponentRsp['ticker'] = "string"
###成份股代码
XTPQueryETFComponentRsp['component_ticker'] = "string"
###成份股名称
XTPQueryETFComponentRsp['component_name'] = "string"
###成份股数量
XTPQueryETFComponentRsp['quantity'] = "int64_t"
###成份股交易市场
XTPQueryETFComponentRsp['component_market'] = "enum"
###成份股替代标识
XTPQueryETFComponentRsp['replace_type'] = "enum"
###溢价比例
XTPQueryETFComponentRsp['premium_ratio'] = "float"
###成分股替代标识为必须现金替代时候的总金额
XTPQueryETFComponentRsp['amount'] = "float"
structDict['XTPQueryETFComponentRsp'] = XTPQueryETFComponentRsp



##########################################################################
###查询当日可申购新股信息
##########################################################################
XTPQueryIPOTickerRsp = OrderedDict()
###交易市场
XTPQueryIPOTickerRsp['market'] = "enum"
###申购代码
XTPQueryIPOTickerRsp['ticker'] = "string"
###申购股票名称
XTPQueryIPOTickerRsp['ticker_name'] = "string"
###申购价格
XTPQueryIPOTickerRsp['price'] = "float"
###申购单元
XTPQueryIPOTickerRsp['unit'] = "int32_t"
###最大允许申购数量
XTPQueryIPOTickerRsp['qty_upper_limit'] = "int32_t"
structDict['XTPQueryIPOTickerRsp'] = XTPQueryIPOTickerRsp



##########################################################################
###查询用户申购额度
##########################################################################
XTPQueryIPOQuotaRsp = OrderedDict()
###交易市场
XTPQueryIPOQuotaRsp['market'] = "enum"
###可申购额度
XTPQueryIPOQuotaRsp['quantity'] = "int32_t"
structDict['XTPQueryIPOQuotaRsp'] = XTPQueryIPOQuotaRsp



#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
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



XTP_ERR_MSG_LEN = 124

XTPRspInfoStruct = {}
XTPRspInfoStruct['error_id'] = 'int32_t'
XTPRspInfoStruct['error_msg'] = 'string'

structDict['XTPRspInfoStruct'] = XTPRspInfoStruct
structDict['XTPRI'] = XTPRspInfoStruct


XTP_ACCOUNT_PASSWORD_LEN = 64

XTPFundTransferReq = {}
XTPFundTransferReq['serial_id'] = 'uint64_t'
XTPFundTransferReq['fund_account'] = 'string'
XTPFundTransferReq['password'] = 'string'
XTPFundTransferReq['amount'] = 'float'
XTPFundTransferReq['transfer_type'] = 'enum'

structDict['XTPFundTransferReq'] = XTPFundTransferReq


structDict['XTPFundTransferAck'] = XTPFundTransferNotice