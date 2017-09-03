//==============================================================================
struct E_ie_Z_cnt_headers
{ char *header[2];
  bool ( *R_sign )( GDataInputStream *, char *[] );
  bool ( *I_tree )( GDataInputStream * );
} E_ie_S_cnt_headers[] =
{ { { "<?xml version=\"1.0\"?>"
    }
  , E_ie_Q_xml_file_R_cnt_sign
  , E_ie_Q_xml_file_I_import_I_tree
  }
, { { "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\"><HTML>\n<HEAD>\n<meta content=\"text/html;charset=UTF-8\" http-equiv=\"Content-Type\">\n<meta name=\"generator\" content=\"NoteCase 1.9.8\">\n<TITLE>"
    , "/TITLE>\n</HEAD>\n<BODY>\n<"
    }
  , E_ie_Q_notecase_file_R_cnt_sign
  , E_ie_Q_notecase_file_I_import_I_tree
  } 
};
//==============================================================================
GRegex *E_ie_Q_re;
//==============================================================================
void
E_ie_Z_gtk_I_import( GSimpleAction *action
, GVariant *param
, void *data
){  GtkWidget *dialog = gtk_file_chooser_dialog_new( "import from file"
    , E_main_Q_window_S
    , GTK_FILE_CHOOSER_ACTION_OPEN
    , "_cancel", GTK_RESPONSE_CANCEL
    , "_import", GTK_RESPONSE_ACCEPT
    , null
    );
    gtk_file_chooser_add_shortcut_folder( GTK_FILE_CHOOSER(dialog), E_file_Q_dialog_S_last_directory, null );
    int result = gtk_dialog_run( GTK_DIALOG(dialog) );
    if( result == GTK_RESPONSE_ACCEPT )
    {   char *path = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
        E_ie_I_import(path);
        g_free(path);
    }
    char *s = gtk_file_chooser_get_current_folder( GTK_FILE_CHOOSER(dialog) );
    if(s)
    {   g_free( E_file_Q_dialog_S_last_directory );
        E_file_Q_dialog_S_last_directory = s;
    }
    gtk_widget_destroy(dialog);
}
void
E_ie_Z_gtk_I_export( GSimpleAction *action
, GVariant *param
, void *data
){  GtkWidget *dialog = gtk_file_chooser_dialog_new( "export to file"
    , E_main_Q_window_S
    , GTK_FILE_CHOOSER_ACTION_SAVE
    , "_cancel", GTK_RESPONSE_CANCEL
    , "_export", GTK_RESPONSE_ACCEPT
    , null
    );
    gtk_file_chooser_add_shortcut_folder( GTK_FILE_CHOOSER(dialog), E_file_Q_dialog_S_last_directory, null );
    g_signal_connect( dialog, "confirm-overwrite", G_CALLBACK( E_file_Z_gtk_Q_dialog_I_no_overwrite ), null );
    gtk_file_chooser_set_do_overwrite_confirmation( GTK_FILE_CHOOSER(dialog), yes );
    int result = gtk_dialog_run( GTK_DIALOG(dialog) );
    if( result == GTK_RESPONSE_ACCEPT )
    {   char *path = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
        E_ie_Q_xml_file_I_export(path);
        g_free(path);
    }
    char *s = gtk_file_chooser_get_current_folder( GTK_FILE_CHOOSER(dialog) );
    if(s)
    {   g_free( E_file_Q_dialog_S_last_directory );
        E_file_Q_dialog_S_last_directory = s;
    }
    gtk_widget_destroy(dialog);
}
void
E_ie_Q_tree_Z_gtk_I_export_branch( GSimpleAction *action
, GVariant *param
, void *data
){  GtkWidget *widget = gtk_window_get_focus( E_main_Q_window_S );
    if( !gtk_tree_selection_get_selected( gtk_tree_view_get_selection( GTK_TREE_VIEW(widget) ), null, null ))
        return;
    GtkWidget *dialog = gtk_file_chooser_dialog_new( "export branch to file"
    , E_main_Q_window_S
    , GTK_FILE_CHOOSER_ACTION_SAVE
    , "_cancel", GTK_RESPONSE_CANCEL
    , "_export", GTK_RESPONSE_ACCEPT
    , null
    );
    gtk_file_chooser_add_shortcut_folder( GTK_FILE_CHOOSER(dialog), E_file_Q_dialog_S_last_directory, null );
    g_signal_connect( dialog, "confirm-overwrite", G_CALLBACK( E_file_Z_gtk_Q_dialog_I_no_overwrite ), null );
    gtk_file_chooser_set_do_overwrite_confirmation( GTK_FILE_CHOOSER(dialog), yes );
    int result = gtk_dialog_run( GTK_DIALOG(dialog) );
    if( result == GTK_RESPONSE_ACCEPT )
    {   char *path = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
        E_ie_Q_xml_file_I_export_branch(path);
        g_free(path);
    }
    char *s = gtk_file_chooser_get_current_folder( GTK_FILE_CHOOSER(dialog) );
    if(s)
    {   g_free( E_file_Q_dialog_S_last_directory );
        E_file_Q_dialog_S_last_directory = s;
    }
    gtk_widget_destroy(dialog);
}
//==============================================================================
void
E_ie_I_import( char *path
){  g_application_mark_busy( G_APPLICATION( E_main_Q_app_S ));
    GFile *file = g_file_new_for_path(path);
    for( int i = 0; i < sizeof E_ie_S_cnt_headers / sizeof E_ie_S_cnt_headers[0]; i++ )
    {   GFileInputStream *in_direct = g_file_read( file, null, &E_error_S );
        E_error_J_return( "open file" )
        {   g_object_unref(file);
            g_application_unmark_busy( G_APPLICATION( E_main_Q_app_S ));
        }
        GInputStream *in_buffered = g_buffered_input_stream_new_sized( G_INPUT_STREAM( in_direct ), E_file_S_buffer_size );
        g_object_unref( in_direct );
        GDataInputStream *in_data = g_data_input_stream_new( in_buffered );
        g_object_unref( in_buffered );
        g_data_input_stream_set_byte_order( in_data, G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN );
        if( E_ie_S_cnt_headers[i].R_sign( in_data, &E_ie_S_cnt_headers[i].header[0] ))
        {   E_note_tab_U_ignore_change = yes;
            E_ie_Q_re = g_regex_new( E_string_Q_xml_S_from_entity_re, G_REGEX_OPTIMIZE, 0, null );
            if( !E_ie_S_cnt_headers[i].I_tree( in_data ))
                E_error_K( "import from the file" );
            g_regex_unref( E_ie_Q_re );
            g_object_unref( in_data );
            E_note_tab_I_unignore_change();
            E_file_P_changed();
            break;
        }
        g_object_unref( in_data );
    }
    g_object_unref(file);
    g_application_unmark_busy( G_APPLICATION( E_main_Q_app_S ));
}
bool
E_ie_Q_xml_file_R_cnt_sign( GDataInputStream *in
, char *headers[]
){  size_t length = strlen( headers[0] );
    GString *s = g_string_sized_new(length);
    g_string_set_size( s,  length );
    gssize n = g_input_stream_read( G_INPUT_STREAM(in), s->str, s->len, null, &E_error_S );
    E_error_J_return_0( "read from the file" )
        g_string_free( s, yes );
    if( n == s->len
      && !memcmp( s->str, headers[0], s->len )
    )
    {   g_string_free( s, yes );
        return yes;
    }
    g_string_free( s, yes );
    return no;
}
bool
E_ie_Q_notecase_file_R_cnt_sign( GDataInputStream *in
, char *headers[]
){  size_t length = strlen( headers[0] );
    GString *s = g_string_sized_new(length);
    g_string_set_size( s,  length );
    gssize n = g_input_stream_read( G_INPUT_STREAM(in), s->str, s->len, null, &E_error_S );
    E_error_J_return_0( "read from the file" )
        g_string_free( s, yes );
    if( n == s->len
      && !memcmp( s->str, headers[0], s->len )
    ){  char *s_ = E_ie_I_read_string( in, yes );
        if( s_ )
        {   g_free( s_ );
            length = strlen( headers[1] );
            g_string_set_size( s,  length );
            gssize n = g_input_stream_read( G_INPUT_STREAM(in), s->str, s->len, null, &E_error_S );
            E_error_J_return_0( "read from the file" )
                g_string_free( s, yes );
            if( n == s->len
              && !memcmp( s->str, headers[1], s->len )
            )
            {   g_string_free( s, yes );
                return yes;
            }
        }
    }
    g_string_free( s, yes );
    return no;
}
//------------------------------------------------------------------------------
bool
E_ie_Q_xml_file_I_import_I_tree( GDataInputStream *in
){  bool success = no;
    char *s = E_ie_I_read_string( in, yes );
    if( !s )
        return success;
    s = E_ie_I_read_string( in, no );
    int n;
    if(s)
    {   if( !strcmp( s, "a" ))
        {   g_free(s);
            n = gtk_tree_model_iter_n_children( E_note_tab_Q_note_tab_S_books_tree_store, null );
            success = E_ie_Q_xml_file_I_import_I_tree_( in, GTK_TREE_STORE( E_note_tab_Q_note_tab_S_books_tree_store ), E_ie_Q_xml_file_I_import_I_tree_I_notes, &s );
            if( success
            && strcmp( s, "/a" )
            )
                success = no;
            gtk_tree_view_expand_all( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] );
        }else if( !strcmp( s, "notes" ))
        {   g_free(s);
            n = gtk_tree_model_iter_n_children( E_note_tab_Q_note_tab_S_books_tree_store, null );
            GtkTreeIter iter;
            GtkTreeStore *tree_store = E_note_tab_Q_tree_Q_store_M();
            gtk_tree_store_insert_with_values( GTK_TREE_STORE( E_note_tab_Q_note_tab_S_books_tree_store )
            , &iter
            , null
            , -1
            , E_note_tab_Q_tree_Z_column_S_title, "[imported]"
            , E_note_tab_Q_tree_Z_column_S_object_ref, tree_store
            , E_note_tab_Q_tree_Z_column_S_ext_data, null
            , -1
            );
            g_object_unref( tree_store );
            success = E_ie_Q_xml_file_I_import_I_tree_( in, tree_store, E_ie_Q_xml_file_I_import_I_tree_I_note, &s );
            if( success
            && strcmp( s, "/notes" )
            )
                success = no;
        }
        g_free(s);
    }else
        success = no;
    if(success)
    {   GtkTreeIter iter;
        if( gtk_tree_model_iter_nth_child( E_note_tab_Q_note_tab_S_books_tree_store, &iter, null, n ))
        {   GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &iter );
            E_note_tab_Q_tree_Z_gtk_I_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
            gtk_tree_path_free(path);
            E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_focus();
        }
    }
    return success;
}
bool
E_ie_Q_xml_file_I_import_I_tree_( GDataInputStream *in
, GtkTreeStore *tree_store
, bool ( *proc_for_cnt )( GDataInputStream *, void **, void ** )
, char **s
){  bool success = yes;
    GtkTreeIter iter, new_iter;
    bool toplevel = yes;
    *s = E_ie_I_read_string( in, yes );
    if( !*s )
        goto End_1;
    *s = E_ie_I_read_string( in, no );
    if( *s )
    {   
Loop:   while(empty)
        {   if( strcmp( *s, "b" ))
            {   if( !toplevel )
                    break;
                goto End;
            }
            g_free( *s );
            *s = E_ie_I_read_string( in, yes );
            if( !*s )
                break;
            g_free( *s );
            *s = E_ie_I_read_string( in, no );
            if( !*s
            || strcmp( *s, "t" )
            )
                break;
            g_free( *s );
            *s = E_ie_I_read_string( in, no );
            if( !s )
                break;
            char *t = g_regex_replace_eval( E_ie_Q_re, *s, -1, 0, 0, E_string_Z_gtk_I_eval_I_replace_from_entities, null, null );
            g_free( *s );
            *s = E_ie_I_read_string( in, no );
            if( !*s
            || strcmp( *s, "/t" )
            ){  g_free(t);
                break;
            }
            g_free( *s );
            *s = E_ie_I_read_string( in, yes );
            if( !*s )
            {   g_free(t);
                break;
            }
            void *p, *d;
            if( !proc_for_cnt( in, &p, &d ))
            {   g_free(t);
                g_object_unref(p);
                break;
            }
            g_free( *s );
            gtk_tree_store_append( tree_store, &new_iter, ( toplevel ? null : &iter ));
            iter = new_iter;
            toplevel = no;
            gtk_tree_store_set( tree_store
            , &iter
            , E_note_tab_Q_tree_Z_column_S_title, t
            , E_note_tab_Q_tree_Z_column_S_object_ref, p
            , E_note_tab_Q_tree_Z_column_S_ext_data, d
            , -1
            );
            g_free(t);
            g_object_unref(p);
            while(empty)
            {   *s = E_ie_I_read_string( in, yes );
                if( !*s )
                    goto End_1;
                g_free( *s );
                *s = E_ie_I_read_string( in, no );
                if( !*s )
                    goto End_1;
                if( toplevel
                || strcmp( *s, "/b" )
                )
                    goto Loop;
                g_free( *s );
                if( gtk_tree_model_iter_parent(( void * )tree_store, &new_iter, &iter ))
                    iter = new_iter;
                else
                    toplevel = yes;
            }
        }
End_1:  success = no;
    }
End:return success;
}
bool
E_ie_Q_xml_file_I_import_I_tree_I_notes( GDataInputStream *in
, void **notes_tree_store
, void **ext_data
){  bool success = no;
    *notes_tree_store = E_note_tab_Q_tree_Q_store_M();
    *ext_data = null;
    char *s = E_ie_I_read_string( in, no );
    if( s
    && !strcmp( s, "a" )
    ){  g_free(s);
        success = E_ie_Q_xml_file_I_import_I_tree_( in, *notes_tree_store, E_ie_Q_xml_file_I_import_I_tree_I_note, &s );
        if( success
        && strcmp( s, "/a" )
        )
            success = no;
    }
    g_free(s);
    return yes;
}
bool
E_ie_Q_xml_file_I_import_I_tree_I_note( GDataInputStream *in
, void **note_buffer
, void **ext_data
){  bool success = no;
    char *s = E_ie_I_read_string( in, no );
    if( s
    && !strcmp( s, "n" )
    ){  g_free(s);
        s = E_ie_I_read_string( in, no );
        if(s)
        {   if( *s )
            {   char *s_ = g_regex_replace_eval( E_ie_Q_re, s, -1, 0, 0, E_string_Z_gtk_I_eval_I_replace_from_entities, null, null );
                g_free(s);
                s = g_strconcat( s_, "\n", null );
                g_free( s_ );
            }
            success = yes;
        }
    }else
        g_free(s);
    if( !success )
        s = g_strdup( "" );
    *note_buffer = E_note_tab_Q_note_Q_buffer_M(s);
    g_free(s);
    *ext_data = E_note_tab_Q_note_Z_ext_data_M();
    if(success)
    {   char *s = E_ie_I_read_string( in, no );
        if( !s
        || strcmp( s, "/n" )
        )
            success = no;
        g_free(s);
    }
    if(success)
    {   char *s = E_ie_I_read_string( in, yes );
        if(s)
            g_free(s);
        else
            success = no;
    }
    gint64 d = 0;
    if(success)
    {   char *s = E_ie_I_read_string( in, no );
        if( s
        && !strcmp( s, "d" )
        ){  g_free(s);
            s = E_ie_I_read_string( in, no );
            if(s)
            {   errno = 0;
                d = g_ascii_strtoll( s, null, 10 );
                if(errno)
                    success = no;
            }else
                success = no;
        }
        g_free(s);
    }
    ( *( struct E_note_tab_Q_note_Z_ext_data ** ) ext_data )->date_uid = d;
    if(success)
    {   char *s = E_ie_I_read_string( in, no );
        if( !s
        || strcmp( s, "/d" )
        )
            success = no;
        g_free(s);
    }
    return success;
}
//------------------------------------------------------------------------------
bool
E_ie_Q_notecase_file_I_import_I_tree( GDataInputStream *in
){  bool success = yes;
    GtkTreeIter books_iter;
    GtkTreeStore *tree_store = E_note_tab_Q_tree_Q_store_M();
    gtk_tree_store_insert_with_values( GTK_TREE_STORE( E_note_tab_Q_note_tab_S_books_tree_store )
    , &books_iter
    , null
    , -1
    , E_note_tab_Q_tree_Z_column_S_title, "[imported]"
    , E_note_tab_Q_tree_Z_column_S_object_ref, tree_store
    , E_note_tab_Q_tree_Z_column_S_ext_data, null
    , -1
    );
    g_object_unref( tree_store );
    bool toplevel = yes;
    char *s = E_ie_I_read_string( in, no );
    if(s)
    {   GtkTreeIter iter;
Tag_dl: while(empty)
        {   if( strcmp( s, "DL" ))
            {   g_clear_pointer( &s, g_free );
                break;
            }
            g_free(s);
            s = E_ie_I_read_string( in, yes );
            if( !s )
                break;
            g_free(s);
            s = E_ie_I_read_string( in, no );
            if( !s )
                break;
Tag_dt:     if( strcmp( s, "DT style=\"font-weight: bold;\"" ))
            {   g_clear_pointer( &s, g_free );
                break;
            }
            g_free(s);
            s = E_ie_I_read_string( in, yes );
            if( !s )
                break;
            char *title = g_regex_replace_eval( E_ie_Q_re, s, -1, 0, 0, E_string_Z_gtk_I_eval_I_replace_from_entities, null, null );
            g_free(s);
            s = E_ie_I_read_string( in, no );
            if( !s )
            {   g_free(title);
                break;
            }
            while( g_str_has_prefix( s, "A " )
            || !strcmp( s, "/A" )
            ){  g_free(s);
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
                char *s_ = g_regex_replace_eval( E_ie_Q_re, s, -1, 0, 0, E_string_Z_gtk_I_eval_I_replace_from_entities, null, null );
                g_free(s);
                s = s_;
                char *title_ = g_strconcat( title, s, null );
                g_free(s);
                g_free(title);
                title = title_;
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
            }
            if( !s )
            {   g_free(title);
                break;
            }
            GtkTreeIter new_iter;
            GtkTextBuffer *note_buffer = E_note_tab_Q_note_Q_buffer_M( "" );
            struct E_note_tab_Q_note_Z_ext_data *ext_data = E_note_tab_Q_note_Z_ext_data_M();
            ext_data->date_uid = 0;
            gtk_tree_store_insert_with_values( tree_store
            , &new_iter
            , ( toplevel ? null : &iter )
            , -1
            , E_note_tab_Q_tree_Z_column_S_title, title
            , E_note_tab_Q_tree_Z_column_S_object_ref, note_buffer
            , E_note_tab_Q_tree_Z_column_S_ext_data, ext_data
            , -1
            );
            g_free(title);
            g_object_unref( note_buffer );
            iter = new_iter;
            toplevel = no;
            if( strcmp( s, "/DT" ))
            {   g_clear_pointer( &s, g_free );
                break;
            }
            do
            {   g_free(s);
                s = E_ie_I_read_string( in, yes );
                if( !s )
                    break;
                g_free(s);
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
            }while( g_str_has_prefix( s, "A " )
              || !strcmp( s, "/A" )
            );
            if( !s )
                break;
            if( strcmp( s, "DD" ))
            {   if( gtk_tree_model_iter_parent( GTK_TREE_MODEL( tree_store ), &new_iter, &iter ))
                    iter = new_iter;
                else if( !toplevel )
                    toplevel = yes;
                else
                {   g_clear_pointer( &s, g_free );
                    break;
                }
                if( strcmp( s, "/DL" ))
                    goto Tag_dt;
                g_free(s);
                s = E_ie_I_read_string( in, yes );
                if( !s )
                    break;
                g_free(s);
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
                goto Tag_dd_e;
            }
            char *note = g_strdup( "" );
            while(empty)
            {   s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
                char *s_ = g_regex_replace_eval( E_ie_Q_re, s, -1, 0, 0, E_string_Z_gtk_I_eval_I_replace_from_entities, null, null );
                g_free(s);
                s = s_;
                char **sa = g_strsplit_set( s, "\n\r", 0 );
                g_free(s);
                s = g_strjoinv( null, sa );
                g_strfreev(sa);
                char *note_ = g_strconcat( note, s, null );
                g_free(s);
                g_free(note);
                note = note_;
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
                if( !strcmp( s, "BR" ))
                {   g_free(s);
                    note_ = g_strconcat( note, "\n", null );
                    g_free(note);
                    note = note_;
                    continue;
                }
                if( g_str_has_prefix( s, "A " ))
                {   note_ = g_strconcat( note, "<", s, ">", null );
                    g_free(s);
                    g_free(note);
                    note = note_;
                    continue;
                }
                if( !strcmp( s, "/A" ))
                {   note_ = g_strconcat( note, "<", s, ">", null );
                    g_free(s);
                    g_free(note);
                    note = note_;
                    continue;
                }
                if( g_str_has_prefix( s, "img " ))
                {   note_ = g_strconcat( note, "<", s, ">", null );
                    g_free(s);
                    g_free(note);
                    note = note_;
                    continue;
                }
                break;
            }
            if( !s )
            {   g_free(note);
                break;
            }
            note_buffer = E_note_tab_Q_note_Q_buffer_M(note);
            g_free(note);
            gtk_tree_store_set( tree_store
            , &iter
            , E_note_tab_Q_tree_Z_column_S_object_ref, note_buffer
            , -1
            );
            g_object_unref( note_buffer );
Tag_dd_e:   while(empty)
            {   if( strcmp( s, "/DD" ))
                {   if( toplevel
                      && !strcmp( s, "/BODY" )
                    ){  g_free(s);
                        goto End;
                    }
                    goto Tag_dl;
                }
                g_free(s);
                if( gtk_tree_model_iter_parent( GTK_TREE_MODEL( tree_store ), &new_iter, &iter ))
                    iter = new_iter;
                else if( !toplevel )
                    toplevel = yes;
                else
                {   s = null;
                    break;
                }
                s = E_ie_I_read_string( in, yes );
                if( !s )
                    break;
                g_free(s);
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
                if( strcmp( s, "/DL" ))
                    goto Tag_dt;
                g_free(s);
                s = E_ie_I_read_string( in, yes );
                if( !s )
                    break;
                g_free(s);
                s = E_ie_I_read_string( in, no );
                if( !s )
                    break;
            }
            if( !s )
                break;
        }
        success = no;
    }
End:;
    GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
    E_note_tab_Q_tree_Z_gtk_I_set_cursor( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
    gtk_tree_path_free(path);
    E_note_tab_Q_note_tab_Z_gtk_X_switch_page_I_focus();
    return success;
}
//------------------------------------------------------------------------------
char *
E_ie_I_read_string( GDataInputStream *in
, bool blank_cnt
){  char *s = g_data_input_stream_read_upto( in, "<>", -1, null, null, &E_error_S );
    E_error_J_return_0( "read from the file" );
    if( !s ) //“end of file”
        return null;
    g_data_input_stream_read_byte( in, null, &E_error_S );
    E_error_J_return_0( "read from the file" )
        g_free(s);
    char *s_ = g_utf8_normalize( s, -1, G_NORMALIZE_DEFAULT_COMPOSE );
    g_free(s);
    if( s_ )
    {   g_strstrip( s_ );
        if( blank_cnt
        && *s_
        )
            E_error_K( s_ );
    }else
        E_error_K( "‘utf-8’ normalize" );
    return s_;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
E_ie_Q_xml_file_I_export( char *path
){  g_application_mark_busy( G_APPLICATION( E_main_Q_app_S ));
    GFile *file = g_file_new_for_path(path);
    GFileOutputStream *out_direct = g_file_create( file, G_FILE_CREATE_NONE, null, &E_error_S );
    g_object_unref(file);
    E_error_J_return( "create file" )
        g_application_unmark_busy( G_APPLICATION( E_main_Q_app_S ));
    GOutputStream *out_buffered = g_buffered_output_stream_new_sized( G_OUTPUT_STREAM( out_direct ), E_file_S_buffer_size );
    GDataOutputStream *out_data = g_data_output_stream_new( out_buffered );
    g_object_unref( out_buffered );
    g_data_output_stream_set_byte_order( out_data, G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN );
    GString *s = g_string_new_len( E_ie_S_cnt_headers[0].header[0], strlen( E_ie_S_cnt_headers[0].header[0] ));
    bool success = E_file_Q_file_I_write( out_data, s );
    if(success)
    {   g_string_append( s, "<a>" );
        E_ie_Q_re = g_regex_new( E_string_Q_xml_S_to_entity_re, G_REGEX_OPTIMIZE, 0, null );
        success = E_ie_Q_xml_file_I_export_I_tree( out_data, s, E_note_tab_Q_note_tab_S_books_tree_store, E_ie_Q_xml_file_I_export_I_tree_I_notes );
        g_regex_unref( E_ie_Q_re );
    }
    if(success)
    {   g_string_append( s, "</a>" );
        success = E_file_Q_file_I_write( out_data, s );
    }
    g_string_free( s, yes );
    g_object_unref( out_direct );
    g_object_unref( out_data );
    g_application_unmark_busy( G_APPLICATION( E_main_Q_app_S ));
}
//------------------------------------------------------------------------------
bool
E_ie_Q_xml_file_I_export_I_tree( GDataOutputStream *out
, GString *s
, GtkTreeModel *tree_store
, bool ( *proc_for_cnt )( GDataOutputStream *, GString *, void *, void * )
){  bool success = yes;
    GtkTreeIter iter, new_iter;
    if( gtk_tree_model_get_iter_first( tree_store, &new_iter ))
    {   while(empty)
        {   iter = new_iter;
            success = E_file_Q_file_I_write( out, s );
            if( !success )
                break;
            g_string_append( s, "<b><t>" );
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
            char *t_ = g_regex_replace_eval( E_ie_Q_re, t, -1, 0, 0, E_string_Q_xml_Z_gtk_I_eval_I_replace_to_entities, null, null );
            g_free(t);
            t = t_;
            g_string_append( s, t );
            g_free(t);
            g_string_append( s, "</t>" );
            success = proc_for_cnt( out, s, p, d );
            if( !success )
                break;
            if( gtk_tree_model_iter_children( tree_store, &new_iter, &iter ))
                continue;
            g_string_append( s, "</b>" );
            new_iter = iter;
            while( !gtk_tree_model_iter_next( tree_store, &new_iter ))
            {   if( !gtk_tree_model_iter_parent( tree_store, &new_iter, &iter ))
                    goto End;
                g_string_append( s, "</b>" );
                iter = new_iter;
            }
        }
End:    ;
    }
    return success;
}
bool
E_ie_Q_xml_file_I_export_I_tree_I_notes( GDataOutputStream *out
, GString *s
, void *notes_tree_store
, void *ext_data
){  g_string_append( s, "<a>" );
    bool ret = E_ie_Q_xml_file_I_export_I_tree( out, s, GTK_TREE_MODEL( notes_tree_store ), E_ie_Q_xml_file_I_export_I_tree_I_note );
    g_string_append( s, "</a>" );
    return ret;
}
bool
E_ie_Q_xml_file_I_export_I_tree_I_note( GDataOutputStream *out
, GString *s
, void *note_buffer
, void *ext_data
){  g_string_append( s, "<n>" );
    GtkTextIter start_iter, end_iter;
    gtk_text_buffer_get_start_iter( note_buffer, &start_iter );
    gtk_text_buffer_get_end_iter( note_buffer, &end_iter );
    char *t = gtk_text_iter_get_text( &start_iter, &end_iter );
    g_strchomp(t);
    char *t_ = g_regex_replace_eval( E_ie_Q_re, t, -1, 0, 0, E_string_Q_xml_Z_gtk_I_eval_I_replace_to_entities, null, null );
    g_free(t);
    t = t_;
    g_string_append( s, t );
    g_free(t);
    g_string_append_printf( s, "</n><d>" J_printf_64d "</d>", (( struct E_note_tab_Q_note_Z_ext_data * ) ext_data )->date_uid );
    return yes;
}
//------------------------------------------------------------------------------
void
E_ie_Q_xml_file_I_export_branch( char *path
){  g_application_mark_busy( G_APPLICATION( E_main_Q_app_S ));
    GtkWidget *widget = gtk_window_get_focus( E_main_Q_window_S );
    GtkTreeModel *tree_store;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected( gtk_tree_view_get_selection( GTK_TREE_VIEW(widget) ), &tree_store, &iter );
    GFile *file = g_file_new_for_path(path);
    GFileOutputStream *out_direct = g_file_create( file, G_FILE_CREATE_NONE, null, &E_error_S );
    g_object_unref(file);
    E_error_J_return( "create file" )
        g_application_unmark_busy( G_APPLICATION( E_main_Q_app_S ));
    GOutputStream *out_buffered = g_buffered_output_stream_new_sized( G_OUTPUT_STREAM( out_direct ), E_file_S_buffer_size );
    GDataOutputStream *out_data = g_data_output_stream_new( out_buffered );
    g_object_unref( out_buffered );
    g_data_output_stream_set_byte_order( out_data, G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN );
    GString *s = g_string_new_len( E_ie_S_cnt_headers[0].header[0], strlen( E_ie_S_cnt_headers[0].header[0] ));
    bool from_books;
    bool success = E_file_Q_file_I_write( out_data, s );
    if(success)
    {   from_books = widget == GTK_WIDGET( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] );
        g_string_append( s, from_books ? "<a>" : "<notes>" );
        E_ie_Q_re = g_regex_new( E_string_Q_xml_S_to_entity_re, G_REGEX_OPTIMIZE, 0, null );
        success = E_ie_Q_xml_file_I_export_branch_I_tree( out_data
        , s
        , tree_store
        , from_books
          ? E_ie_Q_xml_file_I_export_I_tree_I_notes
          : E_ie_Q_xml_file_I_export_I_tree_I_note
        , &iter
        );
        g_regex_unref( E_ie_Q_re );
    }
    if(success)
    {   g_string_append( s, from_books ? "</a>" : "</notes>" );
        success = E_file_Q_file_I_write( out_data, s );
    }
    g_string_free( s, yes );
    g_object_unref( out_direct );
    g_object_unref( out_data );
    g_application_unmark_busy( G_APPLICATION( E_main_Q_app_S ));
}
bool
E_ie_Q_xml_file_I_export_branch_I_tree( GDataOutputStream *out
, GString *s
, GtkTreeModel *tree_store
, bool ( *proc_for_cnt )( GDataOutputStream *, GString *, void *, void * )
, GtkTreeIter *start_iter
){  bool success = yes;
    char *start_iter_s = gtk_tree_model_get_string_from_iter( tree_store, start_iter );
    GtkTreeIter iter, new_iter = *start_iter;
    while(empty)
    {   iter = new_iter;
        success = E_file_Q_file_I_write( out, s );
        if( !success )
            break;
        g_string_append( s, "<b><t>" );
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
        char *t_ = g_regex_replace_eval( E_ie_Q_re, t, -1, 0, 0, E_string_Q_xml_Z_gtk_I_eval_I_replace_to_entities, null, null );
        g_free(t);
        g_string_append( s, t_ );
        g_free( t_ );
        g_string_append( s, "</t>" );
        success = proc_for_cnt( out, s, p, d );
        if( !success )
            break;
        if( gtk_tree_model_iter_children( tree_store, &new_iter, &iter ))
            continue;
        while(empty)
        {   g_string_append( s, "</b>" );
            char *iter_s = gtk_tree_model_get_string_from_iter( tree_store, &iter );
            if( !strcmp( iter_s, start_iter_s ))
            {   g_free( iter_s );
                goto End;
            }
            g_free( iter_s );
            new_iter = iter;
            if( gtk_tree_model_iter_next( tree_store, &new_iter ))
                break;
            gtk_tree_model_iter_parent( tree_store, &new_iter, &iter );
            iter = new_iter;
        }
    }
End:g_free( start_iter_s );
    return success;
}
//==============================================================================
