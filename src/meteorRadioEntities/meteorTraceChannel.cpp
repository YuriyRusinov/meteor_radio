/*
 * @brief Класс модели метеорного следа
 * meteorTraceChannel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorTraceChannel.h"

meteorTraceChannel::meteorTraceChannel( double time_trace_arise, double d_time_trace, double channel_power, double elev, double scatter )
    : _time_trace_arising( time_trace_arise ),
    _d_time_trace( d_time_trace ),
    _channel_power( channel_power ), 
    _elevAngle( elev ),
    _scatterAngle( scatter ) {
}

meteorTraceChannel::meteorTraceChannel( const meteorTraceChannel& MTC )
    : _time_trace_arising( MTC._time_trace_arising ),
    _d_time_trace( MTC._d_time_trace ),
    _channel_power( MTC._channel_power ),
    _elevAngle( MTC._elevAngle ),
    _scatterAngle( MTC._scatterAngle ) {
}

meteorTraceChannel& meteorTraceChannel::operator= ( const meteorTraceChannel& MTC ) {
    if( &MTC != this ) {
        _time_trace_arising = MTC._time_trace_arising;
        _d_time_trace = MTC._d_time_trace;
        _channel_power = MTC._channel_power;
        _elevAngle = MTC._elevAngle;
        _scatterAngle = MTC._scatterAngle;
    }
    return *this;
}

meteorTraceChannel::~meteorTraceChannel() {
}

double meteorTraceChannel::getAriseTime() const {
    return _time_trace_arising;
}

void meteorTraceChannel::setArseTime( double time_trace_arise ) {
    _time_trace_arising = time_trace_arise;
}

double meteorTraceChannel::getTimeTrace() const {
    return _d_time_trace;
}

void meteorTraceChannel::setTimeTrace( double dt ) {
    _d_time_trace = dt;
}

double meteorTraceChannel::getChannelPower() const {
    return _channel_power;
}

void meteorTraceChannel::setChannelPower( double chp ) {
    _channel_power = chp;
}

double meteorTraceChannel::getElevationAngle() const {
    return _elevAngle;
}

void meteorTraceChannel::setElevationAngle( double elev ) {
    _elevAngle = elev;
}

double meteorTraceChannel::getScatterAngle() const {
    return _scatterAngle;
}

void meteorTraceChannel::setScatterAngle( double scatter ) {
    _scatterAngle = scatter;
}
