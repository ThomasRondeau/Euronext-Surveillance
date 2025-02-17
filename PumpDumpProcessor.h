#pragma once
#include "order.h"
#include "Processor.h"

class PumpDumpProcessor : public Processor {
public:
	void process(Order* order) override;
};