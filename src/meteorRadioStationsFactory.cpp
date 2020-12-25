/*
 * @brief Фабрика генерации станций связи
 * meteorRadioStationsFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QWidget>
#include "meteorRadioNetworkForm.h"
#include "meteorRadioStationsFactory.h"

QWidget* meteorRadioStationsFactory::GUIStationsParameters( QWidget* parent, Qt::WindowFlags flags ) const {
    QWidget* w = new meteorRadioNetworkForm( parent, flags );
    return w;
}

meteorRadioStationsFactory::meteorRadioStationsFactory( QObject* parent ) : QObject( parent ) {}

meteorRadioStationsFactory::~meteorRadioStationsFactory() {}
