#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "Callbacks.h"

GtkWidget *window_widget;
GtkWidget *new_object_widget;

GtkBuilder  *gtkBuilder;
GtkTextView *log_box;

GtkTextBuffer *log_buffer;

void log_print(const char* text) {
    GtkTextIter log_iter;
    GtkTextMark *log_mark = gtk_text_buffer_get_insert(log_buffer);
    gtk_text_buffer_get_iter_at_mark (log_buffer, &log_iter, log_mark);
    gtk_text_buffer_insert(log_buffer, &log_iter, text, -1);
    gtk_text_view_scroll_to_mark(log_box, log_mark, 0, false, 0, 0);
}

extern "C" G_MODULE_EXPORT void btn_new_cb(){
    log_print("Open new object window.\n");
    gtk_widget_show(new_object_widget);
}

extern "C" G_MODULE_EXPORT void btn_delete_cb(){
    log_print("Delete object\n");

    GtkTreeSelection *objects_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "objects_treeview_selection"));
    GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
    GtkTreeIter iter;

    if (!gtk_tree_selection_get_selected(objects_treeview_selection, NULL, &iter)) {
        log_print("   Error: Could not get selection\n");
        return;
    }
    gtk_list_store_remove(object_store, &iter);

}

extern "C" G_MODULE_EXPORT void btn_clear_cb(){
    log_print("Clear all objects\n");

    GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
    gtk_list_store_clear(object_store);
}

extern "C" G_MODULE_EXPORT void btn_cancel_obj_cb(){
    log_print("Cancel new object.\n");
    gtk_widget_hide(new_object_widget);
}

extern "C" G_MODULE_EXPORT void btn_add_polygon_coord_cb(){
    log_print("Add polygon coordinates.\n");

    GtkListStore *pol_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));

    GtkEntry *entry_pol_x = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_pol_x"));
    GtkEntry *entry_pol_y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_pol_y"));
    GtkEntry *entry_pol_z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_pol_z"));

    const char* x_c = (char*)gtk_entry_get_text(entry_pol_x);
    const char* y_c = (char*)gtk_entry_get_text(entry_pol_y);
    const char* z_c = (char*)gtk_entry_get_text(entry_pol_z);

    GtkTreeIter pol_coordinates_iter;

    gtk_list_store_append(pol_coordinates, &pol_coordinates_iter);
    gtk_list_store_set (pol_coordinates, &pol_coordinates_iter,
                      0, atof(x_c),
                      1, atof(y_c),
                      2, atof(z_c),
                      -1);
}

extern "C" G_MODULE_EXPORT void btn_delete_polygon_coord_cb(){
    log_print("Delete polygon coordinates.\n");

    GtkTreeSelection *polygon_tree_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "polygon_treeview_selection"));
    GtkListStore *pol_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));
    GtkTreeIter iter;

    if (!gtk_tree_selection_get_selected(polygon_tree_selection, NULL, &iter)) {
        log_print("   Error: Could not get selection\n");
        return;
    }
    gtk_list_store_remove(pol_coordinates, &iter);
}

extern "C" G_MODULE_EXPORT void btn_zoom_in_cb() {
    log_print("Zoom In\n");
}

extern "C" G_MODULE_EXPORT void btn_zoom_out_cb() {
    log_print("Zoom Out\n");
}

extern "C" G_MODULE_EXPORT void btn_right_cb() {
    log_print("Right\n");
}

extern "C" G_MODULE_EXPORT void btn_left_cb() {
    log_print("Left\n");
}

extern "C" G_MODULE_EXPORT void btn_up_cb() {
    log_print("Up\n");
}

extern "C" G_MODULE_EXPORT void btn_down_cb() {
    log_print("Down\n");
}

extern "C" G_MODULE_EXPORT void btn_add_point_cb() {
    log_print("Add point\n");

    GtkEntry *entry_point_name = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_point_name"));
    GtkEntry *entry_point_x = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_point_x"));
    GtkEntry *entry_point_y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_point_y"));
    // GtkEntry *entry_point_z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_point_z"));

    const char* name = (char*)gtk_entry_get_text(entry_point_name);

    if (strcmp(name, "") == 0) {
        log_print("   Error: Object name can't be empty\n");
        return;
    }

    const char* x_c = (char*)gtk_entry_get_text(entry_point_x);
    const char* y_c = (char*)gtk_entry_get_text(entry_point_y);
    // const char* z_c = (char*)gtk_entry_get_text(entry_point_z);

    double x = atof(x_c);
    double y = atof(y_c);
    // double z = atof(z_c);

    GtkColorChooser* btn_color = GTK_COLOR_CHOOSER(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "colorbutton_point"));
    GdkRGBA rgba;

    cairo_t *cr = cairo_create(surface);

    gtk_color_chooser_get_rgba(btn_color, &rgba);
    gdk_cairo_set_source_rgba(cr, &rgba);

    cairo_set_line_width(cr, 1);
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x+1, y+1);
    cairo_close_path(cr);
    cairo_stroke(cr);
    gtk_widget_queue_draw (window_widget);

    GtkListStore *obj_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
    GtkTreeIter obj_store_iter;
    gtk_list_store_append(obj_store, &obj_store_iter);
    gtk_list_store_set (obj_store, &obj_store_iter,
                      0, name,
                      1, "Point",
                      -1);

    gtk_widget_hide(new_object_widget);
}

extern "C" G_MODULE_EXPORT void btn_add_line_cb() {
    log_print("Add line\n");

    // GtkEntry *entry_line_name = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_name"));
    GtkEntry *entry_line_x1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_x1"));
    GtkEntry *entry_line_y1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_y1"));
    // GtkEntry *entry_line_z1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_z1"));
    GtkEntry *entry_line_x2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_x2"));
    GtkEntry *entry_line_y2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_y2"));
    // GtkEntry *entry_line_z2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_z2"));

    // const char* name = (char*)gtk_entry_get_text(entry_line_name);
    const char* x1_c = (char*)gtk_entry_get_text(entry_line_x1);
    const char* y1_c = (char*)gtk_entry_get_text(entry_line_y1);
    // const char* z1_c = (char*)gtk_entry_get_text(entry_line_z1);
    const char* x2_c = (char*)gtk_entry_get_text(entry_line_x2);
    const char* y2_c = (char*)gtk_entry_get_text(entry_line_y2);
    // const char* z2_c = (char*)gtk_entry_get_text(entry_line_z2);

    double x1 = atof(x1_c);
    double y1 = atof(y1_c);
    // double z1 = atof(z1_c);
    double x2 = atof(x2_c);
    double y2 = atof(y2_c);
    // double z2 = atof(z2_c);

    GtkColorChooser* btn_color = GTK_COLOR_CHOOSER(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "colorbutton_line"));
    GdkRGBA rgba;

    cairo_t *cr = cairo_create(surface);

    gtk_color_chooser_get_rgba(btn_color, &rgba);
    // gdk_cairo_set_source_rgba(cr, &rgba);
    cairo_set_source_rgb (cr, rgba.red, rgba.green, rgba.blue);

    cairo_set_line_width(cr, 1);
    cairo_move_to(cr, x1, y1);
    cairo_line_to(cr, x2, y2);
    cairo_close_path(cr);
    cairo_stroke(cr);
    gtk_widget_queue_draw (window_widget);

    gtk_widget_hide(new_object_widget);
}

extern "C" G_MODULE_EXPORT void btn_add_polygon_cb() {
    log_print("Add polygon\n");
    gtk_widget_hide(new_object_widget);
}


int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    GtkWidget *drawing_area;

    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

    window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
    drawing_area = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawingarea1"));
    new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
    log_box = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "log_box"));

    log_buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(log_box, log_buffer);
    gtk_text_view_set_wrap_mode(log_box, GTK_WRAP_NONE);

    // Set utility hint so window floats by default
    gtk_window_set_type_hint((GtkWindow*)window_widget, GDK_WINDOW_TYPE_HINT_UTILITY);
    gtk_window_set_type_hint((GtkWindow*)new_object_widget, GDK_WINDOW_TYPE_HINT_UTILITY);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(cb::redraw), NULL);
    g_signal_connect(drawing_area,"configure-event", G_CALLBACK(cb::create_surface), NULL);
    g_signal_connect(window_widget, "delete_event", G_CALLBACK(cb::close_window), NULL);

    gtk_builder_connect_signals(gtkBuilder, NULL);
    gtk_widget_show_all(window_widget);


    gtk_main ();
    return 0;
}