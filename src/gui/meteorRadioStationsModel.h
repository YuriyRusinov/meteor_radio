/*
 * @brief Модель визуального отображения списка станций метеорной радиосвязи
 * meteorRadioStationsModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QAbstractItemModel>
#include <QSharedPointer>
#include <QVector>

class meteorRadioStation;

class meteorRadioStationsModel : public QAbstractItemModel {
public:
    meteorRadioStationsModel( const QVector< QSharedPointer< meteorRadioStation > >& mStations = QVector< QSharedPointer< meteorRadioStation > >(), QObject *parent = nullptr );
    virtual ~meteorRadioStationsModel();

    int	columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int	rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex index (int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent (const QModelIndex& index) const override;
    
    Qt::ItemFlags flags (const QModelIndex& index) const override;

    QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool insertRows (int row, int count, const QModelIndex& parent = QModelIndex() ) override;
    bool removeRows (int row, int count, const QModelIndex& parent = QModelIndex() ) override;

private:
    QVector< QSharedPointer< meteorRadioStation > > _mStations;

private:
    Q_OBJECT
};
