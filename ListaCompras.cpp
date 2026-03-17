#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "ListaCompras.h"
using namespace std;

Dados ListaCompras(){

 FILE *csv;
 csv = fopen("dados_venda_cluster_0.csv","r");
 if(csv == NULL){
  perror("Erro ao abrir o csv");
  return {};
 }

 int contador = 0;
 char client_buf[30];
 char product_buf[30];
 char data_buf[59];
 char name_buf[59];
 
 vector<string> client_codes;
 vector<string> product_names;
 vector<vector<int>> compras_cliente;

 map<string, int> index_client;
 map<string, int> index_product;

 int next_client = 0;
 int next_product = 0;

 while(fscanf(csv, "%29[^,],%29[^,],%29[^,],%58[^\n]\n", data_buf, client_buf, product_buf, name_buf) == 4){
  if(contador == 0){
   contador++;
   continue;
  }
  client_codes.push_back(client_buf);
  product_names.push_back(name_buf);


  if(index_client.count(client_buf) == 0){
      index_client[client_buf] = next_client++;
  }
      
  if(index_product.count(product_buf) == 0){
      index_product[product_buf] = next_product++;
  }
      

  int client_id = index_client[client_buf];
  int product_id = index_product[product_buf];

  if(client_id >= compras_cliente.size()){
      compras_cliente.resize(client_id+1);
  }
      

  compras_cliente[client_id].push_back(product_id);

 }

 fclose(csv);
 return {compras_cliente, client_codes, product_names, index_client, index_product};

}
