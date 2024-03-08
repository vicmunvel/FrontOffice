#ifndef INSTRUMENTO_H
#define INSTRUMENTO_H

#include "InstrumentDescription.h"
#include "Bond.h"
#include "Swap.h"

class Instrument {
public:
    explicit Instrument(const InstrumentDescription& instrumentDescription);
    double price();

public:
    InstrumentDescription instrumentDescription;
    Bond bond;
    Swap swap;
    bool isBond;

    double computeBondPresentValue(double bondValue) const;
};

#endif // INSTRUMENTO_H
