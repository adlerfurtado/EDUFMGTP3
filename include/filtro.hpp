#ifndef FILTRO_HPP
#define FILTRO_HPP

#include <iostream>

#define org 1  // Origem do voo
#define dst 2  // Destino do voo
#define prc 3  // Preço de uma passagem
#define sea 4  // Número de assentos disponíveis
#define dep 5  // Data-hora de partida
#define arr 6  // Data-hora de chegada
#define sto 7  // Número de paradas
#define dur 8  // Duração total do voo

struct Operador {
    //Armazena os operadores
    char op_org[2]; 
    char op_dst[2];
    char op_prc[2];
    char op_sea[2];
    char op_dep[2];
    char op_arr[2];
    char op_sto[2];
    char op_dur[2];

    //Armazena os números comparativos
    char num_org[3];
    char num_dst[3];
    float num_prc;
    int num_sea;
    int num_dep;
    int num_arr;
    int num_sto;
    int num_dur;

    //Armazena dado útil para conferencia se existe tal filtro
    bool tem_org = 0; 
    bool tem_dst = 0;
    bool tem_prc = 0;
    bool tem_sea = 0;
    bool tem_dep = 0;
    bool tem_arr = 0;
    bool tem_sto = 0;
    bool tem_dur = 0;

};

struct Filtro {
    int num_resultados;        // Número de resultados
    char tipo_filtro[4];       // Tipo de filtro, "psd" ou "sdp"
    char condicao_completa[100];  //string da linha toda armazenada
    Operador operador;

void verifica_org(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_dst(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_prc(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_sea(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_dep(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_arr(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_sto(const char* condicao_completa, Filtro* filtros, int index); 
void verifica_dur(const char* condicao_completa, Filtro* filtros, int index); 
};

#endif
