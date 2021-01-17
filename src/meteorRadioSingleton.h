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

class meteorRadioStationsFactory;
class PatrolSingleton;
class meteorLoader;
class meteorWriter;

class meteorRadioSingleton : public QObject {
public:
    static meteorRadioSingleton* getMeteorRadioS( QObject* parent = nullptr );
    static void resetMRS();
    static PatrolSingleton* getPatrol();

    meteorRadioStationsFactory* getMRS() const { return _mrsF; }

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
    static PatrolSingleton* _patrolInstance;

private:
    Q_OBJECT
};
