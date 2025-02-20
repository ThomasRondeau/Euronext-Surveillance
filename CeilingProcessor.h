#pragma once
#include "order.h"
#include "IProcessor.h"

class CeilingProcessor : public IProcessor{
public:
	std::optional<Alert> process(const Order& order) override;
};