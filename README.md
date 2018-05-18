这是xtp的win32bit 封装过程
***

手动检查是否有**MIGHT WRONG**, 所有捕获错误的内容都是重置为这个;
TdApi主动函数中XTP_XXX_TYPE的类型是enum类型, 手动指定具体枚举类型;

***

* datatype
    1. 枚举类型的数据保持枚举类型;
    2. 修改了源文件的{位置方便;
    3. 需要删除第一个#define的结果;

* datastruct
    1. xquote_api_struct里面的union数据结构 没有使用,在
        *XTPTBT* 这个struct内部, 需要手动修改;
    2. 数组类型数据没有做其他处理, 主要是DepthMarketData还有订单不里面;
        这个留到*process_cpp*里面对structDict的key进行遍历处理;
***
### API
*  主动函数实现req.cpp
    1. 需要补充createapi的函数;
    2.
    1. 返回类型是**定义结构体**的函数需要手动去处理:getApiLastError;
    2. 非visual开头的createApi函数, 自建exit函数需要手动写入;
    3. 注册Api函数不需要;
    4. 返回类型是引用类型的char
    5. 他们把 exchange_id 写成了 exchage_id

-----------------------
TODO
1. process_cpp 中数组数据是否长度为10需要验证;




