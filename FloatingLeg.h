#ifndef PRUEBA_FLOATINGLEG_H
#define PRUEBA_FLOATINGLEG_H

#include "Leg.h"
#include "ZeroCouponCurve.h"
#include "DayCountCalculator.h"

class FloatingLeg : public Leg {
public:
    FloatingLeg(const LegDescription& desc, const ZeroCouponCurve& zcc);
    double price() const override;

private:
    const ZeroCouponCurve& curve;
};

#endif
