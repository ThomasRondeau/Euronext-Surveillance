#include "multipleViewsWindow.h"
#include <Alert.h>

// creation of the window
MultipleViewsWindow::MultipleViewsWindow(QWidget* parent)
    : QMainWindow(parent), 
    m_priceChart(new QChart()),
    m_priceSeries(new QLineSeries()),
    m_chartView(new QChartView(m_priceChart)),
	m_orderBookTable(new QTableWidget(10, 4, this))
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    searchTable = new SearchableTableWidget(this);

    //Test, to refactor
	createPriceChart();
    createOrderBookDisplay();
    
    createSideMenu();

    stackedWidget = new QStackedWidget;
    createPages();

    mainLayout->addWidget(sideMenu);
    mainLayout->addWidget(stackedWidget);

    setMinimumSize(1280, 720);

    connect(m_priceChart, &QChart::plotAreaChanged, this, &MultipleViewsWindow::updateAlertLabelsPositions);
}

//Destructor
MultipleViewsWindow::~MultipleViewsWindow()
{
}

// creation of the side menu to switch between pages
void MultipleViewsWindow::createSideMenu()
{
    sideMenu = new QWidget;
    menuLayout = new QVBoxLayout(sideMenu);

    // Add of buttons
    QPushButton* page1Button = new QPushButton("Executed scan");
    QPushButton* page2Button = new QPushButton("Order book scan");
    QPushButton* page3Button = new QPushButton("Raw Data");

	// Set side menu properties
    sideMenu->setMaximumWidth(200);
    sideMenu->setStyleSheet("background-color: #f0f0f0;");

	//Add buttons to the menu layout
    menuLayout->addWidget(page1Button);
    menuLayout->addWidget(page2Button);
    menuLayout->addWidget(page3Button);
	menuLayout->addStretch(); // Add a stretch to push the buttons to the top

	//Connect the buttons to the changePage function to put a real action in place
    connect(page1Button, &QPushButton::clicked, [this]() { changePage(0); });
    connect(page2Button, &QPushButton::clicked, [this]() { changePage(1); });
    connect(page3Button, &QPushButton::clicked, [this]() { changePage(2); });
}

// creation of the three pages with QWidget
void MultipleViewsWindow::createPages()
{
    QWidget* page1 = new QWidget;
    QWidget* page2 = new QWidget;
    QWidget* page3 = new QWidget;

	//Page 1 : executed data
    QVBoxLayout* layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("Chart on executed data"));
	layout1->addWidget(m_chartView);

    QVBoxLayout* layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("Chart on pretrade data"));
	layout2->addWidget(m_orderBookTable);

    
    QVBoxLayout* layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("Raw data search"));
	layout3->addWidget(searchTable);

	//Add the pages to the stacked widget
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);
}

// change the stack widget index, which allows to switch pages
void MultipleViewsWindow::changePage(int index)
{
    stackedWidget->setCurrentIndex(index);
}

// Create the price chart
void MultipleViewsWindow::createPriceChart()
{
    m_priceSeries->setName("Price");
    m_priceChart->addSeries(m_priceSeries);
    m_priceChart->legend()->hide();

    // Special axis for time
    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setTickCount(5);
	axisX->setFormat("HH:mm:ss");  //specific format for the time for precision
	axisX->setTitleText("Time");

    QValueAxis* axisY = new QValueAxis();
    axisY->setLabelFormat("%.2f");

    m_priceChart->setAxisX(axisX, m_priceSeries);
    m_priceChart->setAxisY(axisY, m_priceSeries);

    m_priceChart->setTitle("Price Evolution");
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

// Create the order book display
void MultipleViewsWindow::createOrderBookDisplay()
{
    m_orderBookTable->setHorizontalHeaderLabels({
        "Bid Size", "Bid Price", "Ask Price", "Ask Size"
    });
}

void MultipleViewsWindow::updatePriceChart(const time_t& time, const double& price)
{
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(time);
    m_priceSeries->append(dateTime.toMSecsSinceEpoch(), price);

	// We could had a rolling window to avoid a too big chart on heavy data load
}

// Add an alert to the chart
void MultipleViewsWindow::addAlert(const Alert& alert)
{
    // Convertir time_t en QDateTime
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(alert.getTimestamp());
    qint64 msTimestamp = dateTime.toMSecsSinceEpoch();

    //Color picking
    QColor alertColor;
    switch (alert.getSeverity()) {
    case AlertSeverity::LOW:
        alertColor = QColor(255, 165, 0); // Orange
        break;
    case AlertSeverity::MEDIUM:
        alertColor = QColor(255, 0, 0);   // Rouge
        break;
    case AlertSeverity::HIGH:
        alertColor = QColor(128, 0, 128); // Violet
        break;
    default:
        alertColor = QColor(255, 0, 0);   // Rouge par défaut
    }
    // Ajouter le point d'alerte
	m_alertSeries->append(msTimestamp, 0.5);  // 0.5 but we could also retrieve the orderId and put the alert at the price level of the order

    // Créer et positionner le texte de l'alerte
    QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem(m_priceChart);
    textItem->setText(QString::fromStdString(alert.getDescription()));
    textItem->setBrush(alertColor);
    textItem->setFont(QFont("Arial", 9, QFont::Bold));

    // Positionner le texte au-dessus du point
    QPointF pointPos = m_priceChart->mapToPosition(QPointF(msTimestamp, 0.5), m_alertSeries);
    textItem->setPos(pointPos.x() - textItem->boundingRect().width() / 2,
        pointPos.y() - 25);  // 25 pixels au-dessus du point

    // Stocker la référence pour pouvoir le mettre à jour ou le supprimer plus tard
    m_alertLabels.append(textItem);
}

// To change the label position when the chart receive a new point
void MultipleViewsWindow::updateAlertLabelsPositions()
{
    for (int i = 0; i < m_alertSeries->count() && i < m_alertLabels.size(); ++i) {
        QPointF point = m_alertSeries->at(i);
        QPointF pointPos = m_priceChart->mapToPosition(point, m_alertSeries);
        m_alertLabels[i]->setPos(pointPos.x() - m_alertLabels[i]->boundingRect().width() / 2,
            pointPos.y() - 25);
    }
}

void MultipleViewsWindow::updateOrderBook(const Order& order)
{
	if (order.getSide() == side::BUY) {
		m_orderBookTable->setItem(0, 0, new QTableWidgetItem(QString::number(order.getQuantity())));
		m_orderBookTable->setItem(0, 1, new QTableWidgetItem(QString::number(order.getPrice())));
	}
	else {
		m_orderBookTable->setItem(0, 2, new QTableWidgetItem(QString::number(order.getPrice())));
		m_orderBookTable->setItem(0, 3, new QTableWidgetItem(QString::number(order.getQuantity())));
	}
}

/*
void MultipleViewsWindow::updateRawData(const Order& order)
{
    MultipleViewsWindow::searchTable->addOrder(order);
}
*/
