#ifndef ZEROCOUPONCURVE_H
#define ZEROCOUPONCURVE_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>

class ZeroCouponCurve {
public:
    ZeroCouponCurve();  // Constructor para inicializar la curva de descuento.
    ~ZeroCouponCurve()=default; // Destructor.

    // Método para obtener el factor de descuento para una fecha dada.
    double get_ZeroCoupon(const boost::gregorian::date& date) const;
    double get_DiscountFactor(double date_period ,const boost::gregorian::date& date) const;

private:
    // Los tipos ZC los almacenaremos en un mapa de par Fecha (tipo boost::gregorian::date) - Valor
    std::map<boost::gregorian::date, double> discountFactors_;
};

#endif
