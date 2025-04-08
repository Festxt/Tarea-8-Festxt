//
// Created by juanf on 02/04/2025.
//

#include "CuentaAhorros.h"
using namespace std;

void CuentaAhorros::mostrar() const {
    cout << "Cuenta Ahorros - Numero: " << numero
              << ", Saldo: " << saldo
              << ", Cliente: " << idCliente
              << ", Tasa de Interes: " << tasaInteres << std::endl;
}

json CuentaAhorros::tojson() const {
    json j = Cuenta::tojson();
    j["tipo"] = "CuentaAhorros";
    j["tasaInteres"] = tasaInteres;
    return j;
}

string CuentaAhorros::getTipo() const {
    return "CuentaAhorros";
}

bool CuentaAhorros::retirar(int monto) {
    if (saldo >= monto) {
        saldo -= monto;
        return true;
    }
    return false;
}

void CuentaAhorros::aplicarInteres() {
    saldo += static_cast<int>(saldo * tasaInteres);
}
