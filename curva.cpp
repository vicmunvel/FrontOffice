#include <iostream>
#include <vector>
#include <fstream>
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
    
    for (const auto& dep : depositos) {
        factoresDescuento.push_back(calcularFactorDescuento(dep.tasa, dep.plazo));
    }

    for (const auto& swap : swaps) {
        factoresDescuento.push_back(calcularFactorDescuento(swap.tasa, swap.plazo));
    }

    return factoresDescuento;
}

// Función para interpolar la curva de factores de descuento
std::vector<double> interpolarCurva(const std::vector<double>& factoresDescuento, size_t numPuntos) {
    std::vector<double> curvaInterpolada;
    double paso = 1.0 / numPuntos;

    for (size_t i = 0; i < factoresDescuento.size() - 1; ++i) {
        double factorInicial = factoresDescuento[i];
        double factorFinal = factoresDescuento[i + 1];
        for (size_t j = 0; j < numPuntos; ++j) {
            double interp = factorInicial + (factorFinal - factorInicial) * j * paso;
            curvaInterpolada.push_back(interp);
        }
    }

    // Agregar el último punto
    curvaInterpolada.push_back(factoresDescuento.back());

    return curvaInterpolada;
}

// Función para generar fechas a partir de una fecha inicial
std::vector<std::string> generarFechas(const std::string& fechaInicial, size_t numFechas) {
    std::vector<std::string> fechas;
    // Aquí deberías implementar la lógica para generar fechas a partir de la fecha inicial
    // Por simplicidad, aquí solo se agregarán fechas dummy
    for (size_t i = 0; i < numFechas; ++i) {
        fechas.push_back("Fecha" + std::to_string(i + 1));
    }
    return fechas;
}

// Función para escribir datos en formato CSV
void escribirCSV(const std::string& nombreArchivo, const std::vector<std::string>& fechas, const std::vector<double>& factoresDescuento) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    archivo << "Fecha,FactorDescuento" << std::endl;
    for (size_t i = 0; i < fechas.size(); ++i) {
        archivo << fechas[i] << "," << factoresDescuento[i] << std::endl;
    }

    archivo.close();
}

int main() {
    // Definir los depósitos y swaps
    std::vector<Deposito> depositos;
    depositos.push_back(Deposito(0.05, 0.5)); // Depósito 6m r = 5%
    
    std::vector<Swap> swaps;
    swaps.push_back(Swap(0.055, 1.0)); // Swap 12m r = 5.5%
    swaps.push_back(Swap(0.06, 1.5));  // Swap 18m r = 6%
    swaps.push_back(Swap(0.064, 2.0)); // Swap 2y r = 6.4%

    // Calibrar la curva de interés
    std::vector<double> factoresDescuento = calibrarCurva(depositos, swaps);

    // Interpolar la curva de factores de descuento
    std::vector<double> curvaInterpolada = interpolarCurva(factoresDescuento, 10); // Cambiar el número de puntos según sea necesario

    // Generar fechas (usando fechas dummy)
    std::vector<std::string> fechas = generarFechas("01/04/2016", curvaInterpolada.size());

    // Escribir los datos en formato CSV
    escribirCSV("curva_factores_descuento.csv", fechas, curvaInterpolada);

    std::cout << "Datos exportados exitosamente a curva_factores_descuento.csv" << std::endl;

    return 0;
}
