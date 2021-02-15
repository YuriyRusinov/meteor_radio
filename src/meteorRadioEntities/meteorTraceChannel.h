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
    meteorTraceChannel( double time_trace_arise = -1.0, double d_time_trace = -1.0, double channel_power = -1.0 );
    meteorTraceChannel( const meteorTraceChannel& MTC );
    meteorTraceChannel& operator= ( const meteorTraceChannel& MTC );
    ~meteorTraceChannel();

    double getAriseTime() const;
    void setArseTime( double time_trace_arise );

    double getTimeTrace() const;
    void setTimeTrace( double dt );

    double getChannelPower() const;
    void setChannelPower( double chp );
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
    // Амплитуда канала
    //
    double _channel_power;
};
