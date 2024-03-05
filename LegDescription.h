#ifndef FRONT_OFFICE_LEGDESCRIPTION_H
#define FRONT_OFFICE_LEGDESCRIPTION_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
/* Esta estructura se utilizará para:
 * Pasar parámetros de manera estructurada a las funciones de construcción de los diferentes tipos de patas.
 * Proporcionar una forma de validar y asegurar que todos los datos necesarios para construir una pata estén presentes
 * y sean correctos antes de la construcción.
 */

struct LegDescription {
    // Fechas a partir de las cuales calculamos el devengo
    boost::gregorian::date startDate;
    boost::gregorian::date endDate;

    // Vector de fechas de los pagos de los flujos de caja
    std::vector<boost::gregorian::date> paymentDates;

    // El nominal
    int nominal;

    // Si pagosXanio es 2, significaria pagos semestrales
    int pagosXanio;

    // Indicamos si calculamos los dias entre 2 fechas y el año: Act/360 o 30/360
    std::string daysCountType;
};

#endif