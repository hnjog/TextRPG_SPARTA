#pragma once
#include <map>
#include <string>
#include <vector>

using namespace std;

struct ItemData;

//상점 기능 이용시 처리 결과
enum class ShopMessage
{
	OK,//문제 없음
	INCORRECT_ITEM,//아이템 ID가 올바르지 않음
	INCORRECT_INPUT,//아이템 ID외 입력이 올바르지 않음
	NO_SELLING_ITEM,//판매중인 아이템이 아님
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

	//판매중인 아이템을 출력한다.
	//* OTHER_ERROR : 판매중인 아이템이 없음
	ShopMessage PrintSellingItems();

	//아이템 1종류를 지정한 개수만큼 추가
	//* INCORRECT_INPUT : 추가할 개수가 0 이하
	ShopMessage AddItem(int itemID, int count = 1);

	//아이템 여러 종류 각각 지정한 개수만큼 추가
	//* INCORRECT_INPUT : itemIDList와 countList의 size가 0이거나 불일치 또는 추가할 개수가 0 이하인 값이 있음
	ShopMessage AddItemRange(vector<int> itemIDList, vector<int> countList);

	//아이템 1종류를 지정한 개수만큼 제거
	//* NO_SELLING_ITEM : 판매중인 아이템이 아님
	//* INCORRECT_INPUT : 제거할 개수가 0 이하
	//* NOT_ENOUGH_STOCK : 제거할 개수가 재고보다 많음
	ShopMessage RemoveItem(int itemID, int count = 1);

	//지정한 아이템과 개수가 얼마인지 확인
	//성공적으로 처리시 price변수에 값이 저장된다. 에러 발생시 0이 저장된다.
	//* INCORRECT_ITEM : 올바른 아이템 번호가 아님
	//* NO_SELLING_ITEM : 판매중인 아이템이 아님
	//* INCORRECT_INPUT : 구매하려는 개수가 0 이하
	//* NOT_ENOUGH_STOCK : 구매하려는 개수가 재고보다 많음
	ShopMessage CheckPrice(int& price, int itemID, int count = 1);

	//아이템 판매
	//상점 입장에서 판매이므로 캐릭터 입장에서는 구매
	//성공적으로 처리시 판매할 아이템이 sellItem에 담기며 실패시 변화 없음
	//* INCORRECT_ITEM : 올바른 아이템 번호가 아님
	//* NO_SELLING_ITEM : 판매중인 아이템이 아님
	//* INCORRECT_INPUT : 구매하려는 개수가 0 이하
	//* NOT_ENOUGH_STOCK : 구매하려는 개수가 재고보다 많음
	ShopMessage SellItem(ItemData& sellItem, int itemID, int count = 1);
};