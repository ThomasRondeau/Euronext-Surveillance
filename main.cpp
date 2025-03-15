#include "multipleViewsWindow.h"

#include "CeilingProcessor.h"
#include "FloorProcessor.h"
#include "PumpDumpProcessor.h"
#include "SpoofingProcessor.h"
#include "WashProcessor.h"

#include <QApplication>
#include <FraudMonitor.cpp>
#include <ChartFraudObserver.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Créer la fenêtre principale
    MultipleViewsWindow mainWindow;
    mainWindow.show();

    // Créer le moniteur de fraude
    FraudMonitor fraudMonitor;

    // Ajouter vos processeurs
    fraudMonitor.addProcessor(std::make_shared<CeilingProcessor>(5));
    fraudMonitor.addProcessor(std::make_shared<FloorProcessor>(5));
	fraudMonitor.addProcessor(std::make_shared<PumpDumpProcessor>());
	fraudMonitor.addProcessor(std::make_shared<SpoofingProcessor>());
	//fraudMonitor.addProcessor(std::make_shared<WashProcessor>());

    // Créer et configurer l'observateur de graphique
    auto chartObserver = std::make_shared<ChartFraudObserver>(&mainWindow);

    // Important: Si vous recevez des mises à jour de prix séparément des alertes,
    // vous devez les transmettre à l'observateur
    // Par exemple, lorsque vous mettez à jour le prix dans le graphique:
    // mainWindow.updatePriceChart(timestamp, price);
    // chartObserver->updateOrderPrice(orderId, price);

    // Ajouter l'observateur au moniteur
    fraudMonitor.addObserver(chartObserver);

    // Autres initialisations...

    return app.exec();
}