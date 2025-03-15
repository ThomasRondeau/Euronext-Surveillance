#include "IFraudObserver.h"
#include "IProcessor.h"
#include <vector>
#include <memory>

class FraudMonitor {
public:
	FraudMonitor() {}

	void processOrder(const Order& order) {
		for (auto processor : _processors) {
			std::optional<Alert> alert = processor->process(order);
			if (alert.has_value()) {
				notifyObservers(alert.value());
			}
		}
	}
	
	void addProcessor(std::shared_ptr<IProcessor> processor) {
		_processors.push_back(std::move(processor));
	}
	void addObserver(std::shared_ptr<IFraudObserver> observer) {
		_observers.push_back(std::move(observer));
	}

private:
	void notifyObservers(const Alert& alert) {
		for (auto observer : _observers) {
			observer->update(alert);
		}
	}

	std::vector<std::shared_ptr<IProcessor>> _processors;
	std::vector<std::shared_ptr<IFraudObserver>> _observers;
};