/*
 * @brief Класс матриц, используемых в расчетах, базируется на основе gsl_matrix
 * matrix.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

class Vector;

class Matrix {
public:
    Matrix( const double* a_data=nullptr, size_t nrows=0, size_t ncols=0 );
    Matrix( double value, size_t nrows=0, size_t ncols=0 );
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

    size_t rowCount() const;
    size_t columnCount() const;
    const gsl_matrix* getData() const;
    gsl_matrix* data();

    void transpose();

    friend Vector operator* ( const Matrix& M, const Vector& V );
    friend Vector solveSystem( const Matrix& M, const Vector& V );

private:
    gsl_matrix* _mData;
    size_t _nRows;
    size_t _nColumns;
};
