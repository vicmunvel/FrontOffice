#include "Index.h"

/*
 * Esta clase se va a encargar de calcular el tipo Forward y el tipo Rm para pagos que no sean anuales, llamando al
 * metodo de la clase ZeroCouponCurve, get_ZeroCoupon.
 * */

Index::Index(const ZeroCouponCurve& zcc, int paymentsPerYear)
        : curve(zcc), m(paymentsPerYear) {}

double Index::computeRF(const boost::gregorian::date& currentDate, const boost::gregorian::date& previousDate,
                        double currentPeriod, double previousPeriod) const {

    if (currentDate == previousDate) {
        return curve.get_ZeroCoupon(currentDate);
    } else {
        double ZcCurrent = curve.get_ZeroCoupon(currentDate);
        double ZcPrevious = curve.get_ZeroCoupon(previousDate);
        return (ZcCurrent * currentPeriod - ZcPrevious * previousPeriod) / (currentPeriod - previousPeriod);
    }

}

double Index::computeRm(const boost::gregorian::date& currentDate, const boost::gregorian::date& previousDate,
                        double currentPeriod, double previousPeriod) const {

    double RF = computeRF(currentDate, previousDate, currentPeriod, previousPeriod);
    return m * (std::exp(RF / m) - 1);

}
