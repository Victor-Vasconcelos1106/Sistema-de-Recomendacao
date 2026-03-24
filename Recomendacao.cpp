#include <iostream>
#include "Recomendacao.h"

bool compararProdutos(const Produto& a, const Produto& b) {
    return a.valor_ranking < b.valor_ranking; 
}

void Recomendacao(int cliente_c, Dados* dados, Matriz_s* matriz, int k, vector<string> *nomes){
    Dados *ptr_dados = dados;
    int numero_clientes = ptr_dados->index_client.size();
    int numero_produtos = ptr_dados->index_product.size();
    vector<list<int>> compras = ptr_dados->compras_cliente;

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
        Produto i = {p,1.0};
        R.push_back({i});
    }

    for (int s : L) {

        float similaridade_cs = matriz->matriz[cliente_c * numero_clientes + s];

        for (int produto : ptr_dados->compras_cliente[s]) {

            auto it = find(ptr_dados->compras_cliente[cliente_c].begin() , ptr_dados->compras_cliente[cliente_c].end(), produto );

            if(it == ptr_dados->compras_cliente[cliente_c].end())
            {

                R[produto].valor_ranking *= similaridade_cs;

            }

        }
    }

    sort(R.begin(), R.end(), compararProdutos);

    vector<string> *ids = nomes;

    for(int i = 0; i < k; i++){
        (*(ids)).push_back(ptr_dados->product_names[R[i].id_produto]);
    }

    
}
