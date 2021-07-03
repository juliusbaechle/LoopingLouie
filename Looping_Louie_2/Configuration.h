#pragma once

#include "CSingletonTemplate.h"
#include "Signal.h"
#include <HardwareSerial.h>

#define cfg Configuration::GetInstance()

#define ADDR_REVERSE      (uint8_t*) 0x0
#define ADDR_MAXTHRUST    (uint8_t*) 0x1
#define ADDR_MODE         (uint8_t*) 0x2
#define ADDR_DRINK        (uint8_t*) 0x3
#define ADDR_COOLDOWN     (uint8_t*) 0x4
#define ADDR_BRIGHTNESS   (uint8_t*) 0x5
#define ADDR_BOOST_MODE   (uint8_t*) 0x6
#define ADDR_BOOST_ACTION (uint8_t*) 0x7

template<typename T>
class Property {
public:
  Property(const char* name, uint8_t* addr) {
    m_value = eeprom_read_byte(addr);
    m_addr = addr;
    m_name = name;
  }

  Signal<T> sglChanged;

  void operator=(T value) { 
    Serial.print("Set "); Serial.print(m_name); Serial.print(" to "); Serial.println(m_value);
    if (m_value == value)
      return;

    m_value = value; 
    sglChanged.emit(m_value);
    eeprom_write_byte(m_addr, value);
  }

  operator T() const { 
    return m_value; 
  }

private:
  T m_value = T();
  uint8_t* m_addr = 0x0;
  const char* m_name = nullptr;
};

class Configuration : public CSingletonTemplate<Configuration> {
  friend class CSingletonTemplate<Configuration>;

public:
  Property<bool>    turnReverse = Property<bool>   ("Reverse"     , ADDR_REVERSE     );
  Property<uint8_t> mode        = Property<uint8_t>("Mode"        , ADDR_MODE        );
  Property<uint8_t> maxThrust   = Property<uint8_t>("Max Thrust"  , ADDR_MAXTHRUST   );
  Property<uint8_t> boostAction = Property<uint8_t>("Boost Action", ADDR_BOOST_ACTION);
  Property<uint8_t> boostMode   = Property<uint8_t>("Boost Mode"  , ADDR_BOOST_MODE  );
  Property<uint8_t> cooldown    = Property<uint8_t>("Cooldown"    , ADDR_COOLDOWN    );
  Property<uint8_t> brightness  = Property<uint8_t>("Brightness"  , ADDR_BRIGHTNESS  );
  Property<uint8_t> drinkMode   = Property<uint8_t>("Drink"       , ADDR_DRINK       );

public:
  void reset();

private:
  Configuration() {};
  ~Configuration() {};
  Configuration(Configuration&) {};
};