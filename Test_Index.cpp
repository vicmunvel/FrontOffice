#define BOOST_TEST_MODULE Test_Index
#include <boost/test/included/unit_test.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "Index.h"
#include "ZeroCouponCurve.h"

BOOST_AUTO_TEST_CASE(test_Index_computeRm) {
    ZeroCouponCurve zcc;
    Index index(zcc, 2); // Supongamos 2 pagos por año para el test

    auto currentDate = boost::gregorian::from_string("2017-04-03");
    auto previousDate = boost::gregorian::from_string("2016-10-03");
    double currentPeriod = 1.019; // Equivalente a 6 meses
    double previousPeriod = 0.514; // El periodo previo empieza en 0

    // Cálculo de Rm esperado manualmente para verificar el resultado
    double expectedRm = 0.0533;

    double resultRm = index.computeRm(currentDate, previousDate, currentPeriod, previousPeriod);
    BOOST_TEST(resultRm == expectedRm, boost::test_tools::tolerance(0.001));
    // Añadimos tolerancia para la comparativa
}