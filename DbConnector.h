#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "order.h"

class DbConnector
{
private:

public:
	std::vector<Order> getOrders(const std::string& filename);
	Order parseOrderFromJson(const nlohmann::json& jsonData);
};