/*
 * @brief Модель визуального отображения списка параметров случайных чисел
 * randomParametersModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

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
        case DistributionFunc::_Exponential: return 1; break;
    }
}

QModelIndex randomParametersModel::index (int row, int column, const QModelIndex& parent) const {
}

QModelIndex randomParametersModel::parent (const QModelIndex& index) const {
}

QVariant randomParametersModel::data (const QModelIndex& index, int role) const {
}

bool randomParametersModel::setData (const QModelIndex& index, const QVariant& value, int role) {
}

QVariant randomParametersModel::headerData (int section, Qt::Orientation orientation, int role) const {

}
