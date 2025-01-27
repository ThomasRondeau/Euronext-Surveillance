#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QVector>
#include <QString>

enum class DataType {
    TRADES,
    ORDERS,
    FIRMS
};

class SearchableTableWidget : public QWidget {
    Q_OBJECT

public:
    explicit SearchableTableWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        setupConnections();
    }

private:
    QTableWidget* table;
    QComboBox* dataTypeSelector;
    QVector<QLineEdit*> searchFields;
    QVBoxLayout* mainLayout;

    void setupUI() {
        mainLayout = new QVBoxLayout(this);

        dataTypeSelector = new QComboBox(this);
        dataTypeSelector->addItem("Trades passés", static_cast<int>(DataType::TRADES));
        dataTypeSelector->addItem("Ordres passés", static_cast<int>(DataType::ORDERS));
        dataTypeSelector->addItem("Firmes autorisées", static_cast<int>(DataType::FIRMS));
        mainLayout->addWidget(dataTypeSelector);

        table = new QTableWidget(this);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSortingEnabled(true);
        mainLayout->addWidget(table);

        setLayout(mainLayout);
    }

    void setupConnections() {
        connect(dataTypeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SearchableTableWidget::onDataTypeChanged);
    }

    void loadTradesData() {
        table->clear();
        table->setColumnCount(5);
        table->setHorizontalHeaderLabels({ "ID", "Date", "Symbol", "Quantité", "Prix" });
        setupSearchFields({ "ID", "Date", "Symbol", "Quantité", "Prix" });
    }

    void loadOrdersData() {
        table->clear();
        table->setColumnCount(6);
        table->setHorizontalHeaderLabels({ "ID", "Date", "Symbol", "Type", "Quantité", "Prix" });
        setupSearchFields({ "ID", "Date", "Symbol", "Type", "Quantité", "Prix" });
    }

    void loadFirmsData() {
        table->clear();
        table->setColumnCount(4);
        table->setHorizontalHeaderLabels({ "ID", "Nom", "Statut", "Date d'autorisation" });
        setupSearchFields({ "ID", "Nom", "Statut", "Date d'autorisation" });
    }

    void setupSearchFields(const QStringList& headers) {
        for (auto* field : searchFields) {
            delete field;
        }
        searchFields.clear();

        QWidget* searchWidget = new QWidget(this);
        QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);

        for (const QString& header : headers) {
            QLineEdit* searchField = new QLineEdit(this);
            searchField->setPlaceholderText("Rechercher " + header);
            searchFields.append(searchField);
            searchLayout->addWidget(searchField);

            connect(searchField, &QLineEdit::textChanged,
                this, &SearchableTableWidget::filterTable);
        }

        mainLayout->insertWidget(1, searchWidget);
    }

private slots:
    void onDataTypeChanged(int index) {
        DataType type = static_cast<DataType>(dataTypeSelector->itemData(index).toInt());
        switch (type) {
        case DataType::TRADES:
            loadTradesData();
            break;
        case DataType::ORDERS:
            loadOrdersData();
            break;
        case DataType::FIRMS:
            loadFirmsData();
            break;
        }
    }

    void filterTable() {
        for (int row = 0; row < table->rowCount(); ++row) {
            bool rowMatch = true;

            for (int col = 0; col < table->columnCount(); ++col) {
                QString searchText = searchFields[col]->text().toLower();
                if (!searchText.isEmpty()) {
                    QString cellText = table->item(row, col)->text().toLower();
                    if (!cellText.contains(searchText)) {
                        rowMatch = false;
                        break;
                    }
                }
            }

            table->setRowHidden(row, !rowMatch);
        }
    }
};