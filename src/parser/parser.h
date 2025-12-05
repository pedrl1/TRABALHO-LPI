#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    char endereco [256];
    char numero [8];
    char complemento [128];
    char bairro [128];
    char cep [9];
    char cidade [32];
    char regiao [32];
    char estado [32];
    char pais [8];
    char conf_frente [256];
    char conf_fundo [256];
    char conf_latEsq [256];
    char ref_point [256];
    char obs [512];
    char coord_s [16];
    char coord_w [16];
    char area_tot [32];
    char area_usada [32];
    char meas_unit [4];
    char conserv_state [32];
    char lim_adm [128];
    char valoracao [256];
    char data_valoracao [16];
    char numero_documento [32];
    char valor_const_nova [16];
} dado_excel;

void parse_txt(const *txt_path, dado_excel *out);

#endif