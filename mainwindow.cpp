#include "mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <random>

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_matchesLCD(new QLCDNumber(this))
    , m_ordersLCD(new QLCDNumber(this))
    , m_latencyLCD(new QLCDNumber(this))
    , m_priceChart(new QChart())
    , m_priceSeries(new QLineSeries())
    , m_chartView(new QChartView(m_priceChart))
    , m_orderBookTable(new QTableWidget(10, 4, this))
    , m_timer(new QTimer(this))
{
    setupUI();

    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateData);
    m_timer->start(1000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setWindowTitle("Trading Monitor");
    resize(1200, 800);

    auto mainLayout = new QGridLayout(this);

    createMetricsDisplay();
    createPriceChart();
    createOrderBookDisplay();

    mainLayout->addWidget(m_matchesLCD, 0, 1);
    mainLayout->addWidget(m_ordersLCD, 0, 3);
    mainLayout->addWidget(m_latencyLCD, 0, 5);
    mainLayout->addWidget(m_chartView, 1, 0, 1, 6);
    mainLayout->addWidget(m_orderBookTable, 2, 0, 1, 6);

    setLayout(mainLayout);
}

void MainWindow::createMetricsDisplay()
{
    auto matchesLabel = new QLabel("Matches/sec:", this);
    m_matchesLCD->setDigitCount(6);
    m_matchesLCD->setSegmentStyle(QLCDNumber::Flat);

    auto ordersLabel = new QLabel("Orders/sec:", this);
    m_ordersLCD->setDigitCount(6);
    m_ordersLCD->setSegmentStyle(QLCDNumber::Flat);

    auto latencyLabel = new QLabel("Avg Latency (µs):", this);
    m_latencyLCD->setDigitCount(6);
    m_latencyLCD->setSegmentStyle(QLCDNumber::Flat);
}

void MainWindow::createPriceChart()
{
    m_priceSeries->setName("Price");
    m_priceChart->addSeries(m_priceSeries);
    m_priceChart->legend()->hide();
    m_priceChart->createDefaultAxes();
    m_priceChart->setTitle("Price Evolution");

    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::createOrderBookDisplay()
{
    m_orderBookTable->setHorizontalHeaderLabels({
        "Bid Size", "Bid Price", "Ask Price", "Ask Size"
    });
}

void MainWindow::updateData()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0, 100);

    // Mise à jour des métriques
    m_matchesLCD->display(static_cast<int>(dis(gen)));
    m_ordersLCD->display(static_cast<int>(dis(gen) * 2));
    m_latencyLCD->display(static_cast<int>(dis(gen) * 10));

    // Mise à jour du graphique
    m_dataPoints++;
    m_priceSeries->append(m_dataPoints, 100 + dis(gen));
    if (m_priceSeries->count() > 50)
        m_priceSeries->remove(0);

    m_priceChart->axes(Qt::Horizontal).first()->setRange(m_dataPoints - 50, m_dataPoints);
    m_priceChart->axes(Qt::Vertical).first()->setRange(0, 200);

    // Mise à jour du carnet d'ordres
    for (int i = 0; i < 10; ++i) {
        double basePrice = 100.0;
        m_orderBookTable->setItem(i, 0, new QTableWidgetItem(
            QString::number(dis(gen), 'f', 2)));
        m_orderBookTable->setItem(i, 1, new QTableWidgetItem(
            QString::number(basePrice - i * 0.1, 'f', 2)));
        m_orderBookTable->setItem(i, 2, new QTableWidgetItem(
            QString::number(basePrice + i * 0.1, 'f', 2)));
        m_orderBookTable->setItem(i, 3, new QTableWidgetItem(
            QString::number(dis(gen), 'f', 2)));
    }
}
