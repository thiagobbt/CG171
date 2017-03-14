#include <gtk/gtk.h>
#include <gdk/gdkwindow.h>
#include <iostream>
#include <vector>

static cairo_surface_t *surface = NULL;
GtkWidget *drawing_area;
GtkWidget *window_widget;
GtkWidget *new_object_widget;
GtkWidget *log_box;

GtkListStore *pol_coordinates;
GtkTreeIter pol_coordinates_iter;

GtkTextBuffer *log_buffer;
GtkTextMark *log_mark;
GtkTextIter log_iter;

void log_print(const char* text) {
    gtk_text_buffer_insert(log_buffer, &log_iter, text, -1);
}

/*Clear the surface, removing the scribbles*/
static void clear_surface() {
    cairo_t *cr;

    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

/*Creates the surface*/
static gboolean create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
    if (surface)
        cairo_surface_destroy(surface);

    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                                                CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width (widget),
                                                gtk_widget_get_allocated_height (widget));
    clear_surface();
    return TRUE;
}

/* Redraw the screen from the surface */
static gboolean redraw (GtkWidget *widget, cairo_t *cr, gpointer data){
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    return FALSE;
}

extern "C" G_MODULE_EXPORT void btn_new_cb(){
    log_print("Open new object window.\n");
    gtk_widget_show(new_object_widget);
}

extern "C" G_MODULE_EXPORT void btn_cancel_obj_cb(){
    log_print("Cancel new object.\n");
    gtk_widget_hide(new_object_widget);
}

extern "C" G_MODULE_EXPORT void btn_add_polygon_coord_cb(){
    log_print("Add polygon coordinates.\n");
    gtk_list_store_set (pol_coordinates, &pol_coordinates_iter,
                      0.0,
                      0.0,
                      0.0,
                      -1);
}

void close_window(GtkWidget *widget, gpointer window) {
    gtk_widget_destroy(GTK_WIDGET(widget));
    gtk_main_quit();
}


int main(int argc, char *argv[]){
    GtkBuilder  *gtkBuilder;
    gtk_init(&argc, &argv);

    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

    window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
    drawing_area = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawingarea1"));
    new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
    log_box = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "log_box"));
    pol_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));

    log_buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer((GtkTextView*)log_box, log_buffer);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(log_box), GTK_WRAP_NONE);
    log_mark = gtk_text_buffer_get_insert(log_buffer);
    gtk_text_buffer_get_iter_at_mark (log_buffer, &log_iter, log_mark);

    // Set utility hint so window floats by default
    gtk_window_set_type_hint((GtkWindow*)window_widget, GDK_WINDOW_TYPE_HINT_UTILITY);
    gtk_window_set_type_hint((GtkWindow*)new_object_widget, GDK_WINDOW_TYPE_HINT_UTILITY);

    g_signal_connect (drawing_area, "draw", G_CALLBACK (redraw), NULL);
    g_signal_connect (drawing_area,"configure-event", G_CALLBACK (create_surface), NULL);
    g_signal_connect (window_widget, "delete_event", G_CALLBACK (close_window), NULL);

    gtk_builder_connect_signals(gtkBuilder, NULL);
    gtk_widget_show_all(window_widget);


    gtk_main ();
    return 0;
}