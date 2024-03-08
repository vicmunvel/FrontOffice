#define BOOST_TEST_MODULE Test_Legs
#include <boost/test/included/unit_test.hpp>
#include "FloatingLeg.h"
#include "FixedLeg.h"
#include "ZeroCouponCurve.h"
#include "LegDescription.h"
#include "DayCountCalculator.h"

// Preparamos la descripción de las patas como en en main
std::vector<boost::gregorian::date> paymentDatesSwap{
        boost::gregorian::from_string("2016-10-03"),
        boost::gregorian::from_string("2017-04-03"),
        boost::gregorian::from_string("2017-10-02"),
        boost::gregorian::from_string("2018-04-02")};

LegDescription floatingLegDesc{
        boost::gregorian::from_string("2016-04-01"),      // Fecha de inicio
        boost::gregorian::from_string("2018-04-02"),       // Fecha final
        paymentDatesSwap,                                // Vector de fechas de pago
        100000000,                                          // Nominal
        0.05,                                             // Tasa fija
        2,                                             // Pagos por año
        "Actual/360",                                    // Tipo de convencion de fechas
        LegDescription::FLOATING                               // Tipo de pata
};

LegDescription fixedLegDesc{
        boost::gregorian::from_string("2016-04-01"),      // Fecha de inicio
        boost::gregorian::from_string("2018-04-02"),       // Fecha final
        paymentDatesSwap,                                // Vector de fechas de pago
        100000000,                                          // Nominal
        0.05,                                             // Tasa fija
        2,                                             // Pagos por año
        "Actual/360",                                    // Tipo de convencion de fechas
        LegDescription::FIXED                               // Tipo de pata
};

// Inicializamos la curva de tipos ZC
ZeroCouponCurve zcc;

BOOST_AUTO_TEST_CASE(test_FixedLeg_price) {
    FixedLeg fixedLeg(fixedLegDesc, zcc);

    // Calcular el precio de la pata fija
    double priceFixed = fixedLeg.price();

    // Comprobar si el precio es igual a un valor específico con una tolerancia
    BOOST_TEST(priceFixed == 9500000, boost::test_tools::tolerance(50000.0));
}

BOOST_AUTO_TEST_CASE(test_FloatingLeg_price) {
    FloatingLeg floatingLeg(floatingLegDesc, zcc);

    // Calcular el precio de la pata flotante
    double price = floatingLeg.price();

    // Comprobar si el precio es igual a un valor específico con una tolerancia
    BOOST_TEST(price == 10000000, boost::test_tools::tolerance(50000.0));
}
