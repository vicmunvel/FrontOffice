#ifndef INSTRUMENTDESCRIPTION_H
#define INSTRUMENTDESCRIPTION_H

#include "LegDescription.h"

// Se utiliza para describir los instrumentos financieros en su totalidad

struct InstrumentDescription{

    enum Type {bond, swap};
    Type type;
    // Constructor. Hay que especificar el tipo al crearlo.
    InstrumentDescription(Type type_):type(type_){}
    LegDescription payer;
    LegDescription receiver;

};

#endif
