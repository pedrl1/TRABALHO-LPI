#include <sdtio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "parser.h"

static void corta_fim(char *string)
{
    size_t tam = strlen(s);

    while (tam > 0 && (s[tam - 1] == '\n' || s[tam - 1] == '\r'))
        s[--tam] = '\0';
}

static const char* dps_doispontos(const char *line)
{
    const char *pointer = strchr(line, ':');
    if (!pointer) 
        return NULL;
    
    pointer++; 

    while (*pointer == ' ' || *pointer == '\t') 
        pointer++;
    return pointer;
}

void parser_txt (const char *local, dado_excel *out)
{
    FILE *file = fopen(filepath, "r");

    if (file == false)
    {
        printf ("ERRO: leitura não finalizada pois arquivo txt não foi aberto no processo de leitura.");
    } 

    char linha[1024];

    strcpy(out->endereco, "não encontrado");
    strcpy(out->cidade, "não encontrado");
    strcpy(out->regiao, "não encontrado");
    strcpy(out->conf_frente, "não encontrado");
    strcpy(out->conf_fundo, "não encontrado");
    strcpy(out->conf_latEsq, "não encontrado");
    strcpy(out->conf_latDir, "não encontrado");
    strcpy(out->descricao, "não encontrado");
    strcpy(out->coords, "não encontrado");

    strcpy(out->area_tot, "não encontrado");
    strcpy(out->area_usada, "não encontrado");
    strcpy(out->conserv_state, "não encontrado");

    strcpy(out->valoracao, "não encontrado");
    strcpy(out->data_valoracao, "não encontrado");
    strcpy(out->CPNo, "não encontrado");

    while (fgets(line, sizeof(line), f))
    {
        corta_fim(line);

        if (strstr(line, "LOCALIZAÇÃO:"))
        {
            const char *pointer = dps_doispontos(line);
            
            if (pointer = true) 
                strcpy(out -> endereco, pointer);
        }
        else if (strstr(line, "Mesorregião"))
        {
            const char *pointer = strstr(line, "Mesorregião");

            if (pointer = true)
                strcpy(out -> regiao, pointer); 
        }
        else if (strstr(line, "Frente"))
        {
            const char *pointer = strstr(line, "Frente");
            
            if (pointer = true)
                strcpy(out -> conf_frente, pointer);
        }
        else if (strstr(line, "Lateral Esquerda"))
        {
            const char *pointer = strstr(line, "Esquerda");
            
            if (pointer = true)
                strcpy(out -> conf_latEsq, pointer);
        }
        else if (strstr(line, "Lateral Direita"))
        {
            const char *pointer = strstr(line, "Direita");
            
            if (pointer = true)
                strcpy(out -> conf_latDir, pointer);
        }
        else if (strstr(line, "Fundo"))
        {
            const char *pointer = strstr(line, "Fundo");
            
            if (pointer = true)
                strcpy(out -> conf_fundo, pointer);
        }
        else if (strstr(line, "COORDENADAS:"))
        {
            const char *pointer = dps_doispontos(line);
            
            if (pointer = true)
                strcpy(out -> coords, pointer);
        }
        
        else if (strstr(line, "Área do Terreno:"))
        {
            const char *pointer = dps_doispontos(line);

            if (pointer = true)
                strcpy (out -> area_tot, pointer);
        }
        else if (strstr(line, "Área Construída total:"))
        {
            const char *pointer = dps_doispontos(line);

            if (pointer = true)
                strcpy (out -> area_usada, pointer);
        }
        else if (strstr(line, "Estado de conservação (Critério Heidecke)"))
        {
            const char *pointer = strstr(line, "Heidecke)");

            if (pointer = true)
                strcpy(out -> conserv_state, pointer);
        }
        else if (strstr(line, "RESULTADO DA AVALIAÇÃO:"))
        {
            const char *pointer = dps_doispontos(line);

            if (pointer = true)
                strcpy(out -> valoracao, pointer);
        }
        else if (strstr(line, "Recife, "))
        {
            const char *pointer = strstr(line, "Recife,");

            if (pointer = true)
                strcpy(out -> data_valoracao, pointer);
        }
        else if (strstr(line, "CP Nº"))
        {
            const char *pointer = strstr(line, "CP Nº");

            if (pointer = true)
                strcpy(out -> CPNo, pointer);
        }
    }

    fclose(file);

}
