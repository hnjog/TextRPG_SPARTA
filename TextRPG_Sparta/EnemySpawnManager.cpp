#include "EnemySpawnManager.h"

// --- 싱글턴 ---
EnemySpawnManager& EnemySpawnManager::GetInstance() {
    static EnemySpawnManager instance;
    return instance;
}

int EnemySpawnManager::LoadFromDataManager(DataManager& dm)
{
    std::vector<EnemyData> list;

    // 벡터 index 데이터 index 맞추기 (1부터 시작)
    int maxIdx = -1;
    for (const auto& d : list) {
        if (d.idx > maxIdx) maxIdx = d.idx;
    }

    enemyDB.clear();
    if (maxIdx >= 0) {
        enemyDB.resize(static_cast<size_t>(maxIdx + 1));
    }

    // 해당 index 에직접 저장
    for (const auto& d : list) {
        if (d.idx < 0) continue;
        if (static_cast<size_t>(d.idx) >= enemyDB.size()) {
            enemyDB.resize(static_cast<size_t>(d.idx + 1));
        }
        enemyDB[d.idx] = d;
    }

    // 유효 슬롯 개수 리턴(이름이 비어있지 않다고 가정)
    int count = 0;
    for (const auto& d : enemyDB) {
        if (!d.name.empty()) ++count;
    }
    return count;
}

std::unique_ptr<Enemy> EnemySpawnManager::SpawnEnemy(int idx, int lvl)
{
    //값 저장
    InitData(idx, lvl); 
    
    // EnemyData 불러오기
    const EnemyData* data = FindbyIndex();
    
    //유효성 체크
    if (!data) {
        std::cout << "[EnemySpawnManger] 유효하지 않은 idx: " << idx << "\n";
        return nullptr;
    }
    
    //Enemy 객체 반환
    return std::make_unique<Enemy>(*data, lvl);
}


// EnemyData 가져오기
const EnemyData* EnemySpawnManager::FindbyIndex() const
{
    if (index < 0) return nullptr;
    if (static_cast<size_t>(index) >= enemyDB.size()) return nullptr;
    const EnemyData& d = enemyDB[index];
    if (d.name.empty()) return nullptr; // 비어있는 슬롯으로 간주
    return &d;
}

// Enemy 스탯 출력
void EnemySpawnManager::GetEnemy() const
{
    //유효성 검사
    const EnemyData* data = FindbyIndex();
    if (!data) {
        std::cout << "[EnemySpawnManager] Enemy index =" << index
            << " 데이터를 찾을 수 없습니다.\n";
        return;
    }

    EnemyData& nonConstData = const_cast<EnemyData&>(*data);
    int levelCopy = level;

    Enemy enemy(nonConstData, levelCopy);
    enemy.DisplayStat();
}

// Enemy 보상 출력
void EnemySpawnManager::DisplayItems() const
{
    // 유효성 검사
    const EnemyData* data = FindbyIndex();
    if (!data) {
        std::cout << "[EnemySpawnManager] Enemy idx=" << index
                  << " 데이터를 찾을 수 없습니다.\n";
        return;
    }

    const std::vector<int>& idxs = data->dropItemIdxVector;

    std::cout << "=== 몬스터 (" << data->name << ", Lv." << level << ") 의 보상 ===\n";
    std::cout << "골드: " << data->dropGold << "\n";
    std::cout << " 경험치: " << data->dropExp << "\n";
    std::cout << "아이템: ";
    for (size_t i = 0; i < idxs.size(); ++i) {
        std::cout << idxs[i];
        if (i + 1 < idxs.size()) std::cout << ", ";
    }
    std::cout << "\n";

 }




