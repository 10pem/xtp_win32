# encoding: UTF-8

import time
from vnxtptd import TdApi

def showName(func):
    def wrapper(*args, **kwargs):
        print('[{}] ------------------'.format(func.__name__))
        func(*args, **kwargs)
    return wrapper


def printDict(d):
    for key, value in d.items():
        print(key,value,sep='  ')

def prin(*args):
    print(*args, sep='  ')

class tdtest(TdApi):
    def __init__(self):
        super(tdtest, self).__init__()

    @showName
    def onDisconnected(self, session, reason):
        prin('session', session)
        prin('reason', reason)

    @showName
    def onError(self, error):
        printDict(error)

    @showName
    def onOrderEvent(self, data, error, session):
        printDict(data)
        printDict(error)
        prin('session', session)

    @showName
    def onTradeEvent(self, data, session):
        printDict(data)
        prin('session', session)

    @showName
    def onCancelOrderError(self, data, error, sessio):
        printDict(data)
        printDict(error)


