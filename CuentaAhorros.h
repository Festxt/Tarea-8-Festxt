//
// Created by juanf on 02/04/2025.
//


#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H
#include <iostream>
#include "json.hpp"
#include "Cuenta.h"

class CuentaAhorros : public Cuenta {
private:
    double tasaInteres;
public:
    CuentaAhorros(int numero, int saldo, int id_cliente, double tasa_interes)
        : Cuenta(numero, saldo, id_cliente), tasaInteres(tasa_interes) { }

    void mostrar() const override;
    json tojson() const override;
    string getTipo() const override;
    bool retirar(int monto) override;
    void aplicarInteres();
};

#endif //CUENTAAHORROS_H

