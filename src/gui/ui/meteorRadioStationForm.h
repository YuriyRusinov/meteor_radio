/*
 * @brief Форма добавления/редактирования параметров станций связи
 * meteorRadioStationForm.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QWidget>

class meteorRadioStation;

namespace Ui {
    class meteor_radio_station_form;
}

class meteorRadioStationForm : public QWidget {
public:
    meteorRadioStationForm( QSharedPointer< meteorRadioStation > mrs, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~meteorRadioStationForm();

private slots:
    void distribFuncChanged(int index);
    void close();
    void saveStation();
    void accept();

signals:
    void saveMeteorRadioStation( QSharedPointer< meteorRadioStation > );

private:
    void init();

private:
    QSharedPointer< meteorRadioStation > _meteorRadioStation;
    Ui::meteor_radio_station_form* _UI;

private:
    Q_OBJECT
};
