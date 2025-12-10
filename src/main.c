#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "gui.h"
#include "pdf_utils.h"

// aqui o aplicativo é "buildado" pelo GTK 
int main(int argc, char *argv[]) {
    init_gui(&argc, &argv);
    return 0;
}
