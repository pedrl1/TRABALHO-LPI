#include "excel_utils.h"
#include <xlsxwriter.h>

bool criar_excel(const char *caminho, const Dadostxt *d)
{
    if (!caminho || !d) return false;

    lxw_workbook  *workbook  = workbook_new(caminho);
    if (!workbook) return false;

    lxw_worksheet *sheet = workbook_add_worksheet(workbook, "Dados");

    int row = 0;

    worksheet_write_string(sheet, row, 0, "Endereço:", NULL);
    worksheet_write_string(sheet, row++, 1, d->endereco, NULL);

    worksheet_write_string(sheet, row, 0, "Cidade:", NULL);
    worksheet_write_string(sheet, row++, 1, d->cidade, NULL);

    worksheet_write_string(sheet, row, 0, "Região:", NULL);
    worksheet_write_string(sheet, row++, 1, d->regiao, NULL);

    worksheet_write_string(sheet, row, 0, "Frente:", NULL);
    worksheet_write_string(sheet, row++, 1, d->conf_frente, NULL);

    worksheet_write_string(sheet, row, 0, "Fundo:", NULL);
    worksheet_write_string(sheet, row++, 1, d->conf_fundo, NULL);

    worksheet_write_string(sheet, row, 0, "Lateral Esquerda:", NULL);
    worksheet_write_string(sheet, row++, 1, d->conf_latEsq, NULL);

    worksheet_write_string(sheet, row, 0, "Lateral Direita:", NULL);
    worksheet_write_string(sheet, row++, 1, d->conf_latDir, NULL);

    worksheet_write_string(sheet, row, 0, "Coordenadas:", NULL);
    worksheet_write_string(sheet, row++, 1, d->coords, NULL);

    worksheet_write_string(sheet, row, 0, "Área Total:", NULL);
    worksheet_write_string(sheet, row++, 1, d->area_tot, NULL);

    worksheet_write_string(sheet, row, 0, "Área Construída:", NULL);
    worksheet_write_string(sheet, row++, 1, d->area_usada, NULL);

    worksheet_write_string(sheet, row, 0, "Estado de Conservação:", NULL);
    worksheet_write_string(sheet, row++, 1, d->conserv_state, NULL);

    worksheet_write_string(sheet, row, 0, "Valoração:", NULL);
    worksheet_write_string(sheet, row++, 1, d->valoracao, NULL);

    worksheet_write_string(sheet, row, 0, "Data Valoração:", NULL);
    worksheet_write_string(sheet, row++, 1, d->data_valoracao, NULL);

    worksheet_write_string(sheet, row, 0, "CP Nº:", NULL);
    worksheet_write_string(sheet, row++, 1, d->CPNo, NULL);

    workbook_close(workbook);

    return true;
}