__author__ = 'HsuPin'

from ojbk.xtp_api_data_type import typedefDict


type_dict = {
    'uint64_t': 'uint64_t',
    'uint32_t': 'uint32_t',
    'int64_t': 'int64_t',
    'int32_t': 'int32_t',
    'char': 'string',
    'double': 'float'
}


def preprocess(line):
    """去除结尾符"""
    cppline = line.replace('\t', ' ').replace('\n', '').replace(';', '')
    cppline = cppline.strip(' ')
    return cppline


def handle_struct(line):
    dict_name = line.split(' ')[1]
    pyline = '{} = OrderedDict()\n'.format(dict_name)
    return dict_name, pyline


def handle_datatype(structname, line):
    """结构体数据类"""
    l = line.split(' ')
    newl = [i for i in l if i]
    pyline = '{}[\'{}\'] = "{}"\n'.format(structname, newl[1], typedefDict[newl[0]])
    return pyline


def handle_typedef(line):
    """两种typedef"""
    l = line.split(' ')
    if len(l) == 4:
        structname = l[-1]
        pyline = 'structDict[\'{}\'] = {}\n'.format(l[-1], l[-2])
    else:
        structname, pyline = handle_struct(line[line.index('struct'):])
    return structname, pyline


def handle_end(structname):
    pyline = 'structDict[\'{}\'] = {}\n\n\n\n'.format(structname, structname)
    return pyline


def main(f1, f2):
    typedefDict.update(type_dict)

    f1 = open(f1, 'r', encoding='gbk')
    f2 = open(f2, 'a', encoding='utf-8')

    f2.write('#encoding: UTF-8\n')
    f2.write('\n')
    f2.write('from collections import OrderedDict\n')
    f2.write('\n')
    f2.write('structDict = {}\n')

    structname = 'whatever'

    lines = f1.readlines()
    for line in lines:

        cppline = preprocess(line)
        if cppline.startswith('//'):
            pyline = cppline.replace('/', '#') + '\n'
        elif  cppline.startswith('struct'):
            structname, pyline = handle_struct(cppline)
        elif cppline.startswith('typedef'):
            # 第二种
            structname, pyline = handle_typedef(cppline)
        elif cppline == '' or cppline.startswith('#') or cppline.startswith('{'):
            # 以#开头, {, }, 空行
            pyline = ''
        elif cppline.startswith('}'):
            pyline = handle_end(structname)

        else:
            # 处理数据行
            pyline = handle_datatype(structname, cppline)
        f2.write(pyline)

    f1.close()
    f2.close()


if __name__ == '__main__':
    f1 = 'xtp\\xoms_api_struct.h'
    f2 = 'ojbk\\xoms_fund_struct.py'
    main(f1, f2)
