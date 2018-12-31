//=============================================================================
//utrzymywanie powiązanego pliku przez sumę kontrolną dla zapisu inkrementacyjnego.
//samoczynny zapis inkrementacyjny, taśmowy, w celu oszczędzania nośnika danych.
//=============================================================================
const char *E_file_S_default_filename = "notepad_gj3d";
const char E_file_S_header[] = "gj3d\0notepad";
const gsize E_file_S_buffer_size = 1024 * 128;
const unsigned E_file_S_saved_version = 6;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned E_file_S_loaded_version;
unsigned E_file_S_autosave_id = 0; //identyfikator zadania (“source”) pętli głównej ‟GTK+” równoznaczny ze stanem dokonania przez operatora jakiejkolwiek zmiany danych względem tych w pliku.
GFile *E_file_S = null;
char *E_file_S_etag = null;
char *E_file_Q_dialog_S_last_directory;
GHashTable *E_file_S_uids;
//=============================================================================
bool
E_file_R_etag_changed( void
){  GFileInfo *info = g_file_query_info( E_file_S, G_FILE_ATTRIBUTE_ETAG_VALUE, G_FILE_QUERY_INFO_NONE, null, &E_error_S );
    E_error_J_return_1( "read “etag”" );
    bool etag_changed = strcmp( E_file_S_etag, g_file_info_get_etag(info) );
    g_object_unref(info);
    if( etag_changed )
        E_file_P_changed();
    return etag_changed;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_file_P_changed( void
){  if( E_note_tab_U_ignore_change )
        return;
    if( !E_file_S_autosave_id )
        E_file_S_autosave_id = g_timeout_add_seconds( 1000, E_file_Z_gtk_Y_auto_save, null );
}
gboolean
E_file_Z_gtk_Y_auto_save( void *data
){  E_file_Z_gtk_I_save( null, null, null );
    return G_SOURCE_CONTINUE;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_file_Z_gtk_I_new( GSimpleAction *action
, GVariant *param
, void *data
){  GtkWidget *dialog = gtk_file_chooser_dialog_new( "new file"
    , E_main_Q_window_S
    , GTK_FILE_CHOOSER_ACTION_SAVE
    , "_cancel", GTK_RESPONSE_CANCEL
    , "_new", GTK_RESPONSE_ACCEPT
    , null
    );
    gtk_file_chooser_add_shortcut_folder(( void * )dialog, E_file_Q_dialog_S_last_directory, null );
    char *backup_source_etag = null;
    g_signal_connect( dialog, "confirm-overwrite", ( void * )E_file_Z_gtk_Q_dialog_X_confirm_overwrite, &backup_source_etag );
    gtk_file_chooser_set_do_overwrite_confirmation(( void * )dialog, yes );
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_P_enabled(no);
#endif
    int result = gtk_dialog_run(( void * )dialog );
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_P_enabled(yes);
#endif
    if( result == GTK_RESPONSE_ACCEPT )
    {   E_file_Z_gtk_I_save( null, null, null );
        if( !E_file_S_autosave_id )
        {   g_object_unref0( E_file_S );
            g_free( E_file_S_etag );
            E_note_tab_U_ignore_change = yes;
            E_note_tab_Q_note_tab_P_clear();
            E_error_Z_gtk_Q_program_I_err_clear( null, null, null );
            int tab = E_note_tab_Q_note_tab_M_();
            E_note_tab_I_unignore_change();
            if( tab != -1 )
                E_note_tab_Q_note_tab_Q_label_P( tab, null );
            char *path = gtk_file_chooser_get_filename(( void * )dialog );
            E_file_S = g_file_new_for_path(path);
            E_file_S_etag = backup_source_etag;
            g_free(path);
            E_main_Q_window_P_title();
        }else
            g_free( backup_source_etag );
    }else
        g_free( backup_source_etag );
    char *s = gtk_file_chooser_get_current_folder(( void * )dialog );
    if(s)
    {   g_free( E_file_Q_dialog_S_last_directory );
        E_file_Q_dialog_S_last_directory = s;
    }
    gtk_widget_destroy(dialog);
}
void
E_file_Z_gtk_I_open( GSimpleAction *action
, GVariant *param
, void *data
){  GtkWidget *dialog = gtk_file_chooser_dialog_new( "open file"
    , E_main_Q_window_S
    , GTK_FILE_CHOOSER_ACTION_OPEN
    , "_cancel", GTK_RESPONSE_CANCEL
    , "_open", GTK_RESPONSE_ACCEPT
    , null
    );
    gtk_file_chooser_add_shortcut_folder(( void * )dialog, E_file_Q_dialog_S_last_directory, null );
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_P_enabled(no);
#endif
    int result = gtk_dialog_run(( void * )dialog );
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_P_enabled(yes);
#endif
    if( result == GTK_RESPONSE_ACCEPT )
    {   E_file_Z_gtk_I_save( null, null, null );
        if( !E_file_S_autosave_id )
        {   char *path = gtk_file_chooser_get_filename(( void * )dialog );
            E_file_Q_file_I_load(path);
            g_free(path);
        }
    }
    char *s = gtk_file_chooser_get_current_folder(( void * )dialog );
    if(s)
    {   g_free( E_file_Q_dialog_S_last_directory );
        E_file_Q_dialog_S_last_directory = s;
    }
    gtk_widget_destroy(dialog);
}
void
E_file_Z_gtk_I_save( GSimpleAction *action
, GVariant *param
, void *data
){  if( E_file_S )
    {   if( E_file_S_etag )
        {   if( !E_file_S_autosave_id
            && !E_file_R_etag_changed()
            )
                return;
            char *path = g_file_get_path( E_file_S );
            if( E_file_I_backup( path, E_file_S_etag ))
            {   g_clear_pointer( &E_file_S_etag, g_free );
                E_file_Q_file_I_save();
            }else
                g_clear_pointer( &E_file_S_etag, g_free );
            g_free(path);
        }else
            E_file_Q_file_I_save();
    }else if( E_file_S_autosave_id )
    {   GtkWidget *dialog = gtk_file_chooser_dialog_new( action ? "save file" : "before that command— save file"
        , E_main_Q_window_S
        , GTK_FILE_CHOOSER_ACTION_SAVE
        , "_cancel", GTK_RESPONSE_CANCEL
        , "_save", GTK_RESPONSE_ACCEPT
        , null
        );
        gtk_file_chooser_add_shortcut_folder(( void * )dialog, E_file_Q_dialog_S_last_directory, null );
        char *backup_source_etag = null;
        g_signal_connect( dialog, "confirm-overwrite", ( void * )E_file_Z_gtk_Q_dialog_X_confirm_overwrite, &backup_source_etag );
        gtk_file_chooser_set_do_overwrite_confirmation(( void * )dialog, yes );
#ifdef C_kdb_focus_wa
        E_note_tab_I_kbd_focus_wa_P_enabled(no);
#endif
        int result = gtk_dialog_run(( void * )dialog );
#ifdef C_kdb_focus_wa
        E_note_tab_I_kbd_focus_wa_P_enabled(yes);
#endif
        if( result == GTK_RESPONSE_ACCEPT )
        {   char *path = gtk_file_chooser_get_filename(( void * )dialog );
            E_file_S = g_file_new_for_path(path);
            if( E_file_I_backup( path, backup_source_etag ))
                E_file_Q_file_I_save();
            g_free(path);
            E_main_Q_window_P_title();
        }
        g_free( backup_source_etag );
        char *s = gtk_file_chooser_get_current_folder(( void * )dialog );
        if(s)
        {   g_free( E_file_Q_dialog_S_last_directory );
            E_file_Q_dialog_S_last_directory = s;
        }
        gtk_widget_destroy(dialog);
    }
}
void
E_file_Z_gtk_I_rename( GSimpleAction *action
, GVariant *param
, void *data
){  if( !E_file_S )
        return;
    GtkWidget *dialog = gtk_file_chooser_dialog_new( "save into new file"
    , E_main_Q_window_S
    , GTK_FILE_CHOOSER_ACTION_SAVE
    , "_cancel", GTK_RESPONSE_CANCEL
    , "_save", GTK_RESPONSE_ACCEPT
    , null
    );
    gtk_file_chooser_add_shortcut_folder(( void * )dialog, E_file_Q_dialog_S_last_directory, null );
    char *backup_source_etag = null;
    g_signal_connect( dialog, "confirm-overwrite", ( void * )E_file_Z_gtk_Q_dialog_X_confirm_overwrite, &backup_source_etag );
    gtk_file_chooser_set_do_overwrite_confirmation(( void * )dialog, yes );
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_P_enabled(no);
#endif
    int result = gtk_dialog_run(( void * )dialog );
#ifdef C_kdb_focus_wa
    E_note_tab_I_kbd_focus_wa_P_enabled(yes);
#endif
    if( result == GTK_RESPONSE_ACCEPT )
    {   E_file_Z_gtk_I_save( null, null, null );
        g_object_unref( E_file_S );
        char *path = gtk_file_chooser_get_filename(( void * )dialog );
        E_file_S = g_file_new_for_path(path);
        g_clear_pointer( &E_file_S_etag, g_free );
        if( E_file_I_backup( path, backup_source_etag ))
            E_file_Q_file_I_save();
        g_free(path);
        E_main_Q_window_P_title();
    }
    g_free( backup_source_etag );
    char *s = gtk_file_chooser_get_current_folder(( void * )dialog );
    if(s)
    {   g_free( E_file_Q_dialog_S_last_directory );
        E_file_Q_dialog_S_last_directory = s;
    }
    gtk_widget_destroy(dialog);
}
//-----------------------------------------------------------------------------
GtkFileChooserConfirmation
E_file_Z_gtk_Q_dialog_I_no_overwrite( GtkFileChooser *file_chooser
, void *data
){  return GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN;
}
GtkFileChooserConfirmation
E_file_Z_gtk_Q_dialog_X_confirm_overwrite( GtkFileChooser *file_chooser
, void *data
){  char *path = gtk_file_chooser_get_filename( file_chooser );
    bool b = E_file_Z_gtk_Q_dialog_X_confirm_overwrite_R_my_cnt_sign(path);
    if(b)
    {   GFile *file = g_file_new_for_path(path);
        g_free(path);
        GFileInfo *info = g_file_query_info( file, G_FILE_ATTRIBUTE_ETAG_VALUE, G_FILE_QUERY_INFO_NONE, null, &E_error_S );
        g_object_unref(file);
        if( E_error_S )
        {   E_error_K( "read “etag” for overwrite confirmation" );
            return GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN;
        }
        *( char ** ) data = g_strdup( g_file_info_get_etag(info) );
        g_object_unref(info);
    }else
        g_free(path);
    return b ? GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM : GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN;
}
bool
E_file_Z_gtk_Q_dialog_X_confirm_overwrite_R_my_cnt_sign( char *path
){  GFile *file = g_file_new_for_path(path);
    GFileInputStream *stream = g_file_read( file, null, &E_error_S );
    g_object_unref(file);
    E_error_J_return_0( "open the file being overwritten" );
    GString *sign = g_string_sized_new( sizeof( E_file_S_header ));
    g_string_set_size( sign, sizeof( E_file_S_header ));
    gsize n;
    if( !g_input_stream_read_all(( void * )stream, sign->str, sign->len, &n, null, &E_error_S )
    || E_error_S
    || n != sign->len
    ){  g_object_unref(stream);
        g_string_free( sign, yes );
        E_error_K( "read content of the file being overwritten" );
        return no;
    }
    bool b = n == sign->len && !memcmp( sign->str, E_file_S_header, sign->len );
    g_string_free( sign, yes );
    return b;
}
bool
E_file_I_backup( char *path
, char *etag
){  if( !etag )
        return yes;
    GFile *file = g_file_new_for_path(path);
    unsigned long i = 0;
    bool b = yes;
    do
    {   GString *backup_path = g_string_new( "" );
        char *basename = g_file_get_basename(file);
        g_string_append_len( backup_path, path, strlen(path) - strlen(basename) );
        g_string_append_printf( backup_path, ".#%s.~%lu~", basename, i );
        g_free(basename);
        GFile *backup_file = g_file_new_for_path( backup_path->str );
        g_string_free( backup_path, yes );
        GFileInfo *info = g_file_query_info( file, G_FILE_ATTRIBUTE_ETAG_VALUE, G_FILE_QUERY_INFO_NONE, null, &E_error_S );
        if( E_error_S )
        {   E_error_K( "read “etag” for backup" );
            g_object_unref( backup_file );
            b = yes;
            break;
        }
        if( strcmp( etag, g_file_info_get_etag(info) ))
        {   g_object_unref(info);
            g_object_unref( backup_file );
            b = no;
            break;
        }
        g_object_unref(info);
        g_file_move( file, backup_file
        , G_FILE_COPY_NONE
        , null
        , null
        , null
        , &E_error_S
        );
        g_object_unref( backup_file );
    }while( E_error_S && ( g_clear_error( &E_error_S ), yes )
    && ((( b = ~i ) && i++ ), b )
    );
    g_object_unref(file);
    return b;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
E_file_Q_file_I_load( char *path
){  g_application_mark_busy(( void * )E_main_Q_app_S );
    GFile *file = g_file_new_for_path(path);
    GFileInputStream *in_direct = g_file_read( file, null, &E_error_S );
    E_error_J_return_0( "open file" )
    {   g_object_unref(file);
        g_application_unmark_busy(( void * )E_main_Q_app_S );
    }
    GInputStream *in_buffered = g_buffered_input_stream_new_sized(( void * )in_direct, E_file_S_buffer_size );
    GString *s = g_string_sized_new( sizeof( E_file_S_header ) + 2 );
    g_string_set_size( s, sizeof( E_file_S_header ) + 2 );
    gsize n;
    if( !g_input_stream_read_all( in_buffered, s->str, s->len, &n, null, &E_error_S )
    || E_error_S
    || n != s->len
    ){  g_object_unref(file);
        g_string_free( s, yes );
        g_object_unref( in_direct );
        g_object_unref( in_buffered );
        g_application_unmark_busy(( void * )E_main_Q_app_S );
        E_error_K( "read from the file" );
        return no;
    }
    bool success;
    if( !memcmp( s->str, E_file_S_header, s->len - 2 )
    && s->str[ s->len - 1 ] == '\0'
    && ( s->str[ s->len - 2 ] == ( E_file_S_loaded_version = E_file_S_saved_version )
        || s->str[ s->len - 2 ] == ( E_file_S_loaded_version = 5 )
        || s->str[ s->len - 2 ] == ( E_file_S_loaded_version = 4 )
      )
    ){  g_string_free( s, yes );
        GZlibDecompressor *decompressor = g_zlib_decompressor_new( G_ZLIB_COMPRESSOR_FORMAT_RAW );
        GInputStream *in_compressed = g_converter_input_stream_new( in_buffered, ( void * )decompressor );
        g_object_unref( in_buffered );
        g_object_unref(decompressor);
        GDataInputStream *in_data = g_data_input_stream_new( in_compressed );
        g_object_unref( in_compressed );
        g_data_input_stream_set_byte_order( in_data, G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN );
        E_note_tab_U_ignore_change = yes;
        E_note_tab_Q_note_tab_P_clear();
        g_hash_table_destroy( E_file_S_uids );
        E_file_S_uids = g_hash_table_new( g_int64_hash, g_int64_equal );
        success = E_file_Q_file_I_load_I_tree( in_data, ( void * )E_note_tab_Q_note_tab_S_books_tree_store, E_file_Q_file_I_load_I_tree_I_notes );
        if( success
        && E_file_S_loaded_version > 4
        ){  int n = g_data_input_stream_read_int16( in_data, null, &E_error_S );
            if( E_error_S )
            {   success = no;
                E_error_K( "read from the file" );
            }
            if(success)
                for( int i = 0; i < n; i++ )
                {   char *s = E_file_Q_file_I_read( in_data );
                    int tab = E_note_tab_Q_note_tab_M_();
                    if( tab == -1 )
                    {   success = no;
                        break;
                    }
                    E_note_tab_Q_note_tab_Q_label_P( tab, s );
                    g_free(s);
                    s = E_file_Q_file_I_read( in_data );
                    if( !s )
                    {   success = no;
                        break;
                    }
                    if( *s )
                    {   GtkTreePath *path = gtk_tree_path_new_from_string(s);
                        g_free(s);
                        //E_note_tab_Q_tree_Z_gtk_I_set_cursor_0( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
                        gtk_tree_view_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path, null, no );
                        gtk_tree_path_free(path);
                        s = E_file_Q_file_I_read( in_data );
                        if( !s )
                        {   success = no;
                            break;
                        }
                        if( *s )
                        {   path = gtk_tree_path_new_from_string(s);
                            g_free(s);
                            //E_note_tab_Q_tree_Z_gtk_I_set_cursor_0( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                            gtk_tree_view_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path, null, no );
                            gtk_tree_path_free(path);
                        }else
                            g_free(s);
                    }else
                        g_free(s);
                }
            if(success)
            {   int tab = g_data_input_stream_read_int16( in_data, null, &E_error_S );
                if( E_error_S )
                {   success = no;
                    E_error_K( "read from the file" );
                }else
                    gtk_notebook_set_current_page( E_note_tab_Q_note_tab_S, tab );
            }
        }
        if(success)
        {   g_object_unref0( E_file_S );
            E_file_S = file;
            g_free( E_file_S_etag );
            GFileInfo *info = g_file_input_stream_query_info( in_direct, G_FILE_ATTRIBUTE_ETAG_VALUE, null, null );
            E_file_S_etag = g_strdup( g_file_info_get_etag(info) );
            g_object_unref(info);
            E_error_Z_gtk_Q_program_I_err_clear( null, null, null );
        }else
        {   g_object_unref(file);
            g_clear_object( &E_file_S );
            g_clear_pointer( &E_file_S_etag, g_free );
            E_note_tab_Q_note_tab_P_clear();
        }
        g_object_unref( in_data );
        int tab;
        if( !success
        || E_file_S_loaded_version < 5
        ){  tab = E_note_tab_Q_note_tab_M_();
            if( tab != -1 )
                E_note_tab_Q_note_tab_Q_label_P( tab, null );
        }
        E_note_tab_I_unignore_change();
        E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_focus();
        E_main_Q_window_P_title();
    }else
    {   success = no;
        g_object_unref(file);
        g_string_free( s, yes );
        g_object_unref( in_buffered );
    }
    g_object_unref( in_direct );
    g_application_unmark_busy(( void * )E_main_Q_app_S );
    return success;
}
bool
E_file_Q_file_I_load_I_tree( GDataInputStream *in
, GtkTreeStore *tree_store
, bool ( *proc_for_cnt )( GDataInputStream *, void **, void ** )
){  bool success = yes;
    GtkTreeIter iter, new_iter;
    bool toplevel = yes;
    while(empty)
    {   char *s = E_file_Q_file_I_read(in);
        if( !s )
        {   success = no;
            break;
        }
        if( !*s )
        {   g_free(s);
            if(toplevel)
                break;
            if( gtk_tree_model_iter_parent(( void * )tree_store, &new_iter, &iter ))
                iter = new_iter;
            else
                toplevel = yes;
            continue;
        }
        if( !strcmp( s, "﻿" ))
        {   g_free(s);
            s = g_strdup( "" );
        }
        void *p, *d;
        if( !proc_for_cnt( in, &p, &d ))
        {   success = no;
            g_free(s);
            g_object_unref(p);
            break;
        }
        gtk_tree_store_append( tree_store, &new_iter, ( toplevel ? null : &iter ));
        iter = new_iter;
        toplevel = no;
        gtk_tree_store_set( tree_store
        , &iter
        , E_note_tab_Q_tree_Z_column_S_title, s
        , E_note_tab_Q_tree_Z_column_S_object_ref, p
        , E_note_tab_Q_tree_Z_column_S_ext_data, d
        , -1
        );
        g_free(s);
        g_object_unref(p);
    }
    return success;
}
bool
E_file_Q_file_I_load_I_tree_I_notes( GDataInputStream *in
, void **notes_tree_store
, void **ext_data
){  *notes_tree_store = E_note_tab_Q_tree_Q_store_M();
    *ext_data = null;
    return E_file_Q_file_I_load_I_tree( in, *notes_tree_store, E_file_Q_file_I_load_I_tree_I_note );
}
bool
E_file_Q_file_I_load_I_tree_I_note( GDataInputStream *in
, void **note_buffer
, void **ext_data
){  bool success = yes;
    char *s = E_file_Q_file_I_read(in);
    if(s)
    {   if( *s )
        {   char *s_ = s;
            s = g_strconcat( s_, "\n", null );
            g_free( s_ );
        }
    }else
    {   success = no;
        s = g_strdup( "" );
    }
    *note_buffer = E_note_tab_Q_note_Q_buffer_M(s);
    g_free(s);
    *ext_data = E_note_tab_Q_note_Z_ext_data_M();
    if( E_file_S_loaded_version > 5 )
    {   ( *( struct E_note_tab_Q_note_Z_ext_data ** ) ext_data )->date_uid = E_note_tab_I_uniq_date_uid( g_data_input_stream_read_int64( in, null, &E_error_S ));
        E_error_J_return_0( "read from the file" );
    }else
        ( *( struct E_note_tab_Q_note_Z_ext_data ** ) ext_data )->date_uid = E_note_tab_I_uniq_date_uid(0);
    return success;
}
char *
E_file_Q_file_I_read( GDataInputStream *in
){  char *s = g_data_input_stream_read_upto( in, "", 1, null, null, &E_error_S );
    E_error_J_return_0( "read from the file" );
    if( !s ) //“end of file”
        if( E_file_S_loaded_version < 5 )
            return g_strdup( "" );
        else
            return null;
    g_data_input_stream_read_byte( in, null, &E_error_S );
    E_error_J_return_0( "read from the file" )
        g_free(s);
    char *s_ = g_utf8_normalize( s, -1, G_NORMALIZE_DEFAULT_COMPOSE );
    g_free(s);
    if( s_ )
        g_strstrip( s_ );
    else
        E_error_K( "‘utf-8’ normalize" );
    return s_;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
E_file_Q_file_I_save( void
){  g_application_mark_busy(( void * )E_main_Q_app_S );
    GFileOutputStream *out_direct;
    if( E_file_S_etag )
    {   out_direct = g_file_replace( E_file_S, E_file_S_etag, no, G_FILE_CREATE_NONE, null, &E_error_S );
        E_error_J_return_0( "replace file" )
            g_application_unmark_busy(( void * )E_main_Q_app_S );
    }else
    {   out_direct = g_file_create( E_file_S, G_FILE_CREATE_NONE, null, &E_error_S );
        E_error_J_return_0( "create file" )
            g_application_unmark_busy(( void * )E_main_Q_app_S );
    }
    GOutputStream *out_buffered = g_buffered_output_stream_new_sized(( void * )out_direct, E_file_S_buffer_size );
    GString *s = g_string_new_len( E_file_S_header, sizeof( E_file_S_header ));
    g_string_append_c( s, E_file_S_saved_version );
    g_string_append_c( s, '\0' );
    if( !E_file_Q_file_I_write( out_buffered, s ))
    {   g_string_free( s, yes );
        g_object_unref( out_direct );
        g_object_unref( out_buffered );
        g_clear_pointer( &E_file_S_etag, g_free );
        g_application_unmark_busy(( void * )E_main_Q_app_S );
        return no;
    }
    GZlibCompressor *compressor = g_zlib_compressor_new( G_ZLIB_COMPRESSOR_FORMAT_RAW, 9 );
    GOutputStream *out_compressed = g_converter_output_stream_new( out_buffered, ( void * )compressor );
    g_object_unref( out_buffered );
    g_object_unref(compressor);
    GDataOutputStream *out_data = g_data_output_stream_new( out_compressed );
    g_object_unref( out_compressed );
    g_data_output_stream_set_byte_order( out_data, G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN );
    bool success = E_file_Q_file_I_save_I_tree( out_data, s, E_note_tab_Q_note_tab_S_books_tree_store, E_file_Q_file_I_save_I_tree_I_notes );
    if(success)
        success = E_file_Q_file_I_write( out_data, s );
    if(success)
    {   g_data_output_stream_put_int16( out_data, gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S ), null, &E_error_S );
        if( E_error_S )
        {   success = no;
            E_error_K( "write to the file" );
        }
    }
    if(success)
    {   int i = 0;
        GtkWidget *tab;
        while( tab = gtk_notebook_get_nth_page( E_note_tab_Q_note_tab_S, i ))
        {   g_string_append( s, gtk_notebook_get_tab_label_text( E_note_tab_Q_note_tab_S, tab ));
            g_string_append_c( s, '\0' );
            GtkTreeIter iter;
            GtkTreeModel *tree_store;
            if( gtk_tree_selection_get_selected( gtk_tree_view_get_selection( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, i ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ), &tree_store, &iter ))
            {   char *s_ = gtk_tree_model_get_string_from_iter( tree_store, &iter );
                g_string_append( s, s_ );
                g_free( s_ );
                g_string_append_c( s, '\0' );
                if( gtk_tree_selection_get_selected( gtk_tree_view_get_selection( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, i ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] ), &tree_store, &iter ))
                {   char *s_ = gtk_tree_model_get_string_from_iter( tree_store, &iter );
                    g_string_append( s, s_ );
                    g_free( s_ );
                }
            }
            g_string_append_c( s, '\0' );
            success = E_file_Q_file_I_write( out_data, s );
            if( !success )
                break;
            i++;
        }
    }
    if(success)
    {   g_data_output_stream_put_int16( out_data, E_note_tab_Q_note_tab_S_current_tab, null, &E_error_S );
        if( E_error_S )
        {   success = no;
            E_error_K( "write to the file" );
        }
    }
    if(success)
    {   g_output_stream_close(( void * )out_data, null, &E_error_S );
        if( E_error_S )
        {   success = no;
            E_error_K( "write to the file" );
        }else
        {   g_free( E_file_S_etag );
            E_file_S_etag = g_strdup( g_file_output_stream_get_etag( out_direct ));
            if( E_file_S_autosave_id )
            {   g_source_remove( E_file_S_autosave_id );
                E_file_S_autosave_id = 0;
            }
            E_error_Z_gtk_Q_program_I_err_clear( null, null, null );
        }
    }else
        g_clear_pointer( &E_file_S_etag, g_free );
    g_string_free( s, yes );
    g_object_unref( out_direct );
    g_object_unref( out_data );
    g_application_unmark_busy(( void * )E_main_Q_app_S );
    return success;
}
bool
E_file_Q_file_I_save_I_tree( GDataOutputStream *out
, GString *s
, GtkTreeModel *tree_store
, bool ( *proc_for_cnt )( GDataOutputStream *, GString *, void *, void * )
){  bool success = yes;
    GtkTreeIter iter, old_iter;
    if( gtk_tree_model_get_iter_first( tree_store, &iter ))
    {   while(empty)
        {   success = E_file_Q_file_I_write( out, s );
            if( !success )
                break;
            char *t;
            void *p, *d;
            gtk_tree_model_get( tree_store
            , &iter
            , E_note_tab_Q_tree_Z_column_S_title, &t
            , E_note_tab_Q_tree_Z_column_S_object_ref, &p
            , E_note_tab_Q_tree_Z_column_S_ext_data, &d
            , -1
            );
            g_object_unref(p);
            g_string_append( s, *t ? t : "﻿" );
            g_free(t);
            g_string_append_c( s, '\0' );
            success = proc_for_cnt( out, s, p, d );
            if( !success )
                break;
            old_iter = iter;
            if( gtk_tree_model_iter_children( tree_store, &iter, &old_iter ))
                continue;
            g_string_append_c( s, '\0' );
            iter = old_iter;
            while( !gtk_tree_model_iter_next( tree_store, &iter ))
            {   g_string_append_c( s, '\0' );
                if( !gtk_tree_model_iter_parent( tree_store, &iter, &old_iter ))
                    goto End;
                old_iter = iter;
            }
        }
End:    ;
    }else
        g_string_append_c( s, '\0' );
    return success;
}
bool
E_file_Q_file_I_save_I_tree_I_notes( GDataOutputStream *out
, GString *s
, void *notes_tree_store
, void *ext_data
){  return E_file_Q_file_I_save_I_tree( out, s, notes_tree_store, E_file_Q_file_I_save_I_tree_I_note );
}
bool
E_file_Q_file_I_save_I_tree_I_note( GDataOutputStream *out
, GString *s
, void *note_buffer
, void *ext_data
){  GtkTextIter start_iter, end_iter;
    gtk_text_buffer_get_start_iter( note_buffer, &start_iter );
    gtk_text_buffer_get_end_iter( note_buffer, &end_iter );
    char *t = gtk_text_iter_get_text( &start_iter, &end_iter );
    g_string_append( s, t );
    g_free(t);
    g_string_append_c( s, '\0' );
    if( !E_file_Q_file_I_write( out, s ))
        return no;
    g_data_output_stream_put_int64( out, (( struct E_note_tab_Q_note_Z_ext_data * ) ext_data )->date_uid, null, &E_error_S );
    E_error_J_return_0( "write to the file" );
    return yes;
}
bool
E_file_Q_file_I_write( void *out
, GString *s
){  gsize n;
    if( !g_output_stream_write_all( out, s->str, s->len, &n, null, &E_error_S )
    || E_error_S
    || n != s->len
    )
    {   E_error_K( "write to the file" );
        return no;
    }
    g_string_truncate( s, 0 );
    return yes;
}
//=============================================================================
