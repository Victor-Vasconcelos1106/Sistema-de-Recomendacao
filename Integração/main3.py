import Recomendacao as R
from ListaCompras import ListaCompras

def main():
    dados = ListaCompras()
    matriz = R.Similaridade(dados)

    for i in range(3):
        cliente = input("Digite o codigo do cliente: ")
        print(R.Recomendar(dados[3][cliente], dados, matriz, 3))


if __name__ == "__main__":
    main()
    
    
