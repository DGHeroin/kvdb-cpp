#include "kvdb.h"

#include <sstream>
#include <assert.h>
#include <iostream>
using namespace std;

/**
 * @brief URL Decode算法字符转成16进制
 * @param unsigned char x
 * @return unsigned char
 */
static unsigned char to_hex(unsigned char x){
    return (x > 9) ? (x + 55) : (x + 48);
}

/**
 * @brief URL Decode算法16进制转成字符
 * @param unsigned char x
 * @return unsigned char
 */
static unsigned char from_hex(unsigned char x){
    unsigned char y;
    if (x >= 'A' && x <= 'Z')      y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

/**
 * @brief URLEncode
 * @param const char* data 输入字节流
 * @param size_t lenght    输入字节流长度
 * @return std::string
 */
std::string URLEncode(const char* data, size_t lenght){
    std::string temp = "";

    for (size_t i = 0; i < lenght; i++){
        temp += "%";
        temp += to_hex ((unsigned char)data[i] >> 4);
        temp += to_hex ((unsigned char)data[i] % 16);
    }
    return temp;
}

/**
 * @brief URLDecode
 * @param const char* data 输入字节流
 * @param size_t lenght    输入字节流长度
 * @return std::string
 */
std::string URLDecode(const char* str, size_t lenght){
    std::string temp = "";
    for (size_t i = 0; i < lenght; i++){
        if (str[i] == '%'){
            assert(i + 2 < lenght);
            unsigned char high = from_hex ((unsigned char)str[++i]);
            unsigned char low  = from_hex ((unsigned char)str[++i]);
            temp += high*16 + low;
        }
    }
    return temp;
}
/**
 * @brief StringSplit 字符串切分函数
 * @param const std::string& str         被切分字符串
 * @param char delim                     分隔符
 * @param std::vector<std::string> elems 切分后存放在这个vector
 */
void StringSplit(const std::string&str, char delim, std::vector<std::string>&elems){
    std::stringstream ss;
    ss.str(str);
    string item;
    while (std::getline(ss, item, delim)){
        elems.push_back (item);
    }
}

/**
 * @brief KVDB::add 添加Key Value对
 * @param const Variant& key
 * @param const Variant& value
 */
void KVDB::add (const Variant &key, const Variant &value){
    this->mapping.insert (std::pair<string, string>(key.to_string (), value.to_string ()));
}
/**
 * @brief KVDB::get 获取Value
 * @param const Variant& key
 * @return Variant
 */
Variant KVDB::get (const Variant& key) const{
    Variant var;
    std::hash_map<std::string, std::string>::const_iterator it  = this->mapping.find (key.to_string ());
    if(it != this->mapping.end ()){
        var.from_string (it->second);
    }
    return var;
}
/**
 * @brief KVDB::unset 按key删除元素
 * @param const Variant& key
 */
void KVDB::unset (const Variant &key){
    this->mapping.erase (key.to_string ());
}

/**
 * @brief KVDB::clear 清空整个DB
 */
void KVDB::clear(){
    this->mapping.clear ();
}

/**
 * @brief Variant::add 添加字节流
 * @param const char* data
 * @param size_t lenght
 */
void Variant::add (const char *data, size_t lenght){
    string val = URLEncode (data, lenght);
    this->vars.push_back (val);
}
/**
 * @brief Variant::get 按偏移获取Variant中的字节流
 * @param size_t index
 * @return std::string
 */
std::string Variant::get (size_t index){
    if (index < this->vars.size ()) {
        string temp = this->vars[index];
        return URLDecode (temp.c_str (), temp.size ());
    }
    return "";
}

/**
 * @brief Variant::to_string 转成字符串
 * @return std::string
 */
std::string Variant::to_string () const{
    std::string temp = "";
    for(size_t i = 0; i < this->vars.size (); i++){
        if (i + 1 < this->vars.size())
            temp += this->vars[i] + ",";
        else
            temp += this->vars[i];
    }
    return temp;
}

/**
 * @brief Variant::from_string 字符串转成Variant
 * @param const string& str
 */
void Variant::from_string(const string &str){
    this->vars.clear ();
    StringSplit (str, ',', this->vars);
}
