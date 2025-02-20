#pragma once
#include "order.h"
#include "IProcessor.h"
#include <vector>

class CeilingProcessor : public IProcessor{
public:
	CeilingProcessor(double ceilingPriceHistoric, double ceilingVolumeHistoric, double priceMargin) : ceilingPriceHistoric(ceilingPriceHistoric), ceilingVolumeHistoric(ceilingVolumeHistoric), priceMargin(priceMargin) {}
	std::optional<Alert> process(const Order& order) override;

private:
	double ceilingPriceHistoric;
	double ceilingVolumeHistoric;
	double priceMargin;
	std::vector<Order> suspiciousOrders;
};