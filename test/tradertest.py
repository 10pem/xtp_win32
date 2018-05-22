# encoding: UTF-8

import time
import os
import threading
from vnxtptd import TdApi

def showName(func):
    def wrapper(*args, **kwargs):
        print('[{}] ------------------'.format(func.__name__))
        func(*args, **kwargs)
        print('\n')
    return wrapper


def printDict(d):
    print('------------')
    for key, value in d.items():
        print(key,value)


class tdtest(TdApi):
    def __init__(self):
        super(tdtest, self).__init__()
        self.reqid = 0
        self.stop = False

    @showName
    def onDisconnected(self, session, reason):
        print('session', session)
        print('reason', reason)

    @showName
    def onError(self, error):
        printDict(error)

    @showName
    def onOrderEvent(self, data, error, session):
        printDict(data)
        printDict(error)
        print('session', session)

    @showName
    def onTradeEvent(self, data, session):
        printDict(data)
        print('session', session)

    @showName
    def onCancelOrderError(self, data, error, sessio):
        printDict(data)
        printDict(error)

    @showName
    def onQueryPosition(self, data, error, last, session):
        printDict(data)
        printDict(error)

    @showName
    def onQueryAsset(self, data, error, last, session):
        printDict(data)
        printDict(error)
        print('last', last)
        print('session', session)

    def conn(self, ip, port, user, password):
        self.session = self.login(ip, port, user, password, 1)

    @showName
    def qryAsset(self):
        while 1:
            self.queryAsset(self.session, self.reqid)
            self.reqid += 1
            time.sleep(20)

            if self.stop:
                break

    def stoprun(self):
        self.stop = True
        self.exit()


if __name__ == '__main__':
    client_id = 2
    path = os.getcwd()

    ip = '120.27.164.69'
    port = 6001
    user = ''
    password = ''
    key = ''
    reqid = 0

    t = tdtest()
    t.createTraderApi(client_id, path)

    # 订阅流
    t.subscribePublicTopic(0)   # 从本交易日开始重传
    t.setSoftwareVersion('test')
    t.setSoftwareKey(key)

    # 登录
    t.conn(ip, port, user, password)

    print('session_id', t.session)
    print('tradingDay', t.getTradingDay())
    print('ApiVersion', t.getApiVersion())

    # 查询资金线程
    time.sleep(2)
    th = threading.Thread(target=t.qryAsset)
    th.start()
    time.sleep(2)

    # 发单测试
    req = {}
    req['order_client_id'] = 1
    req['ticker'] = '000413'
    req['market'] = 1   # 深圳
    req['price'] = 8.55
    #req['stop_price']
    req['quantity'] = 2400
    req['price_type'] = 1   # 限价单
    req['side'] = 1 # 多
    req['business_type'] = 0 # 普通股票业务
    orderid = t.insertOrder(req, t.session)

    # 查询持仓
    t.queryPosition('000413', t.session, t.reqid)
    t.reqid += 1

    time.sleep(30)
    t.stoprun()
