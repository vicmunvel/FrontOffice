#ifndef PRUEBA_FIXEDLEG_H
#define PRUEBA_FIXEDLEG_H

#include "Leg.h"
#include "DayCountCalculator.h"
#include "ZeroCouponCurve.h"

class FixedLeg : public Leg {
public:
    FixedLeg(const LegDescription& legDesc, const ZeroCouponCurve& zeroCouponCurve);
    double price() const override;

private:
    const ZeroCouponCurve& zeroCouponCurve_;
};

#endif