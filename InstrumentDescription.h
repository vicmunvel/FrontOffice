#ifndef FRONT_OFFICE_INSTRUMENTDESCRIPTION_H
#define FRONT_OFFICE_INSTRUMENTDESCRIPTION_H

#include "LegDescription.h"

// Se utilice para describir los instrumentos financieros en su totalidad

struct InstrumentDescription{

    enum Type {bond, swap};
    Type type;
    // Constructor. Hay que especificar el tipo al crearlo.
    InstrumentDescription(Type type_):type(type_){}
    LegDescription payer;
    LegDescription receiver;

};

#endif
