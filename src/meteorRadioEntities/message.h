/*
 * @brief Класс сообщения, отправляемого по метеорной связи 
 * message.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <string>

using std::string;

class message {
public:
    message( const string& ipBuffer=string(), const string& smess=string() );
    message( const message& mess );
    message& operator= ( const message& mess );
    ~message();

    const string& getAddress() const;
    void setAddress( const string& ipBuffer );

    string getMess() const;
    void setMess( const string& smess );
private:
    string _ipAddress;
    string _message;
};
