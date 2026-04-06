import csv

def ListaCompras():
    cod_cliente = []
    nome_produto = []
    index_cliente = {}
    index_produto = {}
    compra_clientes = []

    next_client = 0
    next_product = 0

    with open('dados_venda_cluster_0.csv', mode='r') as arquivo:
        leitor = csv.reader(arquivo, delimiter=',')

    
        linhas = 0
        for linha in leitor:
            if linhas == 0:
                linhas += 1
                continue

            data_buffer, cliente_buffer, produto_buffer, nome_buffer = linha

            if cliente_buffer not in index_cliente:
                index_cliente[cliente_buffer] = next_client
                cod_cliente.append(cliente_buffer)
                compra_clientes.append([])
                next_client += 1
            
            if produto_buffer not in index_produto:
                index_produto[produto_buffer] = next_product
                nome_produto.append(nome_buffer)
                next_product += 1
            
            cliente_id = index_cliente[cliente_buffer]
            produto_id = index_produto[produto_buffer]

            compra_clientes[cliente_id].append(produto_id)
   
    return {
        "cod_cliente": cod_cliente,
        "nome_produto": nome_produto,
        "compra_clientes": compra_clientes,
        "index_produto": index_produto,
        "index_cliente": index_cliente
    }



