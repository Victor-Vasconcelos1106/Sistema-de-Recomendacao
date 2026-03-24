#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "ListaCompras.h"
#include "Similaridade.h"
#include <ctime>

using namespace std;

clock_t inicio_similaridade_exec;
clock_t fim_similaridade_exec;

int main(){
    Dados dados;
    ListaCompras(&dados);
    int numero_clientes = dados.index_client.size();

    Matriz_s matriz;
    
    inicio_similaridade_exec = clock();
    Similaridade(&matriz);
    fim_similaridade_exec = clock();

    cout << "Tempo gasto computando a similaridade de forma não otimizada : " << ((double)(fim_similaridade_exec - inicio_similaridade_exec)/CLOCKS_PER_SEC) << endl;

    inicio_similaridade_exec = clock();
    Similaridade_Otimizada(&matriz);
    fim_similaridade_exec = clock();

    cout << "Tempo gasto computando a similaridade de forma otimizada : " << ((double)(fim_similaridade_exec - inicio_similaridade_exec)/CLOCKS_PER_SEC) << endl;
}