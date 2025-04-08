//
// Created by juanf on 02/04/2025.
//

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Cliente {
private:
    int id;
    string nombre;
    string direccion;
public:
    Cliente(int id, const string& nombre, const string& direccion)
        : id(id), nombre(nombre), direccion(direccion) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getDireccion() const { return direccion; }

    void mostrar() const {
        cout << "ID: " << id << ", Nombre: " << nombre << ", Dirección: " << direccion << endl;
    }

    json tojson() const {
        return json{
                {"id", id},
                {"nombre", nombre},
                {"direccion", direccion}
        };
    }
};

#endif //CLIENTE_H
