#define BOOST_TEST_MODULE Test_Total
#include <boost/test/included/unit_test.hpp>
#include "Instrument.h"
#include "InstrumentDescription.h"

BOOST_AUTO_TEST_CASE(test_main) {

    // Vector de fechas de pago para el BONO
    std::vector<boost::gregorian::date> paymentDatesBond{
            boost::gregorian::from_string("2016-09-28"),
            boost::gregorian::from_string("2017-03-27"),
            boost::gregorian::from_string("2017-09-23"),
            boost::gregorian::from_string("2018-03-22")};

    // Vector de fechas de pago para el SWAP
    std::vector<boost::gregorian::date> paymentDatesSwap{
            boost::gregorian::from_string("2016-10-03"),
            boost::gregorian::from_string("2017-04-03"),
            boost::gregorian::from_string("2017-10-02"),
            boost::gregorian::from_string("2018-04-02")};

    // Descripción de las patas para el SWAP.
    // PATA PAGADORA - FIJA
    LegDescription payerDescSwap{
            boost::gregorian::from_string("2016-04-01"),      // Fecha de inicio
            boost::gregorian::from_string("2018-04-02"),       // Fecha final
            paymentDatesSwap,                                // Vector de fechas de pago
            100000000,                                          // Nominal
            0.05,                                             // Tasa fija
            2,                                             // Pagos por año
            "Actual/360",                                    // Tipo de convencion de fechas
            LegDescription::FIXED                               // Tipo de pata
    };

    // PATA RECEPTORA - FLOTANTE
    LegDescription receiverDescSwap{
            boost::gregorian::from_string("2016-04-01"),      // Fecha de inicio
            boost::gregorian::from_string("2018-04-02"),       // Fecha final
            paymentDatesSwap,                                // Vector de fechas de pago
            100000000,                                          // Nominal
            0.05,                                             // Tasa fija
            2,                                             // Pagos por año
            "Actual/360",                                    // Tipo de convencion de fechas
            LegDescription::FLOATING                            // Tipo de pata
    };

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

    // DESCRIBIMOS LOS INTRUMENTOS
    // Descripcion del SWAP
    InstrumentDescription swapDesc{InstrumentDescription::swap};
    swapDesc.payer=payerDescSwap;
    swapDesc.receiver=receiverDescSwap;

    // Descripcion del BONO
    InstrumentDescription bondDesc{InstrumentDescription::bond};
    bondDesc.payer = receiverDescBond;

    // Inicializamos los instrumentos.
    Instrument instrumentoSwap(swapDesc);  // Asume que swapDesc ya está configurado
    Instrument instrumentoBond(bondDesc);  // Asume que bondDesc ya está configurado

    // Ejecutamos el cálculo de precios.
    double swapPrice = instrumentoSwap.price();
    double bondPrice = instrumentoBond.price();

    // Realizamos las verificaciones.
    // Debes definir qué valores esperas para swapPrice y bondPrice.
    double expectedSwapPrice = -495700; // Este valor debe ser determinado por ti
    double expectedBondPrice = 98.40; // Este valor debe ser determinado por ti
    BOOST_TEST_MESSAGE("Testeando el cálculo del precio para el SWAP");
    BOOST_TEST(swapPrice == expectedSwapPrice, boost::test_tools::tolerance(1000.0));
    BOOST_TEST_MESSAGE("Testeando el cálculo del precio para el BONO");
    BOOST_TEST(bondPrice == expectedBondPrice, boost::test_tools::tolerance(0.01));
}
