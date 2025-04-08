cmake_minimum_required(VERSION 3.30)
project(tarea_8_Festxt)

set(CMAKE_CXX_STANDARD 20)

add_executable(tarea_8_Festxt main.cpp
        Cuenta.cpp
        Cuenta.h
        CuentaAhorros.cpp
        CuentaAhorros.h
        CuentaCorriente.cpp
        CuentaCorriente.h
        Cliente.cpp
        Cliente.h
        Banco.cpp
        Banco.h)
