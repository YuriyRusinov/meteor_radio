/*
 * @brief Класс матриц, используемых в расчетах, базируется на основе gsl_matrix
 * matrix.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

//class gsl_vector;
//class gsl_matrix;
//class gsl_permutation;

class Matrix {
public:
    Matrix( const double* a_data=nullptr, size_t nrows=0, size_t ncols=0 );
    Matrix( double value, int nrows=0, int ncols=0 );
    Matrix( const Matrix& M );
    ~Matrix();

    const double& operator() ( const size_t i, const size_t j ) const;
    double& operator() ( const size_t i, const size_t j );

    Matrix& operator=( const Matrix& M );

    Matrix& operator+=( const Matrix& M );
    Matrix& operator-=( const Matrix& M );
    Matrix& operator*=( const Matrix& M );
    Matrix& operator*=( double alamb );
    Matrix& operator/=( double alamb );
private:
    gsl_matrix* _mData;
    size_t _nRows;
    size_t _nColumns;
};
