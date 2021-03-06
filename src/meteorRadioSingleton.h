/*
 * @brief Синглтон работы ПО моделирования метеорной радиосвязи
 * meteorRadioSingleton.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>

class QTranslator;

class meteorRadioStationsFactory;
class PatrolSingleton;
class GISPatrolDatabase;
class meteorLoader;
class meteorWriter;
class meteorTraceGenerationFactory;

class meteorRadioSingleton : public QObject {
public:
    static meteorRadioSingleton* getMeteorRadioS( QObject* parent = nullptr );
    static void resetMRS();
    static PatrolSingleton* getPatrol();

    meteorRadioStationsFactory* getMRS() const { return _mrsF; }
    void installTranslator() const;

private:
    meteorRadioSingleton( QObject* parent=nullptr ) ;
    ~meteorRadioSingleton();
    meteorRadioSingleton( const meteorRadioSingleton& MRS ) = delete;
    meteorRadioSingleton& operator=( const meteorRadioSingleton& MRS ) = delete;

    static meteorRadioSingleton* _instance;

    GISPatrolDatabase* _mDb;
    meteorLoader* _mLoader;
    meteorWriter* _mWriter;
    meteorRadioStationsFactory* _mrsF;
    meteorTraceGenerationFactory* _mTrGF;
    static PatrolSingleton* _patrolInstance;
    QTranslator* _meteorTor;

private:
    Q_OBJECT
};
