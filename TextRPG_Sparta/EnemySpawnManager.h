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
    // 싱글턴, 데이터 가져오기, 싱글턴 초기화 후에
    // EnemySpawnManager::GetInstance().LoadFromDataManager(dm); 로 호출하여 데이터 가져오기
    static EnemySpawnManager& GetInstance();
    int LoadFromDataManager(DataManager& dm); // DataManager 클래스에 있는 TakeEnemyData 함수를 통해 EnemyData 가져오기 | 데이터 갯수 반환

    //초기값
    int index = 1;
    int level = 1;

    // idx와 level로 몬스터 스폰 | Enemy 반환
    std::unique_ptr<Enemy> SpawnEnemy(int idx, int lvl);

    // 몬스터 정보 출력
    void GetEnemy() const;      // Enemy 정보 출력
    void DisplayItems() const;  // 드랍 결과 출력

private:
    EnemySpawnManager() = default;

    //EnemyData
    std::vector<EnemyData> enemyDB;

    //인덱스, 레벨값 초기화
    void InitData(int idx, int lvl) { index = idx; level = lvl; }

    // 인덱스로 EnemyData 가져오기
    const EnemyData* FindbyIndex() const;
};
