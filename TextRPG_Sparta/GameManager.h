#include "ShopBase.h"

class GameManager
{
public:
    static GameManager& Instance();

private:
    GameManager() {}
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

private:
    //캐릭터 Character
    //몬스터 vector<T>
    class Player* player;
    
public:
    void InitGame();
    void StartGame();

private:
    bool GetIsNameValid(const string& input);
};

