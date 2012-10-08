// -*- C++ -*-
#ifndef TML_H
#define TML_H

#include <string>
#include <vector>
#include <map>

namespace tml
{
  class Value;
  
  typedef std::map<std::string, Value> MapType;
  typedef std::vector<Value> ArrayType;

  enum ValueType {
    Value_NULL,
    Value_String,
    Value_Array,
    Value_Map
  };

  union ValueHolder
  {
    char* string_;
    ArrayType* array_;
    MapType* map_;
  };

  class Value
  {
  public:

    Value(ValueType type = Value_NULL);
    Value(const std::string& path);

    template <typename T>
    Value(T v);

    Value(const Value& other);
    
    Value& operator()(const std::string& key) const;
    Value& operator()(int index) const;
    Value& get(const std::string& key) const;
    Value& get(int index) const;

    bool asBool() const;
    int asInt() const;
    float asFloat() const;
    double asDouble() const;
    std::string asString() const;

    operator bool() const;
    operator int() const;
    operator float() const;
    operator double() const;
    operator std::string() const;

    void dump(std::ostream& s) const;
    void dumpPretty(std::ostream& s, int depth) const;

    bool isAllocated() const;
    bool isString() const;
    bool isArray() const;
    bool isMap() const;

    // array helper functions:
    size_t size() const;
    void push_back(const Value& v);

    // map helper functions:
    bool exists(const std::string& key) const;
    void insert(const std::string& key, const Value& v);

    // parser:
    void parse(const std::string& file);

    virtual ~Value();

  private:

    void parse(std::istringstream& is);
    void parseMap(std::istringstream& is);
    void parseArray(std::istringstream& is);
    
    void deallocate();

  private:

    bool allocated_;

    ValueType type_;

    ValueHolder value_;
  };
}

std::ostream& operator<<(std::ostream& o, const tml::Value& v);

typedef tml::Value Parser;
typedef tml::Value Value;

#endif
