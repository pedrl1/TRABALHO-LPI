#include <stdlib.h>
#include <stdio.h>
#include "xlsxwriter.h"

int main(void) {
  //abre o arquivo
    lxw_workbook  *workbook  = workbook_new("teste.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    worksheet_write_string(worksheet, 0, 0, "Sala", NULL);
    worksheet_write_string(worksheet, 0, 1, "Nome", NULL);
    worksheet_write_string(worksheet, 0, 2, "Horario", NULL);

   
    worksheet_write_string(worksheet, 1, 0, "04", NULL);
    worksheet_write_string(worksheet, 1, 1, "Aluno1 Amanda", NULL);
    worksheet_write_string(worksheet, 1, 2, "14-15", NULL);
    worksheet_write_string(worksheet, 2, 0, "05", NULL);
    worksheet_write_string(worksheet, 2, 1, "Aluno2", NULL);
    worksheet_write_string(worksheet, 2, 2, "20-21", NULL);

    // Fecha o arquivo
    workbook_close(workbook);

    return 0;
}
