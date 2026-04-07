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

    printf("entrando LC");    

    Dados dados;
    ListaCompras(&dados);

    printf("Entrando MS");

    float* matriz = Similaridade();
    
    
    printf("Saindo MS");

    int i;
    int j;
    
    string codigo;
    
    for ( i = 0; i < 1; i++ ) 
    {
                 
        cout << "Código do cliente: " << endl;
        cin >> codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int client_internal_index = dados.index_client[codigo];
        
        vector<string> recomendados;
        Recomendacao( client_internal_index , &dados, matriz, 3, &recomendados);
        
        for( j = 0; j < recomendados.size(); j++)
        {
                    
             cout << "recomendação numero " << (j + 1) << " para o cliente "  << client_internal_index << " :" << endl;
             cout << recomendados[j] << endl;  
        
        }
        
        recomendados.clear();
         
    }
    
}

