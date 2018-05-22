这是xtp的win32bit 封装过程
***
以下是需要注意的项

* 手动检查是否有**MIGHT WRONG**, 所有捕获错误的内容都是重置为这个;
* TdApi主动函数中XTP_XXX_TYPE的类型是enum类型, 手动指定具体枚举类型;
* processTickByTick 返回的共用类型需要手动修改;

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