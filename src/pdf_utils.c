#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "pdf_utils.h"

void extract_text(const char *pdf_path, const char *output_path) {
    // Comando seguro para Windows com aspas
    char cmd[1024];
    
    snprintf(cmd, sizeof(cmd),
             "cmd /C \"\"C:\\msys64\\mingw64\\bin\\pdftotext.exe\" -layout \"%s\" \"%s\"\"",
             pdf_path, output_path);

    // Debug: mostra o comando que será executado
    g_print("[DEBUG] Comando: %s\n", cmd);

    // Executa o comando
    int r = system(cmd);
    if (r != 0) {
        g_print("[ERRO] Falha ao executar pdftotext\n");
    } else {
        g_print("[OK] Texto extraído com sucesso para %s\n", output_path);
    }
}

