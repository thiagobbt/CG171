#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <iostream>
#include <cstring>
#include <gtk/gtk.h>
#include <fstream>
#include "Controller.h"
#include "DrawingManager.h"

namespace {
    static cairo_surface_t *surface = NULL;

    void clear_surface() {
        cairo_t *cr;

        cr = cairo_create(surface);

        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);

        cairo_destroy(cr);
    }

    Controller ctrl;
    GtkBuilder  *gtkBuilder;
    GtkTextBuffer *log_buffer;
    GtkWidget *window_widget;
}

namespace cb {
    static bool create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
        if (surface)
            cairo_surface_destroy(surface);

        surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                                                    CAIRO_CONTENT_COLOR,
                                                    gtk_widget_get_allocated_width(widget),
                                                    gtk_widget_get_allocated_height(widget));
        DrawingManager& dm = DrawingManager::instance();
        dm.setSurface(surface);

        clear_surface();
        return TRUE;
    }

    static bool redraw (GtkWidget *widget, cairo_t *cr, gpointer data){
        clear_surface();
        DrawingManager::instance().redraw();
        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);

        return FALSE;
    }

    void log_print(const char* text) {
        GtkTextIter log_iter;
        GtkTextMark *log_mark = gtk_text_buffer_get_insert(log_buffer);
        gtk_text_buffer_get_iter_at_mark (log_buffer, &log_iter, log_mark);
        gtk_text_buffer_insert(log_buffer, &log_iter, text, -1);
        GtkTextView* log_box = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "log_box"));
        gtk_text_view_scroll_to_mark(log_box, log_mark, 0, false, 0, 0);
    }

    void add_to_obj_list(std::string name, std::string type) {
        GtkListStore *obj_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
        GtkTreeIter obj_store_iter;
        gtk_list_store_append(obj_store, &obj_store_iter);
        gtk_list_store_set (obj_store, &obj_store_iter,
                          0, name.c_str(),
                          1, type.c_str(),
                          -1);
    }

    static void btn_new_cb(){
        log_print("Open new object window.\n");
        GtkWidget *new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
        gtk_widget_show(new_object_widget);
    }

    static void btn_delete_cb(){
        log_print("Delete object\n");

        GtkTreeSelection *objects_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "objects_treeview_selection"));
        GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
        GtkTreeIter iter;

        if (!gtk_tree_selection_get_selected(objects_treeview_selection, NULL, &iter)) {
            log_print("   Error: Could not get selection\n");
            return;
        }

        char* name;

        gtk_tree_model_get(GTK_TREE_MODEL(object_store), &iter, 0, &name, -1);

        ctrl.delete_obj(std::string(name));

        gtk_widget_queue_draw(window_widget);

        gtk_list_store_remove(object_store, &iter);

    }

    static void btn_clear_cb(){
        log_print("Clear all objects\n");

        ctrl.clear_world();
        gtk_widget_queue_draw(window_widget);

        GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
        gtk_list_store_clear(object_store);
    }

    static void btn_cancel_obj_cb(){
        log_print("Cancel new object.\n");
        GtkWidget *new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
        gtk_widget_hide(new_object_widget);
    }

    static void btn_add_polygon_coord_cb(){
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

    static void btn_add_curve_coord_cb(){
        log_print("Add curve coordinates.\n");

        GtkListStore *curve_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));

        GtkEntry *entry_curve_x = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_curve_x"));
        GtkEntry *entry_curve_y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_curve_y"));
        GtkEntry *entry_curve_z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_curve_z"));

        const char* x_c = (char*)gtk_entry_get_text(entry_curve_x);
        const char* y_c = (char*)gtk_entry_get_text(entry_curve_y);
        const char* z_c = (char*)gtk_entry_get_text(entry_curve_z);

        GtkTreeIter curve_coordinates_iter;

        gtk_list_store_append(curve_coordinates, &curve_coordinates_iter);
        gtk_list_store_set (curve_coordinates, &curve_coordinates_iter,
                          0, atof(x_c),
                          1, atof(y_c),
                          2, atof(z_c),
                          -1);
    }

    static void btn_delete_polygon_coord_cb(){
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

    static void btn_delete_curve_coord_cb(){
        log_print("Delete curve coordinates.\n");

        GtkTreeSelection *curve_tree_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "curve_treeview_selection"));
        GtkListStore *pol_coordinates = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));
        GtkTreeIter iter;

        if (!gtk_tree_selection_get_selected(curve_tree_selection, NULL, &iter)) {
            log_print("   Error: Could not get selection\n");
            return;
        }
        gtk_list_store_remove(pol_coordinates, &iter);
    }

    static void btn_zoom_in_cb() {
        log_print("Zoom In\n");
        ctrl.zoom_in(1.2);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_zoom_out_cb() {
        log_print("Zoom Out\n");
        ctrl.zoom_out(1.2);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_right_cb() {
        log_print("Right\n");
        ctrl.pan_x(20);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_left_cb() {
        log_print("Left\n");
        ctrl.pan_x(-20);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_up_cb() {
        log_print("Up\n");
        ctrl.pan_y(20);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_down_cb() {
        log_print("Down\n");
        ctrl.pan_y(-20);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_rotate_r_cb() {
        log_print("Rotate right\n");
        ctrl.rotate(-15);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_rotate_l_cb() {
        log_print("Rotate left\n");
        ctrl.rotate(15);
        gtk_widget_queue_draw(window_widget);
    }

    static void btn_add_point_cb() {
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

        gtk_color_chooser_get_rgba(btn_color, &rgba);

        gtk_widget_queue_draw(window_widget);

        bool success = ctrl.add_point(name, {x, y}, utils::Color{rgba.red, rgba.green, rgba.blue});

        if (!success) {
            log_print("   Error: Object name repetition\n");
            return;
        }

        add_to_obj_list(name, "Point");

        GtkWidget *new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
        gtk_widget_hide(new_object_widget);
    }

    static void btn_add_line_cb() {
        log_print("Add line\n");

        GtkEntry *entry_line_name = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_name"));
        GtkEntry *entry_line_x1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_x1"));
        GtkEntry *entry_line_y1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_y1"));
        // GtkEntry *entry_line_z1 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_z1"));
        GtkEntry *entry_line_x2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_x2"));
        GtkEntry *entry_line_y2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_y2"));
        // GtkEntry *entry_line_z2 = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_line_z2"));

        const char* name = (char*)gtk_entry_get_text(entry_line_name);

        if (strcmp(name, "") == 0) {
            log_print("   Error: Object name can't be empty\n");
            return;
        }

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
        gtk_color_chooser_get_rgba(btn_color, &rgba);

        bool success = ctrl.add_line(name, {x1, y1}, {x2, y2}, utils::Color{rgba.red, rgba.green, rgba.blue});

        if (!success) {
            log_print("   Error: Object name repetition\n");
            return;
        }

        add_to_obj_list(name, "Line");

        gtk_widget_queue_draw (window_widget);

        GtkWidget *new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
        gtk_widget_hide(new_object_widget);
    }

    std::vector<Coordinate> pol_coord_vector;

    int append_pol_coord_vector(GtkTreeModel *model,
                    GtkTreePath  *path,
                    GtkTreeIter  *iter,
                    gpointer      user_data) {

        double x, y;

        gtk_tree_model_get (model, iter,
                            0, &x,
                            1, &y,
                            // 2, &z,
                            -1);

        pol_coord_vector.emplace_back(x, y);

        return 0; // Continue calling
    }

    static void btn_add_polygon_cb() {
        log_print("Add polygon\n");

        GtkTreeModel *pol_coordinates = GTK_TREE_MODEL(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));

        GtkTreeIter iter;
        gtk_tree_model_get_iter_first(pol_coordinates, &iter);

        pol_coord_vector.clear();
        gtk_tree_model_foreach(pol_coordinates, append_pol_coord_vector, NULL);

        GtkEntry *entry_line_name = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_pol_name"));
        const char* name = (char*)gtk_entry_get_text(entry_line_name);

        if (strcmp(name, "") == 0) {
            log_print("   Error: Object name can't be empty\n");
            return;
        }

        GtkColorChooser* btn_color = GTK_COLOR_CHOOSER(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "colorbutton_pol"));
        GdkRGBA rgba;
        gtk_color_chooser_get_rgba(btn_color, &rgba);

        GtkToggleButton *btn_fill = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "checkbutton_pol_fill"));
        bool fill = gtk_toggle_button_get_active(btn_fill);
        
        bool success = ctrl.add_polygon(name, pol_coord_vector, utils::Color{rgba.red, rgba.green, rgba.blue}, fill);

        if (!success) {
            log_print("   Error: Object name repetition\n");
            return;
        }

        gtk_list_store_clear(GTK_LIST_STORE(pol_coordinates));

        add_to_obj_list(name, "Polygon");

        gtk_widget_queue_draw(window_widget);

        GtkWidget *new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
        gtk_widget_hide(new_object_widget);
    }

    static void btn_add_curve_cb() {
        log_print("Add curve\n");

        GtkTreeModel *curve_coordinates = GTK_TREE_MODEL(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "list_store_pol_coordinates"));

        GtkTreeIter iter;
        gtk_tree_model_get_iter_first(curve_coordinates, &iter);

        pol_coord_vector.clear();
        gtk_tree_model_foreach(curve_coordinates, append_pol_coord_vector, NULL);

        if (pol_coord_vector.size() < 4) {
            log_print("   Error: At least 4 points are required\n");
            return;
        }

        GtkEntry *entry_line_name = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_curve_name"));
        const char* name = (char*)gtk_entry_get_text(entry_line_name);

        if (strcmp(name, "") == 0) {
            log_print("   Error: Object name can't be empty\n");
            return;
        }

        GtkColorChooser* btn_color = GTK_COLOR_CHOOSER(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "colorbutton_curve"));
        GdkRGBA rgba;
        gtk_color_chooser_get_rgba(btn_color, &rgba);

        bool success;

        GtkToggleButton *radio_bezier = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "radiobutton_bezier"));

        if (gtk_toggle_button_get_active(radio_bezier)) {
            success = ctrl.add_bezier_curve(name, pol_coord_vector, utils::Color{rgba.red, rgba.green, rgba.blue});
            if (success) {
                add_to_obj_list(name, "Bezier Curve");
            }
        } else {
            success = ctrl.add_bspline_curve(name, pol_coord_vector, utils::Color{rgba.red, rgba.green, rgba.blue});
            if (success) {
                add_to_obj_list(name, "B-Spline Curve");
            }
        }

        if (!success) {
            log_print("   Error: Object name repetition\n");
            return;
        }

        gtk_list_store_clear(GTK_LIST_STORE(curve_coordinates));

        gtk_widget_queue_draw(window_widget);

        GtkWidget *new_object_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "new_object_window"));
        gtk_widget_hide(new_object_widget);
    }

    static void btn_transform_cb() {
        log_print("Open transform window.\n");

        GtkWidget* transform_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "transform_window"));
        gtk_widget_show(transform_widget);
    }

    static void btn_transform_cancel_cb() {
        log_print("Cancel transform.\n");

        GtkWidget* transform_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "transform_window"));
        gtk_widget_hide(transform_widget);
    }

    static void btn_translate_obj_cb() {
        log_print("Translate object.\n");

        GtkEntry *entry_translate_dx = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_translate_dx"));
        GtkEntry *entry_translate_dy = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_translate_dy"));
        // GtkEntry *entry_translate_dz = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_translate_dz"));

        const char* dx_c = (char*)gtk_entry_get_text(entry_translate_dx);
        const char* dy_c = (char*)gtk_entry_get_text(entry_translate_dy);
        // const char* dz_c = (char*)gtk_entry_get_text(entry_translate_dz);

        double dx = atof(dx_c);
        double dy = atof(dy_c);
        // double dz = atof(dz_c);

        GtkTreeSelection *objects_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "objects_treeview_selection"));
        GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
        GtkTreeIter iter;

        if (!gtk_tree_selection_get_selected(objects_treeview_selection, NULL, &iter)) {
            log_print("   Error: Could not get selection\n");
            return;
        }

        char* name;
        gtk_tree_model_get(GTK_TREE_MODEL(object_store), &iter, 0, &name, -1);

        ctrl.move_obj(string(name), dx, dy);

        gtk_widget_queue_draw(window_widget);

        GtkWidget* transform_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "transform_window"));
        gtk_widget_hide(transform_widget);
    }

    static void btn_scale_obj_cb() {
        log_print("Scale object.\n");

        GtkEntry *entry_scale_sx = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_scale_sx"));
        GtkEntry *entry_scale_sy = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_scale_sy"));
        // GtkEntry *entry_scale_sz = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_scale_sz"));

        const char* sx_c = (char*)gtk_entry_get_text(entry_scale_sx);
        const char* sy_c = (char*)gtk_entry_get_text(entry_scale_sy);
        // const char* sz_c = (char*)gtk_entry_get_text(entry_scale_sz);

        double sx = atof(sx_c);
        double sy = atof(sy_c);
        // double sz = atof(sz_c);

        GtkTreeSelection *objects_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "objects_treeview_selection"));
        GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
        GtkTreeIter iter;

        if (!gtk_tree_selection_get_selected(objects_treeview_selection, NULL, &iter)) {
            log_print("   Error: Could not get selection\n");
            return;
        }

        char* name;
        gtk_tree_model_get(GTK_TREE_MODEL(object_store), &iter, 0, &name, -1);

        ctrl.scale_obj(string(name), sx, sy);

        gtk_widget_queue_draw(window_widget);

        GtkWidget* transform_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "transform_window"));
        gtk_widget_hide(transform_widget);
    }

    static void btn_rotate_obj_cb() {
        log_print("Rotate object.\n");

        GtkEntry *entry_rotate_angle = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_rotate_angle"));
        const char* rotate_angle_c = (char*)gtk_entry_get_text(entry_rotate_angle);
        double rotate_angle = atof(rotate_angle_c);

        GtkTreeSelection *objects_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "objects_treeview_selection"));
        GtkListStore *object_store = GTK_LIST_STORE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "object_store"));
        GtkTreeIter iter;

        if (!gtk_tree_selection_get_selected(objects_treeview_selection, NULL, &iter)) {
            log_print("   Error: Could not get selection\n");
            return;
        }

        char* name;
        gtk_tree_model_get(GTK_TREE_MODEL(object_store), &iter, 0, &name, -1);

        GtkToggleButton *radio_rotate_world_center = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "radio_rotate_world_center"));
        GtkToggleButton *radio_rotate_obj_center = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "radio_rotate_obj_center"));
        // GtkToggleButton *radio_rotate_point = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "radio_rotate_point"));

        if (gtk_toggle_button_get_active(radio_rotate_obj_center)) {
            ctrl.rotate_obj(string(name), rotate_angle, 0, 0, false);
        } else if (gtk_toggle_button_get_active(radio_rotate_world_center)) {
            ctrl.rotate_obj(string(name), rotate_angle, 0, 0, true);
        } else {
            GtkEntry *entry_rotate_x = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_rotate_x"));
            GtkEntry *entry_rotate_y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_rotate_y"));
            // GtkEntry *entry_rotate_z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "entry_rotate_z"));

            const char* x_c = (char*)gtk_entry_get_text(entry_rotate_x);
            const char* y_c = (char*)gtk_entry_get_text(entry_rotate_y);
            // const char* z_c = (char*)gtk_entry_get_text(entry_rotate_z);

            double x = atof(x_c);
            double y = atof(y_c);
            // double z = atof(z_c);
            
            ctrl.rotate_obj(string(name), rotate_angle, x, y, true);
        }

        gtk_widget_queue_draw(window_widget);

        GtkWidget* transform_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "transform_window"));
        gtk_widget_hide(transform_widget);
    }

    static void export_obj() {
        log_print("Export Waveform .obj\n");

        GtkWidget *dialog;
        gint res;

        dialog = gtk_file_chooser_dialog_new("Open File",
            GTK_WINDOW(window_widget), GTK_FILE_CHOOSER_ACTION_SAVE,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Open", GTK_RESPONSE_ACCEPT,
            NULL);

        res = gtk_dialog_run (GTK_DIALOG (dialog));
        if (res == GTK_RESPONSE_ACCEPT) {
            char *filename;
            GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
            filename = gtk_file_chooser_get_filename (chooser);

            std::ofstream outfile(filename, std::ofstream::trunc);
            ctrl.export_obj(outfile);
            outfile.close();

            g_free (filename);
        }

        gtk_widget_destroy (dialog);
    }

    static void import_obj() {
        log_print("Import Waveform .obj\n");

        GtkWidget *dialog;
        gint res;

        dialog = gtk_file_chooser_dialog_new("Open File",
            GTK_WINDOW(window_widget), GTK_FILE_CHOOSER_ACTION_OPEN,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Open", GTK_RESPONSE_ACCEPT,
            NULL);

        res = gtk_dialog_run (GTK_DIALOG (dialog));
        if (res == GTK_RESPONSE_ACCEPT) {
            char *filename;
            GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
            filename = gtk_file_chooser_get_filename (chooser);

            std::ifstream infile(filename, std::ifstream::binary);
            ctrl.import_obj(infile);
            infile.close();

            g_free (filename);
        }

        gtk_widget_destroy (dialog);

        gtk_widget_queue_draw(window_widget);
    }

    static bool set_clipping_cs() {
        log_print("Set line clipping to Cohen-Sutherland\n");
        ctrl.set_clipping_cs();
        return false;
    }

    static bool set_clipping_lb() {
        log_print("Set line clipping to Liang-Barsky\n");
        ctrl.set_clipping_lb();
        return false;
    }

    static bool key_handler(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
        switch (event->keyval) {
            case GDK_KEY_Up: btn_up_cb(); return true;
            case GDK_KEY_Down: btn_down_cb(); return true;
            case GDK_KEY_Left: btn_left_cb(); return true;
            case GDK_KEY_Right: btn_right_cb(); return true;
            case GDK_KEY_plus: btn_zoom_in_cb(); break;
            case GDK_KEY_minus: btn_zoom_out_cb(); break;
            case GDK_KEY_q: gtk_main_quit(); break;
            case GDK_KEY_r:
                ctrl.rotate_obj("test_polygon", 15, 0, 0, false);
                gtk_widget_queue_draw(window_widget);
                break;
            case GDK_KEY_R:
                ctrl.rotate_obj("test_polygon", -15, 0, 0, false);
                gtk_widget_queue_draw(window_widget);
                break;
            case GDK_KEY_t:
                ctrl.move_obj("test_polygon", 30, 30);
                gtk_widget_queue_draw(window_widget);
                break;
            case GDK_KEY_T:
                ctrl.move_obj("test_polygon", -30, -30);
                gtk_widget_queue_draw(window_widget);
                break;
            case GDK_KEY_z:
                export_obj();
                break;
            case GDK_KEY_d:
                log_print("Add test objects\n");

                if (!ctrl.add_point("test_point", {20, 20}, utils::Color{1, 0, 0})) {
                    log_print("   Error: Object name repetition\n");
                    return false;
                }

                add_to_obj_list("test_point", "Point");

                gtk_widget_queue_draw (window_widget);
                break;
            case GDK_KEY_p:
                log_print("Add test objects\n");

                if (!ctrl.add_polygon("test_polygon", {
                        {150, 150},
                        {150, 250},
                        {250, 250},
                        {250, 150},
                    }, {1, 0, 0}, true) ||
                 !ctrl.add_line("test_line", {0, 0}, {400, 400}, utils::Color{0, 1, 0})) {
                    log_print("   Error: Object name repetition\n");
                    return false;
                }

                add_to_obj_list("test_polygon", "Polygon");
                add_to_obj_list("test_line", "Line");

                gtk_widget_queue_draw (window_widget);
                break;
            case GDK_KEY_c:
                log_print("Add test bezier curve\n");

                if (!ctrl.add_bezier_curve("test_curve", {
                        {0, 200},
                        {100, 300},
                        {300, 100},
                        {400, 200},
                        {350, 150},
                        {150, 350},
                        {0, 200},
                        }, {1, 0, 0})) {
                    log_print("   Error: Object name repetition\n");
                    return false;
                }

                add_to_obj_list("test_bezier", "Bezier Curve");

                gtk_widget_queue_draw (window_widget);
                break;
            case GDK_KEY_C:
                log_print("Add test bspline curve\n");

                if (!ctrl.add_bspline_curve("test_spline", 
                        {
                            {250,113},
                            {150,113},
                            {100,200},
                            {150,287},
                            {250,287},
                            {300,200},
                            {250,113},
                            {150,113},
                            {100,200},
                        }
                    , {1, 0, 0})) {
                    log_print("   Error: Object name repetition\n");
                    return false;
                }

                add_to_obj_list("test_curve", "B-Spline Curve");

                gtk_widget_queue_draw (window_widget);
                break;
        }

        return false;
    }


    static bool treeview_button_handler(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
        if (event->button == 3) {
            GtkTreePath *path;
            gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), event->x, event->y, &path, NULL, NULL, NULL);

            if (path == NULL) return false;

            gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), path, NULL, false);

            GtkMenu* menu_transform = GTK_MENU(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "menu_transform"));

            gtk_menu_popup(menu_transform, NULL, NULL, NULL, NULL, 3, event->time);
        }

        return false;
    }

    void init() {
        gtkBuilder = gtk_builder_new();
        gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);

        log_buffer = gtk_text_buffer_new(NULL);

        GtkTextView* log_box = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "log_box"));
        gtk_text_view_set_buffer(log_box, log_buffer);
        gtk_text_view_set_wrap_mode(log_box, GTK_WRAP_NONE);

        GtkWidget* drawing_area = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawingarea1"));
        g_signal_connect(drawing_area, "draw", G_CALLBACK(redraw), NULL);
        g_signal_connect(drawing_area,"configure-event", G_CALLBACK(create_surface), NULL);

        window_widget = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "main_window"));
        g_signal_connect(window_widget, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(window_widget, "key_press_event", G_CALLBACK(key_handler), NULL);

        GtkWidget *treeview_objects = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "treeview_objects"));
        g_signal_connect(treeview_objects, "button_press_event", G_CALLBACK(treeview_button_handler), NULL);

        GtkWidget *btn_translate_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_translate_cancel"));
        g_signal_connect(btn_translate_cancel, "button_press_event", G_CALLBACK(btn_transform_cancel_cb), NULL);

        GtkWidget *btn_scale_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_scale_cancel"));
        g_signal_connect(btn_scale_cancel, "button_press_event", G_CALLBACK(btn_transform_cancel_cb), NULL);

        GtkWidget *btn_rotate_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_rotate_cancel"));
        g_signal_connect(btn_rotate_cancel, "button_press_event", G_CALLBACK(btn_transform_cancel_cb), NULL);

        GtkWidget *btn_new_obj = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_new_obj"));
        g_signal_connect(btn_new_obj, "button_press_event", G_CALLBACK(btn_new_cb), NULL);

        GtkWidget *btn_delete_obj = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_delete_obj"));
        g_signal_connect(btn_delete_obj, "button_press_event", G_CALLBACK(btn_delete_cb), NULL);

        GtkWidget *btn_clear_objs = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_clear_objs"));
        g_signal_connect(btn_clear_objs, "button_press_event", G_CALLBACK(btn_clear_cb), NULL);

        GtkWidget *btn_point_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_point_cancel"));
        g_signal_connect(btn_point_cancel, "button_press_event", G_CALLBACK(btn_cancel_obj_cb), NULL);

        GtkWidget *btn_line_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_line_cancel"));
        g_signal_connect(btn_line_cancel, "button_press_event", G_CALLBACK(btn_cancel_obj_cb), NULL);

        GtkWidget *btn_polygon_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_polygon_cancel"));
        g_signal_connect(btn_polygon_cancel, "button_press_event", G_CALLBACK(btn_cancel_obj_cb), NULL);

        GtkWidget *btn_curve_cancel = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_curve_cancel"));
        g_signal_connect(btn_curve_cancel, "button_press_event", G_CALLBACK(btn_cancel_obj_cb), NULL);

        GtkWidget *btn_point_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_point_ok"));
        g_signal_connect(btn_point_ok, "button_press_event", G_CALLBACK(btn_add_point_cb), NULL);

        GtkWidget *btn_line_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_line_ok"));
        g_signal_connect(btn_line_ok, "button_press_event", G_CALLBACK(btn_add_line_cb), NULL);

        GtkWidget *btn_polygon_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_polygon_ok"));
        g_signal_connect(btn_polygon_ok, "button_press_event", G_CALLBACK(btn_add_polygon_cb), NULL);

        GtkWidget *btn_curve_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_curve_ok"));
        g_signal_connect(btn_curve_ok, "button_press_event", G_CALLBACK(btn_add_curve_cb), NULL);

        GtkWidget *btn_polygon_add_coord = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_polygon_add_coord"));
        g_signal_connect(btn_polygon_add_coord, "button_press_event", G_CALLBACK(btn_add_polygon_coord_cb), NULL);

        GtkWidget *btn_curve_add_coord = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_curve_add_coord"));
        g_signal_connect(btn_curve_add_coord, "button_press_event", G_CALLBACK(btn_add_curve_coord_cb), NULL);

        GtkWidget *btn_polygon_delete_coord = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_polygon_delete_coord"));
        g_signal_connect(btn_polygon_delete_coord, "button_press_event", G_CALLBACK(btn_delete_polygon_coord_cb), NULL);

        GtkWidget *btn_curve_delete_coord = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_curve_delete_coord"));
        g_signal_connect(btn_curve_delete_coord, "button_press_event", G_CALLBACK(btn_delete_curve_coord_cb), NULL);

        GtkWidget *btn_pan_up = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_pan_up"));
        g_signal_connect(btn_pan_up, "button_press_event", G_CALLBACK(btn_up_cb), NULL);

        GtkWidget *btn_pan_down = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_pan_down"));
        g_signal_connect(btn_pan_down, "button_press_event", G_CALLBACK(btn_down_cb), NULL);

        GtkWidget *btn_pan_left = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_pan_left"));
        g_signal_connect(btn_pan_left, "button_press_event", G_CALLBACK(btn_left_cb), NULL);

        GtkWidget *btn_pan_right = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_pan_right"));
        g_signal_connect(btn_pan_right, "button_press_event", G_CALLBACK(btn_right_cb), NULL);

        GtkWidget *btn_zoom_in = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_zoom_in"));
        g_signal_connect(btn_zoom_in, "button_press_event", G_CALLBACK(btn_zoom_in_cb), NULL);

        GtkWidget *btn_zoom_out = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_zoom_out"));
        g_signal_connect(btn_zoom_out, "button_press_event", G_CALLBACK(btn_zoom_out_cb), NULL);

        GtkWidget *btn_rotate_r = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_rotate_r"));
        g_signal_connect(btn_rotate_r, "button_press_event", G_CALLBACK(btn_rotate_r_cb), NULL);

        GtkWidget *btn_rotate_l = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_rotate_l"));
        g_signal_connect(btn_rotate_l, "button_press_event", G_CALLBACK(btn_rotate_l_cb), NULL);

        GtkWidget *btn_translate_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_translate_ok"));
        g_signal_connect(btn_translate_ok, "button_press_event", G_CALLBACK(btn_translate_obj_cb), NULL);

        GtkWidget *btn_scale_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_scale_ok"));
        g_signal_connect(btn_scale_ok, "button_press_event", G_CALLBACK(btn_scale_obj_cb), NULL);

        GtkWidget *btn_rotate_ok = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_rotate_ok"));
        g_signal_connect(btn_rotate_ok, "button_press_event", G_CALLBACK(btn_rotate_obj_cb), NULL);

        GtkWidget *menuitem_transform = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "menuitem_transform"));
        g_signal_connect(menuitem_transform, "activate", G_CALLBACK(btn_transform_cb), NULL);

        GtkWidget *btn_import_obj = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_import_obj"));
        g_signal_connect(btn_import_obj, "button_press_event", G_CALLBACK(import_obj), NULL);

        GtkWidget *btn_export_obj = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "btn_export_obj"));
        g_signal_connect(btn_export_obj, "button_press_event", G_CALLBACK(export_obj), NULL);

        GtkToggleButton *radiobutton_cs = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "radiobutton_cs"));
        g_signal_connect(radiobutton_cs, "button_press_event", G_CALLBACK(set_clipping_cs), NULL);

        GtkToggleButton *radiobutton_lb = GTK_TOGGLE_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "radiobutton_lb"));
        g_signal_connect(radiobutton_lb, "button_press_event", G_CALLBACK(set_clipping_lb), NULL);

        gtk_widget_show_all(window_widget);
    }
}

#endif /* CALLBACKS_H */
