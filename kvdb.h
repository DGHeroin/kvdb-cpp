#ifndef __KVDB_H__
#define __KVDB_H__

#include <vector>
#include <string>
#include <hash_map>

// URL Encode/Decode
std::string URLEncode(const char *data, size_t lenght);
std::string URLDecode(const char* str, size_t lenght);

/**
 * @brief 变量类，容纳各种二进制类型
 */
class Variant{
public:
    void add(const char* data, size_t lenght);
    std::string get(size_t index);
    std::string to_string() const;
    void from_string(const std::string& str);
    void operator =(const Variant& rhs) { this->vars = rhs.vars; }
private:
    std::vector<std::string> vars;
};

/**
 * @brief KVDB
 */
class KVDB{
public:
    void add(const Variant &key, const Variant &value);
    Variant get(const Variant& key) const;
    void unset(const Variant& key);
    void clear();
private:
    std::hash_map<std::string, std::string> mapping;
};

#endif __KVDB_H__
