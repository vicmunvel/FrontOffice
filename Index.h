#ifndef PRUEBA_INDEX_H
#define PRUEBA_INDEX_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include "ZeroCouponCurve.h"

class Index {
public:
    Index(const ZeroCouponCurve& zcc, int paymentsPerYear);
    double computeRm(const boost::gregorian::date& currentDate, const boost::gregorian::date& previousDate, double currentPeriod, double previousPeriod) const;

private:
    const ZeroCouponCurve& curve;
    int m; // Número de pagos por año.
    double computeRF(const boost::gregorian::date& currentDate, const boost::gregorian::date& previousDate, double currentPeriod, double previousPeriod) const;
};

#endif
