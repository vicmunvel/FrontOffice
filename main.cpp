#include "GoalSeeker.cpp"
#include "Instrument.h"
#include "InstrumentDescription.h"

void imprimirDetallesLeg(const LegDescription& leg) {
    std::cout << "--------------------------------------------" <<  std::endl;
    std::cout << "Fecha de inicio: " << leg.startDate << std::endl;
    std::cout << "Fecha final: " << leg.endDate << std::endl;
    std::cout << "Nominal: " << leg.nominal << " euros" << std::endl;
    std::cout << "Tasa fija: " << leg.fixedRate*100 << " %" << std::endl;
    std::cout << "Pagos por año: " << leg.pagosXanio << std::endl;
    std::cout << "Tipo de convención de fechas: " << leg.daysCountType << std::endl;
    std::cout << "Tipo de pata: " << (leg.type == LegDescription::FIXED ? "Fija" : "Flotante") << std::endl;
    std::cout << "--------------------------------------------" <<  std::endl;
}

int main() {
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

    /*****************************************************************************/

    // Descripción de las patas para el SWAP.
    LegDescription payerDescSwap{
            boost::gregorian::from_string("2016-04-01"), // Fecha de inicio
            boost::gregorian::from_string("2018-04-02"), // Fecha final
            paymentDatesSwap,                            // Vector de fechas de pago
            100000000,                                   // Nominal
            0.05,                                        // Tasa fija
            2,                                          // Pagos por año
            "Actual/360",                               // Tipo de convención de fechas
            LegDescription::FIXED                        // Tipo de pata
    };

    LegDescription receiverDescSwap{
            boost::gregorian::from_string("2016-04-01"), // Fecha de inicio
            boost::gregorian::from_string("2018-04-02"), // Fecha final
            paymentDatesSwap,                            // Vector de fechas de pago
            100000000,                                   // Nominal
            0.05,                                        // Tasa fija
            2,                                          // Pagos por año
            "Actual/360",                               // Tipo de convención de fechas
            LegDescription::FLOATING                     // Tipo de pata
    };

    // Descripción de las patas para el BONO.
    LegDescription receiverDescBond{
            boost::gregorian::from_string("2016-04-01"), // Fecha de inicio
            boost::gregorian::from_string("2018-03-22"), // Fecha final
            paymentDatesBond,                            // Vector de fechas de pago
            100,                                         // Nominal
            0.06,                                        // Tasa fija
            2,                                          // Pagos por año
            "Actual/360",                               // Tipo de convención de fechas
            LegDescription::FIXED                        // Tipo de pata
    };

    /*****************************************************************************/

    // Descripciones de los instrumentos
    InstrumentDescription swapDesc{InstrumentDescription::swap};
    swapDesc.payer = payerDescSwap;
    swapDesc.receiver = receiverDescSwap;

    InstrumentDescription bondDesc{InstrumentDescription::bond};
    bondDesc.payer = receiverDescBond;

    /*****************************************************************************/

    // Creación de los instrumentos
    Instrument instrumentoSwap(swapDesc);
    Instrument instrumentoBond(bondDesc);

    /*****************************************************************************/

    // Imprimimos detalles de todos los datos del SWAP y del BONO
    std::cout << "--------------------SWAP-------------------" << std::endl;
    std::cout << "Detalles de la pata pagadora del SWAP (FIJA):" << std::endl;
    imprimirDetallesLeg(payerDescSwap);

    std::cout << "Detalles de la pata receptora del SWAP (FLOTANTE):" << std::endl;
    imprimirDetallesLeg(receiverDescSwap);

    // Calculamos el precio y lo mostramos
    double swapPrice = instrumentoSwap.price();
    std::cout << "El precio es: " << swapPrice << " euros" << std::endl;

    std::cout << "\n\n\n--------------------BONO-------------------" << std::endl;
    std::cout << "Detalles de la pata del BONO (FIJA):" << std::endl;
    imprimirDetallesLeg(receiverDescBond);

    // Calculamos el precio y lo mostramos
    double bondPrice = instrumentoBond.price();
    std::cout << "El precio es: " << bondPrice << " euros" << std::endl;

    /*****************************************************************************/

    // Calculamos la TIR del BONO con la clase GoalSeeker
    GoalSeeker seeker;
    std::cout << "\n\n\n--------------------TIR-------------------" << std::endl;
    double tirBond = seeker.find(instrumentoBond, bondPrice);
    std::cout << "La TIR del bono es: " << tirBond*100 << " %" << std::endl;
}
