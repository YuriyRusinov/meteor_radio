/*
 * @brief Модель визуального отображения списка параметров случайных чисел
 * randomParametersModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QAbstractItemModel>
#include <QSharedPointer>
#include <memory>

using std::shared_ptr;

class randomNumbersGenerator;

class randomParametersModel : public QAbstractItemModel {
public:
    randomParametersModel( shared_ptr< randomNumbersGenerator > rng = nullptr, QObject *parent = nullptr );
    virtual ~randomParametersModel();

    int	columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int	rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags( const QModelIndex &index ) const override;

    QModelIndex index (int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent (const QModelIndex& index) const override;
    
    QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    shared_ptr< randomNumbersGenerator > _rng;

private:
    Q_OBJECT
};
