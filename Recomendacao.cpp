#include <iostream>
#include "Recomendacao.h"

vector<string> Recomendacao(int cliente_c, Dados* dados, Matriz_s* matriz, int k){
    Dados *ptr_dados = dados;
    int numero_clientes = dados->index_client.size();
    int numero_produtos = dados->index_product.size();
    vector<list<int>> compras = dados->compras_cliente;

    float *ptr_matriz = matriz->matriz;

    vector<int> L;
    vector<float> R;

   for (int i = 0; i < numero_clientes; i++) {
        if (cliente_c == i){
            continue;
        } 

        float distAtual = *(ptr_matriz + (cliente_c * numero_clientes + i));
        
        if (distAtual < 1) {
            L.push_back(i);
        }
    }


    for(int i = 0; i < numero_produtos; i++){
        R.push_back(1);
    }

    for(int i = 0; i < L.size(); i++){
        
    }






    





}
