#ifndef MEMORY_H
#define MEMORY_H
#include <QAbstractListModel>

struct Data{
    Data(){}
    Data(const int value):value(value){}
    int value;
};

class memory : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
            indexData,
            value
        };
    explicit memory(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void removeData(int row);
    void insertData(int data);
    void onMplusClick(int row);
    void onMmineClick(int row);
    void onClearDataClick();
private:
    QVector<Data> m_data;
};

#endif // MEMORY_H
