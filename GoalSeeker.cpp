#include <iostream>
#include <boost/math/tools/roots.hpp>
#include "Instrument.h"
#include "TIR_NewtonRaphson.cpp"
#include "DayCountCalculator.h"

class GoalSeeker {
public:
    GoalSeeker() {}

    double find(const Instrument& instrument, double marketPrice) {
        Actual_360 dayCount;

        if(instrument.instrumentDescription.type == InstrumentDescription::bond) {

            BondCashFlowFunction bond;
            bond.nominal = instrument.instrumentDescription.payer.nominal;
            bond.couponRate = instrument.instrumentDescription.payer.fixedRate;
            bond.yearsToMaturity = dayCount(instrument.instrumentDescription.payer.startDate,
                                            instrument.instrumentDescription.payer.endDate);
            bond.marketPrice = marketPrice;
            bond.frequency = instrument.instrumentDescription.payer.pagosXanio;

            // Configurar el método de Newton-Raphson
            BondCashFlowFunctor functor(bond);
            double initialGuess = 0.05;  // Supuesto inicial
            double minRate = 0.001;
            double maxRate = 0.5;
            int digits = 5;  // Cantidad de dígitos significativos

            // Encontrar la TIR utilizando el método de Newton-Raphson
            double tir = boost::math::tools::newton_raphson_iterate(functor, initialGuess, minRate, maxRate, digits);

            // Imprimir el resultado y los datos
            std::cout << "Detalles del BONO para calcular la TIR: " << std::endl;
            std::cout << "--------------------------------------------" <<  std::endl;
            std::cout << "Nominal: " << bond.nominal << " euros" << std::endl;
            std::cout << "Precio: " << bond.marketPrice << " euros" << std::endl;
            std::cout << "Cupon (anual): " << bond.couponRate*100 << " %" << std::endl;
            std::cout << "Duracion (años): " << bond.yearsToMaturity<< std::endl;
            std::cout << "Frecuencia (pagos / año): " << bond.frequency << std::endl;
            std::cout << "--------------------------------------------" <<  std::endl;


            return tir;

        }else{ return 0; }
    }
};
