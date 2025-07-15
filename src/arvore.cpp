#include "arvore.hpp"
#include "filtro.hpp"
#include <iostream>

// Função para comparar dois voos de acordo com o trigrama
int comparar_voos(const Voo& voo1, const Voo& voo2, const char* trigrama) {
    for (int i = 0; trigrama[i] != '\0'; ++i) {
        if (trigrama[i] == 'p') {
            if (voo1.preco < voo2.preco) return -1;
            if (voo1.preco > voo2.preco) return 1;
        }
        else if (trigrama[i] == 's') {
            if (voo1.num_paradas < voo2.num_paradas) return -1;
            if (voo1.num_paradas > voo2.num_paradas) return 1;
        }
        else if (trigrama[i] == 'd') {
            if (voo1.duracao < voo2.duracao) return -1;
            if (voo1.duracao > voo2.duracao) return 1;
        }
    }
    return 0;  // Se são iguais em todos os critérios
}

// Função para inserir o voo na árvore de forma ordenada
void inserir(Nodo*& raiz, const Voo& voo, const char* trigrama) {
    if (raiz == nullptr) {
        raiz = new Nodo{voo, nullptr, nullptr};
    } else {
        // Comparação ajustada conforme o trigrama
        if (comparar_voos(voo, raiz->voo, trigrama) < 0) {
            inserir(raiz->esquerda, voo, trigrama);
        } else {
            inserir(raiz->direita, voo, trigrama);
        }
    }
}


// Função para imprimir os voos em ordem, respeitando o número de resultados do filtro
void em_ordem(Nodo* raiz, int& contador, int num_resultados) {
    if (raiz == nullptr) {
        return;
    }
    // Recursão para esquerda (ordem crescente)
    em_ordem(raiz->esquerda, contador, num_resultados);
    // Se já imprimimos o número de resultados que o filtro deseja, retorna
    if (contador >= num_resultados) {
        return;
    }
    // Imprime o voo usando a função mostrar_voo
    raiz->voo.mostrar_voo();  // Usando o método que já está formatado para mostrar o voo
    // Incrementa o contador
    contador++;
    // Recursão para direita
    em_ordem(raiz->direita, contador, num_resultados);
}



// Função para desalocar a memória da árvore
void desalocar_arvore(Nodo* raiz) {
    if (raiz == nullptr) return;
    desalocar_arvore(raiz->esquerda);
    desalocar_arvore(raiz->direita);
    delete raiz;  // Deleta o nó e libera a memória
}
