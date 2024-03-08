#include "ZeroCouponCurve.h"

ZeroCouponCurve::ZeroCouponCurve() {
    // Simulamos una curva de tipos ZC totalmente inventada
    // Fecha inicial de la curva
    boost::gregorian::date start_date(2016, 1, 1);

    for (int i = 0; i < 1339; ++i) { // Simulamos 1339 dias (hasta 2019-01-01 aprox)
        boost::gregorian::date discount_date = start_date + boost::gregorian::days(i);
        double discount_factor = 0.04 + (i * 0.00002); // Simulación de factor de descuento creciente
        discountFactors_[discount_date] = discount_factor;
    }
    // Introducimos los datos del problema a mano ya que el resto serán datos inventados
    discountFactors_[boost::gregorian::from_string("2016-10-03")] = 0.0474;
    discountFactors_[boost::gregorian::from_string("2017-04-03")] = 0.05;
    discountFactors_[boost::gregorian::from_string("2017-10-02")] = 0.0510;
    discountFactors_[boost::gregorian::from_string("2018-04-02")] = 0.0520;

    discountFactors_[boost::gregorian::from_string("2016-09-28")] = 0.05;
    discountFactors_[boost::gregorian::from_string("2017-03-27")] = 0.058;
    discountFactors_[boost::gregorian::from_string("2017-09-23")] = 0.06;
    discountFactors_[boost::gregorian::from_string("2018-03-22")] = 0.068;
}

// Este metodo devuelve el tipo ZC a una fecha concreta
double ZeroCouponCurve::get_ZeroCoupon(const boost::gregorian::date& date) const {

    auto it = discountFactors_.find(date);
    if (it != discountFactors_.end()) {
        return it->second; // Devuelve el segundo elemento del mapa, es decir el tipo ZC

    } else {
        //Si no hay uno para esa fecha devuelve un tipo de ejemplo
        std::cout << "La fecha no tiene asociado un tipo ZC. Se devuelve un valor por defecto - Ver ZeroCouponCurve::get_ZeroCoupon" << std::endl;
        return 0.04;
    }
}

// Este otro metodo devuelve el factor de descuento para una "distancia" dada i y una fecha de pago dada
double ZeroCouponCurve::get_DiscountFactor(double date_period ,const boost::gregorian::date& date) const {
    // Usar get_ZeroCoupon para obtener la tasa ZC y luego calcular el factor de descuento.
    double zcRate = get_ZeroCoupon(date);

    // Calcula el factor de descuento usando la fórmula. e^(-i*ZCi)
    return std::exp(-date_period*zcRate);
}
