#include "PumpDumpProcessor.h"

std::optional<Alert> PumpDumpProcessor::process(const Order& order)
{
	historicOrders.push_back(order);

	while (historicOrders.begin()->getTimestampCreated() < order.getTimestampCreated() - window) {
		historicOrders.erase(historicOrders.begin());
	}
	/*
	if (order.getQuantity() > volumeHistoric)
	{
		if (order.getSide() == side::BUY)
		{
			suspiciousBuyOrders.push_back(order);
		}
		else
		{
			suspiciousSellOrders.push_back(order);
		}
		int totalBuyQuantity = 0;
		int totalSellQuantity = 0;
		for (Order suspected : suspiciousBuyOrders)
		{
			if (order.getIdFirm() == suspected.getIdFirm())
			{
				totalBuyQuantity += suspected.getQuantity();
			}
		}
		for (Order suspected : suspiciousSellOrders)
		{
			if (order.getIdFirm() == suspected.getIdFirm())
			{
				totalSellQuantity += suspected.getQuantity();
			}
		}
		if ((totalBuyQuantity / totalSellQuantity) > )
		{
			return Alert(order.getId(), this->getId(), FraudType::PUMP_AND_DUMP, AlertSeverity::HIGH, AlertType::VOLUME, "Pump and dump scheme detected");
		}
	}
	*/
	return std::nullopt;
}