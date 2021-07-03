#include "DrinkMenu.h"
#include "DrinkDisplay.h"
#include "Displays.h"

DrinkItem** DrinkItem::createItems() {
  DrinkItem** drinkItems = new DrinkItem * [4];

#ifdef JULIUS
  for (int i = 0; i < 4; i++)
    drinkItems[i] = new DrinkMenu(i);
#else
  for (int i = 0; i < 4; i++)
    drinkItems[i] = new DrinkDisplay(i);
#endif

  return drinkItems;
}