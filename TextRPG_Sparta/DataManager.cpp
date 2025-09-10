#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib> // strtol

#ifdef _WIN32
#include <windows.h>
#include <codecvt>
#else
#include <unistd.h>
#include <limits.h>
#endif

#include <iostream>

// ---------- Singleton ----------
DataManager& DataManager::GetInstance()
{
	static DataManager inst;
	return inst;
}

// ---------- Path / IO ----------
#ifdef _WIN32
std::string DataManager::ToUtf8(const std::wstring& w) const
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(w);
}
std::wstring DataManager::ToWide(const std::string& u8) const
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(u8);
}
#endif

std::string DataManager::ResolveFromResourcesOutput(const std::string& relative) const
{
#ifdef _WIN32
	std::wstring full = ToWide("..\\Resources\\output\\");
	full += ToWide(relative);
	return ToUtf8(full);
#else
	return "../Resources/output/" + relative;
#endif
}

// ---- 헬퍼: 바이트 프리픽스 검사
static bool has_prefix(const std::vector<unsigned char>& buf,
	std::initializer_list<unsigned char> p) {
	if (buf.size() < p.size()) return false;
	size_t i = 0;
	for (auto v : p) { if (buf[i++] != v) return false; }
	return true;
}

std::string DataManager::ReadFileToString(const std::string& pathUtf8) const
{
#ifdef _WIN32
	std::ifstream ifs(ToWide(pathUtf8), std::ios::binary);
#else
	std::ifstream ifs(pathUtf8.c_str(), std::ios::binary);
#endif
	if (!ifs) throw std::runtime_error("failed to open: " + pathUtf8);

	// 전체 읽기
	std::vector<unsigned char> buf;
	ifs.seekg(0, std::ios::end);
	std::streamoff sz = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	if (sz > 0)
	{
		buf.resize(static_cast<size_t>(sz));
		ifs.read(reinterpret_cast<char*>(buf.data()), sz);
	}
	if (buf.empty())
		return std::string();

	// --- 인코딩 처리 ---
	// 1) UTF-8 BOM → 제거
	if (has_prefix(buf, { 0xEF, 0xBB, 0xBF })) {
		return std::string(reinterpret_cast<const char*>(buf.data() + 3),
			reinterpret_cast<const char*>(buf.data() + buf.size()));
	}

	// 2) UTF-16 LE → UTF-8 변환
	if (has_prefix(buf, { 0xFF, 0xFE })) {
		const uint16_t* w = reinterpret_cast<const uint16_t*>(buf.data() + 2);
		size_t wc = (buf.size() - 2) / 2;
		std::wstring ws; ws.resize(wc);
		for (size_t i = 0; i < wc; ++i) ws[i] = static_cast<wchar_t>(w[i]);
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.to_bytes(ws);
	}

	// 3) UTF-16 BE → UTF-8 변환
	if (has_prefix(buf, { 0xFE, 0xFF })) {
		const unsigned char* p = buf.data() + 2;
		size_t wc = (buf.size() - 2) / 2;
		std::wstring ws; ws.resize(wc);
		for (size_t i = 0; i < wc; ++i) {
			uint16_t u = (static_cast<uint16_t>(p[2 * i]) << 8) | static_cast<uint16_t>(p[2 * i + 1]);
			ws[i] = static_cast<wchar_t>(u);
		}
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.to_bytes(ws);
	}

	// 4) 그 외는 UTF-8/ASCII로 간주
	return std::string(reinterpret_cast<const char*>(buf.data()),
		reinterpret_cast<const char*>(buf.data() + buf.size()));
}
JsonValue DataManager::ParseJsonFile(const std::string& pathUtf8) const
{
	std::string s = ReadFileToString(pathUtf8);
	JsonParser p(s);
	return p.parse();
}

// ---------- Initialize (부팅 시 1회) ----------
bool DataManager::Initialize()
{
	if (initialized)
		return initialized;

	// items.json (최상위 배열: {"Idx","Name","Effect","Type","Value"})
	try
	{
		std::string path = ResolveFromResourcesOutput("Item.json");
		JsonValue root = ParseJsonFile(path);
		LoadItemsJson(root);
	}
	catch (...)
	{
		std::cout << "Item.json do not exist!" << '\n';
	}

	try
	{
		std::string path = ResolveFromResourcesOutput("Shop.json");
		JsonValue root = ParseJsonFile(path);
		LoadShopJson(root);
	}
	catch (...)
	{
		std::cout << "Shop.json do not exist!" << '\n';
	}

	try
	{
		std::string path = ResolveFromResourcesOutput("Enemy.json");
		JsonValue root = ParseJsonFile(path);
		LoadEnemyJson(root);
	}
	catch (...)
	{
		std::cout << "Enemy.json do not exist!" << '\n';
	}


	initialized = true;

	return initialized;
}

// ---------- JSON → Items ----------
void DataManager::LoadItemsJson(const JsonValue& root)
{
	itemDataVector.clear();

	// 우리가 쓰는 스키마: 최상위가 배열
	if (root.type != JsonValue::Type::Array)
		return;

	itemDataVector.reserve(root.arr.size());
	for (const auto& obj : root.arr) {
		if (obj.type != JsonValue::Type::Object)
			continue;

		ItemData it;

		const JsonValue* pIdx = obj.get("Idx");
		if (pIdx)
		{
			if (pIdx->type == JsonValue::Type::String)
				it.idx = static_cast<int>(std::strtol(pIdx->str.c_str(), nullptr, 10));
			else if (pIdx->type == JsonValue::Type::Number)
				it.idx = static_cast<int>(pIdx->number);
		}

		const JsonValue* pName = obj.get("Name");
		if (pName && pName->type == JsonValue::Type::String)
			it.name = (pName->str);

		const JsonValue* pEffect = obj.get("Effect");
		if (pEffect && pEffect->type == JsonValue::Type::String)
			it.effect = (pEffect->str);

		const JsonValue* pValue = obj.get("Value");
		if (pValue)
		{
			if (pValue->type == JsonValue::Type::String)
				it.value = static_cast<int>(std::strtol(pValue->str.c_str(), nullptr, 10));
			else if (pValue->type == JsonValue::Type::Number)
				it.value = static_cast<int>(pValue->number);
		}

		const JsonValue* pPrice = obj.get("Price");
		if (pPrice)
		{
			if (pPrice->type == JsonValue::Type::String)
				it.price = static_cast<int>(std::strtol(pPrice->str.c_str(), nullptr, 10));
			else if (pPrice->type == JsonValue::Type::Number)
				it.price = static_cast<int>(pPrice->number);
		}

		const JsonValue* pIsConsumable = obj.get("IsConsumable");
		if (pIsConsumable && pIsConsumable->type == JsonValue::Type::String)
		{
			if (pIsConsumable->str == "o")
				it.isConsumable = true;
			else
				it.isConsumable = false;
		}

		const JsonValue* pIsStackable = obj.get("IsStackable");
		if (pIsStackable && pIsStackable->type == JsonValue::Type::String)
		{
			if (pIsStackable->str == "o")
				it.isStackable = true;
			else
				it.isStackable = false;
		}

		itemDataVector.push_back(it);
	}
}

// ---------- JSON → Items ----------
void DataManager::LoadShopJson(const JsonValue& root)
{
	shopDataVector.clear();

	// 우리가 쓰는 스키마: 최상위가 배열
	if (root.type != JsonValue::Type::Array)
		return;

	shopDataVector.reserve(root.arr.size());
	for (const auto& obj : root.arr) {
		if (obj.type != JsonValue::Type::Object)
			continue;

		ShopData sd;

		const JsonValue* sIdx = obj.get("ShopId");
		if (sIdx)
		{
			if (sIdx->type == JsonValue::Type::String)
				sd.shopIdx = static_cast<int>(std::strtol(sIdx->str.c_str(), nullptr, 10));
			else if (sIdx->type == JsonValue::Type::Number)
				sd.shopIdx = static_cast<int>(sIdx->number);
		}

		const JsonValue* sName = obj.get("Name");
		if (sName && sName->type == JsonValue::Type::String)
			sd.name = (sName->str);

		const JsonValue* shopItemList = obj.get("ItemIdxList");
		if (shopItemList && shopItemList->type == JsonValue::Type::Array)
		{
			for (const auto& v : shopItemList->arr) 
			{
				if (v.type == JsonValue::Type::Number) 
				{
					sd.sellItemIdxVector.push_back(static_cast<int>(v.number));
				}
			}
		}
		
		const JsonValue* shopStockList = obj.get("Stock");
		if (shopStockList && shopStockList->type == JsonValue::Type::Array)
		{
			for (const auto& v : shopStockList->arr)
			{
				if (v.type == JsonValue::Type::Number)
				{
					sd.sellItemStockVector.push_back(static_cast<int>(v.number));
				}
			}
		}

		shopDataVector.push_back(sd);
	}
}

void DataManager::LoadEnemyJson(const JsonValue& root)
{
	enemyDataVector.clear();

	// 우리가 쓰는 스키마: 최상위가 배열
	if (root.type != JsonValue::Type::Array)
		return;

	enemyDataVector.reserve(root.arr.size());
	for (const auto& obj : root.arr) {
		if (obj.type != JsonValue::Type::Object)
			continue;

		EnemyData ed;

		const JsonValue* eIdx = obj.get("Idx");
		if (eIdx)
		{
			if (eIdx->type == JsonValue::Type::String)
				ed.idx = static_cast<int>(std::strtol(eIdx->str.c_str(), nullptr, 10));
			else if (eIdx->type == JsonValue::Type::Number)
				ed.idx = static_cast<int>(eIdx->number);
		}

		const JsonValue* eName = obj.get("Name");
		if (eName && eName->type == JsonValue::Type::String)
			ed.name = (eName->str);

		const JsonValue* eBaseHp = obj.get("BaseHp");
		if (eBaseHp)
		{
			if (eBaseHp->type == JsonValue::Type::String)
				ed.baseHp = static_cast<int>(std::strtol(eBaseHp->str.c_str(), nullptr, 10));
			else if (eBaseHp->type == JsonValue::Type::Number)
				ed.baseHp = static_cast<int>(eBaseHp->number);
		}

		const JsonValue* eBaseAttack = obj.get("BaseAttack");
		if (eBaseAttack)
		{
			if (eBaseAttack->type == JsonValue::Type::String)
				ed.baseAttack = static_cast<int>(std::strtol(eBaseAttack->str.c_str(), nullptr, 10));
			else if (eBaseAttack->type == JsonValue::Type::Number)
				ed.baseAttack = static_cast<int>(eBaseAttack->number);
		}

		const JsonValue* eHpPerLevel = obj.get("HpPerLevel");
		if (eHpPerLevel)
		{
			if (eHpPerLevel->type == JsonValue::Type::String)
				ed.hpPerLevel = static_cast<int>(std::strtol(eHpPerLevel->str.c_str(), nullptr, 10));
			else if (eHpPerLevel->type == JsonValue::Type::Number)
				ed.hpPerLevel = static_cast<int>(eHpPerLevel->number);
		}

		const JsonValue* eAttackPerLevel = obj.get("AttackPerLevel");
		if (eAttackPerLevel)
		{
			if (eAttackPerLevel->type == JsonValue::Type::String)
				ed.attackPerLevel = static_cast<int>(std::strtol(eAttackPerLevel->str.c_str(), nullptr, 10));
			else if (eAttackPerLevel->type == JsonValue::Type::Number)
				ed.attackPerLevel = static_cast<int>(eAttackPerLevel->number);
		}

		const JsonValue* eDropGold = obj.get("DropGold");
		if (eDropGold)
		{
			if (eDropGold->type == JsonValue::Type::String)
				ed.dropGold = static_cast<int>(std::strtol(eDropGold->str.c_str(), nullptr, 10));
			else if (eDropGold->type == JsonValue::Type::Number)
				ed.dropGold = static_cast<int>(eDropGold->number);
		}

		const JsonValue* eDropExp = obj.get("DropExp");
		if (eDropExp)
		{
			if (eDropExp->type == JsonValue::Type::String)
				ed.dropExp = static_cast<int>(std::strtol(eDropExp->str.c_str(), nullptr, 10));
			else if (eDropExp->type == JsonValue::Type::Number)
				ed.dropExp = static_cast<int>(eDropExp->number);
		}

		const JsonValue* eDropItemIdx = obj.get("DropItemIdx");
		if (eDropItemIdx && eDropItemIdx->type == JsonValue::Type::Array)
		{
			for (const auto& v : eDropItemIdx->arr)
			{
				if (v.type == JsonValue::Type::Number)
				{
					ed.dropItemIdxVector.push_back(static_cast<int>(v.number));
				}
			}
		}

		const JsonValue* eDropItemChance = obj.get("DropItemChance");
		if (eDropItemChance && eDropItemChance->type == JsonValue::Type::Array)
		{
			for (const auto& v : eDropItemChance->arr)
			{
				if (v.type == JsonValue::Type::Number)
				{
					ed.dropItemChanceVector.push_back(static_cast<int>(v.number));
				}
			}
		}

		enemyDataVector.push_back(ed);
	}
}

// ---------- Move-out ----------
std::vector<ItemData> DataManager::TakeItems()
{
	return std::move(itemDataVector);
}

std::vector<ShopData> DataManager::TakeShopDatas()
{
	return std::move(shopDataVector);
}

std::vector<EnemyData> DataManager::TakeEnemyDatas()
{
	return std::move(enemyDataVector);
}