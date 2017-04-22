#include "Callbacks.h"
#include <gtk/gtk.h>

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    cb::init();
    gtk_main();

    return 0;
}
