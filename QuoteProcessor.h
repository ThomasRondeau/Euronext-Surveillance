#pragma once
#include "order.h"
#include "Processor.h"

class QuoteProcessor : public Processor {
public:
	void process(Order* order) override;
};