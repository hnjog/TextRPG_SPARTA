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

public:
    void StartGame();

private:
    void Battle();
    void ShowInventory();
    void UseShop();
};

