#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "voo.hpp"
#include "arvore.hpp"
#include "filtro.hpp"

#define MAX_LINHAS 1000

// Função para ler o número de filtros do arquivo
void calcula_filtros(FILE* arquivo, int* num_filtros) {
    if (fscanf(arquivo, "%d", num_filtros) != 1) {
        std::cerr << "Erro ao ler o número de filtros.\n";
    }
}

// Função para ler o número total de voos do arquivo
void calcula_voos(FILE* arquivo, int* total_voos) {
    if (fscanf(arquivo, "%d", total_voos) != 1) {
        printf("Erro ao ler o número de voos.\n");
        return;
    }
}

// Função que converte uma string de data/hora para o tipo time_point
std::chrono::system_clock::time_point converte_time(const char data[20]) {
    int ano, mes, dia, hora, minuto, segundo;
    if (sscanf(data, "%4d-%2d-%2dT%2d:%2d:%2d", &ano, &mes, &dia, &hora, &minuto, &segundo) != 6) {
        std::cerr << "Erro ao converter tempo para time_point!" << std::endl;
    }

    std::tm tm = {};
    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;
    tm.tm_mday = dia;
    tm.tm_hour = hora;
    tm.tm_min = minuto;
    tm.tm_sec = segundo;
    tm.tm_isdst = -1;

    std::time_t t = mktime(&tm);
    return std::chrono::system_clock::from_time_t(t);
}

// Função para alocar e preencher a lista de voos a partir de um arquivo
Voo* aloca_voos(FILE* arquivo, int total_voos) {
    Voo* voos = (Voo*)malloc(sizeof(Voo) * total_voos);
    if (voos == nullptr) {
        std::cerr << "Erro ao alocar memória para os voos." << std::endl;
        exit(1);
    }

    for (int i = 0; i < total_voos; i++) {
        char origem[4], destino[4];
        char partida_str[20], chegada_str[20];
        if (fscanf(arquivo, "%3s %3s %f %d %19s %19s %d", origem, destino, &voos[i].preco,
                   &voos[i].assentos_disponiveis, partida_str, chegada_str, &voos[i].num_paradas) == 7) {
            
            std::chrono::system_clock::time_point partida = converte_time(partida_str);
            std::chrono::system_clock::time_point chegada = converte_time(chegada_str);
            
            new (&voos[i]) Voo(origem, destino, voos[i].preco, voos[i].assentos_disponiveis, partida, chegada, voos[i].num_paradas);
        } else {
            std::cerr << "Erro ao ler os dados do voo " << i + 1 << "." << std::endl;
        }
    }

    return voos;
}

// Função para ler os filtros do arquivo
Filtro* le_filtros(FILE* arquivo, int num_filtros) {
    Filtro* filtros = new Filtro[num_filtros];
    
    for (int i = 0; i < num_filtros; ++i) {
        if (fscanf(arquivo, "%d %3s %[^\n]", &filtros[i].num_resultados, filtros[i].tipo_filtro, filtros[i].condicao_completa) != 3) {
            std::cerr << "Erro ao ler a condição " << i + 1 << std::endl;
        }
    }
    return filtros;
}

int main() {
    // Abrir arquivo com os dados
    const char* arquivo_nome = "input_1.txt";
    FILE* arquivo = fopen(arquivo_nome, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Ler o número total de voos e alocar memória para os voos
    int total_voos = 0;
    calcula_voos(arquivo, &total_voos);
    Voo* voos = aloca_voos(arquivo, total_voos);
    
    // Ler o número de filtros e alocar memória para os filtros
    int num_filtros = 0; 
    calcula_filtros(arquivo, &num_filtros);
    Filtro* filtros = le_filtros(arquivo, num_filtros);

    // Inicializar as raízes das árvores de índice
    Nodo* raiz_org = nullptr;
    Nodo* raiz_dst = nullptr;
    Nodo* raiz_preco = nullptr;
    Nodo* raiz_assentos = nullptr;
    Nodo* raiz_partida = nullptr;
    Nodo* raiz_chegada = nullptr;
    Nodo* raiz_paradas = nullptr;
    Nodo* raiz_duracao = nullptr;

    // Construção das 8 árvores de índice, uma para cada critério
    for (int i = 0; i < total_voos; ++i) {
        // Organiza as árvores para cada critério
        inserir(raiz_org, voos[i], "org");
        inserir(raiz_dst, voos[i], "dst");
        inserir(raiz_preco, voos[i], "preco");
        inserir(raiz_assentos, voos[i], "assentos");
        inserir(raiz_partida, voos[i], "partida");
        inserir(raiz_chegada, voos[i], "chegada");
        inserir(raiz_paradas, voos[i], "paradas");
        inserir(raiz_duracao, voos[i], "duracao");
    }

    Nodo* raiz = nullptr;
    for (int i = 0; i < total_voos; ++i) {
        inserir(raiz, voos[i], filtros[0].tipo_filtro);
    }

    // Aplicando os filtros e exibindo os resultados
    for (int i = 0; i < num_filtros; i++) {
        std::cout << filtros[i].num_resultados << " "
                  << filtros[i].tipo_filtro << " "
                  << filtros[i].condicao_completa << std::endl;

        Nodo* raiz_filtrada = nullptr;
        for (int j = 0; j < total_voos; ++j) {
            inserir(raiz_filtrada, voos[j], filtros[i].tipo_filtro);
        }

        int contador = 0;
        em_ordem(raiz_filtrada, contador, filtros[i].num_resultados);
        desalocar_arvore(raiz_filtrada);
    }

    // Desalocando a árvore original
    desalocar_arvore(raiz);

    // Liberando a memória dos voos e filtros
    delete[] voos;
    delete[] filtros;

    // Desalocação das árvores de índice
    desalocar_arvore(raiz_org);
    desalocar_arvore(raiz_dst);
    desalocar_arvore(raiz_preco);
    desalocar_arvore(raiz_assentos);
    desalocar_arvore(raiz_partida);
    desalocar_arvore(raiz_chegada);
    desalocar_arvore(raiz_paradas);
    desalocar_arvore(raiz_duracao);

    return 0;
}
