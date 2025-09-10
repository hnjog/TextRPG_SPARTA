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
    class Player* player;
    
private:
    void InitGame();

    void InitPlayer();
    bool GetIsNameValid(const string& input);

public:
    void StartGame();
};

