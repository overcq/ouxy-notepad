/******************************************************************************/
OBFUSCATE( Q_builder_Z_app_menu );
OBFUSCATE( Q_builder_Z_app_menu_bar );
OBFUSCATE( Q_builder_Z_window );
OBFUSCATE( Q_builder_Z_info_bar );
OBFUSCATE( Q_builder_Z_info_bar_error_list );
OBFUSCATE( Q_builder_Z_note_views );
OBFUSCATE( Q_builder_Z_note_tag_table );
OBFUSCATE( Q_builder_Z_note_search_tag );
//=============================================================================
GActionEntry E_note_tab_Z_gtk_Q_app_actions[] =
{ { "about", E_main_Z_gtk_Q_program_I_about, null, null, null }
, { "err_clear", E_error_Z_gtk_Q_program_I_err_clear, null, null, null }
, { "quit", E_main_Z_gtk_Q_program_I_quit, null, null, null }
, { "file_new", E_file_Z_gtk_I_new, null, null, null }
, { "file_open", E_file_Z_gtk_I_open, null, null, null }
, { "file_save", E_file_Z_gtk_I_save, null, null, null }
, { "file_rename", E_file_Z_gtk_I_rename, null, null, null }
, { "file_import", E_ie_Z_gtk_I_import, null, null, null }
, { "file_export", E_ie_Z_gtk_I_export, null, null, null }
, { "note_view_new", E_note_tab_Q_note_tab_Z_gtk_I_new, null, null, null }
, { "note_view_fork", E_note_tab_Q_note_tab_Z_gtk_I_fork, null, null, null }
, { "note_view_delete", E_note_tab_Q_note_tab_Z_gtk_I_delete, null, null, null }
, { "note_view_fork_tabs", E_note_tab_Q_new_tab_names_Z_gtk_I_fork_tabs, null, null, null }
, { "note_view_prev", E_note_tab_Q_note_tab_Z_gtk_I_prev, null, null, null }
, { "note_view_next", E_note_tab_Q_note_tab_Z_gtk_I_next, null, null, null }
, { "tree_new_before", E_note_tab_Q_tree_Z_gtk_I_new_before, null, null, null }
, { "tree_new_after", E_note_tab_Q_tree_Z_gtk_I_new_after, null, null, null }
, { "tree_new_first", E_note_tab_Q_tree_Z_gtk_I_new_first, null, null, null }
, { "tree_new_last", E_note_tab_Q_tree_Z_gtk_I_new_last, null, null, null }
, { "tree_new_child_first", E_note_tab_Q_tree_Z_gtk_I_new_child_first, null, null, null }
, { "tree_new_child_last", E_note_tab_Q_tree_Z_gtk_I_new_child_last, null, null, null }
, { "tree_delete", E_note_tab_Q_tree_Z_gtk_I_delete, null, null, null }
, { "tree_export", E_ie_Q_tree_Z_gtk_I_export_branch, null, null, null }
, { "note_undo", E_undo_Q_note_Z_gtk_I_undo, null, null, null }
, { "note_redo", E_undo_Q_note_Z_gtk_I_redo, null, null, null }
};
//void *E_main_Q_flow_S_async_result, *E_main_Q_flow_S_async_result_2;
//void *E_main_Q_flow_S_async_finish = null;
GtkApplication *E_main_Q_app_S;
GtkWindow *E_main_Q_window_S;
GtkInfoBar *E_main_Q_info_bar_S;
//=============================================================================
void
E_main_Z_gtk_I_process_events( void
){  for( unsigned i = 0; i < 6000; i++ )
        while( gtk_events_pending() )
            gtk_main_iteration();
}
//void
//E_main_Z_gtk_Q_flow_X_async( GObject *source_object
//, GAsyncResult *result
//, void *data
//){  E_main_Q_flow_S_async_result = (( void * (*)( void *, GAsyncResult *, GError ** )) E_main_Q_flow_S_async_finish )( data, result, &E_error_S );
    //gtk_main_quit();
//}
//void
//E_main_Z_gtk_Q_flow_X_async_2( GObject *source_object
//, GAsyncResult *result
//, void *data
//){  E_main_Q_flow_S_async_result = (( void * (*)( void *, GAsyncResult *, void **, GError ** )) E_main_Q_flow_S_async_finish )( data, result, &E_main_Q_flow_S_async_result_2, &E_error_S );
    //gtk_main_quit();
//}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_main_Q_window_P_title( void
){  if( E_file_S )
    {	char *filename = g_file_get_parse_name( E_file_S );
        char *title = g_strconcat( "“", filename, "” in ‟ouxy notepad”", null );
        g_free(filename);
        gtk_window_set_title( E_main_Q_window_S, title );
        g_free(title);
    }else
        gtk_window_set_title( E_main_Q_window_S, "no file in ‟ouxy notepad”" );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_main_Z_gtk_Q_program_X_activate( GApplication *app
, void *data
){  gtk_window_present( E_main_Q_window_S );
}
_EXPORT_OBFUSCATE
gboolean
E_main_Z_gtk_Q_window_X_delete( GtkWidget *widget
, GdkEvent *event
, void *data
){  E_file_Z_gtk_I_save( null, null, null );
    return E_file_S_autosave_id;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_main_Z_gtk_Q_program_I_about( GSimpleAction *action
, GVariant *param
, void *data
){  const char *const cksum_0 = "4fbd65380cdd255951079008b364516c";
    GFile *lgpl = g_file_new_for_path( "external/lgpl-2.1.txt" );
    char *s_lgpl;
    bool loaded;
    if( loaded = g_file_load_contents( lgpl, null, &s_lgpl, null, null, null ))
    {   gchar *cksum = g_compute_checksum_for_string( G_CHECKSUM_MD5, s_lgpl, -1 );
        if( strcmp( cksum, cksum_0 ))
        {   g_free( s_lgpl );
            loaded = no;
            s_lgpl = "[ ‘GTK+’ licence file forged";
        }
        g_free( cksum );
    }else
        s_lgpl = "[ ‘GTK+’ licence file open error";
    g_object_unref(lgpl);
    if( !loaded )
        s_lgpl = g_strconcat( s_lgpl, ", search on http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html ]", null );
    char *s_licence = g_strconcat(
      "in any other case/default: all rights reserved."
      "\n" "in case interpretation of incomplete licence text— for interests of authors:"
      "\n\t" "standard ‟oux” public licence with exclusions of ‛not native technology’"
      "\n\t" "(„no responsibility for your data processing in program,"
      "\n\t" "implementation errors will be corrected, behaviour will be improved”)."
      "\n" "⁂"
      "\n" "in terms of ‘GTK+’ library ‘LGPL’ licence"
      "\n" "this program is the only “work that uses the Library” as stated in ‘LGPL’ section 5."
      "\n" "if in the law where the program would be used there is assumption This alone is not"
      "\n" "in isolation or in some time this program could be treated as stated in ‘LGPL’ section 6,"
      "\n" "then the licence is not given and you cannot use this program."
      "\n" "⁂"
      "\n" "licence for ‘GTK+’ library available in your system this program is linked with:"
      "\n"
    , s_lgpl
    , null
    );
    g_free( s_lgpl );
    gtk_show_about_dialog( E_main_Q_window_S
    , "program-name", "ouxy notepad"
    , "version", "0.16.0.2 (" __DATE__ ")"
    , "comments", "where an infinity ends or begins…"
    , "copyright", "©2013‐2021 overcq"
    , "authors", ( char *[] ){ "ocq@tutanota.com (overcq)", null }
    , "license", s_licence
    , null
    );
    g_free( s_licence );
}
void
E_main_Z_gtk_Q_program_I_quit( GSimpleAction *action
, GVariant *param
, void *data
){  E_file_Z_gtk_I_save( null, null, null );
    if( !E_file_S_autosave_id )
        gtk_widget_destroy(( void * )E_main_Q_window_S );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
main(
  int argc
, char *argv[]
){  E_main_Q_app_S = gtk_application_new( "com.ouxy.notepad", G_APPLICATION_IS_SERVICE );
    if( !g_application_register(( void * )E_main_Q_app_S, null, null ))
        return -1;
    g_action_map_add_action_entries(( void * )E_main_Q_app_S, E_note_tab_Z_gtk_Q_app_actions, sizeof( E_note_tab_Z_gtk_Q_app_actions ) / sizeof( E_note_tab_Z_gtk_Q_app_actions[0] ), null );
    E_note_tab_Q_actions_Z_tree_P_enabled(no);
    E_note_tab_Q_actions_Z_note_P_enabled(no);
    E_note_tab_Q_note_tab_S_new_tab_names_list_store = ( void * )E_note_tab_Q_new_tab_names_Q_store_M();
    E_note_tab_Q_note_tab_S_books_tree_store = ( void * )E_note_tab_Q_tree_Q_store_M();
    GtkListStore *list_store = gtk_list_store_new( 1, G_TYPE_INT );
    ///‘dirty trick’ zamiast utworzenia własnych klas potomnych “GtkTreeStore” i  “GtkListStore”, by zaimplementować globalizowane w tym programie ‘drag and drop’ ‘high‐level’ dla ‟GTK+”.
    GtkTreeDragSourceIface *drag_source_iface_1 = GTK_TREE_DRAG_SOURCE_GET_IFACE( E_note_tab_Q_note_tab_S_books_tree_store );
    GtkTreeDragSourceIface *drag_source_iface_2 = GTK_TREE_DRAG_SOURCE_GET_IFACE( list_store );
    drag_source_iface_2->row_draggable = drag_source_iface_1->row_draggable = E_dnd_Z_gtk_Q_tree_drag_source_I_row_draggable;
    drag_source_iface_2->drag_data_get = drag_source_iface_1->drag_data_get = E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_get;
    drag_source_iface_2->drag_data_delete = drag_source_iface_1->drag_data_delete = E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete;
    GtkTreeDragDestIface *drag_dest_iface_1 = GTK_TREE_DRAG_DEST_GET_IFACE( E_note_tab_Q_note_tab_S_books_tree_store );
    GtkTreeDragDestIface *drag_dest_iface_2 = GTK_TREE_DRAG_DEST_GET_IFACE( list_store );
    drag_dest_iface_2->row_drop_possible = drag_dest_iface_1->row_drop_possible = E_dnd_Z_gtk_Q_tree_drag_dest_I_row_drop_possible;
    drag_dest_iface_2->drag_data_received = drag_dest_iface_1->drag_data_received = E_dnd_Z_gtk_Q_tree_drag_dest_I_drag_data_received;
    g_object_unref( list_store );
    ///okno główne
    E_note_tab_U_ignore_change = yes;
    GtkBuilder *builder = gtk_builder_new();
    if( !gtk_builder_add_from_file( builder, "window.ui", null ))
        return -1;
    gtk_application_set_app_menu( E_main_Q_app_S, ( void * )gtk_builder_get_object( builder, Q_builder_Z_app_menu ));
    gtk_application_set_menubar( E_main_Q_app_S, ( void * )gtk_builder_get_object( builder, Q_builder_Z_app_menu_bar ));
    E_main_Q_window_S = ( void * )gtk_builder_get_object( builder, Q_builder_Z_window );
    gtk_application_add_window( E_main_Q_app_S, E_main_Q_window_S );
    E_main_Q_info_bar_S = ( void * )gtk_builder_get_object( builder, Q_builder_Z_info_bar );
    E_error_Q_info_bar_S_error_list = ( void * )gtk_builder_get_object( builder, Q_builder_Z_info_bar_error_list );
    E_note_tab_Q_note_tab_S = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note_views );
    E_note_tab_Q_note_S_tag_table = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note_tag_table );
    g_object_ref( E_note_tab_Q_note_S_tag_table );
    E_note_tab_Q_note_Z_tag_S_search = ( void * )gtk_builder_get_object( builder, Q_builder_Z_note_search_tag );
    gtk_builder_connect_signals( builder, null );
    g_object_unref(builder);
    E_clipboard_S_0 = gtk_widget_get_clipboard(( void * )E_main_Q_window_S, GDK_SELECTION_CLIPBOARD );
    E_clipboard_S_1 = gtk_widget_get_clipboard(( void * )E_main_Q_window_S, GDK_SELECTION_PRIMARY );
    E_clipboard_S_2 = gtk_widget_get_clipboard(( void * )E_main_Q_window_S, GDK_SELECTION_SECONDARY );
    E_dnd_Q_tree_Z_data_type_S_native = gdk_atom_intern_static_string( E_dnd_Q_tree_Z_data_type_S_native_S_atom_name );
    E_dnd_Q_tree_Z_data_type_S_text = gdk_atom_intern_static_string( E_dnd_Q_tree_Z_data_type_S_text_S_atom_name );
    ///dane oddzielne okna głównego
    E_note_tab_Q_note_tab_S_ext_data = g_array_sized_new( no, no, sizeof( struct E_note_tab_Q_ext_data_Z ), 1 );
    E_file_Q_dialog_S_last_directory = g_strdup( "" );
    ///uruchomienie okna głównego
    gtk_widget_show_all(( void * )E_main_Q_window_S );
    gtk_widget_hide(( void * )E_main_Q_info_bar_S );
    gtk_window_maximize( E_main_Q_window_S );
    g_signal_connect( E_main_Q_app_S, "activate", ( void * )E_main_Z_gtk_Q_program_X_activate, null );
    ///dane główne programu
    E_file_S_uids = g_hash_table_new( g_int64_hash, g_int64_equal );
    const char *dir = g_get_user_special_dir( G_USER_DIRECTORY_DOCUMENTS );
    if( !dir )
        dir = g_get_home_dir();
    char *filename = g_build_filename( dir
    , E_file_S_default_filename
    , null
    );
    if( !E_file_Q_file_I_load(filename)
    && !gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S )
    ){  E_note_tab_U_ignore_change = yes;
        int tab = E_note_tab_Q_note_tab_M_();
        if( tab == -1 )
            return -1;
        E_note_tab_Q_note_tab_Q_label_P( tab, null );
        E_main_Q_window_P_title();
    }
    g_free(filename);
    ///pętla wykonywania
    gtk_widget_grab_focus(( void * )E_note_tab_Q_note_tab_S );
    g_timeout_add_full( G_PRIORITY_LOW, 183, E_main_I_run_post_init, null, null );
    return g_application_run(( void * )E_main_Q_app_S, argc, argv );
}
//-----------------------------------------------------------------------------
gboolean
E_main_I_run_post_init( void *data
){  E_note_tab_U_ignore_change = no;
    return G_SOURCE_REMOVE;
}
/******************************************************************************/
