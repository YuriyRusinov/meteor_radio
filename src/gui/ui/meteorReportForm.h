/*
 * @brief Форма статистического отчета о количестве сообщений, объеме, метеорных следах
 * meteorReportForm.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QWidget>

class QAbstractItemModel;

namespace Ui {
    class meteor_report_form;
}

class meteorReportForm : public QWidget {
public:
    meteorReportForm( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~meteorReportForm();

    void setModel( QAbstractItemModel* mod );

private slots:
    void updateReport( int messNum, int bytesNum, int tracesNum, qint64 dtMSec, double aveMeteorTraceTime=0.0, double aveMeteorTraceAriseTime=0.0, double aveMeteorTracePower=0.0, double aveSpeed=0.0, double stSpeed=0.0 );
    void saveResults();
    void close();

private:
    Ui::meteor_report_form* _UI;
    friend class meteorRadioStationsFactory;

private:
    Q_OBJECT
};
