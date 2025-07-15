#include "filtro.hpp"
#include "voo.hpp"

// Função que verifica e processa a condição referente à "org" (origem) em uma string de filtro
void verifica_org(const char* condicao_completa, Filtro* filtros, int index) {
    int len = 0;

    // Calcula o comprimento da string de entrada sem usar funções da biblioteca
    while (condicao_completa[len] != '\0') {
        len++;
    }

    // Procura pela substring "org" dentro da string condicao_completa
    for (int i = 0; i < len - 2; i++) { // -2 porque precisamos de 3 caracteres para verificar "org"
        if (condicao_completa[i] == 'o' &&
            condicao_completa[i + 1] == 'r' &&
            condicao_completa[i + 2] == 'g') {
                
            // Se encontrar "org", armazena o operador associado à origem
            filtros[index].operador.op_org[0] = condicao_completa[i + 3];  
            filtros[index].operador.op_org[1] = condicao_completa[i + 4];  
            
            // Armazena o número de comparação após o operador (duração da origem)
            filtros[index].operador.num_org[0] = condicao_completa[i + 5];  
            filtros[index].operador.num_org[1] = condicao_completa[i + 6];  
            filtros[index].operador.num_org[2] = condicao_completa[i + 7];

            // Marca que o filtro foi configurado
            filtros[index].operador.tem_org = 1;
        }
    }
}

// Função que verifica a condição de "dst" (destino) na string de filtro
void verifica_dst(const char* condicao_completa, Filtro* filtros, int index) {
    int len = 0;
    
    // Calcula o comprimento da string (sem utilizar funções da biblioteca)
    while (condicao_completa[len] != '\0') {
        len++;
    }

    // Procura pela substring "dst" na string condicao_completa
    for (int i = 0; i < len - 2; i++) {
        if (condicao_completa[i] == 'd' &&
            condicao_completa[i + 1] == 's' &&
            condicao_completa[i + 2] == 't') {
                
            // Se "dst" for encontrado, armazena o operador associado ao destino
            filtros[index].operador.op_dst[0] = condicao_completa[i + 3];  
            filtros[index].operador.op_dst[1] = condicao_completa[i + 4];  

            // Armazena o número de comparação após o operador (número do destino)
            filtros[index].operador.num_dst[0] = condicao_completa[i + 5];  
            filtros[index].operador.num_dst[1] = condicao_completa[i + 6];  
            filtros[index].operador.num_dst[2] = condicao_completa[i + 7];

            // Marca que o filtro de destino foi configurado
            filtros[index].operador.tem_dst = 1;
        }       
    }
}

// Função que verifica a condição de "prc" (preço) na string de filtro
void verifica_prc(const char* condicao_completa, Filtro* filtros, int index) {
    int len = 0;
    
    // Calcula o comprimento da string sem usar funções da biblioteca
    while (condicao_completa[len] != '\0') {
        len++;
    }

    // Procura pela substring "prc" na string condicao_completa
    for (int i = 0; i < len - 2; i++) {
        if (condicao_completa[i] == 'p' &&
            condicao_completa[i + 1] == 'r' &&
            condicao_completa[i + 2] == 'c') {
                
            // Armazena o operador associado ao preço
            filtros[index].operador.op_prc[0] = condicao_completa[i + 3];  
            filtros[index].operador.op_prc[1] = condicao_completa[i + 4];  

            // Captura e converte o número após o operador para float (número do preço)
            int num_start = i + 5;  
            int num_end = num_start;
            while ((condicao_completa[num_end] >= '0' && condicao_completa[num_end] <= '9') || condicao_completa[num_end] == '.') {
                num_end++;
            }

            // Converte o número string para float manualmente
            char num_str[20];
            int j = 0;
            for (int k = num_start; k < num_end; k++) {
                num_str[j++] = condicao_completa[k];
            }
            num_str[j] = '\0';

            float num_prc = 0.0;
            bool is_negative = false;
            int decimal_pos = -1;
            int length = 0;

            // Determina se o número é negativo e a posição do ponto decimal
            for (int i = 0; num_str[i] != '\0'; i++) {
                if (num_str[i] == '-') {
                    is_negative = true;
                } else if (num_str[i] == '.') {
                    decimal_pos = i;
                }
                length++;
            }

            // Converte a parte inteira e decimal do número
            float integer_part = 0.0;
            for (int i = 0; i < length; i++) {
                if (num_str[i] == '.') break;
                integer_part = integer_part * 10 + (num_str[i] - '0');
            }

            float decimal_part = 0.0;
            if (decimal_pos != -1) {
                float factor = 0.1;
                for (int i = decimal_pos + 1; i < length; i++) {
                    decimal_part += (num_str[i] - '0') * factor;
                    factor /= 10;
                }
            }

            num_prc = integer_part + decimal_part;
            if (is_negative) {
                num_prc = -num_prc;
            }

            // Grava o valor final do preço
            filtros[index].operador.num_prc = num_prc;

            filtros[index].operador.tem_prc = 1;
        }
    }
}

// Função para verificar a condição de "sea" (assento disponível)
void verifica_sea(const char* condicao_completa, Filtro* filtros, int index) {
    int len = 0;
    
    // Calcula o comprimento da string
    while (condicao_completa[len] != '\0') {
        len++;
    }

    // Procura pela substring "sea" dentro da string condicao_completa
    for (int i = 0; i < len - 2; i++) {
        if (condicao_completa[i] == 's' &&
            condicao_completa[i + 1] == 'e' &&
            condicao_completa[i + 2] == 'a') {
                
            // Armazena o operador associado à quantidade de assentos disponíveis
            filtros[index].operador.op_sea[0] = condicao_completa[i + 3];  
            filtros[index].operador.op_sea[1] = condicao_completa[i + 4];  

            // Captura e converte o número de assentos disponíveis
            int num_start = i + 5;  
            int num_end = num_start;
            while (condicao_completa[num_end] >= '0' && condicao_completa[num_end] <= '9') {
                num_end++;
            }

            // Converte o número para inteiro 
            char num_str[10];
            int j = 0;
            for (int k = num_start; k < num_end; k++) {
                num_str[j++] = condicao_completa[k];
            }
            num_str[j] = '\0';

            int num_sea = 0;
            for (int k = 0; num_str[k] != '\0'; k++) {
                num_sea = num_sea * 10 + (num_str[k] - '0');
            }

            // Grava o número de assentos disponíveis
            filtros[index].operador.num_sea = num_sea;

            filtros[index].operador.tem_sea = 1;
        }
    }
}
