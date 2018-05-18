# enconding: UTF-8

import os
import json
from copy import copy
from datetime import datetime, timedelta

# 类型映射
# 价格类型映射
# 开平类型映射
# 交易所类型映射
# 持仓类型映射
# 产品类型映射
# 委托状态映射

class XtpGateway(VtGateway):
    """XTP接口"""

    # --------------------------------------------------
    def __init__(self, eventEngine, gatewayName='XTP'):
        super(XtpGateway, self).__init__(eventEngine, gatewayName)

        self.
