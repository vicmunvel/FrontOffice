#include "Bond.h"

Bond::Bond(const InstrumentDescription& instrument)
        : fixedLeg(instrument.payer, zeroCouponCurve), floatingLeg(instrument.payer, zeroCouponCurve),
          isFixed(instrument.payer.type == LegDescription::FIXED) {}

double Bond::price() const {
    return isFixed ? fixedLeg.price() : floatingLeg.price();
}
