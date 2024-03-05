#include <vector>
#include "LegDescription.h"
#include "InstrumentDescription.h"
#include "ZeroCouponCurve.h"
#include "DayCountCalculator.h"

int main(){

    // Vector de fechas de los pagos
    std::vector<boost::gregorian::date> paymentDates;
    paymentDates.push_back(boost::gregorian::from_string("2016-10-03"));
    paymentDates.push_back(boost::gregorian::from_string("2017-04-03"));
    paymentDates.push_back(boost::gregorian::from_string("2017-10-02"));
    paymentDates.push_back(boost::gregorian::from_string("2018-04-02"));

    // Configuramos la descripcion de las patas
    LegDescription fixedLegDesc{boost::gregorian::from_string("2016-04-01"),
                                boost::gregorian::from_string("2018-04-02"),
                                paymentDates,
                                100000000,
                                2,
                                "Actual/360"};

    LegDescription floatingLegDesc{boost::gregorian::from_string("2016-04-01"),
                                   boost::gregorian::from_string("2018-04-02"),
                                   paymentDates,
                                   100000000,
                                   2,
                                   "Actual/360"};

    // Creamos la descripcion ahora del instrumento - SWAP
    InstrumentDescription swapDesc(InstrumentDescription::Type::swap);
    swapDesc.payer = fixedLegDesc;
    swapDesc.receiver = floatingLegDesc;

    // Probando la calculadora de dias
    Actual_360 actual360Calculator;

    double dayCountYear = actual360Calculator(boost::gregorian::from_string("2017-04-01"),
                                   boost::gregorian::from_string("2017-10-01"));
    std::cout << dayCountYear << std::endl;

    // Probando la clase ZeroCouponCurve
    ZeroCouponCurve zcc;    //Aqui tenemos la curva
    double h = zcc.get_ZeroCoupon(boost::gregorian::from_string("2017-04-01"));
    double j = zcc.get_DiscountFactor(dayCountYear, boost::gregorian::from_string("2017-04-01"));
    printf("%f \n",h);
    printf("%f \n",j);


    printf("Todo OK");
}