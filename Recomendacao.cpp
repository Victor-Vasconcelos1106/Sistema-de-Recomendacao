#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "ListaCompras.h"
#include "Similaridade.h"

int main(){
    Dados dados;
    ListaCompras(&dados);
    int numero_clientes = dados.index_client.size();

    Matriz_s matriz;
    Similaridade(&matriz);

    vector<int> L;

    for (int s = 0; s < numero_clientes; s++) {
        
    }
}