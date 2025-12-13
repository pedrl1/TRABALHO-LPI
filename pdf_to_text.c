#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que troca de .pdf para .txt
void gerar_nome_saida(const char *entrada, char *saida) {
    strcpy(saida, entrada);

    //Procura o último ponto no nome do arquivo
    char *ponto = strrchr(saida, '.');

    if (ponto != NULL) {
        //Se achou, corta a string
        *ponto = '\0';
    }

    //Adiciona a extensão .txt
    strcat(saida, ".txt");
}

int main(int argc, char *argv[]) {
    char input[1024];
    char output[2048];
    char command[600];
    int sucessos = 0;
    int erros = 0;

    // Se o usuário não passou nada, mostra como usar
    if (argc < 2) {
        printf("Uso incorreto.\n");
        printf("Para usar, arraste os arquivos PDF para cima deste executável\n");
        printf("Ou use no terminal: %s arquivo1.pdf arquivo2.pdf\n", argv[0]);

        // Pausa para o usuário ler se estiver no Windows
        printf("\nPressione Enter para sair...");
        getchar();
        return 1;
    }

    printf("=== Conversão em lote iniciada ===\n");
    printf("Arquivos identificados: %d\n\n", argc - 1);

    //Loop que percorrerá todos os arquivos em upload
    for (int i = 1; i < argc; i++) {
        char *input = argv[i];

        //Gera o nome do arquivo de saída automaticamente em .txt
        gerar_nome_saida(input, output);

        printf("[%d/%d] Convertendo: %s -> %s ...", i, argc - 1, input, output);

        //Monta o comando, usa o sprintf para evitar buffer overflow
        sprintf(command, sizeof(command), "pdftotext -layout \"%s\" \"%s\"", input, output);


        //Executa
        int r = system(command);

        if(r == 0) {
            printf("OK!\n");
            sucessos++;
        } else {
            printf("ERRO!\n");
            erros++;
        }
    }

    printf("\n=== Processamento finalizado ===\n");
    printf("Sucessos: %d\n", sucessos);
    printf("Falhas: %d\n", erros);

    //Pausa final para ler o relatório antes de fechar a janela
    printf("\nPressione Enter para fechar...");
    getchar();

return 0;
}