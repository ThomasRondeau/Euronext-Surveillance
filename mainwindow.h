#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtCharts>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTableWidget>
#include <QLCDNumber>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void updateData();

private:
    void setupUI();
    void createMetricsDisplay();
    void createPriceChart();
    void createOrderBookDisplay();

    // Composants UI pour les métriques
    QLCDNumber* m_matchesLCD;
    QLCDNumber* m_ordersLCD;
    QLCDNumber* m_latencyLCD;

    // Composants pour le graphique
    QChart* m_priceChart;
    QLineSeries* m_priceSeries;
    QChartView* m_chartView;

    // Composant pour le carnet d'ordres
    QTableWidget* m_orderBookTable;

    int m_dataPoints{0};
    QTimer* m_timer;
};
#endif // MAINWINDOW_H
