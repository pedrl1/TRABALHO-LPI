#ifndef GUI_H
#define GUI_H

#include "parser.h"
#include <gtk/gtk.h>

void init_gui(int *argc, char ***argv);

void update_textview_with_laudo(GtkTextView *textview, const Dadostxt *dados);

#endif
