import ListaCompras

def main():
    clientes = []

    dados = ListaCompras.ListaCompras()
    
    for i in range(3):
        clientes.append(input("Codigo do cliente: "))
    
    for cliente in clientes:
        idx = -1

        for i in range(len(dados[1])):
            if dados[1][i] == cliente:
                idx = i
                break
        if idx == -1:
            print(f"Cliente {cliente} não encontrado!")
            continue
        print(f"Cliente {cliente} comprou: ",end="")

        for id in dados[0][idx][:3]:
            print(dados[2][id],end=" / ")
        print()    

if __name__ == "__main__":
    main()


