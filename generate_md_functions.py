__author__ = 'HsuPin'

from ojbk.all_struct import structDict
from ojbk.xtp_api_data_type import typedefDict
from process_xoms_struct import type_dict


typedefDict.update(type_dict)
type_dict.update({'int': 'int', 'void':'void'})


def preprocess(line):
    cppline = line.replace('\t', ' ').replace('\n', '')
    cppline = cppline.strip(' ')
    return cppline


def main():
    skiplines = 33
    callback_count = 0  # 回调函数计数

    fr = 'xtp\\xtp_quote_api.h'
    ffuncCounts = open('fheadConstant.h', 'w')
    fheadOn = open('fheadOnfunc.h', 'w')
    fheadPro = open('fheadProcess.h', 'w')
    fheadon = open('fheadon.h', 'w')
    fheadreq = open('fheadreqst.h', 'w')

    fsourcewrap = open('fsourcewrap.h', 'w')
    fsourcedefon = open('fsourcedefon.cpp', 'w')
    fsourcedefreq = open('fsourcedefreq.cpp', 'w')
    fsourcecase = open('fsourcecase.cpp', 'w')
    fsourcereq = open('fsourcereq.cpp', 'w')
    fsourceOn = open('fsourceon.cpp', 'w')
    fsourcepro = open('fsourceprocess.cpp', 'w')

    fr = open(fr, 'r', encoding='gbk')

    fheadPro.write('void processTask();\n')

    lines = fr.readlines()
    for linenum, line in enumerate(lines):
        if linenum < skiplines:
            continue
        cppline = preprocess(line)
        if cppline.startswith('virtual'):
            contents = cppline.split(' ')
            contents = [content for content in contents if content != 'const']
            rettype = contents[1]       # 返回类型
            try:
                funcname = contents[2][:contents[2].index('(')].strip('*')      # 函数名称
            except ValueError:
                funcname = 'MIGHT WRONG'
                print('functionname got cpp:', cppline)
            paramline = cppline[cppline.index('(')+1:cppline.index(')')]
            paramlist = [x for x in paramline.split(',') if x != '']


            # 回调函数
            if funcname.startswith('On'):
                funcname_callback = 'on' + funcname[2:]

                # ffuncCounts
                funccout_line = '#define {} {}\n'.format(funcname.upper(), callback_count)
                callback_count += 1
                ffuncCounts.write(funccout_line)

                # fheadOn
                fheadOn_line = cppline
                fheadOn_strip = fheadOn_line[:fheadOn_line.index(')') + 1] + ';\n'
                fheadOn.write(fheadOn_strip)

                # fheadon and wrap
                fheadon_line = 'virtual void {}('.format(funcname_callback)
                paramline_on = ''
                wrap_cpp_line_add = ('{\n' +
                                     '\ttry\n' +
                                     '\t{\n' +
                                     '\t\tthis->get_override("{}")'.format(funcname_callback))
                wrap_cpp_line_add_param = '('
                datafield = False
                for param_num, param in enumerate(paramlist):
                    if 'error' in param:

                        if param_num != 0:
                            paramline_on += ', '
                            wrap_cpp_line_add_param += ', '

                        paramline_on += 'dict error'
                        wrap_cpp_line_add_param += 'error'

                    elif 'int reason' in param:
                        if param_num != 0:
                            paramline_on += ', '
                            wrap_cpp_line_add_param += ', '

                        paramline_on += 'int reason'
                        wrap_cpp_line_add_param += 'reason'

                    elif 'bool' in param:
                        if param_num != 0:
                            paramline_on += ', '
                            wrap_cpp_line_add_param += ', '

                        paramline_on += 'bool last'
                        wrap_cpp_line_add_param += 'last'

                    else:
                        if datafield == True:
                            continue
                        else:
                            if param_num != 0:
                                paramline_on += ', '
                                wrap_cpp_line_add_param += ', '

                            paramline_on += 'dict data'
                            wrap_cpp_line_add_param += 'data'
                            datafield = True
                fheadon_line = fheadon_line + paramline_on + '){};\n'
                fheadon.write(fheadon_line)
                # wrap
                wrap_cpp_line = fheadon_line[:-4] + '\n'
                wrap_cpp_line_add_param += ');\n'
                wrap_cpp_line += (wrap_cpp_line_add + wrap_cpp_line_add_param +
                                  '\t}\n' +
                                  '\tcatch (error_already_set const &)\n' +
                                  '\t{\n' +
                                  '\t\tPyErr_Print();\n'+
                                  '\t}\n' +
                                  '}\n\n')
                fsourcewrap.write(wrap_cpp_line)

                # ondef
                defon_cpp_line = '.def("{func}", pure_virtual(&MdApiWrap::{func}))\n'.format(func=funcname_callback)
                fsourcedefon.write(defon_cpp_line)

                # fheadPro
                process_line = 'void process{}(Task *task);\n'.format(funcname[2:])
                fheadPro.write(process_line)

                # fsourcecase
                fsourcecase_line = ('case ' + funcname.upper() + ':\n' +
                                    '{\n' +
                                    '\tthis->process{}(task);\n'.format(funcname[2:]) +
                                    '\tbreak;\n' +
                                    '}\n\n')
                fsourcecase.write(fsourcecase_line)

                # cppOn     c++数据到python类型转化
                On_cppline = (rettype + ' MdApi::' + fheadOn_line[fheadOn_line.index('On'):fheadOn_line.index(' {};')] + '\n' +
                                  '{\n' +
                                  '\tTask *task = new Task();\n' +
                                  '\ttask->task_name = ' + funcname.upper() + ';\n\n')
                On_cppline_add = ''
                for param_num, param in enumerate(paramlist):
                    param = param.strip(' ')
                    param_struct = param[:param.index(' ')]
                    try:
                        param_name = param[param.index('*') + 1:]
                    except:
                        param_name = "WHEVERPARAM_NAME"
                    if 'error' in param:
                        On_cppline_add += ('\tif(error_info)\n' +
                                             '\t{\n' +
                                             '\t\tXTPRI *task_error = new XTPRI();\n' +
                                             '\t\t*task_error = *error_info;\n' +
                                             '\t\ttask->task_error = task_error;\n' +
                                             '\t}\n\n')
                    elif 'int reason' in param:
                        On_cppline_add += ('\ttask->task_id = reason;\n')
                    elif 'XTP' in param:    # 只获取结构体数据
                        On_cppline_add += ('\tif(' + param_name +')\n' +
                                             '\t{\n' +
                                             '\t\t' + param_struct + ' *task_data = new ' + param_struct + '();\n' +
                                             '\t\t*task_data = *' + param_name + ';\n' +
                                             '\t\ttask->task_data = task_data;\n' +
                                             '\t}\n\n')
                    elif 'bool' in param:
                        On_cppline_add += ('\ttask->task_last = is_last;\n')
                On_cppline = (On_cppline + On_cppline_add +
                                  '\tthis->task_queue.push(task);\n' +
                                  '}\n\n')
                fsourceOn.write(On_cppline)

                # cpp_process
                process_cppline = ('void MdApi::process' + funcname[2:] + '(Task *task)\n' +
                                   '{\n' +
                                   '\tPyLock lock;\n')
                process_cppline_add = ''
                process_cppline_on = '\tthis->' + funcname_callback + '('
                for param_num, param in enumerate(paramlist):
                    param = param.strip(' ')
                    param_struct = param[:param.index(' ')]
                    if 'error' in param:
                        if param_num != 0:
                            process_cppline_on += ', '
                        process_cppline_add += ('\tdict error;\n' +
                                                '\tif (task->task_error)\n' +
                                                '\t{\n' +
                                                '\t\tXTPRI *task_error = (XTPRI*) task->task_error;\n' +
                                                '\t\terror["error_id"] = task_error->error_id;\n' +
                                                '\t\terror["error_msg"] = task_error->error_msg;\n' +
                                                '\t\tdelete task->task_error;\n' +
                                                '\t}\n\n')
                        process_cppline_on += 'error'
                    elif 'int reason' in param:
                        if param_num != 0:
                            process_cppline_on += ', '
                        process_cppline_on += 'task->task_id'
                    elif 'XTP' in param:
                        listdata_flag = False   # 标记是否需要创建python的list来存放c++数组数据
                        if param_num != 0:
                            process_cppline_on += ', '
                        list_define_line = '\n'
                        list_addtodict_line = ''
                        arr_data_line = ('\n' +
                                         '\t\tfor(int i=0; i<10; ++i)\n' +
                                         '\t\t{\n')
                        psdict = structDict.get(param_struct, "MIGHT WRONG")
                        temp = ('\tdict data;\n' +
                                '\tif (task->task_data)\n' +
                                '\t{\n' +
                                '\t\t' + param_struct + ' *task_data = (' + param_struct + '*) task->task_data;\n')
                        for key, value in psdict.items():
                            # 数组数据处理
                            if '[' in key:
                                # 定义列表数据
                                listdata_flag = True
                                arrname = key.split('[')[0]
                                list_define_line += '\t\tboost::python::list ' + arrname + ';\n'
                                list_addtodict_line += '\t\tdata["{arrname}"] = {arrname};\n'.format(arrname=arrname)
                                # 数组数据赋值到列表
                                arr_data_line += '\t\t\t{listname}.append(task_data->{arrname}[i]);\n'.format(listname=arrname, arrname=arrname)
                            else:
                                if value == 'enum':
                                    temp += '\t\tdata["{}"] = (int) task_data->{};\n'.format(key, key)
                                else:
                                    temp += '\t\tdata["{}"] = task_data->{};\n'.format(key, key)
                        arr_data_line += '\t\t}\n'
                        if listdata_flag == True:
                            temp = temp + list_define_line + arr_data_line + list_addtodict_line
                        temp += '\t\tdelete task->task_data;\n\t}\n\n'
                        process_cppline_add += temp
                        process_cppline_on += 'data'
                    elif 'bool' in param:
                        if param_num != 0:
                            process_cppline_on += ', '
                        process_cppline_on += 'task->task_last'
                process_cppline_on += ');\n\tdelete task;\n}\n\n' # 对齐 process_cppline的{
                process_cppline = process_cppline + process_cppline_add + process_cppline_on
                fsourcepro.write(process_cppline)



            # 主动函数 接受参数是一个结构体的就是dict, 否则平常处理
            else:
                funcname = funcname.strip('*')
                funcname_req = funcname[0].lower() + funcname[1:]
                pyrettype = type_dict.get(rettype, 'MIGHT WRONG')     # 手动处理部分结构体数据

                # h_req
                req_h_line = '{rt} {func}'.format(rt=pyrettype, func=funcname_req)
                # 处理参数
                req_h_param = ''
                for param_num, param in enumerate(paramlist):
                    param = param.strip(' ')
                    param_inward = [x for x in param.split(' ') if x!='const']
                    param_struct = param_inward[0]
                    param_name = param_inward[1].strip('*') # 保留[]用于区分数组数据与否
                    #print(param_struct, param_name)
                    if param_struct == 'char':
                        if param_num != 0:
                            req_h_param += ', '
                        param_name = param_name.split('[')[0]   # char 无视数组
                        req_h_param += 'string {}'.format(param_name)
                    elif param_struct == 'XTP_EXCHANGE_TYPE':
                        if param_num != 0:
                            req_h_param += ', '
                        req_h_param += 'int {}'.format(param_name)
                    elif 'int count' in param:
                        pass    # 不作为一个参数, 在req函数里面, 调用Req的时候直接写1
                    # 针对xxxintxx 这种类型的数据
                    elif 'int' in param_struct:
                        if param_num != 0:
                            req_h_param += ', '
                        req_h_param += 'int {}'.format(param_name)
                    else:
                        if param_num != 0:
                            req_h_param += ', '
                        pydatatype = typedefDict.get(param_struct, 'MIGHT WRONG')
                        if pydatatype == 'enum':
                            pydatatype = 'int'
                        req_h_param += '{} {}'.format(pydatatype, param_name)

                req_h_line = req_h_line + '(' + req_h_param + ');\n'
                fheadreq.write(req_h_line)

                # cpp_operation
                op_cpp_line = '{rt} MdApi::{func}'.format(rt=pyrettype, func=funcname_req) + '(' + req_h_param + ')\n'
                op_cpp_line_add = '{\n'
                # 分成有数组和无数组操作, 没有数组数据直接提取数据调用
                # 没有数组数据的处理
                if '[]' not in paramline:
                    if pyrettype == 'void':
                        op_cpp_line_add += ('\tthis->api->' + funcname + '(')
                    else:
                        op_cpp_line_add += '\t{ctype} i = this->api->{func}('.format(ctype=pyrettype, func=funcname)
                    for param_num, param in enumerate(paramlist):       # param是一定要对应的
                        param = param.strip(' ')
                        param_inward = [x for x in param.split(' ') if x != 'const']
                        param_struct = param_inward[0]
                        param_name = param_inward[1].strip('*')  # 保留[]以区别数组
                        if param_struct == 'char':
                            if param_num != 0:
                                op_cpp_line_add += ', '
                            op_cpp_line_add += '{}.c_str()'.format(param_name)
                        elif 'int' in param_struct:
                            # int count 只会出现在有数组数据的地方; 这里针对的是各种 int类型
                            if param_num != 0:
                                op_cpp_line_add += ', '
                            op_cpp_line_add += param_name
                        else:
                            if param_num != 0:
                                op_cpp_line_add += ', '
                            if typedefDict.get(param_struct, "MIGHT WRONG") == 'enum':
                                # 类似 XTP_EXCHANGE_TYPE
                                op_cpp_line_add += '({}) {}'.format(param_struct, param_name)
                            else:
                                # 主动函数其他的参数类型, 比如需要传入一些结构体数据
                                print('[cpp_op] linenum: ', linenum, " cppline: ", cppline)
                                op_cpp_line_add += 'MIGHT WRONG'
                    if pyrettype == 'void':
                        op_cpp_line_add += ');\n}\n\n'
                    else:
                        op_cpp_line_add += (');\n' +
                                            '\treturn i;\n' +
                                            '}\n\n')
                    op_cpp_line += op_cpp_line_add
                    fsourcereq.write(op_cpp_line)

                # 含数组数据
                else:
                    # op_cpp_line_add2为直接调用函数, ..._add是在add2之前需要添加的数组数据处理行
                    if pyrettype == 'void':
                        op_cpp_line_add2 = '\tthis->api->' + funcname + '('
                    else:
                        op_cpp_line_add2 = '\t{ctype} i = this->api->{func}('.format(ctype=pyrettype, func=funcname)
                    for param_num, param in enumerate(paramlist):
                        param = param.strip(' ')
                        param_inward = [x for x in param.split(' ') if x!='const']
                        param_struct = param_inward[0]
                        param_name = param_inward[1].strip('*') # 保留[]以区别数组

                        if param_struct == 'char':
                            # 数组数据
                            if param_num != 0:
                                op_cpp_line_add2 += ', '
                            param_name = param_name.split('[')[0]
                            op_cpp_line_add += ('\tchar *buffer = (char*) ' + param_name + '.c_str();\n' +
                                                    '\tchar *myreq[1] = { buffer };\n')
                            op_cpp_line_add2 += 'myreq'
                        elif 'int count' in param:
                            if param_num != 0:
                                op_cpp_line_add2 += ', '
                            op_cpp_line_add2 += '1'
                        elif 'int' in param:
                            if param_num != 0:
                                op_cpp_line_add2 += ', '
                            op_cpp_line_add2 += param_name
                        else:
                            if param_num != 0:
                                op_cpp_line_add2 += ', '
                            if typedefDict.get(param_struct, "MIGHT WRONG") == 'enum':
                                op_cpp_line_add2 += '({}){}'.format(param_struct, param_name)
                            else:
                                print('[cpp_op] linenum: ', linenum, " cppline: ", cppline)
                                op_cpp_line_add2 += 'MIGHT WRONG'
                    op_cpp_line_add2 += (');\n' +
                                         '\treturn i;\n')
                    op_cpp_line_add += op_cpp_line_add2 + '}\n\n'
                    op_cpp_line = op_cpp_line + op_cpp_line_add
                    fsourcereq.write(op_cpp_line)

                # reqdef
                defreq_line = '.def("{func}", &MdApiWrap::{func})\n'.format(func=funcname_req)
                fsourcedefreq.write(defreq_line)

        # 其他函数, 创建API的函数
        else:
            pass

    fr.close()
    ffuncCounts.close()
    fheadOn.close()
    fheadPro.close()
    fheadon.close()
    fheadreq.close()
    fsourcewrap.close()

    fsourcedefon.close()
    fsourcedefreq.close()
    fsourcecase.close()
    fsourceOn.close()
    fsourcereq.close()
    fsourcepro.close()

if __name__ == '__main__':
    main()