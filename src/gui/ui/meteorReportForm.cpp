/*
 * @brief Форма статистического отчета о количестве сообщений, объеме, метеорных следах
 * meteorReportForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QTextStream>

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
    _UI->lEAveSpeed->setReadOnly( true );
    _UI->lESpeedSt->setReadOnly( true );

    QObject::connect( _UI->pbSave, &QAbstractButton::clicked, this, &meteorReportForm::saveResults );
    QObject::connect( _UI->pbClose, &QAbstractButton::clicked, this, &meteorReportForm::close );
}

meteorReportForm::~meteorReportForm() {
    delete _UI;
}

void meteorReportForm::updateReport( int messNum, int bytesNum, int tracesNum, qint64 dtMSec, double aveMeteorTraceTime, double aveMeteorTraceAriseTime, double aveMeteorTracePower, double aveSpeed, double stSpeed ) {
    _UI->lEMessNumber->setText( QString::number( messNum ) );
    _UI->lEBytesNumber->setText( QString::number( bytesNum ) );
    _UI->lETracesNumber->setText( QString::number( tracesNum ) );
    _UI->lEModelTime->setText( QString::number( dtMSec/1000.0 ) );
    _UI->lETraceAverage->setText( QString::number( aveMeteorTraceTime ) );
    _UI->lEWaitAverage->setText( QString::number( aveMeteorTraceAriseTime ) );
    _UI->lEAveTracePower->setText( QString::number( aveMeteorTracePower ) );
    _UI->lEAveSpeed->setText( QString::number( aveSpeed ) );
    _UI->lESpeedSt->setText( QString::number( stSpeed ) );
}

void meteorReportForm::setModel( QAbstractItemModel* mod ) {
    QAbstractItemModel * oldMod = _UI->tvDist->model();
    _UI->tvDist->setModel( mod );
    if( oldMod && oldMod != mod )
        delete oldMod;
}

void meteorReportForm::saveResults() {
    QString fileName = QFileDialog::getSaveFileName( this, tr("Save results"), QDir::currentPath(), tr("Data files (*.dat);;All files (*)") );
    if( fileName.isEmpty() )
        return;

    QFile fRes( fileName );
    fRes.open( QIODevice::Append );
    QTextStream fResStr( &fRes );
    int n = _UI->tvDist->model()->rowCount();
    double dist = 0.0;
    double allAverage = 0.0;
    double st = 0.0;

    for (int i=0; i<n; i++) {
        QModelIndex dIndex = _UI->tvDist->model()->index(i, 0);
        dist = _UI->tvDist->model()->data( dIndex, Qt::DisplayRole ).toDouble();
        QModelIndex aveIndex = _UI->tvDist->model()->index(i, 1);
        allAverage = _UI->tvDist->model()->data( aveIndex, Qt::DisplayRole ).toDouble();
        QModelIndex stIndex = _UI->tvDist->model()->index(i, 2);
        st = _UI->tvDist->model()->data( stIndex, Qt::DisplayRole ).toDouble() ;
        fResStr << qSetFieldWidth( 14 ) << qSetRealNumberPrecision(12) <<  dist << ' ' << allAverage << ' ' << st << Qt::endl;
    }
    fResStr << Qt::endl;
    //fResStr << qSetFieldWidth( 14 ) << qSetRealNumberPrecision(12) <<  dist << ' ' << allAverage/n << ' ' << st;
}

void meteorReportForm::close() {
    QMdiSubWindow* mdiChild = qobject_cast<QMdiSubWindow*>(this->parentWidget());
    QWidget::close();
    if( mdiChild )
        mdiChild->close();
}
