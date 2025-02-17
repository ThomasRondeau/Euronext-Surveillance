#ifndef DATAANALYSTWINDOW_H
#define DATAANALYSTWINDOW_H

#include <QWidget>

class QPushButton;

class DataAnalystWindow : public QWidget {
    Q_OBJECT

public:
    explicit DataAnalystWindow(QWidget *parent = nullptr);

private slots:
    void goToLogin();
};

#endif // DATAANALYSTWINDOW_H
