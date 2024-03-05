cmake_minimum_required(VERSION 3.27)
project(Prueba)

set(CMAKE_CXX_STANDARD 17)

# Especifica la ruta de instalación de Boost
set(BOOST_ROOT /home/victor/boost_1_84_0)

# Añade Boost
find_package(Boost COMPONENTS date_time REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Prueba main.cpp
        LegDescription.h
        InstrumentDescription.h
        ZeroCouponCurve.cpp
        ZeroCouponCurve.h
        DayCountCalculator.cpp
        DayCountCalculator.h
)
