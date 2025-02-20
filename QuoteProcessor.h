#pragma once
#include "order.h"
#include "IProcessor.h"

class QuoteProcessor : public IProcessor {
public:
	std::optional<Alert> process(const Order& order) override;
};