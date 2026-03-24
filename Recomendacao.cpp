#include <iostream>
#include "Recomendacao.h"

bool compararProdutos(const Produto& a, const Produto& b) {
    return a.valor_ranking < b.valor_ranking; 
}

vector<string> Recomendacao(int cliente_c, Dados* dados, Matriz_s* matriz, int k){
    Dados *ptr_dados = dados;
    int numero_clientes = dados->index_client.size();
    int numero_produtos = dados->index_product.size();
    vector<list<int>> compras = dados->compras_cliente;

    float *ptr_matriz = matriz->matriz;

    vector<int> L;
    vector<Produto> R;

   for (int i = 0; i < numero_clientes; i++) {
        if (i == cliente_c){
            continue;
        } 

        float dist_atual = *(ptr_matriz + (cliente_c * numero_clientes + i));
        
        if (dist_atual < 1.0) {
            L.push_back(i);
        }
    }

    for (int p = 0; p < numero_produtos; p++) {
        R[p].id_produto = p;
        R[p].valor_ranking = 1.0; 
    }

    for (int s : L) {
        float similaridade_cs = matriz->matriz[cliente_c * numero_clientes + s];
        for (int p : dados->compras_cliente[s]) {

        }
    }





    sort(R.begin(), R.end(), compararProdutos);

}
