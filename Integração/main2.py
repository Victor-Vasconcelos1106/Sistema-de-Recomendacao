import Recomendacao as R
from ListaCompras import ListaCompras

def ClienteMaisSimilar(indice, numero_clientes, matriz, codigos):
    if (indice == 0):
        idx = 1
    else:
        idx = 0
    
    distancia_inicial = matriz[indice * numero_clientes + idx]

    for i in range(numero_clientes):
        if indice == i:
            continue

        distancia_atual = matriz[indice * numero_clientes + i]

        if distancia_atual < distancia_inicial:
            distancia_inicial = distancia_atual
            idx = i
    
    print(f"Cliente digitado: {codigos[indice]}: ")
    print(f"Mais similar [{idx}] [{codigos[idx]}]")

def main():
    dados = ListaCompras()
    matriz = R.Similaridade(dados)
    
    numero_clientes = len(dados[3])

    print(f"O indice de clientes é {numero_clientes - 1} ")
    cliente_1 = int(input("Digite o indice do primeiro cliente: "))
    cliente_2 = int(input("Digite o indice do segundo cliente: "))

    ClienteMaisSimilar(cliente_1, numero_clientes, matriz, dados[1])
    ClienteMaisSimilar(cliente_2, numero_clientes, matriz, dados[1])

if __name__ == "__main__":
    main()
