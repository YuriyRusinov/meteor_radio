/*
 * @brief Модель визуального отображения списка станций метеорной радиосвязи
 * meteorRadioStationsModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorRadioStation.h"
#include "meteorRadioStationsModel.h"

meteorRadioStationsModel::meteorRadioStationsModel( const QVector< QSharedPointer< meteorRadioStation > >& mStations, QObject *parent )
    : QAbstractItemModel( parent ),
    _mStations( mStations ), isCheckSt( mStations.size() ) {
    int nst = mStations.size();
    for( int i=0; i<nst; i++ ) {
        isCheckSt[i] = Qt::Unchecked;
    }
}

meteorRadioStationsModel::~meteorRadioStationsModel() {
}

int	meteorRadioStationsModel::columnCount( const QModelIndex & /*parent*/ ) const {
    return 8;
}

int	meteorRadioStationsModel::rowCount( const QModelIndex& parent ) const {
    if( parent.isValid() )
        return 0;

    return _mStations.size();
}

QModelIndex meteorRadioStationsModel::index( int row, int column, const QModelIndex& parent ) const {
    if( parent.isValid() && parent.column() != 0 )
        return QModelIndex();

    return createIndex(row, column, (void*)_mStations[row].get());
}

QModelIndex meteorRadioStationsModel::parent( const QModelIndex& index ) const {
    Q_UNUSED( index );
    return QModelIndex();
}

Qt::ItemFlags meteorRadioStationsModel::flags (const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant meteorRadioStationsModel::data (const QModelIndex& index, int role ) const {
    if( !index.isValid() )
        return QVariant();

    int row = index.row();
    if( role == Qt::UserRole )
        return _mStations[row]->getId();

    if( role == Qt::UserRole+2 )
        return QVariant::fromValue<QSharedPointer< meteorRadioStation >>(_mStations[row]);

    int column = index.column();
    if( role == Qt::DisplayRole ) {
        switch( column ) {
            case 0: return _mStations[row]->getId(); break;
            case 1: return _mStations[row]->getStationNumber(); break;
            case 2: return _mStations[row]->getAddress(); break;
            case 3: return _mStations[row]->getLongitude(); break;
            case 4: return _mStations[row]->getLatitude(); break;
            case 5: return _mStations[row]->getSrid(); break;
            case 6: return _mStations[row]->getFrequency(); break;
            case 7: return tr("Generator of random messages"); break;
            case 8: return _mStations[row]->getType(); break;
        }
    }
    if( role == Qt::CheckStateRole && column == 0 )
        return isCheckSt[row];

    return QVariant();
}

bool meteorRadioStationsModel::setData (const QModelIndex& index, const QVariant& value, int role ) {
    if( role == Qt::CheckStateRole && index.column() == 0 ) {
        Qt::CheckState chVal = value.value<Qt::CheckState>();
        int row = index.row();
        isCheckSt[row] = chVal;
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant meteorRadioStationsModel::headerData (int section, Qt::Orientation orientation, int role ) const {
    QStringList headers;
    headers << tr("id")
            << tr("Number")
            << tr("Station Address")
            << tr("Longitude")
            << tr("Latitude")
            << tr("Projection")
            << tr("Frequency")
            << tr("Messages generator")
            << tr("Type");
    if( section >= 0 && section < 8 && orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return headers[section];

    return QVariant();
}

bool meteorRadioStationsModel::insertRows (int row, int count, const QModelIndex& parent ) {
}

bool meteorRadioStationsModel::removeRows (int row, int count, const QModelIndex& parent ) {

}
