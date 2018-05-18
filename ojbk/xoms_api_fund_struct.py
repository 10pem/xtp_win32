# encoding: UTF-8

structDict = {}

XTP_ACCOUNT_PASSWORD_LEN = 64

XTPFundTransferReq = {}
XTPFundTransferReq['serial_id'] = 'unit64_t'
XTPFundTransferReq['fund_account'] = 'string'
XTPFundTransferReq['password'] = 'string'
XTPFundTransferReq['amount'] = 'float'
XTPFundTransferReq['transfer_type'] = 'enum'

structDict['XTPFundTransferReq'] = XTPFundTransferReq


structDict['XTPFundTransferAck'] = XTPFundTransferNotice