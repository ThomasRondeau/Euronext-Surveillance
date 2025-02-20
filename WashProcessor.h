#pragma once
#include "order.h"
#include "IProcessor.h"
#include <vector>

class WashProcessor : public IProcessor {
public:
	WashProcessor(double volumeHistoric) : volumeHistoric(volumeHistoric) {}
	std::optional<Alert> process(const Order& order) override;

private:
	double volumeHistoric;
	std::vector<Order> suspiciousOrders;
};