#include <stdio.h>
#include "ListaCompras.h"

int main(){
    Dados dados = ListaCompras();

    // Teste Matriz
 
    // Criar a Matriz, onde as linhas são os clientes
    // e as colunas os produtos.
    // 0 para compra negativa e 1 para compra positiva
    
    //Criar a transposta(colunas viram linhas e linhas colunas)
    
    //Produto das matrizes( linha x coluna = termo )

 // "Alocação" das Matrizes
 
 int *Matriz_compras = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_product.size() ) );
 int *Matriz_compras_transposta = (int*)malloc( sizeof(int) * ( dados.index_product.size() ) * ( dados.index_client.size() ) );
 int *Matriz_intersecao = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_client.size() ) );
 
 // Preencher as matrizes 
 
    // Preencher Matriz de Compras 
    
 int i,j,k;
 
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
            
            *(Matriz_compras + (i*j)) = 0;
            
       }
       
       for( k = 0; k < dados.compras_cliente[i].size(); k++)
       {
           
            *( Matriz_compras + ( i * dados.compras_cliente[i][k]) ) = 1;  
       
       }
 
 }
 	//teste matriz de compras 
 	printf("teste matriz de compra\n\n");
 	
 	for(i = 0; i < dados.index_client.size(); i++)
 	{
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
       	
       		printf("%i",*( Matriz_compras + (i*j) ) );
       	
	   }
	   
	   printf("\n");
	   
	}
 	
    // Preencher matriz_transposta
       
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
          
            *( Matriz_compras_transposta + (j*i) ) = *( Matriz_compras + (i*j) );
       
       }
       
 }
 
 //testes matriz transposta de compras 
 
 printf("\n\n\n");
 printf("teste da matriz de compras transposta\n\n");
 
 for(i = 0; i < dados.index_product.size(); i++)
 {
       
       for( j = 0; j < dados.index_client.size(); j++)
       {
          
            printf("%i", *(Matriz_compras_transposta + (i*j) ) );
       
       }
    
 }
 

 
    // Produto Matrizes

int soma_do_produto = 0;

 for(i = 0; i < dados.index_client.size(); i++)
 {
       for (k = 0 ; k < dados.index_client.size();k++)
	   {
	   
       		for( j = 0; j < dados.index_product.size(); j++)
       		{
          
            	soma_do_produto += ( *( Matriz_compras + (i*j) ) ) * ( *( Matriz_compras_transposta + ( (j) * (k) ) ) );
       
       		}
       		
       		*( Matriz_intersecao + (i*k) ) = soma_do_produto;
       		soma_do_produto = 0;
       
   	   }
       
 }
 
 //teste matriz de intersecao
 printf("\n\n");
 printf("teste matriz de intersecao\n\n");
 
 for(i = 0 ; i < dados.index_client.size(); i++ )
 {
 	
 	for(j = 0 ; j < dados.index_client.size(); j++ )
 	{
 		
 		printf("%i",*( Matriz_intersecao + (i*j) ) );
 		
	}
	
	printf("\n");
	
 	
 }
    
    return 0;
}