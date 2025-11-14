#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[256];
    char output[256];
    char command[600];

    printf("Digite o nome do arquivo PDF (ex: laudo.pdf): ");
    scanf("%255s", input);

    printf("Digite o nome do arquivo TXT de saída (ex: laudo.txt): ");
    scanf("%255s", output);

    // monta o comando final
    sprintf(command, "pdftotext -layout \"%s\" \"%s\"", input, output);

    printf("\nExecutando conversão...\n");

    // executa o utilitário
    int r = system(command);

    if (r != 0) {
        printf("Erro ao converter PDF. Verifique se o pdftotext está instalado.\n");
        return 1;
    }

    printf("Conversão concluída! Arquivo gerado: %s\n", output);

    return 0;
}
