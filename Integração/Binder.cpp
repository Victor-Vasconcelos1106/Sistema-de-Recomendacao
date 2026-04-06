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

std::tuple<std::vector<std::list<int>>, std::vector<std::string>, std::vector<std::string>,
           std::map<std::string, int>, std::map<std::string, int>>
ListaCompras()
{

    std::vector<std::list<int>> compras_cliente;
    std::vector<std::string> client_codes;
    std::vector<std::string> product_names;
    std::map<std::string, int> index_client;
    std::map<std::string, int> index_product;

    FILE *csv;
    csv = fopen("dados_venda_cluster_0.csv", "r");
    if (csv == NULL)
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

    while (fscanf(csv, "%29[^,],%29[^,],%29[^,],%58[^\n]\n", data_buf, client_buf, product_buf, name_buf) == 4)
    {
        if (contador == 0)
        {

            contador++;
            continue;
        }

        if (index_client.count(client_buf) == 0)
        {
            index_client[client_buf] = next_client++;
            client_codes.push_back(client_buf);
        }

        if (index_product.count(product_buf) == 0)
        {
            index_product[product_buf] = next_product++;
            product_names.push_back(name_buf);
        }

        int client_id = index_client[client_buf];
        int product_id = index_product[product_buf];

        if (client_id >= compras_cliente.size())
        {

            compras_cliente.resize(client_id + 1);
        }

        compras_cliente[client_id].push_back(product_id);
    }

    fclose(csv);

    return {compras_cliente, client_codes, product_names, index_client, index_product};
}

std::vector<float> Similaridade(

    std::tuple<std::vector<std::list<int>>, std::vector<std::string>, std::vector<std::string>,
    std::map<std::string, int>, std::map<std::string, int>> dados

                                )
{


    enum index_tuple
    {

        compras_cliente,
        client_codes,
        product_names,
        index_client,
        index_product

    };

    int *Matriz_compras = (int *)malloc(sizeof(int) * ( (std::get<index_client>(dados)).size() ) * ((std::get<index_product>(dados)).size()));
    int *Matriz_compras_transposta = (int *)malloc(sizeof(int) * ((std::get<index_product>(dados)).size()) * ( (std::get<index_client>(dados)).size()));
    int *Matriz_intersecao = (int *)malloc(sizeof(int) * ( (std::get<index_client>(dados)).size()) * ( (std::get<index_client>(dados)).size()));
    float *Matriz_similaridade = (float *)malloc(sizeof(float) *  (std::get<index_client>(dados)).size() *  (std::get<index_client>(dados)).size());

    int i, j, k;
    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {

        for (j = 0; j < (std::get<index_product>(dados)).size(); j++)
        {

            *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + j)) = 0;
        }

        for (int product_id : (std::get<compras_cliente>(dados))[i])
        {

            *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + product_id)) = 1;
        }
    }

    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {

        for (j = 0; j < (std::get<index_product>(dados)).size(); j++)
        {

            *(Matriz_compras_transposta + j *  (std::get<index_client>(dados)).size() + i) = *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + j));
            ;
        }
    }

    int soma_do_produto = 0;

    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {
        for (k = 0; k <  (std::get<index_client>(dados)).size(); k++)
        {

            for (j = 0; j < (std::get<index_product>(dados)).size(); j++)
            {

                soma_do_produto += *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + j)) * *(Matriz_compras_transposta + (j *  (std::get<index_client>(dados)).size() + k));
            }

            *(Matriz_intersecao + (i *  (std::get<index_client>(dados)).size() + k)) = soma_do_produto;
            soma_do_produto = 0;
            //*( Matriz_similaridade + (i *  (std::get<index_client>(dados)).size() + k) ) = soma_do_produto;
        }
    }

    float jacard;
    std::vector<float> Matriz_similaridade_L;

    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {

        for (j = 0; j <  (std::get<index_client>(dados)).size(); j++)
        {

            jacard = (*(Matriz_intersecao + i *  (std::get<index_client>(dados)).size() + j));
            jacard /= (std::get<compras_cliente>(dados))[i].size();
            jacard = 1 - jacard;

            *(Matriz_similaridade + (i *  (std::get<index_client>(dados)).size() + j)) = jacard;
            Matriz_similaridade_L.push_back(jacard);
        }
    }

    free(Matriz_compras);
    free(Matriz_compras_transposta);
    free(Matriz_intersecao);

    return Matriz_similaridade_L;

}

std::vector<float> Similaridade(

    std::tuple<std::vector<std::list<int>>, std::vector<std::string>, std::vector<std::string>,
    std::map<std::string, int>, std::map<std::string, int>> dados

                                )
{


    enum index_tuple
    {

        compras_cliente,
        client_codes,
        product_names,
        index_client,
        index_product

    };

    int *Matriz_compras = (int *)malloc(sizeof(int) * ( (std::get<index_client>(dados)).size() ) * ((std::get<index_product>(dados)).size()));
    int *Matriz_compras_transposta = (int *)malloc(sizeof(int) * ((std::get<index_product>(dados)).size()) * ( (std::get<index_client>(dados)).size()));
    int *Matriz_intersecao = (int *)malloc(sizeof(int) * ( (std::get<index_client>(dados)).size()) * ( (std::get<index_client>(dados)).size()));
    float *Matriz_similaridade = (float *)malloc(sizeof(float) *  (std::get<index_client>(dados)).size() *  (std::get<index_client>(dados)).size());

    int i, j, k;
    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {

        for (j = 0; j < (std::get<index_product>(dados)).size(); j++)
        {

            *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + j)) = 0;
        }

        for (int product_id : (std::get<compras_cliente>(dados))[i])
        {

            *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + product_id)) = 1;
        }
    }

    /*
    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {

        for (j = 0; j < (std::get<index_product>(dados)).size(); j++)
        {

            *(Matriz_compras_transposta + j *  (std::get<index_client>(dados)).size() + i) = *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + j));
            ;
        }
    }
    */
   
    int soma_do_produto = 0;

    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {
        for (k = 0; k <  (std::get<index_client>(dados)).size(); k++)
        {

            for (j = 0; j < (std::get<index_product>(dados)).size(); j++)
            {

                soma_do_produto += *(Matriz_compras + (i * (std::get<index_product>(dados)).size() + j)) * *(Matriz_compras_transposta + (j *  (std::get<index_client>(dados)).size() + k));
            }

            *(Matriz_intersecao + (i *  (std::get<index_client>(dados)).size() + k)) = soma_do_produto;
            soma_do_produto = 0;
            //*( Matriz_similaridade + (i *  (std::get<index_client>(dados)).size() + k) ) = soma_do_produto;
        }
    }

    float jacard;
    std::vector<float> Matriz_similaridade_L;

    for (i = 0; i <  (std::get<index_client>(dados)).size(); i++)
    {

        for (j = 0; j <  (std::get<index_client>(dados)).size(); j++)
        {

            jacard = (*(Matriz_intersecao + i *  (std::get<index_client>(dados)).size() + j));
            jacard /= (std::get<compras_cliente>(dados))[i].size();
            jacard = 1 - jacard;

            *(Matriz_similaridade + (i *  (std::get<index_client>(dados)).size() + j)) = jacard;
            Matriz_similaridade_L.push_back(jacard);
        }
    }

    free(Matriz_compras);
    free(Matriz_compras_transposta);
    free(Matriz_intersecao);

    return Matriz_similaridade_L;

}



bool compararProdutos( std::tuple<int, float> a, std::tuple<int, float> b ) 
{
    bool comparacao = std::get<1>(a) < std::get<1>(b);                    
    return comparacao; 
    
}

std::vector<std::string> recomendacao(

    int cliente_c, 
    std::tuple<std::vector<std::list<int>>, std::vector<std::string>, std::vector<std::string>,
    std::map<std::string, int>, std::map<std::string, int>> dados,
    std::vector<float> Matriz_similaridade_L,
    int k

                 )
{
    
    enum index_tuple
    {

        compras_cliente,
        client_codes,
        product_names,
        index_client,
        index_product

    };

    int numero_clientes = std::get<index_client>(dados).size();
    int numero_produtos = std::get<index_product>(dados).size();
    //cout << "numero clientes : "<< numero_clientes << endl;
    std::vector<std::list<int> > compras = std::get<compras_cliente>(dados);

    //float *matriz = matriz;

    std::vector<int> Clientes_similares;
    std::vector<std::tuple<int, float>> Ranking;

   for (int i = 0; i < numero_clientes - 1 ; i++) 
   {

 
        if (i == cliente_c)
        {
                 
            //cout << "indice pulado : " << i << endl;  
            continue;
            
        } 
        
        float dist_atual = Matriz_similaridade_L[cliente_c * numero_clientes + i];
        
        //cout << "indice atual: " << i << endl;
        printf("\tdistancia atual: %.9f", dist_atual);
        printf("\n");
        
        if ( ( dist_atual < 1.0 ) ) 
        {
                       
            Clientes_similares.push_back(i);
            
        } 
    }
    
    //cout << "end of bullshit" << endl;
    //cout << "Num Clientes Similares" << Clientes_similares.size() << endl;
    
    //if(Clientes_similares.empty()){//cout << "fudeu" << endl;}
    
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
                 
        std::tuple<int, float> i = {p, 1.0};
        Ranking.push_back({i});
        
    }

    for (int s : Clientes_similares) 
    {
        
        //cout << "s = " << s << endl;
      
        
        //AGR SIM EU ACHEI O ERRO, O PROBLEMA OCORRE AQUI
        //QUANDO S = 855 O PROGRAMA DESISTE DE RODAR
        //MINHA TEORIA PERMANECE SENDO ERRO DE MEMORIA MEM�RIA
        // N�O VOU MUDAR O NOME DO ERRO APENAS PORQUE 9060SM01 > 855 
        
        float similaridade_cs = Matriz_similaridade_L[cliente_c * numero_clientes + s];

        for (int produto : std::get<compras_cliente>(dados)[s]) {

            auto it = find(std::get<compras_cliente>(dados)[cliente_c].begin() , std::get<compras_cliente>(dados)[cliente_c].end(), produto );

            if(it == std::get<compras_cliente>(dados)[cliente_c].end())
            {

                std::get<1>(Ranking[produto]) *= similaridade_cs;

            }

        }
    }
    
    //cout << "fim rankeamento" << endl;

    sort(Ranking.begin(), Ranking.end(), compararProdutos);

    std::vector<std::string> recomendacoes;

    for(int i = 0; ( (i < k) && (k < Ranking.size() ) ); i++)
    {
                
        recomendacoes.push_back( (std::get<product_names>(dados))[ std::get<0>(Ranking[i]) ]);
        
    }

    return recomendacoes;

    
}


PYBIND11_MODULE(Recomendacao, R)
{

    R.doc() = "Integração do sistema de recomendação com python";

    R.def("ListaCompras", &ListaCompras);

    R.def("Similaridade", &Similaridade);

    R.def("Recomendar", &recomendacao);

}
