#include "FloatingLeg.h"
#include "Index.h"

FloatingLeg::FloatingLeg(const LegDescription& desc, const ZeroCouponCurve& zcc)
        : Leg(desc), curve(zcc) {}

double FloatingLeg::price() const {
    double presentValue = 0;
    double previousPeriod = 0.0;
    boost::gregorian::date previousDate = description.startDate;
    Actual_360 dayCounter;
    Index index(curve, description.pagosXanio);

    for (const auto& paymentDate : description.paymentDates) {
        double currentPeriod = dayCounter(description.startDate, paymentDate);
        double discountFactor = curve.get_DiscountFactor(currentPeriod, paymentDate);

        double Rm = index.computeRm(paymentDate, previousDate, currentPeriod, previousPeriod);

        presentValue += (description.nominal * Rm * (currentPeriod - previousPeriod) * discountFactor);

        previousPeriod = currentPeriod;
        previousDate = paymentDate;
    }

    std::cout << "El valor presente de los flujos de caja de la pata flotante es: " << presentValue << std::endl;
    return presentValue;
}
