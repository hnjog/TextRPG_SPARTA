#pragma once

#include<string>
#include<vector>

struct ShopData
{
	int shopIdx;
	std::string name;
	std::vector<int> sellItemIdxVector;
	std::vector<int> sellItemStockVector;
};