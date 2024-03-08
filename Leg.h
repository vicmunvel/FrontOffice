#ifndef LEG_H
#define LEG_H

#include "LegDescription.h"

class Leg {
public:
    explicit Leg(const LegDescription& desc);
    virtual ~Leg() = default;
    virtual double price() const = 0;

protected:
    LegDescription description;
};

#endif