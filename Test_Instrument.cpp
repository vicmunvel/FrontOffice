#define BOOST_TEST_MODULE Test_Instrument
#include <boost/test/included/unit_test.hpp>
#include "Instrument.h"

BOOST_AUTO_TEST_CASE(test_additionalCalculationForBond) {

    // Vector de fechas de pago para el BONO
    std::vector<boost::gregorian::date> paymentDatesBond{
            boost::gregorian::from_string("2016-09-28"),
            boost::gregorian::from_string("2017-03-27"),
            boost::gregorian::from_string("2017-09-23"),
            boost::gregorian::from_string("2018-03-22")};

    // Descripción de las patas para el BONO.
    // PATA RECEPTORA - FIJA
    LegDescription receiverDescBond{
            boost::gregorian::from_string("2016-04-01"),      // Fecha de inicio
            boost::gregorian::from_string("2018-03-22"),       // Fecha final
            paymentDatesBond,                                // Vector de fechas de pago
            100,                                          // Nominal
            0.06,                                             // Tasa fija
            2,                                             // Pagos por año
            "Actual/360",                                    // Tipo de convencion de fechas
            LegDescription::FIXED                            // Tipo de pata
    };

    // Preparar la descripción del instrumento
    InstrumentDescription bondDesc{InstrumentDescription::bond};
    bondDesc.payer = receiverDescBond;

    // Creamos el BONO
    Instrument instrumentoBond(bondDesc);

    // Calculamos el valor de la pata fija en el presente
    double bondValue = instrumentoBond.price();

    double expectedValue = 98.40;
    BOOST_TEST(bondValue == expectedValue, boost::test_tools::tolerance(0.01));
}

