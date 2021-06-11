#include "DrinkMenu.h"
#include "DrinkDisplay.h"

DrinkItem** DrinkItem::createItems() {
  DrinkItem** drinkItems = new DrinkItem * [4];

  #ifdef FOR_THOMAS
    for (int i = 0; i < 4; i++) {
      drinkItems[i] = new DrinkDisplay(Displays::getExtraDisplay(i));
    }
  #else  
    for (int i = 0; i < 4; i++) {
      drinkItems[i] = new DrinkMenu(i);
    }
  #endif

  return drinkItems;
}