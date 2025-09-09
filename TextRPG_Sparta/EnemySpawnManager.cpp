#include "EnemySpawnManager.h"

// --- �̱��� ---
EnemySpawnManager& EnemySpawnManager::GetInstance() {
    static EnemySpawnManager instance;
    return instance;
}

int EnemySpawnManager::LoadFromDataManager(DataManager& dm)
{
    std::vector<EnemyData> list;

    // ���� index ������ index ���߱� (1���� ����)
    int maxIdx = -1;
    for (const auto& d : list) {
        if (d.idx > maxIdx) maxIdx = d.idx;
    }

    enemyDB.clear();
    if (maxIdx >= 0) {
        enemyDB.resize(static_cast<size_t>(maxIdx + 1));
    }

    // �ش� index ������ ����
    for (const auto& d : list) {
        if (d.idx < 0) continue;
        if (static_cast<size_t>(d.idx) >= enemyDB.size()) {
            enemyDB.resize(static_cast<size_t>(d.idx + 1));
        }
        enemyDB[d.idx] = d;
    }

    // ��ȿ ���� ���� ����(�̸��� ������� �ʴٰ� ����)
    int count = 0;
    for (const auto& d : enemyDB) {
        if (!d.name.empty()) ++count;
    }
    return count;
}

std::unique_ptr<Enemy> EnemySpawnManager::SpawnEnemy(int idx, int lvl)
{
    //�� ����
    InitData(idx, lvl); 
    
    // EnemyData �ҷ�����
    const EnemyData* data = FindbyIndex();
    
    //��ȿ�� üũ
    if (!data) {
        std::cout << "[EnemySpawnManger] ��ȿ���� ���� idx: " << idx << "\n";
        return nullptr;
    }
    
    //Enemy ��ü ��ȯ
    return std::make_unique<Enemy>(*data, lvl);
}


// EnemyData ��������
const EnemyData* EnemySpawnManager::FindbyIndex() const
{
    if (index < 0) return nullptr;
    if (static_cast<size_t>(index) >= enemyDB.size()) return nullptr;
    const EnemyData& d = enemyDB[index];
    if (d.name.empty()) return nullptr; // ����ִ� �������� ����
    return &d;
}

// Enemy ���� ���
void EnemySpawnManager::GetEnemy() const
{
    //��ȿ�� �˻�
    const EnemyData* data = FindbyIndex();
    if (!data) {
        std::cout << "[EnemySpawnManager] Enemy index =" << index
            << " �����͸� ã�� �� �����ϴ�.\n";
        return;
    }

    EnemyData& nonConstData = const_cast<EnemyData&>(*data);
    int levelCopy = level;

    Enemy enemy(nonConstData, levelCopy);
    enemy.DisplayStat();
}

// Enemy ���� ���
void EnemySpawnManager::DisplayItems() const
{
    // ��ȿ�� �˻�
    const EnemyData* data = FindbyIndex();
    if (!data) {
        std::cout << "[EnemySpawnManager] Enemy idx=" << index
                  << " �����͸� ã�� �� �����ϴ�.\n";
        return;
    }

    const std::vector<int>& idxs = data->dropItemIdxVector;

    std::cout << "=== ���� (" << data->name << ", Lv." << level << ") �� ���� ===\n";
    std::cout << "���: " << data->dropGold << "\n";
    std::cout << " ����ġ: " << data->dropExp << "\n";
    std::cout << "������: ";
    for (size_t i = 0; i < idxs.size(); ++i) {
        std::cout << idxs[i];
        if (i + 1 < idxs.size()) std::cout << ", ";
    }
    std::cout << "\n";

 }




