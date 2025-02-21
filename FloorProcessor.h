#pragma once
#include "order.h"
#include "IProcessor.h"
#include <vector>

class FloorProcessor : public IProcessor {
public:
	FloorProcessor(double floorPriceHistoric, double floorVolumeHistoric, double priceMargin) : floorPriceHistoric(floorPriceHistoric), floorVolumeHistoric(floorVolumeHistoric), priceMargin(priceMargin) {}
	std::optional<Alert> process(const Order& order) override;

private:
	time_t window;
	double floorPriceHistoric;
	double floorVolumeHistoric;
	double priceMargin;
	double percentageVolumeThreshlod;
	std::vector<Order> suspiciousOrders;
	std::vector<Order> historicOrders;
};