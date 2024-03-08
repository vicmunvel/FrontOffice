#ifndef SWAP_H
#define SWAP_H

#include "InstrumentDescription.h"
#include "FixedLeg.h"
#include "FloatingLeg.h"

class Swap {
public:
    explicit Swap(const InstrumentDescription& instrument);
    double price() const;

private:
    FixedLeg fixedPayerLeg;
    FloatingLeg floatingPayerLeg;
    FixedLeg fixedReceiverLeg;
    FloatingLeg floatingReceiverLeg;

    bool isPayerFixed;
    bool isReceiverFixed;

    ZeroCouponCurve zeroCouponCurve;
};

#endif
