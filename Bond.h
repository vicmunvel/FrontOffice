#ifndef BOND_H
#define BOND_H

#include "InstrumentDescription.h"
#include "FixedLeg.h"
#include "FloatingLeg.h"
#include "ZeroCouponCurve.h"

class Bond {
public:
    explicit Bond(const InstrumentDescription& instrument);

    double price() const;

private:
    FixedLeg fixedLeg;
    FloatingLeg floatingLeg;
    bool isFixed;

    ZeroCouponCurve zeroCouponCurve; // Asume que esto se inicializa adecuadamente
};

#endif // BOND_H
