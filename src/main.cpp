#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Callbacks.h"
#include "Controller.h"
#include "DrawingManager.h"

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    cb::init();
    gtk_main();

    return 0;
}