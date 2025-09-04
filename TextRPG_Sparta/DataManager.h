// DataManager.h
#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "JsonParser.h"

#include "ItemData.h"
#include "ShopData.h"
#include "EnemyData.h"

class DataManager {
public:
    static DataManager& GetInstance();

    // 부팅 시 1회
    bool Initialize();

    // 소유권 이전(move-out). 두 번째 호출부터는 빈 벡터가 나감.
    std::vector<ItemData> TakeItems();
    std::vector<ShopData> TakeShopDatas();
    std::vector<EnemyData> TakeEnemyDatas();

private:
    DataManager() = default;
    ~DataManager() = default;
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

    // 파일/경로/파싱 헬퍼
    std::string ResolveFromResourcesOutput(const std::string& relative) const;
    std::string ReadFileToString(const std::string& pathUtf8) const;
    JsonValue   ParseJsonFile(const std::string& pathUtf8) const;

    // 개별 로더
    void LoadItemsJson(const JsonValue& root);
    void LoadShopJson(const JsonValue& root);
    void LoadEnemyJson(const JsonValue& root);

#ifdef _WIN32
    std::string  ToUtf8(const std::wstring& w) const;
    std::wstring ToWide(const std::string& u8) const;
#endif

private:
    bool initialized = false;

    std::vector<ItemData> itemDataVector;
    std::vector<ShopData> shopDataVector;
    std::vector<EnemyData> enemyDataVector;
};
