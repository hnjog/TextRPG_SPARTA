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

private:
    /// <summary>
    /// 상점 입장에서 Player아이템 매입
    /// </summary>
    /// <param name="player">방문한 플레이어</param>
    void Purchase(class Player* player);

    /// <summary>
    /// 상점 입장에서 Player아이템 매도
    /// </summary>
    /// <param name="player">방문한 플레이어</param>
    void Sell(class Player* player);

};