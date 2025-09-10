#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "GameManager.h"
#include "ItemManager.h"

using namespace std;

int main()
{
#ifdef _WIN32
    // 콘솔 입출력 코드페이지를 UTF-8로
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // GameManager::InitGame() 안으로 오실래요 ?
    ItemManager::GetInstance().Init();

    GameManager::Instance().StartGame();
}
