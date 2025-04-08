#include <iostream>
#include "Banco.h"

using namespace std;

void mostrarMenu() {
    cout << "\n====== MENU BANCO JAVERIANO ======\n";
    cout << "1) MANTENIMIENTO DE CLIENTES\n";
    cout << "   1.1) Agregar Cliente\n";
    cout << "   1.2) Listar Clientes\n";
    cout << "\n2) MANTENIMIENTO DE CUENTAS\n";
    cout << "   2.1) Agregar Cuenta\n";
    cout << "   2.2) Listar Cuentas\n";
    cout << "\n3) ESTADISTICAS\n";
    cout << "   3.1) Total de Clientes\n";
    cout << "   3.2) Total de Cuentas\n";
    cout << "   3.3) Promedio del Saldo de las Cuentas\n";
    cout << "   3.4) Numero de Cuentas de Ahorro\n";
    cout << "   3.5) Numero de Cuentas Corrientes\n";
    cout << "\n4) OPERACIONES FINANCIERAS\n";
    cout << "   4.1) Aplicar Tasa de Interés a Cuentas de Ahorro\n";
    cout << "   4.2) Consignar Dinero en una Cuenta\n";
    cout << "   4.3) Retirar Dinero de una Cuenta\n";
    cout << "\n5) SALIR\n";
    cout << "   5.1) Guardar los datos y cerrar el programa\n";
    cout << "==================================\n";
}

int main() {
    Banco banco("Banco Javeriano");
    const string archivo = "BancoJaveriano.json";
    banco.cargar(archivo);

    int opcion = 0;
    while(true) {
        mostrarMenu();
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }
        if(opcion == 1) {
            int subOpcion;
            cout << "\n1.1) Agregar Cliente\n1.2) Listar Clientes\nSeleccione: ";
            cin >> subOpcion;
            if(subOpcion == 1) {
                string nombre, direccion;
                cout << "\nIngrese nombre del cliente: ";
                getline(cin, nombre);
                cout << "Ingrese direccion: ";
                getline(cin, direccion);
                banco.agregarCliente(nombre, direccion);
                cout << "Cliente agregado con exito.\n";
            } else if(subOpcion == 2) {
                banco.listarClientes();
            }
        } else if(opcion == 2) {
            int subOpcion;
            cout << "\n2.1) Agregar Cuenta\n2.2) Listar Cuentas\nSeleccione: ";
            cin >> subOpcion;
            if(subOpcion == 1) {
                int tipo;
                cout << "\nSeleccione tipo de cuenta (1: Ahorros, 2: Corriente): ";
                cin >> tipo;
                int idCliente, saldo;
                cout << "Ingrese ID del cliente: ";
                cin >> idCliente;
                cout << "Ingrese saldo inicial: ";
                cin >> saldo;
                if(tipo == 1) {
                    double tasa;
                    cout << "Ingrese tasa de interes (por ejemplo, 0.05 para 5%): ";
                    cin >> tasa;
                    banco.agregarCuentaAhorros(idCliente, saldo, tasa);
                } else if(tipo == 2) {
                    int limite;
                    cout << "Ingrese limite de sobregiro: ";
                    cin >> limite;
                    banco.agregarCuentaCorriente(idCliente, saldo, limite);
                }
                cout << "Cuenta agregada correctamente.\n";
            } else if(subOpcion == 2) {
                banco.listarCuentas();
            }
        } else if(opcion == 3) {
            int subOpcion;
            cout << "\n3.1) Total de Clientes\n3.2) Total de Cuentas\n3.3) Promedio del Saldo\n3.4) Cuentas de Ahorro\n3.5) Cuentas Corrientes\nSeleccione: ";
            cin >> subOpcion;
            if(subOpcion == 1) {
                cout << "\nTotal de Clientes: " << banco.totalClientes() << endl;
            } else if(subOpcion == 2) {
                cout << "\nTotal de Cuentas: " << banco.totalCuentas() << endl;
            } else if(subOpcion == 3) {
                cout << "\nPromedio del Saldo: " << banco.promedioSaldo() << endl;
            } else if(subOpcion == 4) {
                cout << "\nNumero de Cuentas de Ahorro: " << banco.totalCuentasAhorro() << endl;
            } else if(subOpcion == 5) {
                cout << "\nNumero de Cuentas Corrientes: " << banco.totalCuentasCorriente() << endl;
            }
        } else if(opcion == 4) {
            int subOpcion;
            cout << "\n4.1) Aplicar Tasa de Interes a Cuentas de Ahorro\n4.2) Consignar Dinero\n4.3) Retirar Dinero\nSeleccione: ";
            cin >> subOpcion;
            if(subOpcion == 1) {
                banco.aplicarInteresACuentasAhorro();
            } else if(subOpcion == 2) {
                int numCuenta, monto;
                cout << "Ingrese el numero de cuenta: ";
                cin >> numCuenta;
                cout << "Ingrese el monto a consignar: ";
                cin >> monto;
                if(banco.consignarDinero(numCuenta, monto))
                    cout << "Consignacion exitosa.\n";
                else
                    cout << "Cuenta no encontrada.\n";
            } else if(subOpcion == 3) {
                int numCuenta, monto;
                cout << "Ingrese el numero de cuenta: ";
                cin >> numCuenta;
                cout << "Ingrese el monto a retirar: ";
                cin >> monto;
                if(banco.retirarDinero(numCuenta, monto))
                    cout << "Retiro exitoso.\n";
                else
                    cout << "Operación fallida. Fondos insuficientes o cuenta no encontrada.\n";
            }
        } else if(opcion == 5) {
            banco.guardar(archivo);
            cout << "\nSaliendo del programa...\n";
            break;
        } else {
            cout << "\nOpción no válida. Intente nuevamente.\n";
        }
    }

    return 0;
}
