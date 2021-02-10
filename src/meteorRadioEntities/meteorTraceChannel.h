/*
 * @brief Класс модели метеорного следа
 * meteorTraceChannel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

class meteorTraceChannel {
public:
    meteorTraceChannel( double time_trace_arise = -1.0, double d_time_trace = -1.0, double baud_rate = -1.0 );
    meteorTraceChannel( const meteorTraceChannel& MTC );
    meteorTraceChannel& operator= ( const meteorTraceChannel& MTC );
    ~meteorTraceChannel();

    double getAriseTime() const;
    void setArseTime( double time_trace_arise );

    double getTimeTrace() const;
    void setTimeTrace( double dt );

    double getBaudRate() const;
    void setBaudRate( double br );
private:
    //
    // Время возникновения следа
    //
    double _time_trace_arising; 
    //
    // Время между следами
    //
    double _d_time_trace;
    //
    // Скорость передачи данных
    //
    double _baud_rate;
};
