#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "parser.h"

//---------------------------------------------------------------------------------------------------------------//
static void remove_espaco(char *str) {
    char *start = str;
    char *end;
    
    while(isspace((unsigned char)*start)) start++;                            // Remove espaços no início
    if(*start == 0) {
        *str = '\0';    // Caso string seja vazia
        return;                                                                                                             
    }
    
    end = start + strlen(start) - 1;                                            
    while(end > start && isspace((unsigned char)*end)) end--;                 // Remove espaços no fim
    *(end+1) = '\0';

    memmove(str, start, (size_t)(end - start + 2));                           // Altera o início do buffer
}

static void extrainumero(const char *token_N, char *numero, size_t tam) {
    size_t j = 0;

    for (size_t i = 0; token_N[i] != '\0' && j < tam - 1; i++) {
        if (isdigit((unsigned char)token_N[i])) {
            numero[j++] = token_N[i];
        }
    }

    if (j == 0) {
        // Nenhum dígito encontrado
        strncpy(numero, "não encontrado", tam - 1);
        numero[tam - 1] = '\0';
    } else {
        numero[j] = '\0'; // Finaliza string
    }
}

//---------------------------------------------------------------------------------------------------------------//


static void corta_fim(char *s)
{
    size_t tam = strlen(s);
    while (tam > 0 && (s[tam - 1] == '\n' || s[tam - 1] == '\r'))
        s[--tam] = '\0';
}

//-------------------------------------------------------------------------//
static const char* dps_str(const char *line, const char *substr)
{
    const char *pointer = strstr(line, substr);
    if (!pointer)
        return NULL;
    pointer += strlen(substr); /* avança além da substring */
    while (*pointer == ' ' || *pointer == '\t')
        pointer++;
    return pointer;
}
//-------------------------------------------------------------------------//

static const char* dps_doispontos(const char *line)
{
    const char *pointer = strchr(line, ':');
    if (!pointer)
        return NULL;
    pointer++; /* avança além dos dois pontos */
    while (*pointer == ' ' || *pointer == '\t')
        pointer++;
    return pointer;
}

static void safe_copy(char *dst, size_t dst_size, const char *src)
{
    if (!dst || dst_size == 0) return;
    if (!src) {
        dst[0] = '\0';
        return;
    }
    strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}


//-------------------------------------------------------------------------//
void extraiDadosLocalizacao(char *p_linha, dado_excel *dado_l) { 

    char *token = strtok(p_linha, ",-");
    RemoveEspaco(token);                
    safe_copy(dado_l->endereco, sizeof(dado_l->endereco), token);

    int j = 0;

    while(token != NULL) {
        RemoveEspaco(token);

        if(j == 1) {
            extrainumero(token, dado_l->numero, sizeof(dado_l->numero));

        }
        else if(j == 2) {
            safe_copy(dado_l->bairro, sizeof(dado_l->bairro) , token);
            
        }
        else if(j == 3) {
            safe_copy(dado_l->cidade, sizeof(dado_l->cidade) , token);
            
        }

        token = strtok(NULL, ",-");
        j++;
    }   
}
//-------------------------------------------------------------------------//


void parser_txt(const char *local, dado_excel *out)
{
    if (!local || !out) return;

    FILE *file = fopen(local, "r");
    if (!file)
    {
        fprintf(stderr, "ERRO: não foi possível abrir o ficheiro '%s'\n", local);
        return;
    }

    char line[1024];

    /* Valores padrão */
    safe_copy(out->endereco, sizeof(out->endereco), "não encontrado");
    safe_copy(out->numero, sizeof(out->numero), "não encontrado");  // --nova variavel
    safe_copy(out->bairro, sizeof(out->bairro), "não encontrado");  // --nova variavel
    safe_copy(out->cidade, sizeof(out->cidade), "não encontrado");  // --nova variavel
    safe_copy(out->regiao, sizeof(out->regiao), "não encontrado");
    safe_copy(out->conf_frente, sizeof(out->conf_frente), "não encontrado");
    safe_copy(out->conf_fundo, sizeof(out->conf_fundo), "não encontrado");
    safe_copy(out->conf_latEsq, sizeof(out->conf_latEsq), "não encontrado");
    safe_copy(out->conf_latDir, sizeof(out->conf_latDir), "não encontrado");
    safe_copy(out->coords, sizeof(out->coords), "não encontrado");
    safe_copy(out->area_tot, sizeof(out->area_tot), "não encontrado");
    safe_copy(out->area_usada, sizeof(out->area_usada), "não encontrado");
    safe_copy(out->conserv_state, sizeof(out->conserv_state), "não encontrado");
    safe_copy(out->valoracao, sizeof(out->valoracao), "não encontrado");
    safe_copy(out->data_valoracao, sizeof(out->data_valoracao), "não encontrado");
    safe_copy(out->CPNo, sizeof(out->CPNo), "não encontrado");

    while (fgets(line, sizeof(line), file))
    {
        corta_fim(line);

        if (strstr(line, "LOCALIZAÇÃO:"))
        {
            const char *p = dps_doispontos(line);
            if (p) extraiDadosLocalizacao(p, out->endereco);    // --Safe_Copy substítuido por função extrai dados               
        }
        else if (strstr(line, "Mesorregião"))
        {
            const char *p = strstr(line, "Mesorregião");
            if (p) safe_copy(out->regiao, sizeof(out->regiao), p);
        }
        else if (strstr(line, "Frente"))
        {
            const char *p = strstr(line, "Frente");
            if (p) safe_copy(out->conf_frente, sizeof(out->conf_frente), p);
        }
        else if (strstr(line, "Lateral Esquerda"))
        {
            const char *p = strstr(line, "Esquerda");
            if (p) safe_copy(out->conf_latEsq, sizeof(out->conf_latEsq), p);
        }
        else if (strstr(line, "Lateral Direita"))
        {
            const char *p = strstr(line, "Direita");
            if (p) safe_copy(out->conf_latDir, sizeof(out->conf_latDir), p);
        }
        else if (strstr(line, "Fundo"))
        {
            const char *p = strstr(line, "Fundo");
            if (p) safe_copy(out->conf_fundo, sizeof(out->conf_fundo), p);
        }
        else if (strstr(line, "COORDENADAS:"))
        {
            const char *p = dps_doispontos(line);
            if (p) safe_copy(out->coords, sizeof(out->coords), p);
        }
        else if (strstr(line, "Área do Terreno:"))
        {
            const char *p = dps_doispontos(line);
            if (p) safe_copy(out->area_tot, sizeof(out->area_tot), p);
        }
        else if (strstr(line, "Área Construída total:"))
        {
            const char *p = dps_doispontos(line);
            if (p) safe_copy(out->area_usada, sizeof(out->area_usada), p);
        }
        else if (strstr(line, "Estado de conservação (Critério Heidecke)"))
        {
            const char *p = strstr(line, "Heidecke");
            if (p) safe_copy(out->conserv_state, sizeof(out->conserv_state), p);
        }
        else if (strstr(line, "RESULTADO DA AVALIAÇÃO:"))
        {
            const char *p = dps_doispontos(line);
            if (p) safe_copy(out->valoracao, sizeof(out->valoracao), p);
        }
        else if (strstr(line, "Recife,"))
        {
            const char *p = strstr(line, "Recife,");
            if (p) safe_copy(out->data_valoracao, sizeof(out->data_valoracao), p);
        }
        else if (strstr(line, "CP Nº") || strstr(line, "CP N") || strstr(line, "CP N°"))
        {
            const char *p = strstr(line, "CP Nº");
            if (!p) p = strstr(line, "CP N");
            if (p) safe_copy(out->CPNo, sizeof(out->CPNo), p);
        }
    }

    fclose(file);
}
