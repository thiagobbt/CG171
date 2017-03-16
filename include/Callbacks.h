#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_

#include <gtk/gtk.h>
#include <iostream>

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
}

namespace cb {
    inline gboolean create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
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

    /* Redraw the screen from the surface */
    inline gboolean redraw (GtkWidget *widget, cairo_t *cr, gpointer data){
        clear_surface();
        DrawingManager::instance().redraw();
        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);

        return FALSE;
    }

    inline void close_window(GtkWidget *widget, gpointer window) {
        gtk_widget_destroy(GTK_WIDGET(widget));
        gtk_main_quit();
    }
}

#endif /* _CALLBACKS_H_ */
