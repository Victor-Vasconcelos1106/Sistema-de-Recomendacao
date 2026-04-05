#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <vector>
#include <string>
#include <algorithm>
#include "ListaCompras.h"
#include "Similaridade.h"


struct Produto
{
    int id_produto;
    float valor_ranking;
};

void Recomendacao(int cliente_c, Dados* dados, float* matriz, int k, vector<string>* nomes);


#endif
