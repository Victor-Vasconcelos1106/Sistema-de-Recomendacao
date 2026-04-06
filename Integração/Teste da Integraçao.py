import Recomendacao as R

a = R.ListaCompras()
b = R.Similaridade_Otimizada(a)
c = R.Recomendar(a[3]['9O6OSM01'],a,b,5)

print(c)



