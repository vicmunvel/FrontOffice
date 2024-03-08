cmake_minimum_required(VERSION 3.27)
project(Front_Office)

set(CMAKE_CXX_STANDARD 17)

# Especifica la ruta de instalación de Boost
set(BOOST_ROOT /home/victor/boost_1_84_0)

# Añade Boost
find_package(Boost COMPONENTS date_time unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Valoracion main.cpp
        DayCountCalculator.cpp
        DayCountCalculator.h
        InstrumentDescription.h
        LegDescription.h
        ZeroCouponCurve.cpp
        ZeroCouponCurve.h
        Leg.cpp
        Leg.h
        FixedLeg.cpp
        FixedLeg.h
        FloatingLeg.cpp
        FloatingLeg.h
        Index.cpp
        Index.h
        Swap.cpp
        Swap.h
        Bond.cpp
        Bond.h
        Instrument.cpp
        Instrument.h
        GoalSeeker.cpp
        TIR_NewtonRaphson.cpp)

# Ejecutable para el test de la clase DayCountCalculator
add_executable(Test_1 Test_DayCountCalculator.cpp DayCountCalculator.cpp DayCountCalculator.h)
target_link_libraries(Test_1 ${Boost_LIBRARIES})

# Ejecutable para el test de la clase Index
add_executable(Test_2 Test_Index.cpp Index.cpp Index.h ZeroCouponCurve.cpp ZeroCouponCurve.h)
target_link_libraries(Test_2 ${Boost_LIBRARIES})

# Ejecutable para el test de las patas
add_executable(Test_3 Test_Legs.cpp Leg.cpp Leg.h FixedLeg.cpp FixedLeg.h FloatingLeg.cpp FloatingLeg.h Index.cpp
        Index.h ZeroCouponCurve.cpp ZeroCouponCurve.h LegDescription.h  DayCountCalculator.cpp DayCountCalculator.h)
target_link_libraries(Test_3 ${Boost_LIBRARIES})

# Ejecutable para el test de la clase Instrument para descontar
add_executable(Test_4 Test_Instrument.cpp Instrument.cpp Instrument.h ZeroCouponCurve.cpp ZeroCouponCurve.h Bond.cpp
        Bond.h FixedLeg.cpp FixedLeg.h DayCountCalculator.cpp DayCountCalculator.h FloatingLeg.cpp FloatingLeg.h Swap.h
        Swap.cpp Leg.cpp Leg.h Index.cpp Index.h)
target_link_libraries(Test_4 ${Boost_LIBRARIES})

# Ejecutable para el test del flujo completo de ejecucion
add_executable(Test_5 Test_Total.cpp Instrument.cpp Instrument.h ZeroCouponCurve.cpp ZeroCouponCurve.h Bond.cpp
        Bond.h FixedLeg.cpp FixedLeg.h DayCountCalculator.cpp DayCountCalculator.h FloatingLeg.cpp FloatingLeg.h Swap.h
        Swap.cpp Leg.cpp Leg.h Index.cpp Index.h)
target_link_libraries(Test_5 ${Boost_LIBRARIES})

