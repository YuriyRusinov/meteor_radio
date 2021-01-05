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

message::message( const char* ipBuffer, const string& smess )
    : _ipAddress( ipBuffer != nullptr ? new char [strlen(ipBuffer)] : nullptr ),
    _message( smess ) {
    if( ipBuffer != nullptr )
        strncpy( _ipAddress, ipBuffer, strlen(ipBuffer) );
}

message::message( const message& mess )
    : _ipAddress( mess._ipAddress != nullptr ? new char [strlen(mess._ipAddress)] : nullptr ),
    _message( mess._message ) {
    if( mess._ipAddress != nullptr )
        strncpy( _ipAddress, mess._ipAddress, strlen(mess._ipAddress) );
}

message& message::operator= ( const message& mess ) {
    if( this != &mess ) {
        if( _ipAddress != nullptr )
            delete [] _ipAddress;

        _ipAddress = nullptr;

        if( mess._ipAddress != nullptr ) {
            _ipAddress = new char [strlen(mess._ipAddress)];
            strncpy( _ipAddress, mess._ipAddress, strlen(mess._ipAddress) );
        }
        _message = mess._message;
    }
    return *this;
}

message::~message() {
    if( _ipAddress != nullptr )
        delete [] _ipAddress;
}

const char* message::getAddress() const {
    return _ipAddress;
}

void message::setAddress( const char* ipBuffer ) {
    if( _ipAddress != nullptr )
        delete [] _ipAddress;

    _ipAddress = nullptr;

    if( ipBuffer != nullptr ) {
        _ipAddress = new char [strlen(ipBuffer)];
        strncpy( _ipAddress, ipBuffer, strlen(ipBuffer));
    }

}

string message::getMess() const {
    return _message;
}

void message::setMess( const string& smess ) {
    _message = smess;
}
