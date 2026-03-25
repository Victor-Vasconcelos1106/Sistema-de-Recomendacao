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
    for (int i = 0; i < 3; i++) {  
        cout << "Código do cliente: ";
        cin >> codigo;
        clientes.push_back(codigo);
    }


    vector<int> clientes_idx;

    for( string code : clientes)
    {

        clientes_idx.push_back(dados.index_client[code]);

    }

    for(int H : clientes_idx)
    {

        vector<string> recomendacoes;

        Recomendacao(H, &dados, &matriz, 3, &recomendacoes);

        for(string produto : recomendacoes)
        {

            cout << "cliente " << H << ": "<< produto << endl;

        }

    }

    return 0;
}