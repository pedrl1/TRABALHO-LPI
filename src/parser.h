#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char endereco [256];
    char cidade [32];
    char regiao [32];
    char conf_frente [256];
    char conf_fundo [256];
    char conf_latEsq [256];
    char conf_latDir [256];
    char coords [16];
    char area_tot [32];
    char area_usada [32];
    char conserv_state [32];
    char valoracao [256];
    char data_valoracao [16];
    char CPNo [32];
} dado_excel;

void parser_txt(const char *local, dado_excel *out);

#endif