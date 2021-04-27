/*
 * @brief Класс матриц, используемых в расчетах
 * matrix.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <cmath>
#include <limits>
#include <stdexcept>
#include <iostream>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_blas.h>
#include "matrix.h"

Matrix::Matrix( const double* a_data, size_t nrows, size_t ncols )
    : _mData( gsl_matrix_alloc( nrows, ncols ) ),
    _nRows( nrows ),
    _nColumns( ncols ) {
}

Matrix::Matrix( double value, int nrows, int ncols )
    : _nRows( nrows ),
    _nColumns( ncols ) {
    _mData = gsl_matrix_alloc( nrows, ncols );
    gsl_matrix_set_all( _mData, value );
}

Matrix::Matrix( const Matrix& M )
    : _nRows( M._nRows ),
    _nColumns( M._nColumns ) {
    _mData = gsl_matrix_alloc( _nRows, _nColumns );
}

Matrix::~Matrix() {
    gsl_matrix_free( _mData );
}

const double& Matrix::operator() ( const size_t i, const size_t j ) const {
    return *gsl_matrix_const_ptr( _mData, i, j );
}

double& Matrix::operator() ( const size_t i, const size_t j ) {
    return *gsl_matrix_ptr( _mData, i, j );
}

Matrix& Matrix::operator=( const Matrix& M ) {
    if( this != &M ) {
        if( _nRows != M._nRows || _nColumns != M._nColumns ) {
            if( _mData != nullptr )
                gsl_matrix_free( _mData );
            _mData = gsl_matrix_alloc( M._nRows, M._nColumns );
            gsl_matrix_memcpy( _mData, M._mData );
        }
        _nRows = M._nRows;
        _nColumns = M._nColumns;
    }
    return *this;
}

Matrix& Matrix::operator+=( const Matrix& M ) {
    if( _nRows != M._nRows || _nColumns != M._nColumns ) {
        throw std::out_of_range("Invalid sizes of matrices");
    }
    gsl_matrix_add( _mData, M._mData );
    return *this;
}

Matrix& Matrix::operator-=( const Matrix& M ) {
    if( _nRows != M._nRows || _nColumns != M._nColumns ) {
        throw std::out_of_range("Invalid sizes of matrices");
    }
    gsl_matrix_sub( _mData, M._mData );
    return *this;
}

Matrix& Matrix::operator*=( const Matrix& M ) {
    if( _nColumns != M._nRows ) {
        throw std::out_of_range("Invalid sizes of matrices");
    }
    gsl_matrix * mRes = gsl_matrix_alloc( _nRows, M._nColumns );
    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                  1.0, _mData, M._mData,
                  0.0, mRes);

/*    for( int i=0; i<_nRows; i++ ) {
        for( int j=0; j<M._nColumns; j++ ) {
            double sum = 0.0;
            for( int k=0; k<_nColumns; k++ )
                sum += gsl_matrix_get( _mData, i, k )*gsl_matrix_get( M._mData, k, j );
            gsl_matrix_set( mRes, i, j, sum );
        }
    }*/
    _nColumns = M._nColumns;
    gsl_matrix_free( _mData );
    _mData = gsl_matrix_alloc( _nRows, _nColumns );
    gsl_matrix_memcpy( _mData, mRes );
    gsl_matrix_free( mRes );
    return *this;
}

Matrix& Matrix::operator*=( double alamb ) {
    gsl_matrix_scale( _mData, alamb );
    return *this;
}

Matrix& Matrix::operator/=( double alamb ) {
    if( fabs( alamb ) < std::numeric_limits<double>::epsilon() )
        throw std::logic_error( "Zero division" );
    gsl_matrix_scale( _mData, 1.0/alamb );
    return *this;
}
