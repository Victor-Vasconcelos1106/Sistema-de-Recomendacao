import time
import Recomendacao as R
from ListaCompras import ListaCompras

def main():
    dados = ListaCompras()
    inicio_matriz = time.time()
    R.Similaridade(dados)
    fim_matriz = time.time()
    print(f"Tempo de execução: {fim_matriz - inicio_matriz}")

    inicio_matriz_otimizada = time.time()
    R.Similaridade_Otimizada(dados)
    fim_matriz_otimizada = time.time()
    print(f"Tempo da matriz otimizada: {fim_matriz_otimizada - inicio_matriz_otimizada}")

if __name__ == "__main__":
    main()