#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

struct Matriz_s
{
               
    float *matriz;
    
};

Matriz_s* Similaridade(Matriz_s *ptr);
Matriz_s* Similaridade_Otimizada(Matriz_s *ptr);

#endif
