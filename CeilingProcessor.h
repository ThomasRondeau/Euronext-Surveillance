#pragma once
#include "order.h"
#include "Processor.h"

class CeilingProcessor : public Processor{
public:
	void process(Order* order) override;
};