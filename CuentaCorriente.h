//
// Created by juanf on 02/04/2025.
//

#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H

#include "Cuenta.h"
#include "json.hpp"

class CuentaCorriente : public Cuenta {
private:
    int limiteCredito;
public:
    CuentaCorriente(int numero, int saldo, int id_cliente, int limiteCredito)
        : Cuenta(numero, saldo, id_cliente), limiteCredito(limiteCredito) { }

    void mostrar() const override;
    json tojson() const override;
    string getTipo() const override;

    // Operación de retiro con validación del límite de sobregiro
    bool retirar(int monto) override;
};

#endif //CUENTACORRIENTE_H
