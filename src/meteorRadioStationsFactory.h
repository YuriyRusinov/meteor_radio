/*
 * @brief Фабрика генерации станций связи
 * meteorRadioStationsFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QScopedPointer>
#include <QObject>

#include <memory>

class meteorLoader;
class meteorWriter;

class meteorRadioStationsFactory : public QObject {
public:
    QWidget* GUIStationsParameters( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) const;

private slots:
    void addMeteorStation( QAbstractItemModel* stationsModel );
    void editMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void delMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );

private:
    meteorRadioStationsFactory( meteorLoader* ml = nullptr, meteorWriter* mw = nullptr, QObject* parent = nullptr );
    meteorRadioStationsFactory( const meteorRadioStationsFactory& ) = delete;
    meteorRadioStationsFactory& operator=( const meteorRadioStationsFactory& ) = delete;
    virtual ~meteorRadioStationsFactory();

    friend class meteorRadioSingleton;

    QScopedPointer< meteorLoader > _mLoader;
    QScopedPointer< meteorWriter > _mWriter;

private:
    Q_OBJECT
};
