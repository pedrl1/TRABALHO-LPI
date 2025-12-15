#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "pdf_utils.h"
#include "excel_utils.h"
#include "parser.h"

// Atualiza o TextView com os dados extraídos pelo parser
void update_textview_with_laudo(GtkTextView *textview, const Dadostxt *dados) 
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    char texto[4096];
    snprintf(texto, sizeof(texto),
        "Endereço: %s\n"
        "Número: %s\n"
        "Cidade: %s\n"
        "Estado: %s\n"
        "Região: %s\n" 
        "Confrontante Frente: %s\n" 
        "Confrontante Fundo: %s\n" 
        "Confrontante Lat. Esq: %s\n"
        "Confrontante Lat. Dir: %s\n"
        "Coordenadas W: %s\n"
        "Coordenadas S: %s\n"
        "Área total: %s\n"
        "Área construída: %s\n"
        "Estado de conservação: %s\n"
        "Valoração: %s\n"
        "Data da valoração: %s\n"
        "CP Nº: %s\n",
        dados->endereco, dados->numero, dados->cidade, dados->estado, dados->regiao, dados->conf_frente, dados->conf_fundo,
        dados->conf_latEsq, dados->conf_latDir, dados->coord_W, dados->coord_S,
        dados->area_tot, dados->area_usada, dados->conserv_state,
        dados->valoracao, dados->data_valoracao, dados->CPNo
    );

    gtk_text_buffer_set_text(buffer, texto, -1);
}

//Função que faz o botão de selecionar arquivo funcionar quando clicado
static void on_button_clicked(GtkButton *button, gpointer user_data) 
{
    GtkWidget **widgets = (GtkWidget **)user_data;
    GtkWidget *window = widgets[0];
    GtkTextView *textview = GTK_TEXT_VIEW(widgets[1]);

    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Selecione o PDF",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancelar", GTK_RESPONSE_CANCEL,
        "_Abrir", GTK_RESPONSE_ACCEPT,
        NULL
    );

    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);


    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "PDF");
    gtk_file_filter_add_pattern(filter, "*.pdf");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_print("PDF selecionado: %s\n", filename);

        // Extração do texto
        extract_text(filename, "texto.txt");

        // Parser do TXT
        Dadostxt dados;
        parser_txt("texto.txt", &dados);

        if (criar_excel("laudo.xlsx", &dados)) {
            g_print("Planilha criada com sucesso em build/laudo.xlsx\n");
        } else {
            g_print("Erro ao gerar planilha...\n");
        }

        // Atualiza a GUI
        update_textview_with_laudo(textview, &dados);

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Outra função autoexplicativa (inicia o GUI)
void init_gui(int *argc, char ***argv) 
{
    gtk_init(argc, argv);

    // Cria a janela principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SAD Extractor");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Função que exibe os resultados
    GtkWidget *textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    gtk_widget_set_vexpand(textview, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);

    // Aqui cria o botão de selecionar pdf (visualmente)
    GtkWidget *button = gtk_button_new_with_label("Escolher PDF");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    GtkWidget *widgets[2] = { window, textview };
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), widgets);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}


