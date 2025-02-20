#include "CeilingProcessor.h"

std::optional<Alert> CeilingProcessor::process(const Order& order)
{
	if (order.getInstrumentType() == instrumentType::STOCK && order.getSide() == side::BUY && order.getPrice() > 1000)
	{
		return Alert(order.getId(), order.getId(), 1, FraudType::CEILING, AlertSeverity::HIGH, AlertType::PRICE, "Price is above ceiling");
	}
	return std::nullopt;
}