#include "ZeroCouponCurve.h"

ZeroCouponCurve::ZeroCouponCurve() {
    // Simulamos una curva de tipos ZC totalmente inventada
    // Fecha inicial de la curva
    boost::gregorian::date start_date(2016, 1, 1);

    for (int i = 0; i < 1339; ++i) { // Simulamos 1339 dias (hasta 2019-01-01 aprox)
        boost::gregorian::date discount_date = start_date + boost::gregorian::days(i);
        double discount_factor = 0.052 - (i * 0.00002); // Simulación de factor de descuento decreciente
        discountFactors_[discount_date] = discount_factor;
    }
}

// Este metodo devuelve el tipo ZC a una fecha concreta
double ZeroCouponCurve::get_ZeroCoupon(const boost::gregorian::date& date) const {

    auto it = discountFactors_.find(date);
    if (it != discountFactors_.end()) {
        return it->second; //Devuelve el segundo elemento del mapa, es decir el tipo ZC

    } else {
        //Si no hay uno para esa fecha devuelve un tipo de ejemplo
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
