import ListaCompras

def main():
    clientes = []

    dados = ListaCompras.ListaCompras()
    
    for i in range(3):
        clientes.append(input("Codigo do cliente: "))
    
    for cliente in clientes:
        idx = -1

        for i in range(len(dados["cod_cliente"])):
            if dados["cod_cliente"][i] == cliente:
                idx = i
                break
        if idx == -1:
            print(f"Cliente {cliente} não encontrado!")
            continue
        print(f"Cliente {cliente} comprou: ",end="")

        for id in dados["compra_clientes"][idx][:3]:
            print(dados["nome_produto"][id],end=" / ")
        print()    

if __name__ == "__main__":
    main()


