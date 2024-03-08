#define BOOST_TEST_MODULE Test_DayCountCalculator
#include <boost/test/included/unit_test.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "DayCountCalculator.h"

BOOST_AUTO_TEST_CASE(test_Actual_360_daycount) {
    Actual_360 calculator;
    auto from_date = boost::gregorian::from_simple_string("2016-04-01");
    auto to_date = boost::gregorian::from_simple_string("2016-10-03");

    BOOST_TEST_MESSAGE("Testeando Actual/360 desde " << from_date << " hasta " << to_date);
    int result = calculator.compute_daycount(from_date, to_date);
    BOOST_TEST(result == 185); // Verificamos que hay 185 dias entre medias
}

BOOST_AUTO_TEST_CASE(test_Thirty_360_daycount) {
    Thirty_360 calculator;
    auto from_date = boost::gregorian::from_simple_string("2016-04-01");
    auto to_date = boost::gregorian::from_simple_string("2016-10-03");

    BOOST_TEST_MESSAGE("Testeando Thirty/360 desde " << from_date << " hasta " << to_date);
    int result = calculator.compute_daycount(from_date, to_date);
    BOOST_TEST(result == 182); // Verifica que los días sean 183 según Thirty_360
}
