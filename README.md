# kvdb
一百行代码写一个内存型Key Value Database

设计思路：
###Variant类
管理所有二进制数据。二进制数据全部转成URL Encode的字符串，牺牲了内存与计算资源，但引入极大便利性。

###KVDB类
通过hash_map<std::string, std::string>管理key/value,
key和value中的数据对应是一个元组。
