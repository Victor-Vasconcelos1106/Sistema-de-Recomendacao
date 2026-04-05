#include <iostream>
#include "Recomendacao.h"

bool compararProdutos(const Produto& a, const Produto& b) 
{
                            
    return a.valor_ranking < b.valor_ranking; 
    
}

void Recomendacao(int cliente_c, Dados* ptr_dados, float* matriz, int k, vector<string> *nomes)
{
    //Dados *ptr_dados = &dados;
    int numero_clientes = ptr_dados->index_client.size();
    int numero_produtos = ptr_dados->index_product.size();
    cout << "numero clientes : "<< numero_clientes << endl;
    vector<list<int> > compras = ptr_dados->compras_cliente;

    //float *matriz = matriz;

    vector<int> Clientes_similares;
    vector<Produto> Ranking;

   for (int i = 0; i < numero_clientes - 1/*ESSE 1 � TAPA BURACO(ERRO 9060SM01)*/ ; i++) 
   {

 
        if (i == cliente_c)
        {
                 
            cout << "indice pulado : " << i << endl;  
            continue;
            
        } 
        
        float dist_atual = *(matriz + (cliente_c * numero_clientes + i));
        
        cout << "indice atual: " << i << endl;
        printf("\tdistancia atual: %.9f", dist_atual);
        printf("\n");
        
        if ( ( dist_atual < 1.0 ) ) 
        {
                       
            Clientes_similares.push_back(i);
            
        } 
    }
    
    cout << "end of bullshit" << endl;
    cout << "Num Clientes Similares" << Clientes_similares.size() << endl;
    
    if(Clientes_similares.empty()){cout << "fudeu" << endl;}
    
    // S� SEUS SABE O PORQU�, MAS O ALGORITMO PEIDA NA FAROFA PERANTE O
    // C�DIGO 9060SM01, O CODIGO ACIMA EXECUTA DE FORMA SUPOSTAMENTE NORMAL
    // ENTRETANTO OCORRE ALGUM ERRO NA LINHAS A SEGUIR
    // DESCOBRI(ACHO)
    // ANTES NUMERO_CLIENTES IA AT� 855, E ISSO POSSIVELMENTE GERAVA
    // SEGMENTATION FAULT OU ALGUM ERRO DE MEMORIA DO TIPO
    // AO MENOS � A MINHA TEORIA
    // S� EXISTE UMA CERTEZA, POR ALGUM MOTIVO O INDEX 855 GERAVA PROBLEMAS
    // ERRO 9060SM01 ABAIXO:
            
    for (int p = 0; p < numero_produtos; p++) 
    {
                 
        Produto i = {p,1.0};
        Ranking.push_back({i});
        
    }

    for (int s : Clientes_similares) 
    {
        
        cout << "s = " << s << endl;
      
        
        //AGR SIM EU ACHEI O ERRO, O PROBLEMA OCORRE AQUI
        //QUANDO S = 855 O PROGRAMA DESISTE DE RODAR
        //MINHA TEORIA PERMANECE SENDO ERRO DE MEMORIA MEM�RIA
        // N�O VOU MUDAR O NOME DO ERRO APENAS PORQUE 9060SM01 > 855 
        
        float similaridade_cs = matriz[cliente_c * numero_clientes + s];

        for (int produto : ptr_dados->compras_cliente[s]) {

            auto it = find(ptr_dados->compras_cliente[cliente_c].begin() , ptr_dados->compras_cliente[cliente_c].end(), produto );

            if(it == ptr_dados->compras_cliente[cliente_c].end())
            {

                Ranking[produto].valor_ranking *= similaridade_cs;

            }

        }
    }
    
    cout << "fim rankeamento" << endl;

    sort(Ranking.begin(), Ranking.end(), compararProdutos);

    vector<string> *ids = nomes;

    for(int i = 0; ( (i < k) && (k < Ranking.size() ) ); i++)
    {
                
        (*ids).push_back(ptr_dados->product_names[Ranking[i].id_produto]);
        
    }

    
}
