#include <stdio.h>
#include "ListaCompras.h"
#include <stdlib.h>
#include "Similaridade.h"

Matriz_s* Similaridade(Matriz_s *ptr){
    Dados dados;
	ListaCompras(&dados);
 
 int *Matriz_compras = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_product.size() ) );
 int *Matriz_compras_transposta = (int*)malloc( sizeof(int) * ( dados.index_product.size() ) * ( dados.index_client.size() ) );
 int *Matriz_intersecao = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_client.size() ) );
 float *Matriz_similaridade = (float*)malloc(sizeof(float) * dados.index_client.size() * dados.index_client.size());
 
 int i,j,k;
 
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++){
        *(Matriz_compras + (i * dados.index_product.size() + j)) = 0;  
       }
       
       for(int product_id : dados.compras_cliente[i]){
		*(Matriz_compras + (i * dados.index_product.size() + product_id)) = 1;
	   }
{
    
}
 
 }    
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
          
            *(Matriz_compras_transposta + (j * dados.index_client.size() + i)) = *(Matriz_compras + (i * dados.index_product.size() + j));;
       
       }
       
 }
 
int soma_do_produto = 0;

 for(i = 0; i < dados.index_client.size(); i++)
 {
       for (k = 0 ; k < dados.index_client.size();k++)
	   {
	   
       		for( j = 0; j < dados.index_product.size(); j++)
       		{
          
            	soma_do_produto += *(Matriz_compras + (i * dados.index_product.size() + j)) * *(Matriz_compras_transposta + (j * dados.index_client.size() + k));
       
       		}
       		
       		*(Matriz_intersecao + (i * dados.index_client.size() + k)) = soma_do_produto;
            *( Matriz_similaridade + (i * dados.index_client.size() + k) ) = soma_do_produto;
       		soma_do_produto = 0;
       
   	   }
       
 }

for(i = 0; i < dados.index_client.size(); i++)
 {
 	
       for (j = 0 ; j < dados.index_client.size();j++)
	   {
	   // atualizei o acesso, estava errado antes
	   		*( Matriz_similaridade + ( i * dados.index_client.size() + j ) ) = 1 - ( *( Matriz_similaridade + ( i * dados.index_client.size() + j ) ) ) / ( dados.compras_cliente[i].size() );
	   
	   }
	   
 }

ptr->matriz = Matriz_similaridade;
 
free(Matriz_compras);
free(Matriz_compras_transposta);
free(Matriz_intersecao);

return ptr;
}

Matriz_s* Similaridade_Otimizada(Matriz_s *ptr){
    Dados dados;
	ListaCompras(&dados);
 
 int *Matriz_compras = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_product.size() ) );
 int *Matriz_intersecao = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_client.size() ) );
 float *Matriz_similaridade = (float*)malloc(sizeof(float) * dados.index_client.size() * dados.index_client.size());
 
 int i,j,k;
 
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++){
        *(Matriz_compras + (i * dados.index_product.size() + j)) = 0;  
       }
       
       for(int product_id : dados.compras_cliente[i]){
		*(Matriz_compras + (i * dados.index_product.size() + product_id)) = 1;
	   }
{
    
}
 
 }    
int soma_do_produto = 0;

 for(i = 0; i < dados.index_client.size(); i++)
 {
       for (j = 0 ; j < dados.index_client.size();j++)
	   {
	   
       		for( k = 0; k < dados.index_product.size(); k++)
       		{
          
            	soma_do_produto += *(Matriz_compras + (i * dados.index_product.size() + k)) * *(Matriz_compras + (j * dados.index_client.size() + k));
       
       		}
// possivelemente usa j ao invés de k para definir a coluna  preenchida
// checar durante a execução se as matrizes geradas são iguais
		   
       		*(Matriz_intersecao + (i * dados.index_client.size() + j)) = soma_do_produto;
            *( Matriz_similaridade + (i * dados.index_client.size() + j) ) = soma_do_produto;
       		soma_do_produto = 0;
       
   	   }
       
 }

for(i = 0; i < dados.index_client.size(); i++)
 {
 	
       for (j = 0 ; j < dados.index_client.size();j++)
	   {
	   // estava acessando a memória errado 
		// atualizei o acesso da matriz
	   		*( Matriz_similaridade + ( i * dados.index_client.size() + j ) ) = 1 - (*( Matriz_similaridade + ( i * dados.index_client.size() + j ) )) / ( dados.compras_cliente[i].size() );
	   
	   }
	   
 }

ptr->matriz = Matriz_similaridade;
 
free(Matriz_compras);
free(Matriz_intersecao);

return ptr;

}
