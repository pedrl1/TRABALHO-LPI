#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "pdf_utils.h"
#include "parser.h"

// Atualiza o TextView com os dados extraídos
void update_textview_with_laudo(GtkTextView *textview, const Dadostxt *dados) 
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    char texto[4096];
    snprintf(texto, sizeof(texto),
        "Endereço: %s\n"
        "Região: %s\n" 
        "Confrontante Frente: %s\n" 
        "Confrontante Fundo: %s\n" 
        "Confrontante Lat. Esq: %s\n"
        "Confrontante Lat. Dir: %s\n"
        "Coordenadas Geográficas: %s\n"
        "Área total: %s\n"
        "Área construída: %s\n"
        "Estado de conservação: %s\n"
        "Valoração: %s\n"
        "Data da valoração: %s\n"
        "CP Nº: %s\n",
        dados->endereco, dados->regiao, dados->conf_frente, dados->conf_fundo,
        dados->conf_latEsq, dados->conf_latDir, dados->coords,
        dados->area_tot, dados->area_usada, dados->conserv_state,
        dados->valoracao, dados->data_valoracao, dados->CPNo
    );

    gtk_text_buffer_set_text(buffer, texto, -1);
}

// Callback para o botão "Escolher PDF"
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

        // Atualiza a GUI
        update_textview_with_laudo(textview, &dados);

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Inicializa a GUI
void init_gui(int *argc, char ***argv) 
{
    gtk_init(argc, argv);

    // Janela principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SAD Extractor");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    // Box vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // TextView para exibir os resultados
    GtkWidget *textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    gtk_widget_set_vexpand(textview, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);

    // Botão para selecionar PDF
    GtkWidget *button = gtk_button_new_with_label("Escolher PDF");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Passando ponteiros para a callback
    GtkWidget *widgets[2] = { window, textview };
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), widgets);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}


