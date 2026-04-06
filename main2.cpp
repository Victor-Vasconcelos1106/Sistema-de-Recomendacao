#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "ListaCompras.h"
#include "Similaridade.h"

using namespace std;

void ClienteMaisSimilar(int indice, int total_clientes, float* matriz, const vector<string>& codigos) {
    float menor_distancia; 
    int idx;

    if (indice == 0) {
        idx = 1;
    } else {
        idx = 0;
    }

    menor_distancia = matriz[indice * total_clientes + idx];

    for (int j = 0; j < total_clientes; j++) {
        if (indice == j){
            continue;
        } 

        float dist_atual = matriz[indice * total_clientes + j];
        
        if (dist_atual < menor_distancia) {
            menor_distancia = dist_atual;
            idx = j;
        }
    }

    cout << "Cliente digitado: [" << indice << "] " << codigos[indice] << endl;
    cout << "Mais Similar: [" << idx << "] " << codigos[idx] << endl;
    
}

int main() {
    Dados dados;
    ListaCompras(&dados);
    int numero_clientes = dados.index_client.size();

    float* matriz;
    matriz = Similaridade();

    int cliente1, cliente2;
    cout << "Total dos indices dos clientes: " << numero_clientes - 1 << endl;
    cout << "Digite o indice do primeiro cliente: ";
    cin >> cliente1;
    cout << "Digite o indice do segundo cliente: ";
    cin >> cliente2;
    cout << "\nRESULTADOS:\n" << endl;

    ClienteMaisSimilar(cliente1, numero_clientes, matriz, dados.client_codes);
    ClienteMaisSimilar(cliente2, numero_clientes, matriz, dados.client_codes);

    free(matriz);

    return 0;
}