#ifndef TRADERWINDOW_H
#define TRADERWINDOW_H

#include <QWidget>

class QPushButton;

class TraderWindow : public QWidget {
    Q_OBJECT

public:
    explicit TraderWindow(QWidget *parent = nullptr);

private slots:
    void goToLogin();
};

#endif // TRADERWINDOW_H
