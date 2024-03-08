#include "FixedLeg.h"

FixedLeg::FixedLeg(const LegDescription &legDesc, const ZeroCouponCurve &zeroCouponCurve)
        : Leg(legDesc), zeroCouponCurve_(zeroCouponCurve) {}

double FixedLeg::price() const {
    double totalPresentValue = 0.0;
    double totalPeriod = 0.0;
    boost::gregorian::date previousDate = description.startDate;

    if (description.daysCountType == "Actual/360") {
        Actual_360 actual360Calculator;

        for (const auto &paymentDate: description.paymentDates) {

            double periodYearFraction = actual360Calculator(previousDate, paymentDate);
            double couponPayment = description.fixedRate * description.nominal * periodYearFraction;
            totalPeriod += periodYearFraction;
            double discountFactor = zeroCouponCurve_.get_DiscountFactor(totalPeriod, paymentDate);

            totalPresentValue += couponPayment * discountFactor;
            previousDate = paymentDate;

        }

    } else if (description.daysCountType == "30/360") {
        Thirty_360 thirty360Calculator;

        for (const auto &paymentDate: description.paymentDates) {

            double periodYearFraction = thirty360Calculator(previousDate, paymentDate);
            double couponPayment = description.fixedRate * description.nominal * periodYearFraction;
            totalPeriod += periodYearFraction;
            double discountFactor = zeroCouponCurve_.get_DiscountFactor(totalPeriod, paymentDate);

            totalPresentValue += couponPayment * discountFactor;
            previousDate = paymentDate;

        }

    } else {
        printf("ERROR EN LegFixed.cpp REVISAR CONVENCION DE FECHAS");
    }

    std::cout << "El valor presente de los flujos de caja de la pata fija es: " << totalPresentValue << std::endl;
    return totalPresentValue;
}

