#pragma once
#include <map>
#include <string>
#include <vector>

using namespace std;

//상점 기능 이용시 처리 결과
enum class ShopMessage
{
	OK,//문제 없음
	INCORRECT_ITEM,//아이템 ID가 올바르지 않음
	INCORRECT_INPUT,//아이템 ID외 입력이 올바르지 않음
	NOT_ENOUGH_STOCK,//재고 부족
	OTHER_ERROR,//기타 다른 오류
};

class Shop
{
private:
	int id;//상점 번호
	string name;//상점 이름
	map<int, int> sellList;//판매 목록 <아이템 번호, 재고>

public:
	//상점 생성 (상점 번호와 이름 필요)
	Shop(int shopID = 0, string shopName = "");

	//아이템 1종류를 지정한 개수만큼 추가
	ShopMessage AddItem(int itemID, int count = 1);

	//아이템 여러 종류 각각 지정한 개수만큼 추가
	//* itemIDList와 countList의 size는 동일해야 합니다.
	ShopMessage AddItemRange(vector<int> itemIDList, vector<int> countList);

	//아이템 1종류를 지정한 개수만큼 제거
	//제거 실패시 false
	ShopMessage RemoveItem(int itemID, int count = 1);
};