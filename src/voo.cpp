#include "voo.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>


// Construtor para inicializar o voo
Voo::Voo(const char origem[4], const char destino[4], float preco, int assentos_disponiveis,
         const std::chrono::system_clock::time_point& partida,
         const std::chrono::system_clock::time_point& chegada,
         int num_paradas)
    : preco(preco), assentos_disponiveis(assentos_disponiveis),
      partida(partida), chegada(chegada), num_paradas(num_paradas), duracao(calcular_duracao()) {
    // Copia os valores para os arrays diretamente
    for (int i = 0; i < 3; i++) {
        this->origem[i] = origem[i]; // Copia cada caractere
        this->destino[i] = destino[i]; // Copia cada caractere
    }
    this->origem[3] = '\0';  // Assegura que os chars sejam terminada
    this->destino[3] = '\0';  // Assegura que os chars sejam terminada
}


// Função que calcula a duração do voo com base nas datas e horários de partida e chegada
int Voo::calcular_duracao() {
    auto duracao_dif = chegada - partida;
    return std::chrono::duration_cast<std::chrono::minutes>(duracao_dif).count();
}

// Função para mostrar as informações do voo
void Voo::mostrar_voo() const {
    // Converte o horário de partida e chegada para o formato de char
    std::time_t partida_time = std::chrono::system_clock::to_time_t(partida);
    std::time_t chegada_time = std::chrono::system_clock::to_time_t(chegada);

    // Formata a data e hora conforme o VPL
    char partida_str[20], chegada_str[20];
    std::strftime(partida_str, sizeof(partida_str), "%Y-%m-%dT%H:%M:%S", std::localtime(&partida_time));
    std::strftime(chegada_str, sizeof(chegada_str), "%Y-%m-%dT%H:%M:%S", std::localtime(&chegada_time));

    // Imprime conforme o VPL
    std::cout << origem << " " << destino << " " << preco << " " 
              << assentos_disponiveis << " " << partida_str << " "
              << chegada_str << " " << num_paradas << std::endl;
}
