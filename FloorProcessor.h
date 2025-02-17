#pragma once
#include "order.h"
#include "Processor.h"

class FloorProcessor : public Processor {
public:
	void process(Order* order) override;
};