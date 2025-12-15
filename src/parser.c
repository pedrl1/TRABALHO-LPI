#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "parser.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  FUNÇÕES AUXILIARES  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------------------------------------------------------------------------------------------------//
// função que "pula" todos os espaços em branco que ocorrerem após uma string que for definida como parâmetro
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
//---------------------------------------------------------------------------------------------------------------//

// função que corta o fim do parser (quando pula linha)
static void corta_fim(char *s)
{
    size_t tam = strlen(s);
    while (tam > 0 && (s[tam - 1] == '\n' || s[tam - 1] == '\r'))
        s[--tam] = '\0';
}

//-------------------------------------------------------------------------//
// função que retorna o ponteiro para a primeira ocorrência de um caractere, diferente de espaço ou tabulação, que aparece em uma linha após a string que for definida como parâmetro
static char* dps_str(char *line, char *substr)
{
    char *pointer = strstr(line, substr);
    if (!pointer)
        return NULL;
    pointer += strlen(substr); /* avança além da substring */
    while (*pointer == ' ' || *pointer == '\t')
        pointer++;
    return pointer;
}
//-------------------------------------------------------------------------//

// função que faz ele ler depois dos dois pontos (ele ignora os dois pontos após a palavra que ele identifica como igual para que o parser leia tudo após ela)
static char* dps_doispontos(char *line)
{
    char *pointer = strchr(line, ':');
    if (!pointer)
        return NULL;
    pointer++; /* avança além dos dois pontos */
    while (*pointer == ' ' || *pointer == '\t')
        pointer++;
    return pointer;
}

static void safe_copy(char *dst, size_t dst_size, char *src)
{
    if (!dst || dst_size == 0) return;
    if (!src) {
        dst[0] = '\0';
        return;
    }
    strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  FUNÇÕES DE EXTRAÇÃO  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//-------------------------------------------------------------------------//
// função que filtra e altera o que está armazenado numa string, deixando apenas os números e ignorando qualquer outra forma de caractere.
static void extrainumero(char *token_N, char *numero, size_t tam) {
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

// função que extrai o logradouro, número, bairro e cidade (ou município) contidos numa linha (que está dividida em vírgulas ou hífens)
void extrai_dados_localizacao(char *p_line, dado_excel *dado_l) { 

    char *token = strtok(p_line, ",-");    // separa a linha em tokens (ou partições), dividos por vírgula ou hífen
    remove_espaco(token);                
    safe_copy(dado_l->endereco, sizeof(dado_l->endereco), token);

    int j = 0;    // cada índice de "j" indica um token diferente

    while(token != NULL) {    
        remove_espaco(token);

        if(j == 1) {
            extrainumero(token, dado_l->numero, sizeof(dado_l->numero));

        }
        else if(j == 2) {
            safe_copy(dado_l->cidade, sizeof(dado_l->cidade) , token);
            
        }
        else if(j == 3) {
            safe_copy(dado_l->estado, sizeof(dado_l->estado) , token);
            
        }

        token = strtok(NULL, ",-");
        j++;
    }   
}

// função que extrai as coordenadas S e W, que estão contidas na linha que recebeu de parâmetro
void extrai_coordenadas(char *p_line, dado_excel *dado_c) {
    char *S_start = p_line;
    
    // acha o 'S'
    char *S_end = strchr(S_start, 'S');
    if (!S_end) S_end = strchr(S_start, 's');   // medida anti case sensitive
    if (!S_end) return;

    
    size_t S_size = (size_t)(S_end - S_start);
    if (S_size >= sizeof(dado_c->coord_S))    // medida anti overflow
        S_size = sizeof(dado_c->coord_S) - 1;

    // copia coordenada S
    strncpy(dado_c->coord_S, S_start, S_size);  // usa os ponteiros como delimitadores para copiar o tamanho exato da coordenada
    dado_c->coord_S[S_size] = '\0';
    remove_espaco(dado_c->coord_S);

    // --- W ---
    char *W_start = S_end + 1;    // as coordenadas de W vem logo após o 'S'
    remove_espaco(W_start);

    // acha o primeiro dígito (início da coordenada W)
    while (*W_start && !isdigit((unsigned char)*W_start)) W_start++;
    if (!*W_start) return;

    char *W_end = strchr(W_start, 'W');
    if (!W_end) W_end = strchr(W_start, 'w');   // medida anti case sensitive
    if (!W_end) return;

    size_t W_size = (size_t)(W_end - W_start);
    if (W_size >= sizeof(dado_c->coord_W))    // medida anti overflow
        W_size = sizeof(dado_c->coord_W) - 1;

    // copia coordenada W
    strncpy(dado_c->coord_W, W_start, W_size);  // usa os ponteiros como delimitadores para copiar o tamanho exato da coordenada
    dado_c->coord_W[W_size] = '\0';
    remove_espaco(dado_c->coord_W);
}
//-------------------------------------------------------------------------//


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  FUNÇÃO PRINCIPAL DO PARSER  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
void parser_txt(char *local, dado_excel *out)
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
    safe_copy(out->cidade, sizeof(out->cidade), "não encontrado");  // --nova variavel
    safe_copy(out->regiao, sizeof(out->regiao), "não encontrado");
    safe_copy(out->conf_frente, sizeof(out->conf_frente), "não encontrado");
    safe_copy(out->conf_fundo, sizeof(out->conf_fundo), "não encontrado");
    safe_copy(out->conf_latEsq, sizeof(out->conf_latEsq), "não encontrado");
    safe_copy(out->conf_latDir, sizeof(out->conf_latDir), "não encontrado");
    safe_copy(out->coord_S, sizeof(out->coord_S), "não encontrado");    // --nova variavel
    safe_copy(out->coord_W, sizeof(out->coord_W), "não encontrado");    // --nova variavel
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
            char *p = dps_doispontos(line);
            if (p) extrai_dados_localizacao(p, out);    // --Safe_Copy substítuido por função extrai dados localização              
        }
        else if (strstr(line, "Mesorregião"))
        {
            char *p = strstr(line, "Mesorregião");
            if (p) safe_copy(out->regiao, sizeof(out->regiao), p);
        }
        // nova forma de extração de confrontantes
        else if (strstr(line, "CONFRONTANTES")){
            char *p_fr, *p_e, *p_d, *p_fu;  // ponteiros para cada confrantante
            for (size_t j = 0; j < 5; j++){       // confrantantes geralmente se encontram nas próximas 5 linhas
            
                fgets(line, sizeof(line), file);
                corta_fim(line);

                if (strstr(line, "Frente"))
                { 
                    p_fr = dps_str(line, "Frente");    // uso da função dps_str para não levar os espaços do ínicio em conta na hora de adquirir o confrontante
                    if (p_fr) safe_copy(out->conf_frente, sizeof(out->conf_frente), p_fr);
                }
                else if (strstr(line, "Lateral Esquerda"))
                { 
                    p_e = dps_str(line, "Esquerda");
                    if (p_e) safe_copy(out->conf_latEsq, sizeof(out->conf_latEsq), p_e);                                  
                }
                else if (strstr(line, "Lateral Direita"))
                { 
                    p_d = dps_str(line, "Direita");
                    if (p_d) safe_copy(out->conf_latDir, sizeof(out->conf_latDir), p_d);
                }
                else if (strstr(line, "Fundos"))
                { 
                    p_fu = dps_str(line, "Fundos");
                    if (p_fu) safe_copy(out->conf_fundo, sizeof(out->conf_fundo), p_fu);
                }
            }
        }
        else if (strstr(line, "COORDENADAS:"))
        {
            char *p = dps_doispontos(line);
            if (p) extrai_coordenadas(p, out);  // --Safe_Copy substítuido por função extrai coordenadas
        }
        else if (strstr(line, "Área do Terreno:"))
        {
            char *p = dps_doispontos(line);
            if (p) safe_copy(out->area_tot, sizeof(out->area_tot), p);
        }
        else if (strstr(line, "Área Construída total:"))
        {
            char *p = dps_doispontos(line);
            if (p) safe_copy(out->area_usada, sizeof(out->area_usada), p);
        }
        else if (strstr(line, "Estado de conservação")) // nova forma de adquirir estado de conservação
        {
            char *p;
            for (size_t j = 0; j < 5; j++){       // estado de conervação pode ser encontrado nas próximas 5 linhas
            
                fgets(line, sizeof(line), file);
                corta_fim(line);

                if (strstr(line, "anos"))                                                // se a string "anos" estiver em uma das 5 linhas lidas
                {                                                                        // tudo o que estiver depois de "anos" será copiado para
                    p = dps_str(line, "anos");                                           // o estado de conservação
                    if (p) safe_copy(out->conserv_state, sizeof(out->conserv_state), p);
                    
                }
            }
        }
        else if (strstr(line, "RESULTADO DA AVALIAÇÃO:"))
        {
            char *p = dps_doispontos(line);
            if (p) safe_copy(out->valoracao, sizeof(out->valoracao), p);
        }
        else if (strstr(line, "Recife,"))
        {
            char *p = strstr(line, "Recife,");
            if (p) safe_copy(out->data_valoracao, sizeof(out->data_valoracao), p);
        }
        else if (strstr(line, "CP Nº") || strstr(line, "CP N") || strstr(line, "CP N°"))
        {
            char *p = strstr(line, "CP Nº");
            if (!p) p = strstr(line, "CP N");
            if (p) safe_copy(out->CPNo, sizeof(out->CPNo), p);
        }
    }

    fclose(file);
}