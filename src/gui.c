#include <stdio.h>
#include <stdlib.h>
#include "gui.h"
#include "pdf_utils.h"

static void on_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Selecione o PDF",
                                                    GTK_WINDOW(window),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Cancelar", GTK_RESPONSE_CANCEL,
                                                    "_Abrir", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "PDF");
    gtk_file_filter_add_pattern(filter, "*.pdf");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_print("PDF selecionado: %s\n", filename);

        extract_text(filename, "texto.txt");  // chama a função de pdf_utils

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void init_gui(int *argc, char ***argv) {
    gtk_init(argc, argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SAD Extractor");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    GtkWidget *button = gtk_button_new_with_label("Escolher PDF");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);

    gtk_container_add(GTK_CONTAINER(window), button);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}
