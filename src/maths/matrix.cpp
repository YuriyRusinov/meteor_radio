/*
 * @brief Класс матриц, используемых в расчетах
 * matrix.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "matrix.h"
#include "vector.h"

using std::out_of_range;
using std::cout;
using std::logic_error;
using std::endl;
using std::stringstream;
using std::swap;

Matrix::Matrix( const double* a_data, size_t nrows, size_t ncols )
    : _mData( gsl_matrix_alloc( nrows, ncols ) ),
    _nRows( nrows ),
    _nColumns( ncols ) {
    int counter = 0;
    for( int i=0; i<nrows; i++ )
        for( int j=0; j<ncols; j++ ) {
            gsl_matrix_set (_mData, i, j, a_data[counter]);
            counter++;
        }
}

Matrix::Matrix( double value, size_t nrows, size_t ncols )
    : _nRows( nrows ),
    _nColumns( ncols ) {
    _mData = gsl_matrix_alloc( nrows, ncols );
    gsl_matrix_set_all( _mData, value );
}

Matrix::Matrix( const Matrix& M )
    : _nRows( M._nRows ),
    _nColumns( M._nColumns ) {
    _mData = gsl_matrix_alloc( _nRows, _nColumns );
    gsl_matrix_memcpy( _mData, M._mData );
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
        }
        gsl_matrix_memcpy( _mData, M._mData );
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
    gsl_blas_dgemm( CblasNoTrans, CblasNoTrans,
                  1.0, _mData, M._mData,
                  0.0, mRes );
/*
    for( int i=0; i<_nRows; i++ ) {
        stringstream resRowS;
        for( int j=0; j<_nColumns; j++ ) {
            resRowS << gsl_matrix_get( _mData, i, j ) << ' ';
        }
        cout << resRowS.str() << endl;
    }
    cout << __PRETTY_FUNCTION__ << endl;

    for( int i=0; i<_nRows; i++ ) {
        stringstream resRowS;
        for( int j=0; j<M._nColumns; j++ ) {
            resRowS << gsl_matrix_get( mRes, i, j ) << ' ';
        }
        cout << resRowS.str() << endl;
    }
*/
    _nColumns = M._nColumns;
    if( _mData != nullptr )
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

size_t Matrix::rowCount() const {
    return _nRows;
}

size_t Matrix::columnCount() const {
    return _nColumns;
}

const gsl_matrix* Matrix::getData() const {
    return _mData;
}

gsl_matrix* Matrix::data() {
    return _mData;
}

void Matrix::transpose() {
    swap( _nRows, _nColumns );
    gsl_matrix_transpose( _mData );
}

Vector operator* ( const Matrix& M, const Vector& V ) {
    Vector y( V.getSize() );
    int res = gsl_blas_dgemv( CblasNoTrans, 1.0, M.getData(), V.getData(), 0.0, y.data() );
    return y;
}

Vector solveSystem( const Matrix& M, const Vector& V ) {
    Vector x( V.getSize() );
    Matrix MC( M );
    gsl_permutation * p = gsl_permutation_alloc( V.getSize() );
    int s;
    gsl_linalg_LU_decomp( MC.data(), p, &s );
    gsl_linalg_LU_solve( MC.getData(), p, V.getData(), x.data() );

    return x;
}
