#pragma once
#include "order.h"
#include "IProcessor.h"
#include <vector>

class SpoofingProcessor : public IProcessor {
public:
	std::optional<Alert> process(const Order& order) override;

private:
	time_t window;
	time_t detectionWindow;
	double volumeHistoric;
	std::vector<Order> suspiciousOrders;
	std::vector<Order> historicOrders;
};