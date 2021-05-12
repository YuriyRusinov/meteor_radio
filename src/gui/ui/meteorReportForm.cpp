/*
 * @brief Форма статистического отчета о количестве сообщений, объеме, метеорных следах
 * meteorReportForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorReportForm.h"
#include "ui_meteor_report_form.h"

meteorReportForm::meteorReportForm( QWidget* parent, Qt::WindowFlags flags ) 
    : QWidget( parent, flags ),
    _UI( new Ui::meteor_report_form ) {
    _UI->setupUi( this );
    _UI->lEMessNumber->setReadOnly( true );
    _UI->lEBytesNumber->setReadOnly( true );
    _UI->lETracesNumber->setReadOnly( true );
    _UI->lEModelTime->setReadOnly( true );
    _UI->lETraceAverage->setReadOnly( true );
    _UI->lEWaitAverage->setReadOnly( true );
    _UI->lEAveTracePower->setReadOnly( true );
}

meteorReportForm::~meteorReportForm() {
    delete _UI;
}

void meteorReportForm::updateReport( int messNum, int bytesNum, int tracesNum, qint64 dtMSec, double aveMeteorTraceTime, double aveMeteorTraceAriseTime, double aveMeteorTracePower ) {
    _UI->lEMessNumber->setText( QString::number( messNum ) );
    _UI->lEBytesNumber->setText( QString::number( bytesNum ) );
    _UI->lETracesNumber->setText( QString::number( tracesNum ) );
    _UI->lEModelTime->setText( QString::number( dtMSec/1000.0 ) );
    _UI->lETraceAverage->setText( QString::number( aveMeteorTraceTime ) );
    _UI->lEWaitAverage->setText( QString::number( aveMeteorTraceAriseTime ) );
    _UI->lEAveTracePower->setText( QString::number( aveMeteorTracePower ) );
}
