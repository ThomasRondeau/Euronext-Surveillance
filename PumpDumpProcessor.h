#pragma once
#include "order.h"
#include "IProcessor.h"

class PumpDumpProcessor : public IProcessor {
public:
	std::optional<Alert> process(const Order& order) override;
};