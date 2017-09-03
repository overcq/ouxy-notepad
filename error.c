//=============================================================================
GError *E_error_S = null;
GtkTreeView *E_error_Q_info_bar_S_error_list;
GtkTreeModel *E_error_Q_info_bar_S_list_store = null;
//=============================================================================
void
E_error_K( char *s
){  g_printerr( "error message:\n ‟ouxy notepad”: %s\n", s );
    if( E_error_S )
        g_printerr( " ‟gtk+”: %s\n", E_error_S->message );
    if( !E_error_Q_info_bar_S_list_store )
    {   E_error_Q_info_bar_S_list_store = ( void * )E_error_Q_info_bar_Q_error_M();
        gtk_tree_view_set_model( E_error_Q_info_bar_S_error_list, E_error_Q_info_bar_S_list_store );
        g_object_unref( E_error_Q_info_bar_S_list_store );
        gtk_widget_show(( void * )E_main_Q_info_bar_S );
    }
    GtkTreeIter iter;
    gtk_list_store_insert_with_values(( void * )E_error_Q_info_bar_S_list_store, &iter, -1
    , 0, s
    , -1
    );
    if( E_error_S )
        gtk_list_store_set(( void * )E_error_Q_info_bar_S_list_store, &iter
        , 1, E_error_S->message
        , -1
        );
    GtkTreePath *path = gtk_tree_model_get_path( E_error_Q_info_bar_S_list_store, &iter );
    gtk_tree_view_scroll_to_cell( E_error_Q_info_bar_S_error_list
    , path, null
    , yes, 1, 0
    );
    gtk_tree_path_free(path);
    g_clear_error( &E_error_S );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GtkListStore *
E_error_Q_info_bar_Q_error_M(
){  GtkListStore *list_store = gtk_list_store_new( 2, G_TYPE_STRING, G_TYPE_STRING );
    gtk_tree_view_enable_model_drag_source( E_error_Q_info_bar_S_error_list
    , GDK_BUTTON1_MASK
    , E_dnd_Q_tree_S_data_types
    , sizeof( E_dnd_Q_tree_S_data_types ) / sizeof( GtkTargetEntry )
    , GDK_ACTION_MOVE
    );
    gtk_tree_view_enable_model_drag_dest( E_error_Q_info_bar_S_error_list
    , E_dnd_Q_tree_S_data_types
    , sizeof( E_dnd_Q_tree_S_data_types ) / sizeof( GtkTargetEntry )
    , GDK_ACTION_MOVE
    );
    return list_store;
}
void
E_error_Z_gtk_Q_program_I_err_clear( GSimpleAction *action
, GVariant *param
, void *data
){  if( E_error_Q_info_bar_S_list_store )
    {   gtk_tree_view_unset_rows_drag_source( E_error_Q_info_bar_S_error_list );
        gtk_tree_view_unset_rows_drag_dest( E_error_Q_info_bar_S_error_list );
        gtk_widget_hide(( void * )E_main_Q_info_bar_S );
        gtk_tree_view_set_model( E_error_Q_info_bar_S_error_list, E_error_Q_info_bar_S_list_store = null );
    }
}
//=============================================================================
