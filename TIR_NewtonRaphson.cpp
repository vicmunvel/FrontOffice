#include <iostream>
#include <boost/math/tools/roots.hpp>

// Funcion que representa el flujo de efectivo del bono
struct BondCashFlowFunction {
    double nominal;         // Valor nominal del bono
    double couponRate;      // Tasa de cupón del bono
    double yearsToMaturity; // Años hasta el vencimiento del bono
    double marketPrice;     // Precio de mercado del bono
    double frequency;       // Frecuencia de pagos

    // Funcion que calcula el flujo de efectivo del bono para una tasa dada
    double operator()(double rate) const {
        double cashFlow = -marketPrice;
        // CashFlow de los bonos
        for (double i = 0.5; i <= yearsToMaturity; i += 1/frequency) {
            cashFlow += ((couponRate * nominal)/frequency) * std::exp(-i*rate);
        }

        // Cashflow del nominal a vencimiento
        cashFlow += nominal * std::exp(-yearsToMaturity * rate);

        return cashFlow;
    }

    // Derivada de la función
    double derivative(double rate) const {
        double derivative = 0.0;

        for (double i = 0.5; i <= yearsToMaturity; i += 1/frequency) {
            derivative -= (couponRate * i * nominal/frequency) * std::exp(-i*rate);
        }

        derivative -= yearsToMaturity * nominal * std::exp(-yearsToMaturity * rate);

        return derivative;
    }
};

// Creacion de estructura en tupla (Bono, Derivada) para que sea input de la funcion de Boost
struct BondCashFlowFunctor {
    const BondCashFlowFunction& bond;

    BondCashFlowFunctor(const BondCashFlowFunction& b) : bond(b) {}

    std::tuple<double, double> operator()(double rate) const {
        double value = bond(rate);
        double derivative = bond.derivative(rate);
        return std::make_tuple(value, derivative);
    }
};
