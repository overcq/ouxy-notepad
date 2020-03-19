/******************************************************************************/
OBFUSCATE( Q_builder_Z_note_tab_container );
OBFUSCATE( Q_builder_Z_books_tree );
OBFUSCATE( Q_builder_Z_books_tree_renderer_text );
OBFUSCATE( Q_builder_Z_notes_tree );
OBFUSCATE( Q_builder_Z_notes_tree_renderer_text );
OBFUSCATE( Q_builder_Z_note );
OBFUSCATE( Q_builder_Z_note_attr );
OBFUSCATE( Q_builder_Z_note_date );
OBFUSCATE( Q_builder_Z_new_tab_names );
OBFUSCATE( Q_builder_Z_search );
OBFUSCATE( Q_builder_Z_search_inexact );
OBFUSCATE( Q_builder_Z_search_exact );
OBFUSCATE( Q_builder_Z_search_exact_chars );
OBFUSCATE( Q_builder_Z_search_next );
OBFUSCATE( Q_builder_Z_search_previous );
//=============================================================================
GtkNotebook *E_note_tab_Q_note_tab_S;
GtkTreeModel *E_note_tab_Q_note_tab_S_books_tree_store, *E_note_tab_Q_note_tab_S_new_tab_names_list_store;
GtkTextTagTable *E_note_tab_Q_note_S_tag_table;
GtkTextTag *E_note_tab_Q_note_Z_tag_S_search;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GArray *E_note_tab_Q_note_tab_S_ext_data;
int E_note_tab_Q_note_tab_S_current_tab; ///wartość ustawiana dla systemu procedur ‟gtk+”, w ‹raporcie› ‟gtk+”, czyli po wizualnym zaliczeniu przez ‟gtk+”, a nie dla systemu procedur bezpośrednich tego programu, gdy już było i tak wiadomo, że karta jest usuwana.
bool E_note_tab_U_ignore_change; ///ponieważ jest dokonywana nie przez operatora, nie w modyfikacji danych.
unsigned E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S = 0;
#ifdef C_kdb_focus_wa
unsigned E_note_tab_I_kbd_focus_wa_S = 0;
bool E_note_tab_I_kbd_focus_wa_U_ignore = no;
#endif
//=============================================================================
gint64
E_note_tab_I_uniq_date_uid( gint64 d
){  while( g_hash_table_contains( E_file_S_uids, &d ))
        d++;
    g_hash_table_add( E_file_S_uids, &d );
    return d;
}
//==============================================================================
void
E_note_tab_I_unignore_change( void
){  E_main_Z_gtk_I_process_events();
    E_note_tab_U_ignore_change = no;
}
//=============================================================================
_EXPORT_OBFUSCATE
void
E_note_tab_Q_note_tab_Z_gtk_X_switch_page( GtkNotebook *notebook
, GtkWidget *child
, unsigned tab
, void *data
){  if( !E_note_tab_U_ignore_change )
    {   struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
        GtkWidget *focused = gtk_window_get_focus( E_main_Q_window_S );
        if( focused != note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]
        && focused != note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]
        )
            focused = note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ];
        g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).focused = focused;
    }
    E_note_tab_Q_note_tab_S_current_tab = tab;
    if( !E_note_tab_U_ignore_change )
    {   E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_focus();
        if( E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S )
            g_source_remove( E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S );
        E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S = g_idle_add( E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus, GUINT_TO_POINTER(tab) );
        E_file_P_changed();
    }
}
void
E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_focus( void
){  struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    GtkTreeSelection *selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
    GtkTreeModel *tree_store;
    GtkTreeIter iter;
    if( gtk_tree_selection_get_selected( selection, &tree_store, &iter ))
    {   GtkTreePath *path = gtk_tree_model_get_path( tree_store, &iter );
        E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
        gtk_tree_path_free(path);
        selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]);
        if( gtk_tree_selection_get_selected( selection, &tree_store, &iter ))
        {   GtkTreePath *path = gtk_tree_model_get_path( tree_store, &iter );
            E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
            gtk_tree_path_free(path);
        }
#ifdef C_kdb_focus_wa
        E_note_tab_I_kbd_focus_wa_M();
#endif
    }
}
gboolean
E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus( void *data
){  if( GPOINTER_TO_UINT(data) == E_note_tab_Q_note_tab_S_current_tab )
        gtk_widget_grab_focus( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).focused );
    E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S = 0;
    return G_SOURCE_REMOVE;
}
//-----------------------------------------------------------------------------
_EXPORT_OBFUSCATE
void
E_note_tab_Q_note_tab_Z_gtk_X_page_reordered( GtkNotebook *notebook
, GtkWidget *child
, unsigned tab
, void *data
){  struct E_note_tab_Q_ext_data_Z tmp = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    g_array_remove_index( E_note_tab_Q_note_tab_S_ext_data, E_note_tab_Q_note_tab_S_current_tab );
    g_array_insert_val( E_note_tab_Q_note_tab_S_ext_data, tab, tmp );
    E_note_tab_Q_note_tab_S_current_tab = tab;
    E_file_P_changed();
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_note_tab_Z_gtk_X_page_removed( GtkNotebook *notebook
, GtkWidget *child
, unsigned tab
, void *data
){  if( E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S )
    {   g_source_remove( E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S );
        E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_post_focus_S = 0;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_tree_Z_gtk_X_button_release_event( GtkWidget *widget
, GdkEvent *event
, void *data
){  
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_M();
#endif
    gtk_clipboard_set_with_owner( E_clipboard_S_1
    , E_clipboard_Q_tree_Q_1_S_data_types
    , sizeof( E_clipboard_Q_tree_Q_1_S_data_types ) / sizeof( GtkTargetEntry )
    , E_dnd_Z_gtk_Q_tree_Q_clipboard_S_1_I_supply_data
    , ( GtkClipboardClearFunc )gtk_false
    , ( void * )widget
    );
    return no;
}
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_tree_Z_gtk_X_focus_in_event( GtkWidget *widget
, GdkEvent *event
, void *data
){  E_note_tab_Q_actions_Z_tree_P_enabled(yes);
    return no;
}
#ifdef C_kdb_focus_wa
_EXPORT_OBFUSCATE
void
E_note_tab_Q_tree_Z_gtk_X_drag_begin( GtkWidget *widget
, GdkDragContext *event
, void *data
){  E_note_tab_I_kbd_focus_wa_P_enabled(no);
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_tree_Z_gtk_X_drag_end( GtkWidget *widget
, GdkDragContext *event
, void *data
){  E_note_tab_I_kbd_focus_wa_P_enabled(yes);
    E_note_tab_I_kbd_focus_wa_M();
}
#endif
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_tree_Z_gtk_X_focus_out_event( GtkWidget *widget
, GdkEvent *event
, void *data
){  
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_W();
#endif
    E_note_tab_Q_actions_Z_tree_P_enabled(no);
    return no;
}
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_tree_Z_gtk_X_query_tooltip( GtkWidget *tree
, int x
, int y
, gboolean by_keyboard
, GtkTooltip *tooltip
, void *data
){  GtkTreeModel *tree_store;
    GtkTreePath *path;
    GtkTreeIter iter;
    if( !gtk_tree_view_get_tooltip_context(( void * )tree, &x, &y, by_keyboard, &tree_store, &path, &iter ))
        return no;
    bool show = no;
    char *t;
    gtk_tree_model_get( tree_store, &iter, E_note_tab_Q_tree_Z_column_S_title, &t, -1 );
    if( *t )
    {   struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
        GtkCellRenderer *renderer = ( void * )note_tab_ext_data->tree_renderer_text[ ( void * )tree == note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ? E_note_tab_Q_ext_data_Z_tree_S_books : E_note_tab_Q_ext_data_Z_tree_S_notes ];
        bool editing;
        g_object_get( renderer, "editing", &editing, null );
        if( !editing )
        {   int natural_width;
            gtk_cell_renderer_get_preferred_width( renderer, tree, null, &natural_width );
            GdkRectangle cell_rect;
            gtk_tree_view_get_cell_area(( void * )tree
            , path, gtk_tree_view_get_column(( void * )tree, E_note_tab_Q_tree_Z_column_S_title )
            , &cell_rect
            );
            if( natural_width >= cell_rect.width )
            {   gtk_tooltip_set_text( tooltip, t );
                gtk_tree_view_set_tooltip_row(( void * )tree, tooltip, path );
                show = yes;
            }
        }
    }
    g_free(t);
    gtk_tree_path_free(path); //NDFN w dokumentacji nie jest napisane, by zwalniać ścieżkę z “gtk_tree_view_get_tooltip_context”, i nie wiadomo, ale ścieżki alokowane generalnie się zwalnia.
    return show;
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_tree_Z_gtk_X_row_expanded( GtkTreeView *tree_view
, GtkTreeIter *iter
, GtkTreePath *path
, void *data
){  gtk_tree_view_expand_row( tree_view, path, yes );
}
void
E_note_tab_Q_tree_Z_gtk_I_set_cursor_0( GtkTreeView *tree_view
, GtkTreePath *path
){  gtk_tree_view_scroll_to_cell( tree_view
    , path, null
    , yes, 0.2, 0
    );
}
void
E_note_tab_Q_tree_Z_gtk_I_set_cursor( GtkTreeView *tree_view
, GtkTreePath *path
){  E_note_tab_Q_tree_Z_gtk_I_set_cursor_0( tree_view, path );
    E_main_Z_gtk_I_process_events();
    gtk_tree_view_set_cursor( tree_view, path, gtk_tree_view_get_column( tree_view, 0 ), no );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef C_kdb_focus_wa
///WA (2) wymuszenie wyświetlenia wskaźnika klawiatury mimo niewyłączalnego gównianego ‚smart’ ukrywania przez ‟GTK+”.
void
E_note_tab_I_kbd_focus_wa_P_enabled( bool b
){  if(b)
        E_note_tab_I_kbd_focus_wa_U_ignore = no;
    else
    {   E_note_tab_I_kbd_focus_wa_U_ignore = yes;
        E_note_tab_I_kbd_focus_wa_W();
    }
}
gboolean
E_note_tab_I_kbd_focus_wa_I( void *data
){  struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    GtkWidget *widget = gtk_window_get_focus( E_main_Q_window_S );
    if( widget != ( void * )note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]
    && widget != ( void * )note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]
    )
        goto End; ///to zakończenie jest otwarte na “E_note_tab_U_ignore_change”, ale też na inne błędy (czasowe) i dlatego powoduje brak determinizmu zaznaczania.
    GtkCellRenderer *renderer = ( void * )note_tab_ext_data->tree_renderer_text[ ( void * )widget == note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ? E_note_tab_Q_ext_data_Z_tree_S_books : E_note_tab_Q_ext_data_Z_tree_S_notes ];
    gboolean editing;
    g_object_get( renderer, "editing", &editing, null );
    if( !editing )
    {   GdkDisplay *display = gtk_widget_get_display(( void * )E_main_Q_window_S );
        GList *devices = gdk_device_manager_list_devices( gdk_display_get_device_manager(display), GDK_DEVICE_TYPE_MASTER );
        GdkDevice *device = null;
        while( devices->next )
        {   devices = devices->next;
            device = devices->data;
            if( gdk_device_get_source(device) == GDK_SOURCE_KEYBOARD )
                break;
        }
        g_list_free(devices);
        if( !device )
            goto End;
        GdkEvent *ev = gdk_event_new( GDK_KEY_PRESS );
        ev->key.type = GDK_KEY_PRESS;
        ev->key.window = gtk_widget_get_window(widget);
        if( ev->key.window )
            g_object_ref( ev->key.window );
        ev->key.keyval = GDK_KEY_KP_Right;
        GdkKeymapKey *keys;
        int n;
        if( !gdk_keymap_get_entries_for_keyval( gdk_keymap_get_for_display(display), ev->key.keyval, &keys, &n ))
        {   g_free(keys);
            goto End_2;
        }
        ev->key.hardware_keycode = keys[0].keycode;
        ev->key.group = keys[0].group;
        g_free(keys);
        gdk_event_set_device( ev, device );
        gdk_event_put(ev);
        ev->key.type = GDK_KEY_RELEASE;
        gdk_event_put(ev);
End_2:  gdk_event_free(ev);
    }
End:E_note_tab_I_kbd_focus_wa_S = 0;
    return G_SOURCE_REMOVE;
}
void
E_note_tab_I_kbd_focus_wa_M( void
){  if( !E_note_tab_U_ignore_change
    && !E_note_tab_I_kbd_focus_wa_U_ignore
    && !E_note_tab_I_kbd_focus_wa_S
    )
        E_note_tab_I_kbd_focus_wa_S = g_idle_add_full( G_PRIORITY_LOW, E_note_tab_I_kbd_focus_wa_I, null, null );
}
void
E_note_tab_I_kbd_focus_wa_W( void
){  if( E_note_tab_I_kbd_focus_wa_S )
    {   g_source_remove( E_note_tab_I_kbd_focus_wa_S );
        E_note_tab_I_kbd_focus_wa_S = 0;
    }
}
#endif
//------------------------------------------------------------------------------
_EXPORT_OBFUSCATE
void
E_note_tab_Q_books_tree_Z_gtk_X_selection_changed( GtkTreeSelection *selection
, void *data
){  GtkTreeView *tree_view = gtk_tree_selection_get_tree_view(selection);
    GtkTreeView *notes_tree_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, gtk_notebook_page_num( E_note_tab_Q_note_tab_S, gtk_widget_get_parent( gtk_widget_get_parent(( void * )tree_view )))).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ];
    GtkTreeIter iter;
    GtkTreeModel *notes_tree_store = null;
    if( gtk_tree_selection_get_selected( selection, null, &iter ))
    {   gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &iter
        , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_tree_store
        , -1
        );
        g_object_unref( notes_tree_store );
#ifdef C_kdb_focus_wa
        E_note_tab_I_kbd_focus_wa_M();
#endif
        if( notes_tree_store == gtk_tree_view_get_model( notes_tree_view ))
            return;
    }
    E_undo_S_join_broken = yes;
    if( notes_tree_store )
    {   gtk_tree_view_set_model( notes_tree_view, notes_tree_store );
        gtk_tree_view_set_search_column( notes_tree_view, E_note_tab_Q_tree_Z_column_S_title );
        gtk_tree_view_expand_all( notes_tree_view );
    }else
    {   GtkTreeStore *notes_tree_store = E_note_tab_Q_tree_Q_store_M();
        gtk_tree_view_set_model( notes_tree_view, ( void * )notes_tree_store );
        g_object_unref( notes_tree_store );
    }
    g_object_set( notes_tree_view, "can-focus", !!notes_tree_store, null );
    E_file_P_changed();
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed( GtkTreeSelection *selection
, void *data
){  E_undo_S_join_broken = yes;
    GtkTreeView *tree_view = gtk_tree_selection_get_tree_view(selection);
    struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, gtk_notebook_page_num( E_note_tab_Q_note_tab_S, gtk_widget_get_parent( gtk_widget_get_parent(( void * )tree_view ))));
    GtkTextView *note_text_view = note_tab_ext_data->note;
    GtkTreeModel *notes_tree_store;
    GtkTreeIter iter;
    GtkTextBuffer *text_buffer;
    if( gtk_tree_selection_get_selected( selection, &notes_tree_store, &iter ))
    {   gtk_tree_model_get( notes_tree_store
        , &iter
        , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
        , -1
        );
        g_object_unref( text_buffer );
        if( text_buffer != gtk_text_view_get_buffer( note_text_view ))
        {   struct E_note_tab_Q_note_Z_ext_data *ext_data;
            gtk_tree_model_get( notes_tree_store
            , &iter
            , E_note_tab_Q_tree_Z_column_S_ext_data, &ext_data
            , -1
            );
            GDateTime *date = g_date_time_new_from_unix_local( ext_data->date_uid / 1000000 );
            char *label = g_date_time_format( date, "%Y‒%-m‒%-d %A %-H:%M" );
            gtk_label_set_text( note_tab_ext_data->note_date, label );
            g_free(label);
            g_date_time_unref(date);
            E_note_tab_Q_note_I_clear_search( text_buffer );
            if( !note_tab_ext_data->Q_notes_tree_U_selected )
            {   gtk_widget_show(( void * )note_tab_ext_data->note_attr );
                gtk_text_view_set_cursor_visible( note_text_view, yes );
                gtk_text_view_set_editable( note_text_view, yes );
                g_object_set( note_text_view, "can-focus", yes, null );
                note_tab_ext_data->Q_notes_tree_U_selected = yes;
            }
            gtk_text_view_set_buffer( note_text_view, text_buffer );
        }
#ifdef C_kdb_focus_wa
        E_note_tab_I_kbd_focus_wa_M();
#endif
    }else if( note_tab_ext_data->Q_notes_tree_U_selected )
    {   g_object_set( note_text_view, "can-focus", no, null );
        gtk_text_view_set_editable( note_text_view, no );
        gtk_text_view_set_cursor_visible( note_text_view, no );
        E_note_tab_Q_note_I_clear_search( gtk_text_view_get_buffer( note_text_view ));
        text_buffer = E_note_tab_Q_note_Q_buffer_M(null);
        gtk_text_view_set_buffer( note_text_view, text_buffer );
        g_object_unref( text_buffer );
        gtk_widget_hide(( void * )note_tab_ext_data->note_attr );
        note_tab_ext_data->Q_notes_tree_U_selected = no;
    }
    E_file_P_changed();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
_EXPORT_OBFUSCATE
void
E_note_tab_Q_books_tree_Q_branch_Z_gtk_X_editing_canceled( GtkCellRenderer *renderer
, void *data
){  gtk_widget_grab_focus(( void * )g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_books_tree_Q_branch_Z_gtk_X_edited( GtkCellRendererText *renderer
, char *path
, char *text
, void *data
){  E_note_tab_Q_notes_tree_Q_branch_X_edited( E_note_tab_Q_ext_data_Z_tree_S_books, path, text );
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_notes_tree_Q_branch_Z_gtk_X_editing_canceled( GtkCellRenderer *renderer
, void *data
){  gtk_widget_grab_focus(( void * )g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]);
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_notes_tree_Q_branch_Z_gtk_X_edited( GtkCellRendererText *renderer
, char *path
, char *text
, void *data
){  E_note_tab_Q_notes_tree_Q_branch_X_edited( E_note_tab_Q_ext_data_Z_tree_S_notes, path, text );
}
//-----------------------------------------------------------------------------
void
E_note_tab_Q_notes_tree_Q_branch_X_edited( int i
, const char *path
, const char *text
){  GtkTreeModel *tree_store = gtk_tree_view_get_model( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[i] );
    char *s = g_utf8_normalize( text, -1, G_NORMALIZE_DEFAULT_COMPOSE );
    if(s)
    {   g_strstrip(s);
        GtkTreeIter iter;
        gtk_tree_model_get_iter_from_string( tree_store, &iter, path );
        gtk_tree_store_set(( void * )tree_store
        , &iter
        , E_note_tab_Q_tree_Z_column_S_title, s
        , -1
        );
        g_free(s);
    }else
        E_error_K( "‘utf-8’ normalize" );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_note_Z_gtk_X_focus_in_event( GtkWidget *text_view
, GdkEvent *event
, void *data
){  gtk_text_view_scroll_to_mark(( void * )text_view, gtk_text_buffer_get_mark( gtk_text_view_get_buffer(( void * )text_view ), "insert" ), 0, no, 0, 0 );
    E_note_tab_Q_actions_Z_note_P_enabled(yes);
    return no;
}
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_note_Z_gtk_X_focus_out_event( GtkWidget *widget
, GdkEvent *event
, void *data
){  E_note_tab_Q_actions_Z_note_P_enabled(no);
    E_undo_S_join_broken = yes;
    return no;
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_note_Z_gtk_X_changed( GtkTextBuffer *text_buffer
, void *data
){  E_note_tab_Q_note_I_clear_search( text_buffer );
    E_file_P_changed();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_search_Z_gtk_X_focus_in_event( GtkWidget *widget
, GdkEvent *event
, void *data
){  struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    gtk_widget_grab_default(( void * )( note_tab_ext_data->default_previous ? note_tab_ext_data->search_previous : note_tab_ext_data->search_next ));
    return no;
}
_EXPORT_OBFUSCATE
gboolean
E_note_tab_Q_search_Z_gtk_X_focus_out_event( GtkWidget *widget
, GdkEvent *event
, void *data
){  gtk_window_set_default( E_main_Q_window_S, null );
    return no;
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_search_Z_gtk_X_changed( GtkEditable *buffer
, void *data
){  E_note_tab_Q_note_I_clear_search( gtk_text_view_get_buffer( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).note ));
}
//=============================================================================
void
E_note_tab_Q_note_tab_Z_gtk_I_new( GSimpleAction *action
, GVariant *param
, void *data
){  int tab = E_note_tab_Q_note_tab_M();
    if( tab != -1 )
    {   E_note_tab_Q_note_tab_Q_label_P( tab, null );
        gtk_notebook_set_current_page( E_note_tab_Q_note_tab_S, tab );
    }
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_note_tab_Z_gtk_I_fork( GSimpleAction *action
, GVariant *param
, void *data
){  int tab = E_note_tab_Q_note_tab_M_i( gtk_notebook_get_current_page( E_note_tab_Q_note_tab_S ));
    if( tab == -1 )
        return;
    E_note_tab_Q_note_tab_Q_label_P( tab, null );
    GtkTreeIter iter;
    GtkTreeSelection *selection = gtk_tree_view_get_selection( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
    if( gtk_tree_selection_get_selected( selection, null, &iter ))
    {   GtkTreePath *books_path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &iter );
        selection = gtk_tree_view_get_selection( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]);
        GtkTreePath *notes_path = null;
        if( gtk_tree_selection_get_selected( selection, null, &iter ))
            notes_path = gtk_tree_model_get_path( gtk_tree_view_get_model( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]), &iter );
        E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
        E_note_tab_Q_tree_Z_gtk_I_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], books_path );
        gtk_tree_path_free( books_path );
        if( notes_path )
        {   E_note_tab_Q_tree_Z_gtk_I_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], notes_path );
            gtk_tree_path_free( notes_path );
        }
        E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = no;
    }
    E_file_P_changed();
}
void
E_note_tab_Q_note_tab_Z_gtk_I_delete( GSimpleAction *action
, GVariant *param
, void *data
){  if( gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S ) > 1 )
        E_note_tab_Q_note_tab_W( E_note_tab_Q_note_tab_S_current_tab );
}
//------------------------------------------------------------------------------
void
E_note_tab_Q_note_tab_Z_gtk_I_prev( GSimpleAction *action
, GVariant *param
, void *data
){  if( E_note_tab_Q_note_tab_S_current_tab )
        gtk_notebook_set_current_page( E_note_tab_Q_note_tab_S, --E_note_tab_Q_note_tab_S_current_tab );
    else
    {   int n = gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S ) - 1;
        if( E_note_tab_Q_note_tab_S_current_tab != n )
            gtk_notebook_set_current_page( E_note_tab_Q_note_tab_S, E_note_tab_Q_note_tab_S_current_tab = n );
    }
}
void
E_note_tab_Q_note_tab_Z_gtk_I_next( GSimpleAction *action
, GVariant *param
, void *data
){  if( E_note_tab_Q_note_tab_S_current_tab != gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S ) - 1 )
        gtk_notebook_set_current_page( E_note_tab_Q_note_tab_S, ++E_note_tab_Q_note_tab_S_current_tab );
    else if( E_note_tab_Q_note_tab_S_current_tab )
        gtk_notebook_set_current_page( E_note_tab_Q_note_tab_S, E_note_tab_Q_note_tab_S_current_tab = 0 );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_note_tab_Q_tree_Z_gtk_I_new_before( GSimpleAction *action
, GVariant *param
, void *data
){  E_note_tab_Q_tree_Z_gtk_I_new_I( no, E_note_tab_Q_tree_Q_branch_Z_position_S_before );
}
void
E_note_tab_Q_tree_Z_gtk_I_new_after( GSimpleAction *action
, GVariant *param
, void *data
){  E_note_tab_Q_tree_Z_gtk_I_new_I( no, E_note_tab_Q_tree_Q_branch_Z_position_S_after );
}
void
E_note_tab_Q_tree_Z_gtk_I_new_first( GSimpleAction *action
, GVariant *param
, void *data
){  E_note_tab_Q_tree_Z_gtk_I_new_I( no, E_note_tab_Q_tree_Q_branch_Z_position_S_first );
}
void
E_note_tab_Q_tree_Z_gtk_I_new_last( GSimpleAction *action
, GVariant *param
, void *data
){  E_note_tab_Q_tree_Z_gtk_I_new_I( no, E_note_tab_Q_tree_Q_branch_Z_position_S_last );
}
void
E_note_tab_Q_tree_Z_gtk_I_new_child_first( GSimpleAction *action
, GVariant *param
, void *data
){  E_note_tab_Q_tree_Z_gtk_I_new_I( yes, E_note_tab_Q_tree_Q_branch_Z_position_S_first );
}
void
E_note_tab_Q_tree_Z_gtk_I_new_child_last( GSimpleAction *action
, GVariant *param
, void *data
){  E_note_tab_Q_tree_Z_gtk_I_new_I( yes, E_note_tab_Q_tree_Q_branch_Z_position_S_last );
}
//-----------------------------------------------------------------------------
void
E_note_tab_Q_tree_Z_gtk_I_new_I(
  bool child
, int position_e
){  struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    void *widget = gtk_window_get_focus( E_main_Q_window_S );
    if( widget != note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]
    && widget != note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]
    )
        return;
    E_note_tab_Q_tree_Q_branch_M( widget, child, position_e );
}
//-----------------------------------------------------------------------------
void
E_note_tab_Q_tree_Z_gtk_I_delete( GSimpleAction *action
, GVariant *param
, void *data
){  struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    void *widget = gtk_window_get_focus( E_main_Q_window_S );
    if( widget != note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]
    && widget != note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]
    )
        return;
    E_note_tab_Q_tree_Q_branch_W(widget);
}
//=============================================================================
int
E_note_tab_Q_note_tab_M_i( int i
){  GtkBuilder *builder = gtk_builder_new();
    if( !gtk_builder_add_from_file( builder, "note_tab.ui", null ))
        return -1;
    GtkWidget *note_tab_container = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note_tab_container );
    int tab;
    if( i == -2 )
        tab = gtk_notebook_prepend_page( E_note_tab_Q_note_tab_S, note_tab_container, null );
    else
    {   tab = gtk_notebook_insert_page( E_note_tab_Q_note_tab_S, note_tab_container, null, i );
        if( tab <= E_note_tab_Q_note_tab_S_current_tab )
            E_note_tab_Q_note_tab_S_current_tab++;
    }
    if( tab == -1 )
    {   g_object_unref(builder);
        return tab;
    }
    gtk_container_child_set(( void * )E_note_tab_Q_note_tab_S, note_tab_container, "reorderable", yes, null );
    struct E_note_tab_Q_ext_data_Z note_tab_ext_data;
    note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] = ( void * )gtk_builder_get_object( builder, Q_builder_Z_books_tree );
    note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] = ( void * )gtk_builder_get_object( builder, Q_builder_Z_notes_tree );
    note_tab_ext_data.tree_renderer_text[ E_note_tab_Q_ext_data_Z_tree_S_books ] = ( void * )gtk_builder_get_object( builder, Q_builder_Z_books_tree_renderer_text );
    note_tab_ext_data.tree_renderer_text[ E_note_tab_Q_ext_data_Z_tree_S_notes ] = ( void * )gtk_builder_get_object( builder, Q_builder_Z_notes_tree_renderer_text );
    note_tab_ext_data.note = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note );
    note_tab_ext_data.note_attr = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note_attr );
    note_tab_ext_data.note_date = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note_date );
    note_tab_ext_data.new_tab_names_tree = ( void * )gtk_builder_get_object( builder, Q_builder_Z_new_tab_names );
    gtk_tree_view_set_model( note_tab_ext_data.new_tab_names_tree, E_note_tab_Q_note_tab_S_new_tab_names_list_store );
    GtkTreePath *path = gtk_tree_path_new_first();
    gtk_tree_view_set_cursor( note_tab_ext_data.new_tab_names_tree, path, null, no );
    gtk_tree_path_free(path);
    note_tab_ext_data.search_inexact = ( void * )gtk_builder_get_object( builder, Q_builder_Z_search_inexact );
    note_tab_ext_data.search_exact = ( void * )gtk_builder_get_object( builder, Q_builder_Z_search_exact );
    note_tab_ext_data.search_exact_chars = ( void * )gtk_builder_get_object( builder, Q_builder_Z_search_exact_chars );
    note_tab_ext_data.Q_notes_tree_U_selected = no;
    note_tab_ext_data.default_previous = no;
    note_tab_ext_data.search_next = ( void * )gtk_builder_get_object( builder, Q_builder_Z_search_next );
    note_tab_ext_data.search_previous = ( void * )gtk_builder_get_object( builder, Q_builder_Z_search_previous );
    note_tab_ext_data.focused = ( void * )E_note_tab_Q_note_tab_S;
    g_array_insert_val( E_note_tab_Q_note_tab_S_ext_data, tab, note_tab_ext_data );
    gtk_tree_view_set_model( note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], E_note_tab_Q_note_tab_S_books_tree_store );
    gtk_tree_view_set_search_column( note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], E_note_tab_Q_tree_Z_column_S_title );
    GtkTreeStore *notes_tree_store = E_note_tab_Q_tree_Q_store_M();
    gtk_tree_view_set_model( note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], ( void * )notes_tree_store );
    g_object_unref( notes_tree_store );
    for( enum E_note_tab_Q_ext_data_Z_tree i = 0; i != E_note_tab_Q_ext_data_Z_tree_S_n_; i++ )
    {   gtk_tree_view_set_search_equal_func( note_tab_ext_data.tree[i]
        , E_search_Q_tree_Z_gtk_I_search_cmp
        , null
        , null
        );
        gtk_tree_view_enable_model_drag_source( note_tab_ext_data.tree[i]
        , GDK_BUTTON1_MASK
        , E_dnd_Q_tree_S_data_types
        , sizeof( E_dnd_Q_tree_S_data_types ) / sizeof( GtkTargetEntry )
        , GDK_ACTION_MOVE
        );
        gtk_tree_view_enable_model_drag_dest( note_tab_ext_data.tree[i]
        , E_dnd_Q_tree_S_data_types
        , sizeof( E_dnd_Q_tree_S_data_types ) / sizeof( GtkTargetEntry )
        , GDK_ACTION_MOVE
        );
    }
    gtk_text_view_set_border_window_size( note_tab_ext_data.note, GTK_TEXT_WINDOW_TOP, 5 );
    gtk_text_view_set_border_window_size( note_tab_ext_data.note, GTK_TEXT_WINDOW_BOTTOM, 5 );
    gtk_text_view_set_border_window_size( note_tab_ext_data.note, GTK_TEXT_WINDOW_LEFT, 7 );
    gtk_text_view_set_border_window_size( note_tab_ext_data.note, GTK_TEXT_WINDOW_RIGHT, 7 );
    GList *tab_order = null;
    tab_order = g_list_prepend( tab_order, gtk_widget_get_parent(( void * )note_tab_ext_data.search_inexact ));
    tab_order = g_list_prepend( tab_order, gtk_widget_get_parent(( void * )note_tab_ext_data.note ));
    tab_order = g_list_prepend( tab_order, gtk_widget_get_parent(( void * )note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]));
    tab_order = g_list_prepend( tab_order, gtk_widget_get_parent(( void * )note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]));
    tab_order = g_list_prepend( tab_order, gtk_widget_get_parent(( void * )note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]));
    gtk_container_set_focus_chain(( void * )note_tab_container, tab_order );
    g_list_free( tab_order );
    tab_order = null;
    tab_order = g_list_prepend( tab_order, note_tab_ext_data.search_exact_chars );
    tab_order = g_list_prepend( tab_order, note_tab_ext_data.search_exact );
    tab_order = g_list_prepend( tab_order, note_tab_ext_data.search_inexact );
    GtkWidget *search = ( void * )gtk_builder_get_object( builder, Q_builder_Z_search );
    gtk_container_set_focus_chain(( void * )search, tab_order );
    g_list_free( tab_order );
    gtk_builder_connect_signals( builder, null );
    g_object_unref(builder);
    gtk_widget_show_all( note_tab_container );
    gtk_widget_hide(( void * )note_tab_ext_data.note_attr );
    gtk_tree_view_expand_all( note_tab_ext_data.tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
    return tab;
}
int
E_note_tab_Q_note_tab_M_( void
){  return E_note_tab_Q_note_tab_M_i( -1 );
}
int
E_note_tab_Q_note_tab_M( void
){  return E_note_tab_Q_note_tab_M_i( -2 );
}
void
E_note_tab_Q_note_tab_Q_label_P( int tab
, char *s
){  GDateTime *date = g_date_time_new_now_local();
    char *menu_label = g_date_time_format( date, "%b%-e\\%-k:%M/%Y" );
    g_date_time_unref(date);
    char *tab_label;
    if(s)
    {   tab_label = s;
        s = g_strconcat( "(", menu_label, ") ", tab_label, null );
        g_free( menu_label );
        menu_label = s;
    }else
        tab_label = menu_label;
    GtkWidget *note_tab_container = gtk_notebook_get_nth_page( E_note_tab_Q_note_tab_S, tab );
    gtk_notebook_set_menu_label_text( E_note_tab_Q_note_tab_S, note_tab_container, menu_label );
    gtk_notebook_set_tab_label_text( E_note_tab_Q_note_tab_S, note_tab_container, tab_label );
    g_free( menu_label );
}
void
E_note_tab_Q_note_tab_W( int tab
){  g_array_remove_index( E_note_tab_Q_note_tab_S_ext_data, tab );
    gtk_notebook_remove_page( E_note_tab_Q_note_tab_S, tab );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
_EXPORT_OBFUSCATE
void
E_note_tab_Q_new_tab_names_Z_gtk_I_fork_tabs( GSimpleAction *action
, GVariant *param
, void *data
){  GtkTreeIter iter;
    gtk_tree_model_iter_children( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, null );
    do
    {   char *name;
        gtk_tree_model_get( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0, &name, -1 );
        if( *name )
        {   int tab = E_note_tab_Q_note_tab_M();
            if( tab == -1 )
            {   g_free(name);
                goto Error;
            }
            E_note_tab_Q_note_tab_Q_label_P( tab, name );
            struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab );
            note_tab_ext_data->focused = ( void * )note_tab_ext_data->search_inexact;
            gtk_entry_set_text( note_tab_ext_data->search_inexact, name );
            E_search_Q_note_tab_Z_gtk_I_search_next( null, GINT_TO_POINTER(tab) );
        }
        g_free(name);
    }while( gtk_tree_model_iter_next( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter ));
    gtk_list_store_clear(( void * )E_note_tab_Q_note_tab_S_new_tab_names_list_store );
    gtk_list_store_insert_with_values(( void * )E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0
    , 0, ""
    , -1
    );
    GtkTreePath *path = gtk_tree_path_new_first();
    for( unsigned i = 0; i < E_note_tab_Q_note_tab_S_ext_data->len; i++ )
        gtk_tree_view_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, i ).new_tab_names_tree, path, null, no );
    gtk_tree_path_free(path);
Error:
    E_file_P_changed();
}
_EXPORT_OBFUSCATE
void
E_note_tab_Q_new_tab_names_Q_branch_Z_gtk_X_edited( GtkCellRendererText *renderer
, char *path
, char *text
, void *data
){  GtkTreeIter iter_0, iter;
    gtk_tree_model_get_iter_from_string( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter_0, path );
    gtk_list_store_set(( void * )E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter_0
    , 0, text
    , -1
    );
    GtkTreePath *path_0 = gtk_tree_path_new_from_string(path);
    GtkTreePath *path_i = gtk_tree_path_new_first();
    if( *text )
    {   struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
        while( gtk_tree_path_compare( path_0, path_i ))
        {   gtk_tree_model_get_iter( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, path_i );
            gtk_tree_model_get( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0, &text, -1 );
            if( !*text )
            {   gtk_tree_view_set_cursor( note_tab_ext_data->new_tab_names_tree, path_i, null, no );
                g_idle_add( E_note_tab_Q_new_tab_names_Q_branch_Z_gtk_X_edited_I_post_focus, note_tab_ext_data );
                g_free(text);
                gtk_tree_path_free( path_i );
                gtk_tree_path_free( path_0 );
                return;
            }
            g_free(text);
            gtk_tree_path_next( path_i );
        }
        gtk_tree_path_next( path_i );
        while( gtk_tree_model_get_iter( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, path_i ))
        {   gtk_tree_model_get( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0, &text, -1 );
            if( !*text )
            {   gtk_tree_view_set_cursor( note_tab_ext_data->new_tab_names_tree, path_i, null, no );
                g_idle_add( E_note_tab_Q_new_tab_names_Q_branch_Z_gtk_X_edited_I_post_focus, note_tab_ext_data );
                g_free(text);
                gtk_tree_path_free( path_i );
                gtk_tree_path_free( path_0 );
                return;
            }
            g_free(text);
            gtk_tree_path_next( path_i );
        }
        gtk_tree_path_free( path_i );
        gtk_list_store_insert_with_values(( void * )E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0
        , 0, ""
        , -1
        );
        path_i = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter );
        gtk_tree_view_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).new_tab_names_tree, path_i, null, no );
        g_idle_add( E_note_tab_Q_new_tab_names_Q_branch_Z_gtk_X_edited_I_post_focus, note_tab_ext_data );
    }else
    {   while( gtk_tree_path_compare( path_0, path_i ))
        {   gtk_tree_model_get_iter( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, path_i );
            gtk_tree_model_get( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0, &text, -1 );
            if( !*text )
            {   gtk_list_store_remove(( void * )E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter_0 );
                g_free(text);
                gtk_tree_path_free( path_i );
                gtk_tree_path_free( path_0 );
                return;
            }
            g_free(text);
            gtk_tree_path_next( path_i );
        }
        gtk_tree_path_next( path_i );
        while( gtk_tree_model_get_iter( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, path_i ))
        {   gtk_tree_model_get( E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter, 0, &text, -1 );
            if( !*text )
            {   gtk_list_store_remove(( void * )E_note_tab_Q_note_tab_S_new_tab_names_list_store, &iter_0 );
                g_free(text);
                gtk_tree_path_free( path_i );
                gtk_tree_path_free( path_0 );
                return;
            }
            g_free(text);
            gtk_tree_path_next( path_i );
        }
    }
    gtk_tree_path_free( path_i );
    gtk_tree_path_free( path_0 );
}
gboolean
E_note_tab_Q_new_tab_names_Q_branch_Z_gtk_X_edited_I_post_focus( void *data
){  GList *path = gtk_tree_selection_get_selected_rows( gtk_tree_view_get_selection((( struct E_note_tab_Q_ext_data_Z * )data )->new_tab_names_tree ), null );
    gtk_tree_view_set_cursor((( struct E_note_tab_Q_ext_data_Z * )data )->new_tab_names_tree
    , path->data
    , gtk_tree_view_get_column((( struct E_note_tab_Q_ext_data_Z * )data )->new_tab_names_tree, 0 )
    , yes
    );
    g_list_free_full( path, ( GDestroyNotify )gtk_tree_path_free );
    return G_SOURCE_REMOVE;
}
//-----------------------------------------------------------------------------
GtkListStore *
E_note_tab_Q_new_tab_names_Q_store_M( void
){  GtkListStore *list_store = gtk_list_store_new( 1, G_TYPE_STRING );
    GtkTreeIter iter;
    gtk_list_store_insert_with_values( list_store, &iter, -1
    , 0, ""
    , -1
    );
    return list_store;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_note_tab_Q_actions_Z_tree_P_enabled( bool b
){  GActionEntry *list = &E_note_tab_Z_gtk_Q_app_actions[0];
    while( memcmp( list->name, "tree_", 5 ))
        list++;
    do
    {   GSimpleAction *action = ( void * )g_action_map_lookup_action(( void * )E_main_Q_app_S, list++->name );
        g_simple_action_set_enabled( action, b );
    }while( !memcmp( list->name, "tree_", 5 ));
}
void
E_note_tab_Q_actions_Z_note_P_enabled( bool b
){  char **list = ( char ** )( char *[] ) { "note_undo", "note_redo", null };
    while( *list )
    {   GSimpleAction *action = ( void * )g_action_map_lookup_action(( void * )E_main_Q_app_S, *list++ );
        g_simple_action_set_enabled( action, b );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_note_tab_Q_note_tab_P_clear( void
){  int n = gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S );
    for( int i = n - 1; i >= 0; i-- )
        E_note_tab_Q_note_tab_W(i);
    gtk_tree_model_foreach( E_note_tab_Q_note_tab_S_books_tree_store, E_note_tab_Q_note_tab_P_clear_Q_books_Z_gtk_I_foreach, null );
    gtk_tree_store_clear(( void * )E_note_tab_Q_note_tab_S_books_tree_store );
}
//-----------------------------------------------------------------------------
gboolean
E_note_tab_Q_note_tab_P_clear_Q_books_Z_gtk_I_foreach( GtkTreeModel *model
, GtkTreePath *path
, GtkTreeIter *iter
, void *data
){  GtkTreeStore *notes_store;
    gtk_tree_model_get( model
    , iter
    , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_store
    , -1
    );
    g_object_unref( notes_store );
    gtk_tree_model_foreach(( void * )notes_store, E_note_tab_Q_note_tab_P_clear_Q_notes_Z_gtk_I_foreach, null );
    return no;
}
gboolean
E_note_tab_Q_note_tab_P_clear_Q_notes_Z_gtk_I_foreach( GtkTreeModel *model
, GtkTreePath *path
, GtkTreeIter *iter
, void *data
){  void *note_data;
    gtk_tree_model_get( model
    , iter
    , E_note_tab_Q_tree_Z_column_S_ext_data, &note_data
    , -1
    );
    E_note_tab_Q_note_Z_ext_data_W( note_data );
    return no;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//poniższe muszą być jako sygnały ‟gtk+”, ponieważ nie zarządzam wszystkimi możliwymi źródłami zmian w drzewach, np. “drag & drop”.
void
E_note_tab_Q_tree_Z_gtk_X_row_inserted( GtkTreeModel *tree_model
, GtkTreePath *path
, GtkTreeIter *iter
, void *data
){  E_file_P_changed();
}
void
E_note_tab_Q_tree_Z_gtk_X_row_changed( GtkTreeModel *tree_model
, GtkTreePath *path
, GtkTreeIter *iter
, void *data
){  E_file_P_changed();
}
void
E_note_tab_Q_tree_Z_gtk_X_row_deleted( GtkTreeModel *tree_model
, GtkTreePath *path
, void *data
){  E_file_P_changed();
}
void
E_note_tab_Q_tree_Z_gtk_X_rows_reordered( GtkTreeModel *tree_model
, GtkTreePath *path
, GtkTreeIter *iter
, void *order
, void *data
){  E_file_P_changed();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GtkTreeStore *
E_note_tab_Q_tree_Q_store_M( void
){  GtkTreeStore *tree_store = gtk_tree_store_new( 3, G_TYPE_STRING, G_TYPE_OBJECT, G_TYPE_POINTER );
    g_signal_connect( tree_store, "row-inserted", ( GCallback )E_note_tab_Q_tree_Z_gtk_X_row_inserted, null );
    g_signal_connect( tree_store, "row-changed", ( GCallback )E_note_tab_Q_tree_Z_gtk_X_row_changed, null );
    g_signal_connect( tree_store, "row-deleted", ( GCallback )E_note_tab_Q_tree_Z_gtk_X_row_deleted, null );
    g_signal_connect( tree_store, "rows-reordered", ( GCallback )E_note_tab_Q_tree_Z_gtk_X_rows_reordered, null );
    return tree_store;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_note_tab_Q_tree_Q_branch_M( GtkTreeView *tree_view
, bool child
, int position_e
){  GtkTreeSelection *selection = gtk_tree_view_get_selection( tree_view );
    GtkTreeModel *tree_model;
    GtkTreeIter iter, *iter_p;
    int position;
    if( gtk_tree_selection_get_selected( selection, &tree_model, &iter ))
    {   if(child)
        {   iter_p = &iter;
            position = position_e;
        }else
        {   if( position_e < E_note_tab_Q_tree_Q_branch_Z_position_S_before )
                position = position_e;
            else
            {   GtkTreePath *path = gtk_tree_model_get_path( tree_model, &iter );
                int n;
                const int *is = gtk_tree_path_get_indices_with_depth( path, &n );
                position = is[ n - 1 ];
                gtk_tree_path_free(path);
                if( position_e == E_note_tab_Q_tree_Q_branch_Z_position_S_after )
                    position++;
            }
            GtkTreeIter new_iter;
            if( gtk_tree_model_iter_parent( tree_model, &new_iter, &iter ))
            {   iter = new_iter;
                iter_p = &iter;
            }else
                iter_p = null;
        }
    }else
    {   iter_p = null;
        position = 0;
    }
    void *object;
    struct E_note_tab_Q_note_Z_ext_data *ext_data;
    if( tree_model == E_note_tab_Q_note_tab_S_books_tree_store )
    {   object = E_note_tab_Q_tree_Q_store_M();
        ext_data = null;
    }else
    {   ext_data = E_note_tab_Q_note_Z_ext_data_M();
        ext_data->date_uid = E_note_tab_I_uniq_date_uid( g_get_real_time() );
        GtkTreeIter iter, old_iter;
        if( gtk_tree_model_get_iter_first( tree_model, &iter ))
            while(empty)
            {   struct E_note_tab_Q_note_Z_ext_data *d;
                gtk_tree_model_get( tree_model
                , &iter
                , E_note_tab_Q_tree_Z_column_S_ext_data, &d
                , -1
                );
                if( d->date_uid == ext_data->date_uid )
                {   ext_data->date_uid++;
                    gtk_tree_model_get_iter_first( tree_model, &iter );
                    continue;
                }
                old_iter = iter;
                if( gtk_tree_model_iter_children( tree_model, &iter, &old_iter ))
                    continue;
                iter = old_iter;
                while( !gtk_tree_model_iter_next( tree_model, &iter ))
                {   if( !gtk_tree_model_iter_parent( tree_model, &iter, &old_iter ))
                        goto End_iter;
                    old_iter = iter;
                }
            }
End_iter:
        object = E_note_tab_Q_note_Q_buffer_M(null);
    }
    GtkTreeIter new_iter;
    gtk_tree_store_insert_with_values(( void * )tree_model, &new_iter, iter_p
    , position
    , E_note_tab_Q_tree_Z_column_S_title, ""
    , E_note_tab_Q_tree_Z_column_S_object_ref, object
    , E_note_tab_Q_tree_Z_column_S_ext_data, ext_data
    , -1
    );
    iter = new_iter;
    g_object_unref(object);
    GtkTreePath *path = gtk_tree_model_get_path( tree_model, &iter );
    gtk_tree_view_expand_to_path( tree_view, path );
    gtk_tree_view_set_cursor( tree_view
    , path
    , gtk_tree_view_get_column( tree_view, E_note_tab_Q_tree_Z_column_S_title )
    , yes
    );
    gtk_tree_path_free(path);
}
//-----------------------------------------------------------------------------
void
E_note_tab_Q_tree_Q_branch_W( GtkTreeView *tree_view
){  GtkTreeSelection *selection = gtk_tree_view_get_selection( tree_view );
    GtkTreeModel *tree_store;
    GtkTreeIter iter;
    if( !gtk_tree_selection_get_selected( selection, &tree_store, &iter ))
        return;
    GtkTreePath *start, *end;
    if( !gtk_tree_view_get_visible_range( tree_view, &start, &end ))
        return;
    GtkTreePath *path = gtk_tree_model_get_path( tree_store, &iter );
    if( gtk_tree_path_compare( path, start ) < 0
    || gtk_tree_path_compare( end, path ) < 0
    )
    {   gtk_tree_path_free(path);
        gtk_tree_path_free(start);
        gtk_tree_path_free(end);
        return;
    }
    gtk_tree_path_free(path);
    gtk_tree_path_free(start);
    gtk_tree_path_free(end);
    struct Q_gtk_Q_tree_model_I_foreach_S_data_E_olet *data = g_new( struct Q_gtk_Q_tree_model_I_foreach_S_data_E_olet, 1 );
    data->branch = no;
    data->iter = &iter;
    data->iter_s = gtk_tree_model_get_string_from_iter( tree_store, &iter );
    gtk_tree_model_foreach( tree_store, tree_store == E_note_tab_Q_note_tab_S_books_tree_store ? E_note_tab_Q_tree_Q_branch_W_Q_books_Z_gtk_I_foreach_E_olet : E_note_tab_Q_tree_Q_branch_W_Q_notes_Z_gtk_I_foreach_E_olet, data );
    g_free( data->iter_s );
    g_free(data);
    gtk_tree_store_remove(( void * )tree_store, &iter );
    if( gtk_tree_selection_get_selected( selection, null, &iter ))
    {   GtkTreePath *path = gtk_tree_model_get_path( tree_store, &iter );
        gtk_tree_view_set_cursor( tree_view, path, null, no );
        gtk_tree_path_free(path);
    }
}
gboolean
E_note_tab_Q_tree_Q_branch_W_Q_books_Z_gtk_I_foreach_E_olet( GtkTreeModel *model
, GtkTreePath *path
, GtkTreeIter *iter
, void *data_
){  struct Q_gtk_Q_tree_model_I_foreach_S_data_E_olet *data = data_;
    if( !data->branch )
    {   char *s = gtk_tree_model_get_string_from_iter( model, iter );
        if( strcmp( data->iter_s, s ))
            return no;
        data->branch = yes;
    }else if( !gtk_tree_store_is_ancestor(( void * )model, data->iter, iter ))
        return yes;
    GtkTreeStore *notes_tree_store;
    gtk_tree_model_get( model
    , iter
    , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_tree_store
    , -1
    );
    g_object_unref( notes_tree_store );
    gtk_tree_model_foreach(( void * )notes_tree_store, E_note_tab_Q_note_tab_P_clear_Q_notes_Z_gtk_I_foreach, null );
    return no;
}
gboolean
E_note_tab_Q_tree_Q_branch_W_Q_notes_Z_gtk_I_foreach_E_olet( GtkTreeModel *model
, GtkTreePath *path
, GtkTreeIter *iter
, void *data_
){  struct Q_gtk_Q_tree_model_I_foreach_S_data_E_olet *data = data_;
    if( !data->branch )
    {   char *s = gtk_tree_model_get_string_from_iter( model, iter );
        if( strcmp( data->iter_s, s ))
            return no;
        data->branch = yes;
    }else if( !gtk_tree_store_is_ancestor(( void * )model, data->iter, iter ))
        return yes;
    void *note_data;
    gtk_tree_model_get( model
    , iter
    , E_note_tab_Q_tree_Z_column_S_ext_data, &note_data
    , -1
    );
    E_note_tab_Q_note_Z_ext_data_W( note_data );
    return no;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GtkTextBuffer *
E_note_tab_Q_note_Q_buffer_M( char *s
){  GtkTextBuffer *buffer = gtk_text_buffer_new( E_note_tab_Q_note_S_tag_table );
    if(s)
        gtk_text_buffer_set_text( buffer, s, -1 );
    g_signal_connect( buffer, "changed", ( GCallback )E_note_tab_Q_note_Z_gtk_X_changed, null );
    g_signal_connect( buffer, "insert-text", ( GCallback )E_undo_Q_note_Z_gtk_X_insert_text, null );
    g_signal_connect( buffer, "delete-range", ( GCallback )E_undo_Q_note_Z_gtk_X_delete_range, null );
    return buffer;
}
struct E_note_tab_Q_note_Z_ext_data *
E_note_tab_Q_note_Z_ext_data_M( void
){  struct E_note_tab_Q_note_Z_ext_data *data = g_new( struct E_note_tab_Q_note_Z_ext_data, 1 );
    data->undo_array = null;
    return data;
}
void
E_note_tab_Q_note_Z_ext_data_W( struct E_note_tab_Q_note_Z_ext_data *data
){  if( data->undo_array )
    {   unsigned i;
        for( i = 0; i < data->undo_array->len - data->undo_back; i++ )
        {   struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, i );
            if( undo->type == E_undo_Q_note_Z_action_S_text_deleted )
                g_free( undo->u.text );
        }
        for( ; i < data->undo_array->len; i++ )
        {   struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, i );
            if( undo->type == E_undo_Q_note_Z_action_S_text_inserted )
                g_free( undo->u.text );
        }
        g_array_unref( data->undo_array );
    }
    g_free( data );
}
/******************************************************************************/
