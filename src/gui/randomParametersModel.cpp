/*
 * @brief Модель визуального отображения списка параметров случайных чисел
 * randomParametersModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include <randomNumbGenerator.h>
#include "randomParametersModel.h"

randomParametersModel::randomParametersModel( QSharedPointer< randomNumbersGenerator > rng, QObject *parent )
    : QAbstractItemModel( parent ),
    _rng( rng ) {
}

randomParametersModel::~randomParametersModel() {
}

int	randomParametersModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent );
    return 1;
}

int	randomParametersModel::rowCount( const QModelIndex& parent ) const {
    if( parent.isValid() )
        return 0;

    switch( _rng->getDistrib() ) {
        case DistributionFunc::_Undefined: default: return 0; break;
        case DistributionFunc::_Uniform: case DistributionFunc::_Gaussian: return 2; break;
        case DistributionFunc::_Exponential: case DistributionFunc::_Rayleigh: return 1; break;
    }
}

QModelIndex randomParametersModel::index (int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() || column < 0 || column >= 1)
        return QModelIndex();

    quintptr indId = row;
    QModelIndex resInd = createIndex(row, column, indId);
    return resInd;
}

QModelIndex randomParametersModel::parent (const QModelIndex& index) const {
    Q_UNUSED( index );
    return QModelIndex();
}

Qt::ItemFlags randomParametersModel::flags( const QModelIndex &index ) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant randomParametersModel::data (const QModelIndex& index, int role) const {
    if(role == Qt::UserRole+2)
        return QVariant::fromValue< QSharedPointer< randomNumbersGenerator > > (_rng);

    int i = index.row();
    if( role == Qt::DisplayRole && !_rng.isNull() ) {
//        qDebug() << __PRETTY_FUNCTION__ << i << _rng->getParamSize();
        if( i >= 0 && i < _rng->getParamSize() )
            return _rng->at(i);
    }
    return QVariant();
}

bool randomParametersModel::setData (const QModelIndex& index, const QVariant& value, int role) {
    if( role == Qt::UserRole+2 ) {
        QSharedPointer< randomNumbersGenerator > wrng = value.value< QSharedPointer< randomNumbersGenerator > >();
        _rng = wrng;
        emit dataChanged( index, index );
        return true;
    }

    int i = index.row();
    if( (role == Qt::DisplayRole || role == Qt::EditRole) && i >=0 && i < _rng->getParamSize() ) {
        _rng->operator[](i) = value.toDouble ();
        emit dataChanged( index, index );
        return true;
    }

    return false;
}

QVariant randomParametersModel::headerData (int section, Qt::Orientation orientation, int role) const {
    if( orientation == Qt::Horizontal && section == 0 )
        return tr("Parameter value");

    return QVariant();
}
