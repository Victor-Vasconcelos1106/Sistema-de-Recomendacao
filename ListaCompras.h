#ifndef LISTA_COMPRAS_H
#define LISTA_COMPRAS_H

#include <vector>
#include <string>
#include <map>
using namespace std;

struct Dados {
    vector<vector<int>> compras_cliente; 
    vector<string> client_codes;        
    vector<string> product_names;
    map<string, int> index_client;
    map<string, int> index_product;       
           
};

Dados ListaCompras();

#endif