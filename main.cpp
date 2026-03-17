#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ListaCompras.h"
using namespace std;

int main() {
    Dados dados = ListaCompras();

    vector<string> clientes;
    string codigo;
    for (int i = 0; i < 3; i++) {  
        cout << "Código do cliente: ";
        cin >> codigo;
        clientes.push_back(codigo);
    }

    for (auto &cli : clientes) {
        int idx = -1;
        for (int i = 0; i < dados.client_codes.size(); i++) {
            if (dados.client_codes[i] == cli) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            cout << "Cliente " << cli << " não encontrado!\n";
            continue;
        }

        cout << "Cliente " << cli << " comprou: ";
        for (int pid : dados.compras_cliente[idx]) {
            cout << dados.product_names[pid] << " / ";
        }
        cout << endl;
    }

    return 0;
}