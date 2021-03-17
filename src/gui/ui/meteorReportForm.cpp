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
}

meteorReportForm::~meteorReportForm() {
    delete _UI;
}

void meteorReportForm::updateReport( int messNum, int bytesNum, int tracesNum, qint64 dtMSec ) {
    _UI->lEMessNumber->setText( QString::number( messNum ) );
    _UI->lEBytesNumber->setText( QString::number( bytesNum ) );
    _UI->lETracesNumber->setText( QString::number( tracesNum ) );
    _UI->lEModelTime->setText( QString::number( dtMSec ) );
}
