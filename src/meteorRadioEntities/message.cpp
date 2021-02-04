/*
 * @brief Класс сообщения, отправляемого по метеорной связи 
 * message.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <string.h>
#include "message.h"

message::message( const string& ipBuffer, const string& smess )
    : _ipAddress( ipBuffer ),
    _message( smess ) {
}

message::message( const message& mess )
    : _ipAddress( mess._ipAddress ),
    _message( mess._message ) {
}

message& message::operator= ( const message& mess ) {
    if( this != &mess ) {
        _ipAddress = mess._ipAddress;
        _message = mess._message;
    }
    return *this;
}

message::~message() {
}

const string& message::getAddress() const {
    return _ipAddress;
}

void message::setAddress( const string& ipBuffer ) {
    _ipAddress = ipBuffer;
}

string message::getMess() const {
    return _message;
}

void message::setMess( const string& smess ) {
    _message = smess;
}
