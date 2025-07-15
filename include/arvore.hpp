#ifndef ARVORE_HPP
#define ARVORE_HPP

#include "voo.hpp"

struct Nodo {
    Voo voo;
    Nodo* esquerda;
    Nodo* direita;
};

// Declaração da função de comparação
int comparar_voos(const Voo& voo1, const Voo& voo2, const char* trigrama);

// Função para inserir na árvore binária
void inserir(Nodo*& raiz, const Voo& voo, const char* trigrama);
void em_ordem(Nodo* raiz, int& contador, int num_resultados); // Função de impressão da árvore em ordem
void desalocar_arvore(Nodo* raiz); // Função para desalocar a árvore

#endif
