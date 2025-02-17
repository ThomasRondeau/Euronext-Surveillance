#ifndef INSTRUMENTMANAGERWINDOW_H
#define INSTRUMENTMANAGERWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include "APIManager.h"

class InstrumentManagerWindow : public QWidget {
    Q_OBJECT

public:
    explicit InstrumentManagerWindow(APIManager* apiManager, QWidget *parent = nullptr);

private slots:
    void goToLogin();
    void refreshTable();
    void addInstrument();
    void modifyInstrument();
    void deleteInstrument();
    void populateFieldsFromTable(int row, int column);

private:
    APIManager* apiManager;
    QTableWidget* instrumentTable;

    // Form fields
    QLineEdit* isinEntry;
    QLineEdit* micEntry;
    QLineEdit* currencyEntry;
    QLineEdit* statusEntry;

    // Buttons
    QPushButton* logoutButton;
    QPushButton* refreshButton;
    QPushButton* addButton;
    QPushButton* modifyButton;
    QPushButton* deleteButton;

    void populateInstrumentTable();
};

#endif // INSTRUMENTMANAGERWINDOW_H
