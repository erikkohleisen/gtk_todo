#include <gtk/gtk.h>

typedef struct callBackObject {
    GtkEntryBuffer *buf;
    GtkWidget *list;
} callBackObject;

callBackObject cbObject;

static void list_box_row_activated (GtkListBox* self, GtkListBoxRow* row, gpointer user_data) {
    gtk_list_box_remove (self, (GtkWidget*) row);
}

static void add_item_to_listBox (GtkWidget *widget, gpointer data)
{
    (void)widget;

    callBackObject *cb = (callBackObject*) data;
    GtkEntryBuffer *buffer = (GtkEntryBuffer*) cb->buf;
    GtkListBox *listBox = (GtkListBox*) cb->list;
    GtkWidget * row = gtk_list_box_row_new ();

    const char *text = gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (buffer));

    GtkWidget *label;
    label = gtk_label_new (text);
    gtk_list_box_row_set_child (GTK_LIST_BOX_ROW (row), label);

    gtk_list_box_append (listBox, row);

    gtk_entry_buffer_delete_text (buffer, 0, -1);
}

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *input;
    GtkWidget *listBox;
    GtkWidget *label;
    GtkWidget *separator;
    
    GtkEntryBuffer *buffer;

    // create the window
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "My TODO App");
    gtk_window_set_default_size (GTK_WINDOW (window), 600, 700);

    // create container box and set it as first child to window
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_valign (box, GTK_ALIGN_START);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_window_set_child (GTK_WINDOW (window), box);
    
    // create the container grid for input
    grid = gtk_grid_new ();
    gtk_grid_set_column_spacing (GTK_GRID (grid), 10);
    gtk_widget_set_margin_top (grid, 10);
    // insert grid into first element in box
    gtk_box_append (GTK_BOX (box), grid);

    separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append(GTK_BOX (box), separator);

    listBox = gtk_list_box_new ();
    gtk_list_box_set_show_separators (GTK_LIST_BOX (listBox), true);
    label = gtk_label_new ("TODO list will be displayed here");
    gtk_list_box_set_placeholder (GTK_LIST_BOX (listBox), label);
    gtk_list_box_set_activate_on_single_click (GTK_LIST_BOX (listBox), true);
    
    gtk_box_append(GTK_BOX (box), listBox);

    // create inputBuffer
    buffer = gtk_entry_buffer_new (NULL, 0);

    // create input field
    input = gtk_entry_new_with_buffer (buffer);
    gtk_entry_set_placeholder_text (GTK_ENTRY (input), "Enter your new TODO!");

    //create the Callback Object
    cbObject.buf = buffer;
    cbObject.list = listBox;

    // create a button
    button = gtk_button_new_with_label ("Add");
    // connect buttons signal
    g_signal_connect (
        button, 
        "clicked", 
        G_CALLBACK (add_item_to_listBox), 
        &cbObject
    );
    g_signal_connect (
        input,
        "activate",
        G_CALLBACK (add_item_to_listBox),
        &cbObject
    );
    g_signal_connect(
        listBox, 
        "row-activated", 
        G_CALLBACK (list_box_row_activated), 
        NULL
    );

    // insert input and button into grid
    gtk_grid_attach (GTK_GRID (grid), input, 0, 0, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

    // finally show the window
    gtk_widget_show (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("com.github.erikkohleisen.mytodoapp", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
