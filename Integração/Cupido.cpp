#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <stdio.h>
#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <map>
#include <string>

namespace py = pybind11;

struct Dados {
    
    std::vector<std::list<int> > compras_cliente; 
    std::vector<std::string> client_codes;        
    std::vector<std::string> product_names;
    std::map<std::string, int> index_client;
    std::map<std::string, int> index_product;       
           
};

std::tuple< std::vector<std::list<int>>, std::vector<std::string>, std::vector<std::string>,
std::map<std::string, int>,std::map<std::string, int> > ListaCompras()
{

    std::vector<std::list<int>> compras_cliente;
    std::vector<std::string> client_codes;
    std::vector<std::string> product_names;
    std::map<std::string, int> index_client;
    std::map<std::string, int> index_product;

    /*enum index_tuple{

        compras_cliente,
        client_codes,
        product_names,
        index_client,
        index_product

                    };
    */  
    FILE *csv;
    csv = fopen("dados_venda_cluster_0.csv","r");
    if(csv == NULL)
    {

    perror("Erro ao abrir o csv");
    
    }

    int contador = 0;
    char client_buf[30];
    char product_buf[30];
    char data_buf[59];
    char name_buf[59];

    int next_client = 0;
    int next_product = 0;

    while(fscanf(csv, "%29[^,],%29[^,],%29[^,],%58[^\n]\n", data_buf, client_buf, product_buf, name_buf) == 4){
    if(contador == 0)
    {
                
    contador++;
    continue;
    
    }

    if(index_client.count(client_buf) == 0){
        index_client[client_buf] = next_client++;
        client_codes.push_back(client_buf);
    }
        
    if(index_product.count(product_buf) == 0){
        index_product[product_buf] = next_product++;
        product_names.push_back(name_buf);
    }
        

    int client_id = index_client[client_buf];
    int product_id = index_product[product_buf];

    if(client_id >= compras_cliente.size())
    {

        compras_cliente.resize(client_id + 1);

    }
        

    compras_cliente[client_id].push_back(product_id);

    }

    fclose(csv);

    return {compras_cliente, client_codes, product_names, index_client, index_product};

}


PYBIND11_MODULE(Recomendacao,R)
{

    R.doc() = "Integração do sistema de recomendação com python"; 

    R.def("ListaCompras", &ListaCompras);



}

