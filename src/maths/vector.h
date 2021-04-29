/*
 * @brief Класс векторов, используемых в расчетах, базируется на основе gsl_vector
 * vector.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

class Matrix;

class Vector {
public:
    Vector( const double* v_data=nullptr, size_t n=0 );
    Vector( size_t n=0 );
    Vector( double value, size_t n=0 );
    Vector( const Vector& V );
    Vector( Vector&& V );
    Vector& operator=( const Vector& V );
    ~Vector();

    const double& operator() ( const size_t i ) const;
    double& operator() ( const size_t i );

    Vector& operator+=( const Vector& V );
    Vector& operator-=( const Vector& V );
    double operator*=( const Vector& V );
    Vector& operator*=( double alamb );
    Vector& operator/=( double alamb );

    size_t getSize() const;
    const gsl_vector* getData() const;
    gsl_vector* data();

private:
    gsl_vector* _vData;
    size_t _n;
};
