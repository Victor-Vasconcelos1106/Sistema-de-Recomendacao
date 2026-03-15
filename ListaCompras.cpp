#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{

 FILE *csv;
 csv = fopen("dados_venda_cluster_0.csv","r");
 if(csv == NULL){
  perror("Erro ao abrir o csv");
  return 1;
 }

 char client_buf[30];
 char product_buf[30];
 char data_buf[59];
 char name_buf[59];
 
 vector<string> client_codes;
 vector<string> product_names;
 vector<vector<int> > compras_cliente;

 map<string, int> index_client;
 map<string, int> index_product;

 int next_client = 0;
 int next_product = 0;

 while(fscanf(csv, "%29[^,],%29[^,],%29[^,],%58[^\n]\n", data_buf, client_buf, product_buf, name_buf) == 4){
  client_codes.push_back(client_buf);
  product_names.push_back(name_buf);


  if(index_client.count(client_buf) == 0)
      index_client[client_buf] = next_client++;

  if(index_product.count(product_buf) == 0)
      index_product[product_buf] = next_product++;

  int client_id = index_client[client_buf];
  int product_id = index_product[product_buf];

  if(client_id >= compras_cliente.size())
      compras_cliente.resize(client_id+1);

  compras_cliente[client_id].push_back(product_id);

 }

 fclose(csv);
 
 // Teste Matriz
 
    // Criar a Matriz, onde as linhas são os clientes
    // e as colunas os produtos.
    // 0 para compra negativa e 1 para compra positiva
    
    //Criar a transposta(colunas viram linhas e linhas colunas)
    
    //Produto das matrizes( linha x coluna = termo )

 // "Alocação" das Matrizes
 
 int Matriz_compras[index_client.size()][index_product.size()];
 int Matriz_compras_transposta[index_product.size()][index_client.size()];
 int Matriz_intersecao[index_client.size()][index_client.size()];
 
 // Preencher as matrizes 
 
    // Preencher Matriz de Compras 
    
 int i,j,k;
 
 for(i = 0; i < index_client.size(); i++)
 {
       
       for( j = 0; j < index_product.size(); j++)
       {
            
            Matriz_compras[i][j] = 0;
            
       }
       
       for( k = 0; k < compras_cliente[i].size(); k++)
       {
           
            Matriz_compras[i][ compras_cliente[i][k] ] = 1;  
       
       }
 
 }
 
    // Preencher matriz_transposta
       
 for(i = 0; i < index_client.size(); i++)
 {
       
       for( j = 0; j < index_product.size(); j++)
       {
          
            Matriz_compras_transposta[j][i] = Matriz_compras[i][j];
       
       }
       
 }
 
    // Produto Matrizes
 
 //for(i = 0; i < index_client.size(); i++)
 //{
       
       //for( j = 0; j < index_product.size(); j++)
       //{
          
            //Matriz_compras_transposta[j][i] = Matriz_compras[i][j];
       
       //}
       
 //}
 
 return 0;

}
