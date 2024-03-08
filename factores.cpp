#include <iostream>
#include <vector>
#include <cmath>

// Estructura para representar un instrumento financiero genérico
struct Instrumento {
    double tasa;
    double plazo; // en años
};

// Estructura para representar un depósito
struct Deposito : public Instrumento {
    Deposito(double t, double p) {
        tasa = t;
        plazo = p;
    }
};

// Estructura para representar un swap
struct Swap : public Instrumento {
    Swap(double t, double p) {
        tasa = t;
        plazo = p;
    }
};

// Función para calcular el factor de descuento usando la tasa y el plazo
double calcularFactorDescuento(double tasa, double plazo) {
    return exp(-tasa * plazo);
}

// Función para calibrar la curva de interés
std::vector<double> calibrarCurva(const std::vector<Deposito>& depositos, const std::vector<Swap>& swaps) {
    std::vector<double> factoresDescuento;

    // Calcular el factor de descuento del depósito a 6 meses
    double factorDescuentoDeposito6m = calcularFactorDescuento(depositos[0].tasa, depositos[0].plazo);
    factoresDescuento.push_back(factorDescuentoDeposito6m);

    // Calcular los factores de descuento de los swaps
    double factorDescuentoAnterior = factorDescuentoDeposito6m;
for (size_t i = 0; i < swaps.size(); ++i) {
    double numeroDias = swaps[i].plazo; // Convertir el plazo de años a días
    double sumaTasasFactorDescuentoAnteriores = 0.0;
    for (size_t j = 0; j < i; ++j) {
        sumaTasasFactorDescuentoAnteriores += swaps[j].tasa * ((-365+swaps[j].plazo) / 360.0) * factoresDescuento[j];
    }
    double factorDescuentoSwap = (1 - sumaTasasFactorDescuentoAnteriores - swaps[i].tasa * (swaps[i].plazo / 360.0) * factoresDescuento[i]) / (1 + swaps[i].tasa * (numeroDias / 360.0));
    factoresDescuento.push_back(factorDescuentoSwap);
    factorDescuentoAnterior = factorDescuentoSwap;
}


    return factoresDescuento;
}

int main() {
    // Definir los depósitos y swaps
    std::vector<Deposito> depositos;
    depositos.push_back(Deposito(0.05, 0.5)); // Depósito 6m r = 5%
    
    std::vector<Swap> swaps;
    swaps.push_back(Swap(0.055, 182)); // Swap 12m r = 5.5%
    swaps.push_back(Swap(0.06, 364));  // Swap 18m r = 6%
    swaps.push_back(Swap(0.064, 546)); // Swap 2y r = 6.4%

    // Calibrar la curva de interés
    std::vector<double> factoresDescuento = calibrarCurva(depositos, swaps);

    // Imprimir los factores de descuento calculados
    std::cout << "Factores de descuento calculados:" << std::endl;
    for (size_t i = 0; i < factoresDescuento.size(); ++i) {
        std::cout << "Factor " << i + 1 << ": " << factoresDescuento[i] << std::endl;
    }

    return 0;
}