__author__ = 'HsuPin'

# c++类型到python类型的映射
typedict = {
    'int': 'int',
    'short': 'int',
    'double': 'float',
    'char': 'string'
}


def preprocess(line):
    """使用一个空格代替tab"""
    line = line.replace('\t', ' ')
    line = line[:-1]
    line = line.replace(';', '')
    try:
        return line[:line.index('[')]
    except ValueError:
        return line


def handle_comment(line):
    return '#' + line + '\n'


def handle_define(line):
    """这里第一个需要手动更改"""
    l = line.split(' ')
    pyline = '{} = {}\n'.format(l[1], l[-1])
    return pyline


def handle_typedef_char(line):
    l = line.split(' ')

    pyline = 'typedefDict[\'{}\'] = "{}"\n'.format(l[-1], typedict[l[1]])
    return pyline


def handle_typedef_enum(line):
    l = line.split(' ')
    pyline = 'typedefDict[\'{}\'] = "{}"\n'.format(l[-1], l[1])
    return pyline


def main():
    f1 = 'xtp\\xtp_api_data_type.h'
    f2 = 'ojbk\\xtp_api_data_type.py'

    f1 = open(f1, 'r', encoding='GBK')
    f2 = open(f2, 'w', encoding='UTF-8')

    f2.write('#encoding: UTF-8\n')
    f2.write('typedefDict = {}\n')

    lines = f1.readlines()
    for line in lines:
        cpp_line = preprocess(line)
        if cpp_line.startswith('///'):
            pyline = handle_comment(cpp_line)
        elif cpp_line.startswith('#define'):
            pyline = handle_define(cpp_line)
        elif cpp_line.startswith('typedef char'):
            pyline = handle_typedef_char(cpp_line)
        elif cpp_line.startswith('typedef enum'):
            pyline = handle_typedef_enum(cpp_line)
        else:
            pyline = ''

        f2.write(pyline)

    f1.close()
    f2.close()


if __name__ == '__main__':
    main()
