#include "excel_utils.h"
#include <xlsxwriter.h>

//Função com o nome auto explicativo (cria o arquivo excel e coloca os dados em sua respectiva célula)
bool criar_excel(const char *caminho, const Dadostxt *dado)
{
    if (!caminho || !dado) return false;

    lxw_workbook  *workbook  = workbook_new(caminho);
    if (!workbook) return false;

    lxw_worksheet *sheet = workbook_add_worksheet(workbook, "Dados");

    int row = 0;

    worksheet_write_string(sheet, row, 0, "Endereço:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->endereco, NULL);

    worksheet_write_string(sheet, row, 0, "Cidade:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->cidade, NULL);

    worksheet_write_string(sheet, row, 0, "Região:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->regiao, NULL);

    worksheet_write_string(sheet, row, 0, "Frente:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->conf_frente, NULL);

    worksheet_write_string(sheet, row, 0, "Fundo:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->conf_fundo, NULL);

    worksheet_write_string(sheet, row, 0, "Lateral Esquerda:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->conf_latEsq, NULL);

    worksheet_write_string(sheet, row, 0, "Lateral Direita:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->conf_latDir, NULL);

    worksheet_write_string(sheet, row, 0, "Coordenadas:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->coords, NULL);

    worksheet_write_string(sheet, row, 0, "Área Total:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->area_tot, NULL);

    worksheet_write_string(sheet, row, 0, "Área Construída:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->area_usada, NULL);

    worksheet_write_string(sheet, row, 0, "Estado de Conservação:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->conserv_state, NULL);

    worksheet_write_string(sheet, row, 0, "Valoração:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->valoracao, NULL);

    worksheet_write_string(sheet, row, 0, "Data Valoração:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->data_valoracao, NULL);

    worksheet_write_string(sheet, row, 0, "CP Nº:", NULL);
    worksheet_write_string(sheet, row++, 1, dado->CPNo, NULL);

    workbook_close(workbook);

    return true;
}