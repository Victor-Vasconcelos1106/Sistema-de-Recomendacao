#include <stdio.h>
#include "ListaCompras.h"
#include <stdlib.h>
#include "Similaridade.h"

float* Similaridade(){
	
	Dados dados;
	ListaCompras(&dados);
	
	int *Matriz_compras = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_product.size() ) );
	int *Matriz_compras_transposta = (int*)malloc( sizeof(int) * ( dados.index_product.size() ) * ( dados.index_client.size() ) );
	int *Matriz_intersecao = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_client.size() ) );
	float *Matriz_similaridade = (float*)malloc(sizeof(float) * dados.index_client.size() * dados.index_client.size());
	
	int i,j,k;
	
	for(i = 0; i < dados.index_client.size(); i++)
	{
		
		for( j = 0; j < dados.index_product.size(); j++)
		{

			*(Matriz_compras + (i * dados.index_product.size() + j)) = 0;  

		}
		
		for(int product_id : dados.compras_cliente[i])
		{

			*(Matriz_compras + (i * dados.index_product.size() + product_id)) = 1;

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
				*(Matriz_intersecao + (k * dados.index_client.size() + i)) = soma_do_produto;
				
				soma_do_produto = 0;
		
		}
		
	}

	float jacard;

	for(i = 0; i < dados.index_client.size(); i++)
	{
		
		for (j = 0 ; j < dados.index_client.size();j++)
		{
				jacard = ( *( Matriz_intersecao + i * dados.index_client.size() + j ) );
				jacard /= dados.compras_cliente[i].size();
				jacard = 1 - jacard;

				*( Matriz_similaridade + ( i * dados.index_client.size() + j ) ) = jacard;
		
		}
		
	}


	
	free(Matriz_compras);
	free(Matriz_compras_transposta);
	free(Matriz_intersecao);

	return Matriz_similaridade;

}

float* Similaridade_Otimizada(){
	
	Dados dados;
	ListaCompras(&dados);
	
	int *Matriz_compras = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_product.size() ) );
	int *Matriz_compras_transposta = (int*)malloc( sizeof(int) * ( dados.index_product.size() ) * ( dados.index_client.size() ) );
	int *Matriz_intersecao = (int*)malloc( sizeof(int) * ( dados.index_client.size() ) * ( dados.index_client.size() ) );
	float *Matriz_similaridade = (float*)malloc(sizeof(float) * dados.index_client.size() * dados.index_client.size());
	
	int i,j,k;
	
	for(i = 0; i < dados.index_client.size(); i++)
	{
		
		for( j = 0; j < dados.index_product.size(); j++)
		{

			*(Matriz_compras + (i * dados.index_product.size() + j)) = 0;  

		}
		
		for(int product_id : dados.compras_cliente[i])
		{

			*(Matriz_compras + (i * dados.index_product.size() + product_id)) = 1;

		}
	
	
	} 
	
	

	for(i = 0; i < dados.index_client.size(); i++)
	{
		
		for( j = 0; j < dados.index_product.size(); j++)
		{
			
				*(Matriz_compras_transposta + j * dados.index_client.size() + i) = *(Matriz_compras + (i * dados.index_product.size() + j));;
		
		}
		
	}
	
	int soma_do_produto = 0;

	for(i = 0; i < dados.index_client.size(); i++)
	{
		for (k = i ; k < dados.index_client.size();k++)
		{
		
				for( j = 0; j < dados.index_product.size(); j++)
				{
			
					soma_do_produto += *(Matriz_compras + (i * dados.index_product.size() + j)) * *(Matriz_compras_transposta + (k * dados.index_product.size() + j));
		
				}
				
				*(Matriz_intersecao + (i * dados.index_client.size() + k)) = soma_do_produto;
				*(Matriz_intersecao + (i * dados.index_client.size() + k)) = soma_do_produto;
				soma_do_produto = 0;
		
		}
		
	}

	float jacard;

	for(i = 0; i < dados.index_client.size(); i++)
	{
		
		for (j = 0 ; j < dados.index_client.size();j++)
		{
				jacard = ( *( Matriz_intersecao + i * dados.index_client.size() + j ) );
				jacard /= dados.compras_cliente[i].size();
				jacard = 1 - jacard;

				*( Matriz_similaridade + ( i * dados.index_client.size() + j ) ) = jacard;
		
		}
		
	}


	
	free(Matriz_compras);
	free(Matriz_compras_transposta);
	free(Matriz_intersecao);

	return Matriz_similaridade;

}

