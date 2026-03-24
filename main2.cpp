#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "ListaCompras.h"
#include "Similaridade.h"
#include <ctime>

using namespace std;

void ClienteMaisSimilar(int indice, int total_clientes, float* matriz, const vector<string>& codigos) {
    float menorDistancia; 
    int idx;

    if (indice == 0) {
        idx = 1;
    } else {
        idx = 0;
    }

    menorDistancia = matriz[indice * total_clientes + idx];

    for (int j = 0; j < total_clientes; j++) {
        if (indice == j){
            continue;
        } 

        float distAtual = matriz[indice * total_clientes + j];
        
        if (distAtual < menorDistancia) {
            menorDistancia = distAtual;
            idx = j;
        }
    }

    cout << "Cliente digitado: [" << indice << "] " << codigos[indice] << endl;
    if (idx != -1) {
        cout << "Mais Similar: [" << idx << "] " << codigos[idx] << endl;
    }
}

int main() {
    Dados dados;
    ListaCompras(&dados);
    int numero_clientes = dados.index_client.size();

    Matriz_s matriz;

    int cliente1, cliente2;
    cout << "Total dos indices dos clientes: " << numero_clientes - 1 << endl;
    cout << "Digite o indice do primeiro cliente: ";
    cin >> cliente1;
    cout << "Digite o indice do segundo cliente: ";
    cin >> cliente2;
    cout << "\nRESULTADOS:\n" << endl;

    ClienteMaisSimilar(cliente1, numero_clientes, matriz.matriz, dados.client_codes);
    ClienteMaisSimilar(cliente2, numero_clientes, matriz.matriz, dados.client_codes);

    free(matriz.matriz);

    return 0;
}