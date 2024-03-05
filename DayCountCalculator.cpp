#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "DayCountCalculator.h"

// Convertimos el string a tipo de dato gregoriano y llamamos a la implementacion siguiente
short Actual_360::compute_daycount(const std::string& from, const std::string& to){

    boost::gregorian::date from_date(boost::gregorian::from_string(from));
    boost::gregorian::date to_date(boost::gregorian::from_string(to));
    return compute_daycount(from_date, to_date);
}

//Esta funcion es la que verdaderamente calcula la diferencia de dias
short Actual_360::compute_daycount(const boost::gregorian::date & from,
                                   const boost::gregorian::date & to)
{
    return (to - from).days();  //Esta funcion es de boost. Devuelve la diferencia de dias en dos variables gregorian
}



//-----------------------------------------------------------------------------------------------------------------\\


short Thirty_360::compute_daycount(const std::string& from, const std::string& to){

    auto from_date(boost::gregorian::date(boost::gregorian::from_string(from)));
    auto to_date(boost::gregorian::date(boost::gregorian::from_string(to)));
    return compute_daycount(from_date, to_date);
    //Llama a la siguiente funcion que recibe dos valores de fecha de tipo gregoriano
}

short Thirty_360::compute_daycount(const boost::gregorian::date & from,
                                   const boost::gregorian::date & to){

    //year_month_day() imagino que convierte una fecha de tipo gregoriano a año-mes-dia y para sacarlo hay q usar los
    //metodos .year, .month, .day

    auto from_date(from.year_month_day());
    auto to_date(to.year_month_day());
    auto years = to_date.year - from_date.year;
    auto months = to_date.month - from_date.month;
    return compute_daycount(years, months, from_date.day, to_date.day);

    //Ahora que ya se han preparado los datos se llama a la siguiente implementacion que recibe años, mes y dias
}

//Esta implementacion es la que verdaderamente calcula los dias de diferencia
short Thirty_360::compute_daycount(const short years, const short months,
                                   const short days_from,
                                   const short days_to)
{
    return (360 * years) + 30 * (months -1) +
           std::max<short>(0, 30 - days_from) +
           std::min<short>(30, days_to);
}

