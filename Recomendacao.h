#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <vector>
#include <string>
#include <algorithm>
#include "ListaCompras.h"
#include "Similaridade.h"

struct Produto{
    int id_produto;
    float valor_ranking;
};

vector<string> Recomendacao(string cliente_c, Dados* dados, Matriz_s* matriz, int k);


#endif