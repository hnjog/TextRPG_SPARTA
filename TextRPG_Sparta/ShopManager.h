#include "ShopBase.h"

class ShopManager {
public:
    static ShopManager& Instance();

private:
    ShopManager() {}
    ShopManager(const ShopManager&) = delete;
    ShopManager& operator=(const ShopManager&) = delete;

    ShopBase shop;

public:
    void InitShop();
    void VisitShop(class Player* player);

};