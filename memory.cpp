#include "memory.h"

memory::memory(QObject *parent) :
    QAbstractListModel(parent)
{
//    m_data
//            << Data(0)
//            << Data(10)
//            << Data (20)
//            << Data (30);

}

int memory::rowCount( const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant memory::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    const Data &data = m_data.at(index.row());
    if ( role == value )
         return data.value;
    else
        return QVariant();
}
QHash<int, QByteArray> memory::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {value, "value"},
    };
    return mapping;
}

void memory::removeData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    qDebug() << "remove data: " << row << " " << m_data[row].value;
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void memory::insertData(int data)
{
    qDebug() << "insert data memory list";
    QVector<Data> dataInsert;
    dataInsert << Data(data);
    beginInsertRows(QModelIndex(), 0, 0);
    m_data.insert(0, data);
    endInsertRows();
}

void memory::onMplusClick(int row)
{
    Data currentData = m_data[row];
    currentData.value += m_data[0].value;
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
    beginInsertRows(QModelIndex(), row, row);
    m_data.insert(row, currentData);
    endInsertRows();
}

void memory::onMmineClick(int row)
{
    Data currentData = m_data[row];
    currentData.value -= m_data[0].value;
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
    beginInsertRows(QModelIndex(), row, row);
    m_data.insert(row, currentData);
    endInsertRows();
}

void memory::onClearDataClick()
{
   qDebug() << "length memory Lits: " << m_data.count();
   for (int i = 0; i < m_data.count(); i++){
       removeData(i);
   }
}
