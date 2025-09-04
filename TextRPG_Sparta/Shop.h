#pragma once
#include <map>
#include <vector>

using namespace std;

class Shop
{
private:
	int shopID;//상점 번호
	map<int, int> sellList;//판매 목록 <아이템 번호, 재고>

public:
	//상점 생성 (상점 번호 필요)
	Shop(int shopID = 0);

	//아이템 1종류를 지정한 개수만큼 추가
	void AddItem(int itemID, int count = 1);

	//아이템 여러 종류 각각 지정한 개수만큼 추가
	//* itemIDList와 countList의 size는 동일해야 합니다.
	void AddItemRange(vector<int> itemIDList, vector<int> countList);

	//아이템 1종류를 지정한 개수만큼 제거
	//제거 실패시 false
	bool RemoveItem(int itemID, int count = 1);
};