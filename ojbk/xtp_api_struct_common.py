# encoding: UTF-8

structDict = {}

XTP_ERR_MSG_LEN = 124

XTPRspInfoStruct = {}
XTPRspInfoStruct['error_id'] = 'int32_t'
XTPRspInfoStruct['error_msg'] = 'string'

structDict['XTPRspInfoStruct'] = XTPRspInfoStruct
structDict['XTPRI'] = XTPRspInfoStruct
