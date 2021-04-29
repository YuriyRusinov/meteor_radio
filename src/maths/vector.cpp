/*
 * @brief Класс векторов, используемых в расчетах, базируется на основе gsl_vector
 * vector.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <cmath>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "vector.h"

using std::out_of_range;
using std::cout;
using std::logic_error;
using std::endl;
using std::stringstream;

Vector::Vector( const double* v_data, size_t n )
    : _vData( gsl_vector_alloc( n ) ),
    _n( n ) {
    for( int i=0; i<n; i++ ) {
        gsl_vector_set( _vData, i, v_data[i] );
    }
}

Vector::Vector( double value, size_t n )
    : _vData( gsl_vector_alloc( n ) ),
    _n( n ) {
    gsl_vector_set_all( _vData, value );
}

Vector::Vector( const Vector& V )
    : _vData( gsl_vector_alloc( V._n ) ),
    _n( V._n ) {
    gsl_vector_memcpy( _vData, V._vData );
}

Vector::Vector( Vector&& V )
    : _vData( nullptr ),
    _n( V._n ) {
    gsl_vector_swap( _vData, V._vData );
}

Vector& Vector::operator=( const Vector& V ) {
    if( this != &V ) {
        if( _vData != nullptr )
            gsl_vector_free( _vData );
        _vData = gsl_vector_alloc( V._n );
        gsl_vector_memcpy( _vData, V._vData );
        _n = V._n;
    }
    return *this;
}

Vector::~Vector() {
    gsl_vector_free( _vData );
}

const double& Vector::operator() ( const size_t i ) const {
    return *gsl_vector_const_ptr( _vData, i );
}

double& Vector::operator() ( const size_t i ) {
    return *gsl_vector_ptr( _vData, i );
}

Vector& Vector::operator+=( const Vector& V ) {
    if( _n != V._n ) {
        throw out_of_range("Invalid sizes of vectors");
    }
    gsl_vector_add( _vData, V._vData );
    return *this;
}

Vector& Vector::operator-=( const Vector& V ) {
    if( _n != V._n ) {
        throw out_of_range("Invalid sizes of vectors");
    }
    gsl_vector_sub( _vData, V._vData );
    return *this;
}

double Vector::operator*=( const Vector& V ) {
    double res;
    gsl_blas_ddot( _vData, V._vData, &res );
    return res;
}

Vector& Vector::operator*=( double alamb ) {
    gsl_vector_scale( _vData, alamb );
    return *this;
}

Vector& Vector::operator/=( double alamb ) {
    if( fabs( alamb ) < std::numeric_limits<double>::epsilon() )
        throw std::logic_error( "Zero division" );
    gsl_vector_scale( _vData, 1.0/alamb );
    return *this;
}

size_t Vector::getSize() const {
    return _n;
}

const gsl_vector* Vector::getData() const {
    return _vData;
}

gsl_vector* Vector::data() {
    return _vData;
}
