#ifndef FRONT_OFFICE_LEGDESCRIPTION_H
#define FRONT_OFFICE_LEGDESCRIPTION_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <utility>
/* Esta estructura se utilizará para:
 * Pasar parámetros de manera estructurada a las funciones de construcción de los diferentes tipos de patas.
 * Proporcionar una forma de validar y asegurar que todos los datos necesarios para construir una pata estén presentes
 * y sean correctos antes de la construcción.
 */

struct LegDescription {

    enum Type { FIXED, FLOATING };

    // Fechas a partir de las cuales calculamos el devengo
    // Se inicializan los tipos boost::gregorian::date a not-a-date-time por defecto
    boost::gregorian::date startDate;
    boost::gregorian::date endDate;

    // Vector de fechas de los pagos de los flujos de caja
    std::vector<boost::gregorian::date> paymentDates;

    // Nominal. Inicializamos a un valor por defecto de 0
    double nominal = 0.0;
    // Tipo de interes tipo fijo. Inicializamos a un valor por defecto de 0
    double fixedRate = 0.0;
    // Numero de pagos al año. Inicializamos a un valor por defecto de 1
    int pagosXanio = 1;
    // Indicamos la convencion de fechas entre 2 fechas: ACTUAL_360 o THIRTY_360
    // Inicializamos a un valor por defecto de ACTUAL_360
    std::string daysCountType = "Actual/360";

    // Tipo de la pata (FIXED o FLOATING)
    Type type;

    // Constructor por defecto
    LegDescription() = default;

    // Constructor con todos los parámetros
    LegDescription(boost::gregorian::date start, boost::gregorian::date end,
                   std::vector<boost::gregorian::date> paymentDates_, double nominal_, double fixedRate_, int pagosXanio_,
                   std::string dayCount_, Type type_):

            startDate(start),
            endDate(end),
            paymentDates(std::move(paymentDates_)),
            nominal(nominal_),
            fixedRate(fixedRate_),
            pagosXanio(pagosXanio_),
            daysCountType(std::move(dayCount_)),
            type(type_){}

};

#endif
