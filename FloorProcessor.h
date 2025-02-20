#pragma once
#include "order.h"
#include "IProcessor.h"
#include <vector>

class FloorProcessor : public IProcessor {
public:
	FloorProcessor(double floorPriceHistoric, double floorVolumeHistoric, double priceMargin) : floorPriceHistoric(floorPriceHistoric), floorVolumeHistoric(floorVolumeHistoric), priceMargin(priceMargin) {}
	std::optional<Alert> process(const Order& order) override;

private:
	double floorPriceHistoric;
	double floorVolumeHistoric;
	double priceMargin;
	std::vector<Order> suspiciousOrders;
};