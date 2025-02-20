#pragma once
#include "order.h"
#include "IProcessor.h"

class FloorProcessor : public IProcessor {
public:
	std::optional<Alert> process(const Order& order) override;
};