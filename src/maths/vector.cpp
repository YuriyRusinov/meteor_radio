/*
 * @brief Класс векторов, используемых в расчетах, базируется на основе gsl_vector
 * vector.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <gsl/gsl_vector.h>
#include "vector.h"

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

Vector::~Vector() {
    gsl_vector_free( _vData );
}
