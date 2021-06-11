#pragma once

#include <inttypes.h>

class MyString
{
public:
  MyString();
  MyString(char a_char);
  MyString(const char* a_cStr);
  ~MyString();

  operator const char* () const;
  char at(uint64_t index) const { if (index > m_length) return 0; return m_str[index]; }

  MyString& append(MyString str);
  MyString& operator+ (MyString str) { return append(str); }
  void operator= (const char* str) { append(str); };

  MyString& insert(uint64_t index, MyString str);
  MyString& remove(MyString what);
  MyString& replace(MyString what, MyString with);
  
  MyString& arg(MyString str);
  MyString& arg(uint64_t number);
  MyString& arg(bool a_bool);

  inline uint64_t length() const { return m_length; };
  bool contains(MyString str) const;
  int64_t indexOf(MyString str, int64_t from = 0) const;
  int64_t lastIndexOf(MyString str, int64_t from = -1) const;

  static MyString number(int64_t number);

private:
  void remove(int64_t index, uint64_t length);
  void replace(int64_t index, MyString what, MyString with);
  uint64_t length(const char* a_cStr) const;

private:
  char* m_str;
  uint64_t m_length;
};