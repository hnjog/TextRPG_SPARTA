#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include "Enemy.h"
#include "EnemyData.h"
#include "DataManager.h"   

class EnemySpawnManager {
public:
    // �̱���, ������ ��������, �̱��� �ʱ�ȭ �Ŀ�
    // EnemySpawnManager::GetInstance().LoadFromDataManager(dm); �� ȣ���Ͽ� ������ ��������
    static EnemySpawnManager& GetInstance();
    int LoadFromDataManager(DataManager& dm); // DataManager Ŭ������ �ִ� TakeEnemyData �Լ��� ���� EnemyData �������� | ������ ���� ��ȯ

    //�ʱⰪ
    int index = 1;
    int level = 1;

    // idx�� level�� ���� ���� | Enemy ��ȯ
    std::unique_ptr<Enemy> SpawnEnemy(int idx, int lvl);

    // ���� ���� ���
    void GetEnemy() const;      // Enemy ���� ���
    void DisplayItems() const;  // ��� ��� ���

private:
    EnemySpawnManager() = default;

    //EnemyData
    std::vector<EnemyData> enemyDB;

    //�ε���, ������ �ʱ�ȭ
    void InitData(int idx, int lvl) { index = idx; level = lvl; }

    // �ε����� EnemyData ��������
    const EnemyData* FindbyIndex() const;
};
