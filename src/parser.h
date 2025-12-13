#ifndef PARSER_H
#define PARSER_H

typedef struct DadosTxt
{
    char endereco [256];
    char numero [32];   
    char cidade [32];   
    char estado [32];   
    char regiao [32];
    char conf_frente [256];
    char conf_fundo [256];
    char conf_latEsq [256];
    char conf_latDir [256];
    char coords [64];
    char area_tot [32];
    char area_usada [32];
    char conserv_state [32];
    char valoracao [256];
    char data_valoracao [32];
    char CPNo [32];
} Dadostxt;

typedef Dadostxt dado_excel;

void extrai_dados_localizacao(char *p_linha, dado_excel *dado_l); //--Função que extrai endereço, número, bairro e cidade.

void parser_txt(char *local, dado_excel *out);

#endif