#include "Display.h"

Display::Display(LCD* lcd)
  : m_cols(16)
  , m_rows(2)
  , m_currentCol(0)
  , m_currentRow(0)
  , m_lcd(lcd)
{
  m_lcd->clear();
  reset();
}


void Display::setCursor(uint8_t col, uint8_t row) {
  if(col >= 0 && col < m_cols)
    m_currentCol = col;

  if(row >= 0 && row < m_rows)
    m_currentRow = row;
}

void Display::print(const char* string) {
  for (uint8_t i = 0; string[i] != 0 && m_currentCol + i < m_cols; i++) {
    m_chars[m_currentRow][m_currentCol + i] = string[i];
  }
}

void Display::println(const char* str, uint8_t row, EDecor decoration, EAlign alignment) {
  uint8_t length = 0;
  while (str[length] != 0) length ++;

  uint8_t start = 0;
  switch (alignment) {
    case EAlign::Left:
      start = 0;
      break;
    case EAlign::Mid:
      start = (m_cols - length) / 2;
      break;
    case EAlign::Right:
      start = (m_cols - length);
      break;
  }

  for (uint8_t i = 0; i < m_cols; i++) {
    m_chars[row][i] = ' ';
  }

  for (uint8_t i = 0; i < length && i < m_cols; i++) {
    m_chars[row][i + start] = str[i];
  }

  if (decoration == EDecor::Left  || decoration == EDecor::Both) m_chars[row][0] = '<';
  if (decoration == EDecor::Right || decoration == EDecor::Both) m_chars[row][m_cols - 1] = '>';
  if (decoration == EDecor::Selected) { m_chars[row][0] = '='; m_chars[row][m_cols - 1] = '='; }
}



void Display::print(char c)
{
  m_chars[m_currentRow][m_currentCol] = c;
}

void Display::update()
{ 
  for (uint8_t row = 0; row < m_rows; row++) {
    m_lcd->setCursor(0, row);
  
    for (uint8_t col = 0; col < m_cols; col++) {
      m_lcd->print(m_chars[row][col]);
    }
  }
}

void Display::reset() {
  for (uint8_t row = 0; row < m_rows; row++) {
    for (uint8_t col = 0; col < m_cols; col++) {
      m_chars[row][col] = ' ';
    }
  }
}