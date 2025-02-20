#pragma once
#include "order.h"
#include "IProcessor.h"
#include <vector>

class PumpDumpProcessor : public IProcessor {
public:
	PumpDumpProcessor(double volumeHistoric) : volumeHistoric(volumeHistoric) {}
	std::optional<Alert> process(const Order& order) override;

private:
	double volumeHistoric;
	std::vector<Order> suspiciousBuyOrders;
	std::vector<Order> suspiciousSellOrders;
};