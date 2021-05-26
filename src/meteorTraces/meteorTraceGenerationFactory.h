/*
 * @brief Фабрика генерации следов метеоров подходящих для радиосвязи
 * meteorTraceGenerationFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>
#include <QSharedPointer>
#include <memory>

#include <gsl/gsl_matrix.h>

#include <matrix.h>

class meteorTraceChannel;
class meteorRadioStationsFactory;
class meteorTraceController;

using std::unique_ptr;
using std::weak_ptr;

class meteorTraceGenerationFactory : public QObject {
public:
    QSharedPointer< meteorTraceChannel > generate() const;
    int getTracesNumber() const;

    double getAveAriseTime() const;
    double getAveDurationTime() const;
    double getAvePower() const;
    double getStArise() const;

    void setDistances( const Matrix& matrDist );

private slots:
    void stopTraceGen();
    void setTraceParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, double elevMin, double elevMax, double scatterMin, double scatterMax );
    void retransmitMeteorTrace( QSharedPointer< meteorTraceChannel > mtc );

signals:
    void sendTrace( QSharedPointer< meteorTraceChannel > );

private:
    meteorTraceGenerationFactory( QObject* parent = nullptr );
    meteorTraceGenerationFactory( const meteorTraceGenerationFactory& MTGF ) = delete;
    meteorTraceGenerationFactory& operator=( const meteorTraceGenerationFactory& MTGF ) = delete;
    virtual ~meteorTraceGenerationFactory();

    void setStationFactory( meteorRadioStationsFactory* rsf );

    friend class meteorRadioSingleton;
    meteorRadioStationsFactory* _mRSF;
    QSharedPointer< int > _traceCounter;
    meteorTraceController* _mTraceController;

    //
    // Априорные параметры генерации метеорных следов
    //
    double _ariseMathExp;
    double _existanceTimeMathExp;
    double _existanceTimeSt;
    double _aveAmpl;
    //
    // Апостериорные параметры генерации набора следов
    //
    double _aveMeteorDurationTraceTime;
    double _aveMeteorAriseTime;
    double _stMeteorTraceTime;
    double _aveMeteorTracePower;

    std::vector< double > _ariseTime;
    Matrix _mDistances;

private:
    Q_OBJECT
};
