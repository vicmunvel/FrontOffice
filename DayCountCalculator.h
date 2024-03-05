#ifndef MANEJO_FECHAS_HPP
#define MANEJO_FECHAS_HPP

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

class DayCountCalculator {
public:
    static boost::gregorian::date make_date(const std::string& date);
};

// Actual/360: Utiliza el número real de días entre dos fechas y divide este número por 360
class Actual_360 : public DayCountCalculator { // Actual_360 -> Clase derivada de DayCountCalculator
public:
    //short es un tipo de variable en C++ para almacenar enteros de 16 bits, como almacenamos numero de dias, bien.
    static short compute_daycount(const std::string& from, const std::string& to);
    static short compute_daycount(const boost::gregorian::date &from, const boost::gregorian::date &to);
    template<class DATE>
    double operator()(const DATE& start, const DATE& end) const{
        return compute_daycount(start, end) / 360.0;
    }
};

//30/360: Este método asume que todos los meses tienen 30 días, lo que simplifica los cálculos de interés
class Thirty_360 : public DayCountCalculator { // Thirty_360 -> Clase derivada de DayCountCalculator
public:
    static short compute_daycount(const std::string& from, const std::string& to);
    static short compute_daycount(const boost::gregorian::date &from, const boost::gregorian::date &to);
    static short compute_daycount(const short years, const short months, const short days_from, const short days_to);

    template<class DATE>
    double operator()(const DATE& start, const DATE& end) const{
        return compute_daycount(start, end) / 360.0;
    }
};

#endif