#ifndef VOO_HPP
#define VOO_HPP

#include <chrono>
#include <iostream>

class Voo {
public:
    char origem[4];  
    char destino[4]; 
    float preco;
    int assentos_disponiveis;

    // Usando time_point para representar a data e hora
    std::chrono::system_clock::time_point partida;
    std::chrono::system_clock::time_point chegada;

    int num_paradas;
    int duracao; 

    // Construtor para inicializar o voo
    Voo(const char origem[4], const char destino[4], float preco, int assentos_disponiveis,
        const std::chrono::system_clock::time_point& partida,
        const std::chrono::system_clock::time_point& chegada,
        int num_paradas);

    // Função que calcula a duração do voo com base nas datas e horários de partida e chegada
    int calcular_duracao();

    // Função que aloca dinamicamente os voos
    Voo* aloca_voos(FILE* arquivo, int total_voos);

    // Função para mostrar as informações do voo
    void mostrar_voo() const;

};

#endif