#pragma once
#include "order.h"
#include "Processor.h"

class WashProcessor : public Processor {
public:
	void process(Order* order) override;
};