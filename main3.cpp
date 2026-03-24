#include "Recomendacao.h"
#include <iostream>
#include "ListaCompras.h"
#include <string>
#include "Similaridade.h"

int main(){
    Dados dados;
    ListaCompras(&dados);

    Matriz_s matriz;
    Similaridade(&matriz);



    vector<string> clientes;
    string codigo;
    for (int i = 0; i < 1; i++) {  
        cout << "Código do cliente: ";
        cin >> codigo;
        clientes.push_back(codigo);
    }


    vector<int> clientes_idx;

    for( string code : clientes)
    {

        clientes_idx.push_back(dados.index_client[code]);

    }

    for(int idx : clientes_idx)
    {

        vector<string> recomendacoes;

        Recomendacao(idx, &dados, &matriz, 3, &recomendacoes);

        for(string produto : recomendacoes)
        {

            cout << "cliente " << idx << ": "<< produto;

        }

    }

    return 0;
}