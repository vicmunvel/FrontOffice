#define BOOST_TEST_MODULE Test_Legs
#include <boost/test/included/unit_test.hpp>
#include "FloatingLeg.h"
#include "FixedLeg.h"
#include "ZeroCouponCurve.h"
#include "LegDescription.h"
#include "DayCountCalculator.h"

// Preparamos la descripción de las patas y las fechas de los pagos como en en main()
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

    // Calculamos el precio (Valor Presente) de la pata fija
    double priceFixed = fixedLeg.price();

    // Comprobamos si el precio es igual a un valor del Excel con una tolerancia
    BOOST_TEST_MESSAGE("Testeando el descuento de los flujos de caja de la pata fija");
    BOOST_TEST(priceFixed == 9500000, boost::test_tools::tolerance(50000.0));
}

BOOST_AUTO_TEST_CASE(test_FloatingLeg_price) {
    FloatingLeg floatingLeg(floatingLegDesc, zcc);

    // Calcular el precio (Valor Presente) de la pata flotante
    double price = floatingLeg.price();

    // Comprobamos si el precio es igual a un valor del Excel con una tolerancia
    BOOST_TEST_MESSAGE("Testeando el descuento de los flujos de caja de la pata flotante");
    BOOST_TEST(price == 10010000, boost::test_tools::tolerance(20000.0));
}
