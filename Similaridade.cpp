#include <stdio.h>
#include "ListaCompras.h"
#include <stdlib.h>

int main(){
    Dados dados = ListaCompras();
 
 int *Matriz_compras = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_product.size() ) );
 int *Matriz_compras_transposta = (int*)malloc( sizeof(int) * ( dados.index_product.size() ) * ( dados.index_client.size() ) );
 int *Matriz_intersecao = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_client.size() ) );
 int *total_produtos = (int*)malloc(sizeof(int) * dados.index_client.size());
 float *Matriz_jaccard = (float*)malloc(sizeof(float) * dados.index_client.size() * dados.index_client.size());
 int i,j,k;
 
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
            
            *(Matriz_compras + (i * dados.index_product.size() + j)) = 0;
            
       }
       
       for( k = 0; k < dados.compras_cliente[i].size(); k++)
       {
           
            *(Matriz_compras + (i * dados.index_product.size() + dados.compras_cliente[i][k])) = 1;  
       
       }
 
 }
 	printf("teste matriz de compra\n\n");
 	
 	for(i = 0; i < dados.index_client.size(); i++)
 	{
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
       	
       		printf("%i", *(Matriz_compras + (i * dados.index_product.size() + j)));
       	
	   }
	   
	   printf("\n");
	   
	}
       
 for(i = 0; i < dados.index_client.size(); i++)
 {
       
       for( j = 0; j < dados.index_product.size(); j++)
       {
          
            *(Matriz_compras_transposta + (j * dados.index_client.size() + i)) = *(Matriz_compras + (i * dados.index_product.size() + j));;
       
       }
       
 }
 
 printf("\n\n\n");
 printf("teste da matriz de compras transposta\n\n");
 
 for(i = 0; i < dados.index_product.size(); i++)
 {
       
       for( j = 0; j < dados.index_client.size(); j++)
       {
          
            printf("%i", *(Matriz_compras_transposta + (i * dados.index_client.size() + j)));;
       
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
       		
       		*(Matriz_intersecao + (i * dados.index_client.size() + k)) = soma_do_produto;;
       		soma_do_produto = 0;
       
   	   }
       
 }
 
 printf("\n\n");
 printf("teste matriz de intersecao\n\n");
 
 for(i = 0 ; i < dados.index_client.size(); i++ )
 {
 	
 	for(j = 0 ; j < dados.index_client.size(); j++ )
 	{
 		
        printf("%i", *(Matriz_intersecao + (i * dados.index_client.size() + j)));;
 		
	}
	
	printf("\n");
 }

for(i = 0; i < dados.index_client.size(); i++)
{
    total_produtos[i] = 0;

    for(j = 0; j < dados.index_product.size(); j++)
    {
        total_produtos[i] += *(Matriz_compras + (i * dados.index_product.size() + j));
    }
}

for(i = 0; i < dados.index_client.size(); i++)
{
    for(k = 0; k < dados.index_client.size(); k++)
    {
        int intersecao = *(Matriz_intersecao + (i * dados.index_client.size() + k));
        
        int uniao = total_produtos[i] + total_produtos[k] - intersecao;

        if(uniao != 0)
        {
            *(Matriz_jaccard + (i * dados.index_client.size() + k)) =
                (float) intersecao / uniao;
        }
        else
        {
            *(Matriz_jaccard + (i * dados.index_client.size() + k)) = 0;
        }
    }
}

printf("\n\nMatriz de Jaccard:\n\n");

for(i = 0; i < dados.index_client.size(); i++)
{
    for(k = 0; k < dados.index_client.size(); k++)
    {
        printf("%.2f ", *(Matriz_jaccard + (i * dados.index_client.size() + k)));
    }
    printf("\n");
}

free(Matriz_compras);
free(Matriz_compras_transposta);
free(Matriz_intersecao);
free(Matriz_jaccard);
free(total_produtos);


    return 0;
}