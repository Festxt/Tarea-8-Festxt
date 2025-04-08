#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Cliente.h"
#include "Cuenta.h"
#include "CuentaAhorros.h"
#include "CuentaCorriente.h"

using namespace std;
using json = nlohmann::json;

class Banco {
private:
    string nombre;
    vector<Cliente*> clientes;
    vector<Cuenta*> cuentas;
    int nextClienteId;
    int nextCuentaNumero;
public:
    Banco(const string& nombre)
        : nombre(nombre), nextClienteId(1), nextCuentaNumero(100) { }
    
    ~Banco() {
        for(auto c : clientes) delete c;
        for(auto c : cuentas) delete c;
    }
    void agregarCliente(const string& nombre, const string& direccion) {
        Cliente* c = new Cliente(nextClienteId++, nombre, direccion);
        clientes.push_back(c);
    }
    
    void listarClientes() const {
        cout  << endl << "Lista de Clientes:" << endl;
        for(auto c : clientes)
            c->mostrar();
    }
    void agregarCuentaAhorros(int idCliente, int saldo, double tasaInteres) {
        Cuenta* cuenta = new CuentaAhorros(nextCuentaNumero++, saldo, idCliente, tasaInteres);
        cuentas.push_back(cuenta);
    }
    
    void agregarCuentaCorriente(int idCliente, int saldo, int limiteCredito) {
        Cuenta* cuenta = new CuentaCorriente(nextCuentaNumero++, saldo, idCliente, limiteCredito);
        cuentas.push_back(cuenta);
    }
    
    void listarCuentas() const {
        cout << endl << "Lista de Cuentas:" << endl;
        for(auto cuenta : cuentas)
            cuenta->mostrar();
    }
    int totalClientes() const {
        return clientes.size();
    }
    
    int totalCuentas() const {
        return cuentas.size();
    }
    
    double promedioSaldo() const {
        if(cuentas.empty()) return 0;
        int total = 0;
        for(auto c : cuentas)
            total += c->getSaldo();
        return static_cast<double>(total) / cuentas.size();
    }
    
    int totalCuentasAhorro() const {
        int count = 0;
        for(auto c : cuentas)
            if(c->getTipo() == "CuentaAhorros")
                count++;
        return count;
    }
    
    int totalCuentasCorriente() const {
        int count = 0;
        for(auto c : cuentas)
            if(c->getTipo() == "CuentaCorriente")
                count++;
        return count;
    }
    void aplicarInteresACuentasAhorro() {
        for(auto c : cuentas) {
            if(c->getTipo() == "CuentaAhorros") {
                CuentaAhorros* ca = dynamic_cast<CuentaAhorros*>(c);
                if(ca)
                    ca->aplicarInteres();
            }
        }
        cout << endl <<"Se ha aplicado la tasa de interés a las cuentas de ahorro." << endl;
    }
    
    bool consignarDinero(int numeroCuenta, int monto) {
        for(auto c : cuentas) {
            if(c->getNumero() == numeroCuenta) {
                c->consignar(monto);
                return true;
            }
        }
        return false;
    }
    
    bool retirarDinero(int numeroCuenta, int monto) {
        for(auto c : cuentas) {
            if(c->getNumero() == numeroCuenta) {
                return c->retirar(monto);
            }
        }
        return false;
    }

    json toJson() const {
        json j;
        j["nombre"] = nombre;
        j["clientes"] = json::array();
        for(auto c : clientes)
            j["clientes"].push_back(c->tojson());
        j["cuentas"] = json::array();
        for(auto c : cuentas)
            j["cuentas"].push_back(c->tojson());
        j["nextClienteId"] = nextClienteId;
        j["nextCuentaNumero"] = nextCuentaNumero;
        return j;
    }
    
    void guardar(const string& filename) const {
        ofstream file(filename);
        if(file.is_open()){
            file << toJson().dump(4);
            file.close();
            cout  << endl << "Datos guardados en " << filename << endl;
        } else {
            cout << "No se pudo abrir el archivo para guardar." << endl;
        }
    }
    
    void cargar(const string& filename) {
        ifstream file(filename);
        if(file.is_open()){
            json j;
            file >> j;
            file.close();
            for(auto c : clientes) delete c;
            clientes.clear();
            for(auto c : cuentas) delete c;
            cuentas.clear();
            
            nombre = j["nombre"];
            for(auto& item : j["clientes"]) {
                int id = item["id"];
                string nom = item["nombre"];
                string dir = item["direccion"];
                Cliente* c = new Cliente(id, nom, dir);
                clientes.push_back(c);
            }
            for(auto& item : j["cuentas"]) {
                string tipo = item["tipo"];
                int numero = item["numero"];
                int saldo = item["saldo"];
                int idCliente = item["idCliente"];
                if(tipo == "CuentaAhorros") {
                    double tasaInteres = item["tasaInteres"];
                    Cuenta* c = new CuentaAhorros(numero, saldo, idCliente, tasaInteres);
                    cuentas.push_back(c);
                } else if(tipo == "CuentaCorriente") {
                    int limiteCredito = item["limiteCredito"];
                    Cuenta* c = new CuentaCorriente(numero, saldo, idCliente, limiteCredito);
                    cuentas.push_back(c);
                }
            }
            nextClienteId = j["nextClienteId"];
            nextCuentaNumero = j["nextCuentaNumero"];
            cout << endl << "Datos cargados desde " << filename << endl;
        } else {
            cout << "No se pudo abrir el archivo para cargar." << endl;
        }
    }
};

#endif //BANCO_H
