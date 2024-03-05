#ifndef FRONT_OFFICE_INSTRUMENTDESCRIPTION_H
#define FRONT_OFFICE_INSTRUMENTDESCRIPTION_H

#include "LegDescription.h"

// Es probable que se utilice para describir los instrumentos financieros en su totalidad

struct InstrumentDescription{

    enum Type {bond, swap};
    Type type;
    InstrumentDescription(Type type_):type(type_){} // Constructor. Hay que especificar el tipo al crearlo.
    LegDescription payer;
    LegDescription receiver;

};

#endif
