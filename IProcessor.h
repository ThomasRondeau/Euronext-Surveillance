#pragma once
#include "order.h"
#include "Alert.h"
#include <optional>

class IProcessor {
public:
	virtual std::optional<Alert> process(const Order& order) = 0;
private:
	int _id;
};