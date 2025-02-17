#pragma once
#include "order.h"
#include "Processor.h"

class SpoofingProcessor : public Processor {
public:
	void process(Order* order) override;
};