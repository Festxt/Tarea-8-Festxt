//
// Created by juanc on 02/04/2025.
//

#ifndef CUENTA_H
#define CUENTA_H
#include <string>
#include <iostream>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class Cuenta {
protected:
    int numero;
    int saldo;
    int idCliente;

public:
    Cuenta(int numero, int saldo, int id_Cliente) :
    numero(numero), saldo(saldo), idCliente(id_Cliente) {
    }

    virtual json tojson() const {
        return json{{"numero",numero},{"saldo",saldo},{"idCliente",idCliente},{"tipo","Cuenta"}};
    }

    virtual void mostrar() const = 0;


    virtual string getTipo() const = 0;

    virtual bool retirar(int monto) = 0;

    virtual void consignar(int monto) {
        saldo += monto;
    }

    int getNumero() {
        return numero;
    }
    int getSaldo() {
        return saldo;
    }
    int getIdCLiente() {
        return idCliente;
    }
};


#endif //CUENTA_H