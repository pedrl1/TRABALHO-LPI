#include <sdtio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

static void corta_fim(char *string)
{
    size_t tam = strlen(s);

    while (tam > 0 && (s[tam - 1] == '\n' || s[tam - 1] == '\r'))
        s[--tam] = '\0';
}



int parser_txt (const char *local, dado_excel *out )
{
    FILE *file = fopen(filepath, "r");

    if (file == false)
    {
        printf ("ERRO: leitura não finalizada pois arquivo txt não foi aberto no processo de leitura.");
    } 

    char linha[1024];

    strcpy(out->endereco, "não encontrado");
    strcpy(out->numero, "não encontrado");
    strcpy(out->complemento, "não encontrado");
    strcpy(out->bairro, "não encontrado");
    strcpy(out->cep, "não encontrado");
    strcpy(out->cidade, "não encontrado");
    strcpy(out->regiao, "não encontrado");
    strcpy(out->estado, "não encontrado");
    strcpy(out->pais, "não encontrado");
    strcpy(out->conf_frente, "não encontrado");
    strcpy(out->conf_fundo, "não encontrado");
    strcpy(out->conf_latEsq, "não encontrado");
    strcpy(out->conf_latDir, "não encontrado");
    strcpy(out->ref_point, "não encontrado");
    strcpy(out->obs, "não encontrado");
    strcpy(out->coord_s, "não encontrado");
    strcpy(out->coord_w, "não encontrado");

    strcpy(out->area_tot, "não encontrado");
    strcpy(out->area_usada, "não encontrado");
    strcpy(out->meas_unit, "não encontrado");
    strcpy(out->conserv_state, "não encontrado");
    strcpy(out->lim_adm, "não encontrado");

    strcpy(out->valoracao, "não encontrado");
    strcpy(out->data_valoracao, "não encontrado");
    strcpy(out->num_doc, "não encontrado");
    strcpy(out->valor_const_nova, "não encontrado");

    while (fgets(line, sizeof(line), f))
    {
        
    }

}
