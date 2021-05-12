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

namespace Ui {
    class meteor_report_form;
}

class meteorReportForm : public QWidget {
public:
    meteorReportForm( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~meteorReportForm();

private slots:
    void updateReport( int messNum, int bytesNum, int tracesNum, qint64 dtMSec, double aveMeteorTraceTime=0.0, double aveMeteorTraceAriseTime=0.0, double aveMeteorTracePower=0.0 );

private:
    Ui::meteor_report_form* _UI;
    friend class meteorRadioStationsFactory;

private:
    Q_OBJECT
};
