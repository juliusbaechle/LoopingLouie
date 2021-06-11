#include "MyString.h"

MyString::MyString()
{
  m_length = 0;
  m_str = new char[1];
  m_str[0] = 0;
}

MyString::MyString(char a_char)
{
  m_length = 1;
  m_str = new char[2];
  m_str[0] = a_char;
  m_str[1] = 0;
}

MyString::MyString(const char* a_cStr)
{
  m_length = length(a_cStr);
  m_str = new char[m_length + 1];
  for (uint64_t i = 0; i < m_length; i++)
    m_str[i] = a_cStr[i];
  m_str[m_length] = 0;
}

MyString::~MyString() {
  delete[] m_str;
}

MyString::operator const char* () const
{
  return m_str;
}

uint64_t MyString::length(const char* a_cStr) const
{
  uint64_t length = 0;
  while (a_cStr[length] != 0) length++;
  return length;
}

MyString& MyString::append(MyString str)
{  
  char* tempArr = new char [m_length + str.length() + 1];

  for (uint64_t i = 0; i < m_length; i++)
    tempArr[i] = m_str[i];

  for (uint64_t i = m_length; i < m_length + str.length(); i++)
    tempArr[i] = str.m_str[i - m_length];

  tempArr[m_length + str.length()] = 0;

  delete[] m_str;
  m_str = tempArr;
  m_length += str.length();

  return (*this);
}

MyString& MyString::insert(uint64_t index, MyString str)
{
  char* tempArr = new char[m_length + str.length() + 1];
  
  for (uint64_t i = 0; i < index; i++)
    tempArr[i] = m_str[i];

  for (uint64_t i = index; i < index + str.length(); i++)
    tempArr[i] = str.m_str[i - index];

  for (uint64_t i = index + str.length(); i < m_length + str.length(); i++)
    tempArr[i] = m_str[i - str.length()];

  tempArr[m_length + str.length()] = 0;

  delete[] m_str;
  m_str = tempArr;
  m_length += str.length();

  return (*this);
}

int64_t MyString::indexOf(MyString a_str, int64_t from) const
{
  for (uint64_t i = from; i < (m_length + 1) - a_str.length(); i++)
  {
    bool matches = true;

    for (uint64_t j = 0; j < a_str.length(); j++)
      matches &= (m_str[i + j] == a_str[j]);
    
    if (matches) return i;
  }

  return -1;
}

int64_t MyString::lastIndexOf(MyString a_str, int64_t from) const
{
  if (from == -1) from = m_length;

  for (int64_t i = from - a_str.length() - 1; i >= 0; i--)
  {
    bool matches = true;

    for (uint64_t j = 0; j < a_str.length(); j++)
      matches &= (m_str[i + j] == a_str[j]);

    if (matches) return i;
  }

  return -1;
}

bool MyString::contains(MyString a_str) const
{
  return indexOf(a_str) > 0;
}

MyString& MyString::remove(MyString a_str)
{
  int64_t index = 0;
  while ((index = indexOf(a_str)) > 0)
    remove(index, a_str.length());
  return (*this);
}

void MyString::remove(int64_t index, uint64_t length)
{
  char* tempArr = new char[(m_length + 1) - length];

  for (uint64_t i = 0; i < index; i++)
    tempArr[i] = m_str[i];

  for (uint64_t i = index; i < m_length - length; i++)
    tempArr[i] = m_str[i + length];

  tempArr[m_length - length] = 0;

  delete[] m_str;
  m_str = tempArr;
  m_length -= length;
}

MyString& MyString::replace(MyString what, MyString with)
{
  int64_t index = indexOf(what);
  while (index > 0) {
    replace(index, what, with);
    index = indexOf(what);
  }    
  return (*this);
}

void MyString::replace(int64_t index, MyString what, MyString with)
{
  if (index < 0) return;

  char* tempArr = new char[(m_length + with.length() + 1) - what.length()];

  //copy arr until index
  for (uint64_t i = 0; i < index; i++)
    tempArr[i] = m_str[i];

  //append with
  for (uint64_t i = index; i < index + with.length(); i++)
    tempArr[i] = with.m_str[i - index];

  //append rest of m_str
  for (uint64_t i = index + with.length(); i < m_length + ((int64_t)with.length() - what.length()); i++)
    tempArr[i] = m_str[i + ((int64_t)what.length() - with.length())];

  tempArr[(m_length + with.length()) - what.length()] = 0;

  delete[] m_str;
  m_str = tempArr;
  m_length += (int64_t)with.length() - what.length();
}

MyString& MyString::arg(MyString str)
{
  int64_t index = 0;
  char lowestNumber = '9';

  while (index >= 0)
  {
    index = indexOf("%", index + 1);
    if (index == -1) break;

    char number = at(index + 1);
    if (number < lowestNumber) {
      lowestNumber = number;
    }      
  }

  char positioner[3];
  positioner[0] = '%';
  positioner[1] = lowestNumber;
  positioner[2] = 0;

  MyString what("%");
  what.append(lowestNumber);
  replace(what, str);
  return(*this);
}


static inline uint64_t pow(uint8_t i) { return i > 0 ? 10 * pow(i - 1) : 1; }

MyString MyString::number(int64_t number) {
  bool negative = number < 0;
  if (negative) number = -number;

  char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

  uint8_t nrDigits = 1;
  while (pow(nrDigits) < number) nrDigits++;

  char str[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  for (uint8_t i = 0; i < nrDigits; i++) {
    uint64_t temp = number;     //1234
    uint64_t div = pow(i);
    temp /= div;                //1234 / 10 = 123
    temp %= 10;                //123 % 10 = 3

    str[nrDigits - (i + 1)] = digits[temp];
  }
  str[nrDigits + 1] = 0;

  if (negative) 
    return MyString("-") + MyString(str);
  
  return MyString(str);
}


MyString& MyString::arg(uint64_t number) {
  return arg(MyString::number(number));
}

MyString& MyString::arg(bool a_bool) {
  MyString str;
  if (a_bool)  str = "1";
  else         str = "0";

  return arg(str); 
};