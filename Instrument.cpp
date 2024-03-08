#include "Instrument.h"
#include "ZeroCouponCurve.h"

Instrument::Instrument(const InstrumentDescription& instrumentDescription)
        : instrumentDescription(instrumentDescription),
          bond(instrumentDescription),
          swap(instrumentDescription),
          isBond(instrumentDescription.type == InstrumentDescription::bond) {}

double Instrument::price() {
    if (isBond) {
        double CouponBondValue = bond.price();
        return computeBondPresentValue(CouponBondValue);
    } else {
        return swap.price();
    }
}

double Instrument::computeBondPresentValue(double CouponBondValue) const {

    ZeroCouponCurve zcc;

    // Calcular la duración en años según la convención Actual/360
    auto start = instrumentDescription.payer.startDate;
    auto end = instrumentDescription.payer.endDate;
    double duration = static_cast<double>((end - start).days()) / 360.0;

    // Obtener el factor de descuento para la duración y la fecha de vencimiento
    double discountFactor = zcc.get_DiscountFactor(duration, end);

    // Calcular el valor presente del nominal y sumarlo al valor del bono
    double nominalPresentValue = instrumentDescription.payer.nominal * discountFactor;
    return CouponBondValue + nominalPresentValue;
}
