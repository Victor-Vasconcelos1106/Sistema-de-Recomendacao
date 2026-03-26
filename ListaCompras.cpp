#include <stdio.h>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "ListaCompras.h"
using namespace std;

void ListaCompras(Dados *ptr){

 FILE *csv;
 csv = fopen("dados_venda_cluster_0.csv","r");
 if(csv == NULL){
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
  
  if(ptr->index_client.count(client_buf) == 0){
      ptr->index_client[client_buf] = next_client++;
      ptr->client_codes.push_back(client_buf);
  }
      
  if(ptr->index_product.count(product_buf) == 0){
      ptr->index_product[product_buf] = next_product++;
      ptr->product_names.push_back(name_buf);
  }
      

  int client_id = ptr->index_client[client_buf];
  int product_id = ptr->index_product[product_buf];

  if(client_id >= ptr->compras_cliente.size()){
      ptr->compras_cliente.resize(client_id+1);
  }
      

  ptr->compras_cliente[client_id].push_back(product_id);

 }
 fclose(csv);


}
