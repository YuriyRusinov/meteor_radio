/*
 * @brief Класс векторов, используемых в расчетах, базируется на основе gsl_vector
 * vector.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

class Vector {
public:
    Vector( const double* v_data=nullptr, size_t n=0 );
    Vector( double value, size_t n=0 );
    Vector( const Vector& V );
    ~Vector();

private:
    gsl_vector* _vData;
    size_t _n;
};
