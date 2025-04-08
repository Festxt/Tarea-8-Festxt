//
// Created by juanf on 02/04/2025.
//

#include "CuentaCorriente.h"

void CuentaCorriente::mostrar() const {
    cout << "Cuenta Corriente - Numero: " << numero
              << ", Saldo: " << saldo
              << ", Cliente: " << idCliente
              << ", Limite de Credito: " << limiteCredito << std::endl;
}

json CuentaCorriente::tojson() const {
    return json{
            {"numero", numero},
            {"saldo", saldo},
            {"idCliente", idCliente},
            {"limiteCredito", limiteCredito},
            {"tipo", "CuentaCorriente"}
    };
}

string CuentaCorriente::getTipo() const {
    return "CuentaCorriente";
}

bool CuentaCorriente::retirar(int monto) {
    // Permite sobregiro hasta -limiteCredito
    if (saldo - monto >= -limiteCredito) {
        saldo -= monto;
        return true;
    }
    return false;
}
