#include "excel_utils.h"
#include <xlsxwriter.h>

//Função com o nome auto explicativo (cria o arquivo excel e coloca os dados em sua respectiva célula)
bool criar_excel(const char *caminho, const Dadostxt *dado)
{
    if (!caminho || !dado) return false;

    int leitura = 0;
    
    lxw_workbook  *workbook  = workbook_new(caminho);
    if (!workbook) return false;


    lxw_worksheet *sheet = workbook_add_worksheet(workbook, "Dados");

    

    int collumn = 0;
    int row = 1;
    
    

    worksheet_write_string(sheet, 0, collumn++, "Endereço:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Número:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Cidade:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Estado:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Região:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Frente:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Fundo:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Lateral Esquerda:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Lateral Direita:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Coordenada W:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Coordenada S:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Área Total:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Área Construída:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Estado de Conservação:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Valoração:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "Data Valoração:", NULL);
    worksheet_write_string(sheet, 0, collumn++, "CP Nº:", NULL);

 
    collumn = 0;
    worksheet_write_string(sheet, row, collumn++, dado->endereco, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->numero, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->cidade, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->estado, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->regiao, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->conf_frente, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->conf_fundo, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->conf_latEsq, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->conf_latDir, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->coord_W, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->coord_S, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->area_tot, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->area_usada, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->conserv_state, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->valoracao, NULL);
    worksheet_write_string(sheet, row, collumn++, dado->data_valoracao, NULL);
    worksheet_write_string(sheet, row++, collumn++, dado->CPNo, NULL);

    workbook_close(workbook);
    
    return true;
}