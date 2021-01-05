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
    message( const char* ipBuffer=nullptr, const string& smess=string() );
    message( const message& mess );
    message& operator= ( const message& mess );
    ~message();

    const char* getAddress() const;
    void setAddress( const char* ipBuffer );

    string getMess() const;
    void setMess( const string& smess );
private:
    char* _ipAddress;
    string _message;
};
