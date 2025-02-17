#pragma once
#include "order.h"

class Processor {
public:
	virtual void process(Order* order) = 0;
};