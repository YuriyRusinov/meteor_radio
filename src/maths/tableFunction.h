/*
 * @brief Класс значений функции, заданной таблично
 * tableFunction.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <iostream>
#include <vector>

using std::istream;
using std::ostream;
using std::vector;

class funct2Point {
public:
    funct2Point(double x=0.0, double y=0.0, double dy=-1.0);

    double getX() const;
    void setX( double x );

    double getY() const;
    void setY( double y );

    double getDY() const;
    void setDY( double dy );
    
    bool operator< ( const funct2Point& P );

private:
    double _xarg;
    double _yfun;
    double _dyfun;
};

class tableFunction : public vector< funct2Point > {
public:
    tableFunction( int n=0 );
    tableFunction( const tableFunction& TF );

    friend istream& operator>> (istream& f, tableFunction& vfun );
    friend ostream& operator<< (ostream& f, const tableFunction& vfun );
};
