#include <iostream>
#include <ios>
#include <limits>
#include <string>
#include <vector>
#include <map>


#include "Recomendacao.h"
#include "ListaCompras.h"
#include "Similaridade.h"

int main()
{
                         
    Dados dados;
    ListaCompras(&dados);

    Matriz_s matriz;
    Similaridade(&matriz);
    
    int i;
    int j;
    
    string codigo;
    
//Teste da matriz similaridade(acho que está errada(linhas muito homogeneas) )    
    for(i = 0; i < dados.index_client.size(); i++)
    {
            
            for(j = 0; j < dados.index_client.size(); j++)
            {
                    
                    cout << matriz.matriz[ i * dados.index_client.size() + j ]<< ",";
                    
            }
         
            cout << endl;
            
    
    }
    
    for ( i = 0; i < 3; i++ ) 
    {
                 
        cout << "CÃ³digo do cliente: " << endl;
        cin >> codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int client_internal_index = dados.index_client[codigo];
        
        vector<string> recomendados;
        Recomendacao( client_internal_index , &dados, &matriz, 3, &recomendados);
        
        for( j = 0; j < recomendados.size(); j++)
        {
                    
             cout << "recomendação numero " << (j + 1) << " para o cliente "  << client_internal_index << " :" << endl;
             cout << recomendados[j] << endl;  
        
        }
        
        recomendados.clear();
         
    }
    
}


   /* vector<int> clientes_idx;

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

            cout < < "cliente " < < H < < ": "< < produto < < endl;
        }

    }

    return 0;
}
*/
