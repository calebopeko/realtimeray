#include "tml.h"

#include <cstring>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <fstream>

#include <iostream>

namespace tml {

  const std::string space=" \t";
  const std::string empty="";

  static inline char* duplicateString(const char* value)
  {
    unsigned int length = (unsigned int)strlen(value);
    char *newString = static_cast<char *>( malloc( length + 1 ) );
    memcpy( newString, value, length );
    newString[length] = 0;
    return newString;
  }

  static inline ArrayType* duplicateArray(const ArrayType* array)
  {
    return new ArrayType(*array);
  }

  static inline MapType* duplicateMap(const MapType* map)
  {
    return new MapType(*map);
  }

  static std::string trimString(const std::string& s)
  {
    size_t tmp = s.find_first_not_of(space);
    if(tmp>=s.size()){
      return empty;
    }
    return std::string(s, tmp, s.find_last_not_of(space)-tmp+1);
  }

  Value::Value(ValueType type)
    : allocated_(true), type_(type)
  {
    switch(type) {
    case Value_NULL:
    case Value_String:
      value_.string_ = duplicateString("");
      break;
    case Value_Array:
      value_.array_ = new ArrayType();
      break;
    case Value_Map:
      value_.map_ = new MapType();
      break;
    default:
      assert(0);
      break;
    }
  }

  Value::Value(const std::string& path)
    : allocated_(false), type_(Value_NULL)
  {
    parse(path);
  }

  template <typename T>
  Value::Value(T v)
    : allocated_(true), type_(Value_String)
  {
    std::stringstream s;
    s << v;
    value_.string_ = duplicateString(s.str().c_str());
  }

  Value::Value(const Value& other)
    : allocated_(other.allocated_), type_(other.type_)
  {
    switch ( type_ ) {
    case Value_NULL:
    case Value_String:
      value_.string_ = duplicateString(other.value_.string_);
      break;
    case Value_Array:
      value_.array_ = duplicateArray(other.value_.array_);
      break;
    case Value_Map:
      value_.map_ = duplicateMap(other.value_.map_);
      break;
    default:
      assert(0);
      break;
    }
  }

  Value& Value::operator()(const std::string& key) const { return get(key); }
  Value& Value::operator()(int index) const { return get(index); }

  Value& Value::get(const std::string& key) const
  {
    assert(isMap());
    return (*(value_.map_))[key];
  }

  Value& Value::get(int index) const
  {
    assert(isArray());
    return (*(value_.array_))[index];
  }

  Value::operator bool() const
  {
    return asBool();
  }


  Value::operator int() const
  {
    return asInt();
  }

  Value::operator float() const
  {
    return asFloat();
  }

  Value::operator double() const
  {
    return asDouble();
  }

  Value::operator std::string() const
  {
    return asString();
  }

  bool Value::asBool() const
  {
    assert(isAllocated());
    switch ( type_ ) {
    case Value_String:
      {
	std::stringstream sstream(value_.string_);
	bool v;
	sstream >> v;
	assert(!sstream.bad());
	return v;
      }
    case Value_NULL:
    case Value_Array:
    case Value_Map:
    default:
      return false;
    }
  }

  int Value::asInt() const
  {
    assert(isAllocated());
    switch ( type_ ) {
    case Value_String:
      {
	std::stringstream sstream(value_.string_);
	int v;
	sstream >> v;
	assert(!sstream.bad());
	return v;
      }
    case Value_NULL:
    case Value_Array:
    case Value_Map:
    default:
      return 0;
    }
  }

  double Value::asDouble() const
  {
    assert(isAllocated());
    switch ( type_ ) {
    case Value_String:
      {
	std::stringstream sstream(value_.string_);
	double v;
	sstream >> v;
	assert(!sstream.bad());
	return v;
      }
    case Value_NULL:
    case Value_Array:
    case Value_Map:
    default:
      return 0.0;
    }
  }

  float Value::asFloat() const
  {
    assert(isAllocated());
    switch ( type_ ) {
    case Value_String:
      {
	std::stringstream sstream(value_.string_);
	float v;
	sstream >> v;
	assert(!sstream.bad());
	return v;
      }
    case Value_NULL:
    case Value_Array:
    case Value_Map:
    default:
      return 0.0;
    }
  }

  std::string Value::asString() const
  {
    assert(isAllocated());
    switch ( type_ ) {
    case Value_String:
      return std::string(value_.string_);
    case Value_NULL:
    case Value_Array:
    case Value_Map:
    default:
      return std::string("");
    }
  }

  bool Value::isAllocated() const
  {
    return allocated_;
  }

  bool Value::isString() const
  {
    assert(isAllocated());
    return type_ == Value_String;
  }

  bool Value::isArray() const
  {
    assert(isAllocated());
    return type_ == Value_Array;
  }

  bool Value::isMap() const
  {
    assert(isAllocated());
    return type_ == Value_Map;
  }

  size_t Value::size() const
  {
    assert(isArray());
    return (*(value_.array_)).size();
  }

  bool Value::exists(const std::string& key) const
  {
    assert(isMap());
    return (*(value_.map_)).find(key) != (*(value_.map_)).end();
  }

  void Value::push_back(const Value& v)
  {
    assert(isArray());
    (*(value_.array_)).push_back(v);
  }

  void Value::insert(const std::string& key, const Value& v)
  {
    assert(isMap());
    (*(value_.map_))[key] = v;
  }

  void Value::dump(std::ostream& s) const
  {
    if ( allocated_ ) {
      switch(type_) {
      case Value_NULL:
	s << "NULL; ";
	break;
      case Value_String:
	s << value_.string_ << "; ";
	break;
      case Value_Array:
	{
	  s << "[ ";
	  ArrayType& array = *(value_.array_);
	  for ( unsigned int i = 0; i < array.size(); i++ ) {
	    array[i].dump(s);
	  }
	  s << "]; ";
	  break;
	}
      case Value_Map:
	{
	  s << "{ ";
	  MapType& map = *(value_.map_);
	  for ( MapType::const_iterator i = map.begin(); i != map.end(); ++i ) {
	    s << (i->first) << " = ";
	    (i->second).dump(s);
	  }
	  s << "}; ";
	  break;
	}
      }
    }
  }

  void Value::dumpPretty(std::ostream& s, int depth) const
  {
    if ( allocated_ ) {
      switch(type_) {
      case Value_NULL:
	s << std::string(depth, ' ') << "NULL;" << std::endl;
	break;
      case Value_String:
	s << std::string(depth, ' ') << value_.string_ << ";" << std::endl;
	break;
      case Value_Array:
	{
	  s << std::string(depth, ' ') << "[" << std::endl;
	  ArrayType& array = *(value_.array_);
	  for ( unsigned int i = 0; i < array.size(); i++ ) {
	    array[i].dumpPretty(s, depth+2);
	  }
	  s << std::string(depth, ' ') << "];" << std::endl;
	  break;
	}
      case Value_Map:
	{
	  s << std::string(depth, ' ') << "{" << std::endl;
	  MapType& map = *(value_.map_);
	  for ( MapType::const_iterator i = map.begin(); i != map.end(); ++i ) {
	    s << std::string(depth, ' ') << (i->first) << " = ";
	    (i->second).dumpPretty(s, depth+2);
	  }
	  s << std::string(depth, ' ') << "};" << std::endl;
	  break;
	}
      }
    }
  }

  void Value::deallocate()
  {
    if ( allocated_ ) {
      switch(type_) {
      case Value_String:
	free(value_.string_);
	break;
      case Value_Array:
	delete value_.array_;
	break;
      case Value_Map:
	delete value_.map_;
	break;
      default:
	break;
      }
    }
    allocated_ = false;
  }

  Value::~Value()
  {
    deallocate();
  }
  
  void Value::parse(const std::string& file)
  {
    std::ifstream is;
    is.open(file.c_str(), std::ios::binary);

    is.seekg(0, std::ios::end);
    long length = is.tellg();
    is.seekg (0, std::ios::beg);

    char *buffer = new char [length];

    is.read (buffer,length);
    std::istringstream iss(buffer);

    delete [] buffer;
    is.close();

    parse(iss);
  }

  void Value::parseMap(std::istringstream& is)
  {
    assert(isMap());
    while ( is.good() && !is.eof() ) {
      is >> std::ws;
      char c = is.peek();
      if ( c == '}' ) return;
      std::string key;
      getline(is, key, '=');
      key = trimString(key);
      Value& val = (*(value_.map_))[key];
      val.parse(is);
    }
  }

  void Value::parseArray(std::istringstream& is)
  {
    assert(isArray());
    while ( is.good() && !is.eof() ) {
      is >> std::ws;
      char c = is.peek();
      if ( c == ']' ) return;
      Value val;
      val.parse(is);
      (*(value_.array_)).push_back(val);
    }
  }

  void Value::parse(std::istringstream& is)
  {
    deallocate();
    
    if ( is.good() && !is.eof() ) {

      is >> std::ws;
      char c = is.peek();
      switch (c) {
      case '{':
	{
	  // map
	  is.ignore(1);
	  type_ = Value_Map;
	  value_.map_ = new MapType;
	  allocated_ = true;
	  parseMap(is);
	  std::string tmp;
	  getline(is, tmp, ';');
	}
	break;
      case '[':
	{
	  // array
	  is.ignore(1);
	  type_ = Value_Array;
	  value_.array_ = new ArrayType;
	  allocated_ = true;
	  parseArray(is);
	  std::string tmp;
	  getline(is, tmp, ';');
	}
	break;
      default:
	{
	  // string
	  std::string tmp;
	  getline(is, tmp, ';');
	  type_ = Value_String;
	  value_.string_ = duplicateString(trimString(tmp).c_str());
	  allocated_ = true;
	}
	break;
      }
    }
  }
}

std::ostream& operator<<(std::ostream& o, const tml::Value& v)
{
  v.dump(o);
  return o;
}
