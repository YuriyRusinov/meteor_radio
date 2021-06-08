/*
 * @brief Класс значений функции, заданной таблично
 * tableFunction.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <iomanip>
#include <string>
#include <sstream>

#include "tableFunction.h"

using std::endl;
using std::stringstream;
using std::string;
using std::setw;
using std::setprecision;

funct2Point::funct2Point(double x, double y, double dy)
    : _xarg( x ),
    _yfun( y ),
    _dyfun( dy ) {}

double funct2Point::getX() const {
    return _xarg;
}

void funct2Point::setX( double x ) {
    _xarg = x;
}

double funct2Point::getY() const {
    return _yfun;
}

void funct2Point::setY( double y ) {
    _yfun = y;
}

double funct2Point::getDY() const {
    return _dyfun;
}

void funct2Point::setDY( double dy ) {
    _dyfun = dy;
}

bool funct2Point::operator< ( const funct2Point& P ) {
    return _xarg < P._xarg;
}

tableFunction::tableFunction( int n )
    : vector< funct2Point >( n ) {}

tableFunction::tableFunction( const tableFunction& TF )
    : vector< funct2Point >( TF ) {}

istream& operator>> (istream& f, tableFunction& vfun ) {
    vfun.clear();
    while( !f.eof( ) ) {
        string fstr;
        getline( f, fstr );
        if( fstr.size() == 0 )
            continue;
        double x, y, dy;
        stringstream sFun( fstr );
        sFun >> x >> y >> dy;
        funct2Point P (x, y, dy );
        vfun.push_back( P );
    }
    return f;
}

ostream& operator<< (ostream& f, const tableFunction& vfun ) {
    int n = vfun.size();
    for(int i=0; i<n; i++) {
        stringstream sOut;
        sOut << setw(14) << setprecision(12) << vfun[i].getX()/1000.0 << ' '
             << setw(14) << setprecision(12) << vfun[i].getY() << ' '
             << setw(14) << setprecision(12) << vfun[i].getDY();
        f << sOut.str() << endl;
    }
    return f;
}
