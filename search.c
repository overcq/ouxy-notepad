/******************************************************************************/
bool E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = no;
//=============================================================================
gboolean
E_search_Q_tree_Z_gtk_I_search_cmp( GtkTreeModel *tree_store
, int column
, const char *key_
, GtkTreeIter *s_iter
, void *data
){  char *s;
    gtk_tree_model_get( tree_store, s_iter, column, &s, -1 );
    gunichar *key = g_utf8_to_ucs4_fast( key_, -1, null );
    E_string_Q_unistring_P_to_lower(key);
    bool b = yes;
    char *s_p = s;
    gunichar *key_p = key;
    while( *s_p )
    {   if( g_unichar_tolower( g_utf8_get_char( s_p )) == *key_p )
        {   if( !*++key_p )
            {   b = no;
                break;
            }
        }else if( key_p != key )
            key_p = key;
        s_p = g_utf8_next_char( s_p );
    }
    g_free(key);
    g_free(s);
    return b;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool
E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( gunichar *s_u
, gunichar **words
, unsigned words_n
){  for( unsigned i = 0; i < words_n; i++ )
        if( !E_string_Q_unistring_R_substr_after( s_u, words[i] ))
            return no;
    return yes;
}
bool
E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( gunichar *s_u
, gunichar **words
, unsigned words_n
, gunichar **words_found
){  for( unsigned i = 0; i < words_n; i++ )
        words_found[i] = words[i];
    gunichar *inbound = null;
    bool alnum = g_unichar_isalnum( *s_u );
    s_u--;
    while( *++s_u )
    {   if( !inbound )
        {   if( !alnum )
            {   alnum = g_unichar_isalnum( *( s_u + 1 ));
                continue;
            }
            inbound = s_u;
        }else if( inbound == s_u )
        {   if(alnum)
                inbound++;
            alnum = g_unichar_isalnum( *( s_u + 1 ));
            continue;
        }else if( inbound + 1 == s_u
        && alnum
        )
            inbound++;
        alnum = g_unichar_isalnum( *( s_u + 1 ));
        bool word_left_yet = no;
        bool word_matching = no;
        for( unsigned i = 0; i < words_n; i++ )
        {   if( !words_found[i] )
            {   word_left_yet = yes;
                continue;
            }
            if( !*words_found[i] )
                continue;
            if( *words_found[i] == *s_u
            && ( *( words_found[i] + 1 )
                || !alnum
              )
            ){  if( *++words_found[i] )
                {   word_left_yet = yes;
                    word_matching = yes;
                }
            }else
            {   words_found[i] = null;
                word_left_yet = yes;
            }
        }
        if( !word_left_yet )
            return yes;
        if( !word_matching )
        {   if( inbound == s_u )
                inbound++;
            else
            {   s_u = inbound;
                inbound = null;
            }
            alnum = g_unichar_isalnum( *( s_u + 1 ));
            for( unsigned i = 0; i < words_n; i++ )
                if( !words_found[i] )
                    words_found[i] = words[i];
        }
    }
    return no;
}
bool
E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( gunichar *s_u
, gunichar *chars
){  if( !E_string_Q_unistring_R_substr_after( s_u, chars ))
            return no;
    return yes;
}
bool
E_search_Q_note_tab_Z_gtk_I_search_I_note( GtkTextBuffer *text_buffer
, gunichar **inexact_words
, unsigned inexact_words_n
, gunichar **exact_words
, unsigned exact_words_n
, gunichar **exact_words_found
, void *exact_words_bit
, gunichar *exact_chars
){  GtkTextIter start, end;
    gtk_text_buffer_get_bounds( text_buffer, &start, &end );
    char *s = gtk_text_iter_get_slice( &start, &end );
    gunichar *s_u_ = g_utf8_to_ucs4_fast( s, -1, null );
    g_free(s);
    E_string_Q_unistring_P_to_lower( s_u_ );
    if( inexact_words_n )
        for( unsigned i = 0; i < inexact_words_n; i++ )
        {   unsigned word_len = E_string_Q_unistring_R_length( inexact_words[i] );
            gunichar *s_u = s_u_, *s_u_f;
            while( s_u_f = E_string_Q_unistring_R_substr_after( s_u, inexact_words[i] ))
            {   GtkTextIter start, end;
                gtk_text_buffer_get_iter_at_offset( text_buffer, &start, s_u_f - s_u_ - word_len );
                gtk_text_buffer_get_iter_at_offset( text_buffer, &end, s_u_f - s_u_ );
                gtk_text_buffer_apply_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
                s_u = s_u_f - word_len + 1;
            }
            if( s_u == s_u_ )
            {   g_free( s_u_ );
                gtk_text_buffer_remove_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
                return no;
            }
        }
    if( exact_words_n )
    {   for( unsigned i = 0; i < exact_words_n; i++ )
            exact_words_found[i] = exact_words[i];
        E_string_Q_bit_array_P_all_zero( exact_words_bit, exact_words_n );
        gunichar *s_u = s_u_;
        gunichar *inbound = null;
        bool alnum = g_unichar_isalnum( *s_u );
        s_u--;
        while( *++s_u )
        {   if( !inbound )
            {   if( !alnum )
                {   alnum = g_unichar_isalnum( *( s_u + 1 ));
                    continue;
                }
                inbound = s_u;
            }else if( inbound == s_u )
            {   if(alnum)
                    inbound++;
                alnum = g_unichar_isalnum( *( s_u + 1 ));
                continue;
            }else if( inbound + 1 == s_u
            && alnum
            )
                inbound++;
            alnum = g_unichar_isalnum( *( s_u + 1 ));
            GtkTextIter end;
            bool word_matching = no;
            for( unsigned i = 0; i < exact_words_n; i++ )
            {   if( !exact_words_found[i] )
                    continue;
                if( *exact_words_found[i] == *s_u
                && ( *( exact_words_found[i] + 1 )
                    || !alnum
                  )
                ){  if( *( exact_words_found[i] + 1 ))
                    {   exact_words_found[i]++;
                        word_matching = yes;
                    }else
                    {   if( !word_matching )
                            gtk_text_buffer_get_iter_at_offset( text_buffer, &end, s_u - s_u_ + 1 );
                        GtkTextIter start;
                        gtk_text_buffer_get_iter_at_offset( text_buffer, &start, ( s_u - s_u_ ) - ( exact_words_found[i] - exact_words[i] ));
                        gtk_text_buffer_apply_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
                        exact_words_found[i] = null;
                        E_string_Q_bit_array_P_one( exact_words_bit, i );
                    }
                }else
                    exact_words_found[i] = null;
            }
            if( !word_matching
            || !*( s_u + 1 )
            ){  if( inbound == s_u )
                {   if( !*( s_u + 1 ))
                        break;
                    inbound++;
                }else
                {   s_u = inbound;
                    inbound = null;
                }
                alnum = g_unichar_isalnum( *( s_u + 1 ));
                for( unsigned i = 0; i < exact_words_n; i++ )
                    exact_words_found[i] = exact_words[i];
            }
        }
        if( !E_string_Q_bit_array_R_all_one( exact_words_bit, exact_words_n ))
        {   g_free( s_u_ );
            gtk_text_buffer_remove_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
            return no;
        }
    }
    if( *exact_chars != '\0' )
    {   unsigned chars_len = E_string_Q_unistring_R_length( exact_chars );
        gunichar *s_u = s_u_, *s_u_f;
        while( s_u_f = E_string_Q_unistring_R_substr_after( s_u, exact_chars ))
        {   GtkTextIter start, end;
            gtk_text_buffer_get_iter_at_offset( text_buffer, &start, s_u_f - s_u_ - chars_len );
            gtk_text_buffer_get_iter_at_offset( text_buffer, &end, s_u_f - s_u_ );
            gtk_text_buffer_apply_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
            s_u = s_u_f - chars_len + 1;
        }
        if( s_u == s_u_ )
        {   g_free( s_u_ );
            gtk_text_buffer_remove_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
            return no;
        }
    }
    g_free( s_u_ );
    return yes;
}
char *
E_note_tab_Q_search_Z_gtk_Q_key_string_R_norm( const char *s_
){  char *s_0 = g_utf8_normalize( s_, -1, G_NORMALIZE_DEFAULT_COMPOSE ), *s = s_0;
    if( !s )
    {   E_error_K( "‘utf-8’ normalize" );
        return g_strdup( "" );
    }
    GString *str = g_string_new(null);
    bool inbound = no;
    while( *s )
    {   gunichar c = g_utf8_get_char(s);
        if( !inbound )
        {   if( g_unichar_isalnum(c) )
            {   inbound = yes;
                g_string_append_unichar( str, c );
            }
        }else
        {   if( g_unichar_isspace(c) )
            {   inbound = no;
                c = ' ';
            }
            g_string_append_unichar( str, c );
        }
        s = g_utf8_next_char(s);
    }
    g_free( s_0 );
    if( str->len
    && str->str[ str->len - 1 ] == ' '
    )
        g_string_truncate( str, str->len - 1 );
    return g_string_free( str, no );
}
char *
E_note_tab_Q_search_Z_gtk_Q_string_R_norm( const char *s_
){  char *s = g_utf8_normalize( s_, -1, G_NORMALIZE_DEFAULT_COMPOSE );
    if( !s )
    {   E_error_K( "‘utf-8’ normalize" );
        return g_strdup( "" );
    }
    GString *str = g_string_new(s);
    g_free(s);
    while( str->len
    && g_unichar_isspace( g_utf8_get_char( g_utf8_prev_char( str->str + str->len )))
    ){  char *s_ = g_utf8_prev_char( str->str + str->len );
        g_string_erase( str, s_ - str->str, -1 );
    }
    while( str->len
    && g_unichar_isspace( g_utf8_get_char( str->str ))
    ){  char *s_ = g_utf8_next_char( str->str );
        g_string_erase( str, 0, s_ - str->str );
    }
    return g_string_free( str, no );
}
void
E_search_Q_note_tab_Z_gtk_I_search_next_I_note_found_ending( GtkTextBuffer *text_buffer
, struct E_note_tab_Q_ext_data_Z *note_tab_ext_data
){  E_main_Z_gtk_I_process_events();
    E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = no;
    GtkTextIter text_iter;
    gtk_text_buffer_get_start_iter( text_buffer, &text_iter );
    if( !gtk_text_iter_begins_tag( &text_iter, E_note_tab_Q_note_Z_tag_S_search ))
        gtk_text_iter_forward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search );
    gtk_text_view_scroll_to_iter( note_tab_ext_data->note, &text_iter, 0, yes, 0, 0 );
}
gboolean
E_search_Q_note_tab_I_grab_default_Z_gtk_I_idle( void *widget
){  gtk_widget_grab_default(widget);
    return G_SOURCE_REMOVE;
}
_EXPORT_OBFUSCATE
void
E_search_Q_note_tab_Z_gtk_I_search_next( GtkButton *button
, void *data
){  int tab;
    if( !button )
        tab = GPOINTER_TO_INT(data);
    else
        tab = E_note_tab_Q_note_tab_S_current_tab;
    struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab );
    note_tab_ext_data->default_previous = no;
    g_idle_add( E_search_Q_note_tab_I_grab_default_Z_gtk_I_idle, note_tab_ext_data->search_next );
    char *s = E_note_tab_Q_search_Z_gtk_Q_key_string_R_norm( gtk_entry_get_text( note_tab_ext_data->search_inexact ));
    gunichar **inexact_words = ( gunichar ** ) g_strsplit( s, " ", 0 );
    g_free(s);
    s = E_note_tab_Q_search_Z_gtk_Q_key_string_R_norm( gtk_entry_get_text( note_tab_ext_data->search_exact ));
    gunichar **exact_words = ( gunichar ** ) g_strsplit( s, " ", 0 );
    g_free(s);
    gunichar *exact_chars = g_utf8_to_ucs4_fast( E_note_tab_Q_search_Z_gtk_Q_string_R_norm( gtk_entry_get_text( note_tab_ext_data->search_exact_chars )), -1, null );
    E_string_Q_unistring_P_to_lower( exact_chars );
    gunichar **a = inexact_words;
    while( *a )
    {   gunichar *s = g_utf8_to_ucs4_fast( *( char ** ) a, -1, null );
        g_free( *a );
        E_string_Q_unistring_P_to_lower(s);
        *a = s;
        a++;
    }
    unsigned inexact_words_n = a - inexact_words;
    a = exact_words;
    while( *a )
    {   gunichar *s = g_utf8_to_ucs4_fast( *( char ** ) a, -1, null );
        g_free( *a );
        E_string_Q_unistring_P_to_lower(s);
        *a = s;
        a++;
    }
    unsigned exact_words_n = a - exact_words;
    gunichar **exact_words_found = null;
    void *exact_words_bit = null;
    if( exact_words_n )
    {   exact_words_found = g_new( gunichar *, exact_words_n );
        exact_words_bit = E_string_Q_bit_array_M( exact_words_n );
    }
    if( !exact_words_n && !inexact_words_n && *exact_chars == '\0' )
        goto End_0;
    bool b;
    char *start_notes_iter_s = null;
    GtkTreeModel *notes_tree_store;
    GtkTreeSelection *selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] );
    GtkTreeIter new_iter, books_iter;
    //etap 1.: początkowe niepełne drzewo notatek.
    if( b = gtk_tree_selection_get_selected( selection, null, &books_iter ))
    {   selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] );
        GtkTreeIter notes_iter;
        if( gtk_tree_selection_get_selected( selection, &notes_tree_store, &notes_iter ))
        {   GtkTextBuffer *text_buffer;
            gtk_tree_model_get( notes_tree_store
            , &notes_iter
            , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
            , -1
            );
            g_object_unref( text_buffer );
            GtkTextIter text_iter, start;
            gtk_text_buffer_get_start_iter( text_buffer, &start );
            text_iter = start;
            if( gtk_text_iter_begins_tag( &text_iter, E_note_tab_Q_note_Z_tag_S_search )
            || gtk_text_iter_forward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search )
            ){  GtkTextView *text_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).note;
                GdkRectangle rect, iter_rect;
                gtk_text_view_get_visible_rect( text_view, &rect );
                do
                {   gtk_text_iter_forward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search );
                    gtk_text_view_get_iter_location( text_view, &text_iter, &iter_rect );
                }while( iter_rect.y + iter_rect.height <= rect.y + rect.height
                && gtk_text_iter_forward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search )
                );
                if( iter_rect.y + iter_rect.height > rect.y + rect.height )
                {   gtk_text_view_scroll_to_iter( note_tab_ext_data->note, &text_iter, 0, yes, 0, 0 );
                    goto End_0;
                }
                GtkTextIter end;
                gtk_text_buffer_get_end_iter( text_buffer, &end );
                gtk_text_buffer_remove_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
            }else if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
            {   E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                gtk_tree_path_free(path);
                E_search_Q_note_tab_Z_gtk_I_search_next_I_note_found_ending( text_buffer, note_tab_ext_data );
                goto End_0;
            }
            start_notes_iter_s = gtk_tree_model_get_string_from_iter( notes_tree_store, &notes_iter );
            bool b = yes;
            if( !gtk_tree_model_iter_children( notes_tree_store, &new_iter, &notes_iter ))
            {   new_iter = notes_iter;
                while( !gtk_tree_model_iter_next( notes_tree_store, &new_iter ))
                {   if( !gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter ))
                    {   b = no;
                        break;
                    }
                    notes_iter = new_iter;
                }
            }
            notes_iter = new_iter;
            if(b)
                while(empty)
                {   char *s;
                    gtk_tree_model_get( notes_tree_store
                    , &notes_iter
                    , E_note_tab_Q_tree_Z_column_S_title, &s
                    , -1
                    );
                    gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
                    g_free(s);
                    E_string_Q_unistring_P_to_lower( s_u );
                    if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
                    && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
                    && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
                    ){  g_free( s_u );
                        GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                        E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                        gtk_tree_path_free(path);
                        goto End_1;
                    }
                    g_free( s_u );
                    GtkTextBuffer *text_buffer;
                    gtk_tree_model_get( notes_tree_store
                    , &notes_iter
                    , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
                    , -1
                    );
                    g_object_unref( text_buffer );
                    if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
                    {   E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                        GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                        E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                        gtk_tree_path_free(path);
                        E_search_Q_note_tab_Z_gtk_I_search_next_I_note_found_ending( text_buffer, note_tab_ext_data );
                        goto End_1;
                    }
                    b = no;
                    if( !gtk_tree_model_iter_children( notes_tree_store, &new_iter, &notes_iter ))
                    {   new_iter = notes_iter;
                        while( !gtk_tree_model_iter_next( notes_tree_store, &new_iter ))
                        {   if( !gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter ))
                            {   b = yes;
                                break;
                            }
                            notes_iter = new_iter;
                        }
                    }
                    if(b)
                        break;
                    notes_iter = new_iter;
                }
        }
    }else if( !gtk_tree_model_get_iter_first( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter ))
        goto End_1;
    char *start_books_iter_s = gtk_tree_model_get_string_from_iter( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
    if( start_notes_iter_s )
    {   if( !gtk_tree_model_iter_children( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, &books_iter ))
        {   new_iter = books_iter;
            while( !gtk_tree_model_iter_next( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter ))
            {   if( !gtk_tree_model_iter_parent( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, &books_iter ))
                {   gtk_tree_model_get_iter_first( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter );
                    break;
                }
                books_iter = new_iter;
            }
        }
        books_iter = new_iter;
    }
    if( start_notes_iter_s
    || !b
    ){  char *s;
        gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_title, &s
        , -1
        );
        gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
        g_free(s);
        E_string_Q_unistring_P_to_lower( s_u );
        if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
        && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
        && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
        ){  g_free( s_u );
            GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
            gtk_tree_selection_unselect_path( gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ), path );
            E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
            gtk_tree_path_free(path);
            goto End_2;
        }
        g_free( s_u );
    }
    //etap 2.: pełne drzewa notatek.
    while(empty)
    {   gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_tree_store
        , -1
        );
        g_object_unref( notes_tree_store );
        GtkTreeIter notes_iter;
        if( gtk_tree_model_get_iter_first( notes_tree_store, &notes_iter ))
            while(empty)
            {   char *s;
                gtk_tree_model_get( notes_tree_store
                , &notes_iter
                , E_note_tab_Q_tree_Z_column_S_title, &s
                , -1
                );
                gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
                g_free(s);
                E_string_Q_unistring_P_to_lower( s_u );
                if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
                && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
                && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
                ){  g_free( s_u );
                    GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
                    gtk_tree_path_free(path);
                    path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                    gtk_tree_path_free(path);
                    goto End_2;
                }
                g_free( s_u );
                GtkTextBuffer *text_buffer;
                gtk_tree_model_get( notes_tree_store
                , &notes_iter
                , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
                , -1
                );
                g_object_unref( text_buffer );
                if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
                {   GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
                    E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
                    gtk_tree_path_free(path);
                    path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                    gtk_tree_path_free(path);
                    E_search_Q_note_tab_Z_gtk_I_search_next_I_note_found_ending( text_buffer, note_tab_ext_data );
                    goto End_2;
                }
                b = no;
                if( !gtk_tree_model_iter_children( notes_tree_store, &new_iter, &notes_iter ))
                {   new_iter = notes_iter;
                    while( !gtk_tree_model_iter_next( notes_tree_store, &new_iter ))
                    {   if( !gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter ))
                        {   b = yes;
                            break;
                        }
                        notes_iter = new_iter;
                    }
                }
                if(b)
                    break;
                notes_iter = new_iter;
            }
        if( !gtk_tree_model_iter_children( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, &books_iter ))
        {   new_iter = books_iter;
            while( !gtk_tree_model_iter_next( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter ))
            {   if( !gtk_tree_model_iter_parent( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, &books_iter ))
                {   gtk_tree_model_get_iter_first( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter );
                    break;
                }
                books_iter = new_iter;
            }
        }
        books_iter = new_iter;
        char *s;
        gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_title, &s
        , -1
        );
        gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
        g_free(s);
        E_string_Q_unistring_P_to_lower( s_u );
        if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
        && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
        && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
        ){  g_free( s_u );
            GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
            gtk_tree_selection_unselect_path( gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ), path );
            E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
            gtk_tree_path_free(path);
            goto End_2;
        }
        g_free( s_u );
        char *books_iter_s = gtk_tree_model_get_string_from_iter( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
        int b = strcmp( books_iter_s, start_books_iter_s );
        g_free( books_iter_s );
        if( !b )
            break;
    }
    //etap 3.: końcowe niepełne drzewo notatek.
    if( start_notes_iter_s )
    {   gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_tree_store
        , -1
        );
        g_object_unref( notes_tree_store );
        GtkTreeIter notes_iter;
        gtk_tree_model_get_iter_first( notes_tree_store, &notes_iter );
        while(empty)
        {   char *s;
            gtk_tree_model_get( notes_tree_store
            , &notes_iter
            , E_note_tab_Q_tree_Z_column_S_title, &s
            , -1
            );
            gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
            g_free(s);
            E_string_Q_unistring_P_to_lower( s_u );
            if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
            && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
            && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
            ){  g_free( s_u );
                GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                gtk_tree_path_free(path);
                goto End_2;
            }
            g_free( s_u );
            GtkTextBuffer *text_buffer;
            gtk_tree_model_get( notes_tree_store
            , &notes_iter
            , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
            , -1
            );
            g_object_unref( text_buffer );
            if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
            {   E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                gtk_tree_path_free(path);
                E_search_Q_note_tab_Z_gtk_I_search_next_I_note_found_ending( text_buffer, note_tab_ext_data );
                goto End_2;
            }
            char *notes_iter_s = gtk_tree_model_get_string_from_iter( notes_tree_store, &notes_iter );
            int b = strcmp( notes_iter_s, start_notes_iter_s );
            g_free( notes_iter_s );
            if( !b )
                break;
            if( !gtk_tree_model_iter_children( notes_tree_store, &new_iter, &notes_iter ))
            {   new_iter = notes_iter;
                while( !gtk_tree_model_iter_next( notes_tree_store, &new_iter ))
                {   gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter );
                    notes_iter = new_iter;
                }
            }
            notes_iter = new_iter;
        }
    }
End_2:
    g_free( start_books_iter_s );
End_1:
    g_free( start_notes_iter_s );
End_0:
    g_free( exact_words_found );
    E_string_Q_bit_array_W( exact_words_bit );
    g_strfreev(( char ** ) exact_words );
    g_strfreev(( char ** ) inexact_words );
}
void
E_search_Q_note_tab_Z_gtk_I_search_previous_I_note_found_ending( GtkTextBuffer *text_buffer
, struct E_note_tab_Q_ext_data_Z *note_tab_ext_data
){  E_main_Z_gtk_I_process_events();
    E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = no;
    GtkTextIter text_iter;
    gtk_text_buffer_get_end_iter( text_buffer, &text_iter );
    if( !gtk_text_iter_ends_tag( &text_iter, E_note_tab_Q_note_Z_tag_S_search ))
        gtk_text_iter_backward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search );
    gtk_text_view_scroll_to_iter( note_tab_ext_data->note, &text_iter, 0, yes, 0, 1 );
}
_EXPORT_OBFUSCATE
void
E_search_Q_note_tab_Z_gtk_I_search_previous( GtkButton *button
, void *data
){  int tab;
    if( !button )
        tab = GPOINTER_TO_INT(data);
    else
        tab = E_note_tab_Q_note_tab_S_current_tab;
    struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab );
    note_tab_ext_data->default_previous = yes;
    g_idle_add( E_search_Q_note_tab_I_grab_default_Z_gtk_I_idle, note_tab_ext_data->search_previous );
    char *s = E_note_tab_Q_search_Z_gtk_Q_key_string_R_norm( gtk_entry_get_text( note_tab_ext_data->search_inexact ));
    gunichar **inexact_words = ( gunichar ** ) g_strsplit( s, " ", 0 );
    g_free(s);
    s = E_note_tab_Q_search_Z_gtk_Q_key_string_R_norm( gtk_entry_get_text( note_tab_ext_data->search_exact ));
    gunichar **exact_words = ( gunichar ** ) g_strsplit( s, " ", 0 );
    g_free(s);
    gunichar *exact_chars = g_utf8_to_ucs4_fast( E_note_tab_Q_search_Z_gtk_Q_string_R_norm( gtk_entry_get_text( note_tab_ext_data->search_exact_chars )), -1, null );
    E_string_Q_unistring_P_to_lower( exact_chars );
    gunichar **a = inexact_words;
    while( *a )
    {   gunichar *s = g_utf8_to_ucs4_fast( *( char ** ) a, -1, null );
        g_free( *a );
        E_string_Q_unistring_P_to_lower(s);
        *a = s;
        a++;
    }
    unsigned inexact_words_n = a - inexact_words;
    a = exact_words;
    while( *a )
    {   gunichar *s = g_utf8_to_ucs4_fast( *( char ** ) a, -1, null );
        g_free( *a );
        E_string_Q_unistring_P_to_lower(s);
        *a = s;
        a++;
    }
    unsigned exact_words_n = a - exact_words;
    gunichar **exact_words_found = null;
    void *exact_words_bit = null;
    if( exact_words_n )
    {   exact_words_found = g_new( gunichar *, exact_words_n );
        exact_words_bit = E_string_Q_bit_array_M( exact_words_n );
    }
    if( !exact_words_n && !inexact_words_n && *exact_chars == '\0' )
        goto End_0;
    char *start_notes_iter_s = null;
    GtkTreeModel *notes_tree_store;
    bool note_previous;
    int n;
    GtkTreeSelection *selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] );
    GtkTreeIter new_iter, books_iter;
    //etap 1.: początkowe niepełne drzewo notatek.
    if( gtk_tree_selection_get_selected( selection, null, &books_iter ))
    {   selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] );
        GtkTreeIter notes_iter;
        if( gtk_tree_selection_get_selected( selection, &notes_tree_store, &notes_iter ))
        {   GtkTextBuffer *text_buffer;
            gtk_tree_model_get( notes_tree_store
            , &notes_iter
            , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
            , -1
            );
            g_object_unref( text_buffer );
            GtkTextIter text_iter, end;
            gtk_text_buffer_get_end_iter( text_buffer, &end );
            text_iter = end;
            if( gtk_text_iter_ends_tag( &text_iter, E_note_tab_Q_note_Z_tag_S_search )
            || gtk_text_iter_backward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search )
            ){  GtkTextView *text_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, tab ).note;
                GdkRectangle rect, iter_rect;
                gtk_text_view_get_visible_rect( text_view, &rect );
                do
                {   gtk_text_iter_backward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search );
                    gtk_text_view_get_iter_location( text_view, &text_iter, &iter_rect );
                }while( iter_rect.y >= rect.y
                && gtk_text_iter_backward_to_tag_toggle( &text_iter, E_note_tab_Q_note_Z_tag_S_search )
                );
                if( iter_rect.y < rect.y )
                {   gtk_text_view_scroll_to_iter( note_tab_ext_data->note, &text_iter, 0, yes, 0, 1 );
                    goto End_0;
                }
                GtkTextIter start;
                gtk_text_buffer_get_start_iter( text_buffer, &start );
                gtk_text_buffer_remove_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
                char *s;
                gtk_tree_model_get( notes_tree_store
                , &notes_iter
                , E_note_tab_Q_tree_Z_column_S_title, &s
                , -1
                );
                gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
                g_free(s);
                E_string_Q_unistring_P_to_lower( s_u );
                if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
                && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
                && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
                ){  g_free( s_u );
                    GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                    gtk_tree_path_free(path);
                    goto End_0;
                }
                g_free( s_u );
            }
            start_notes_iter_s = gtk_tree_model_get_string_from_iter( notes_tree_store, &notes_iter );
            new_iter = notes_iter;
            bool b = yes;
            if( !( note_previous = gtk_tree_model_iter_previous( notes_tree_store, &new_iter ))
            && !gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter )
            )
                b = no;
            notes_iter = new_iter;
            if(b)
                while(empty)
                {   if( note_previous )
                        while( n = gtk_tree_model_iter_n_children( notes_tree_store, &notes_iter ))
                        {   gtk_tree_model_iter_nth_child( notes_tree_store, &new_iter, &notes_iter, n - 1 );
                            notes_iter = new_iter;
                        }
                    GtkTextBuffer *text_buffer;
                    gtk_tree_model_get( notes_tree_store
                    , &notes_iter
                    , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
                    , -1
                    );
                    g_object_unref( text_buffer );
                    if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
                    {   E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                        GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                        E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                        gtk_tree_path_free(path);
                        E_search_Q_note_tab_Z_gtk_I_search_previous_I_note_found_ending( text_buffer, note_tab_ext_data );
                        goto End_1;
                    }
                    char *s;
                    gtk_tree_model_get( notes_tree_store
                    , &notes_iter
                    , E_note_tab_Q_tree_Z_column_S_title, &s
                    , -1
                    );
                    gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
                    g_free(s);
                    E_string_Q_unistring_P_to_lower( s_u );
                    if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
                    && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
                    && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
                    ){  g_free( s_u );
                        GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                        E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                        gtk_tree_path_free(path);
                        goto End_1;
                    }
                    g_free( s_u );
                    b = no;
                    new_iter = notes_iter;
                    if( !( note_previous = gtk_tree_model_iter_previous( notes_tree_store, &new_iter ))
                    && !gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter )
                    ){  b = yes;
                        break;
                    }
                    if(b)
                        break;
                    notes_iter = new_iter;
                }
            char *s;
            gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
            , &books_iter
            , E_note_tab_Q_tree_Z_column_S_title, &s
            , -1
            );
            gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
            g_free(s);
            E_string_Q_unistring_P_to_lower( s_u );
            if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
            && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
            && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
            ){  g_free( s_u );
                GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
                gtk_tree_selection_unselect_path( gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ), path );
                E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
                gtk_tree_path_free(path);
                goto End_1;
            }
            g_free( s_u );
        }
    }else if( !gtk_tree_model_get_iter_first( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter ))
        goto End_1;
    char *start_books_iter_s = gtk_tree_model_get_string_from_iter( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
    bool books_previous;
    //etap 2.: pełne drzewa notatek.
    while(empty)
    {   new_iter = books_iter;
        if( !( books_previous = gtk_tree_model_iter_previous( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter ))
        && !gtk_tree_model_iter_parent( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, &books_iter )
        )
            books_previous = gtk_tree_model_iter_nth_child( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, null, gtk_tree_model_iter_n_children( E_note_tab_Q_note_tab_S_books_tree_store, null ) - 1 );
        books_iter = new_iter;
        if( books_previous )
            while( n = gtk_tree_model_iter_n_children( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter ))
            {   gtk_tree_model_iter_nth_child( E_note_tab_Q_note_tab_S_books_tree_store, &new_iter, &books_iter, n - 1 );
                books_iter = new_iter;
            }
        if( start_notes_iter_s ) //czy opóźnić jeszcze wyjście, by przeszukać startowe drzewo notatek, które nie było przeszukiwane.
        {   char *books_iter_s = gtk_tree_model_get_string_from_iter( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
            int b = strcmp( books_iter_s, start_books_iter_s );
            g_free( books_iter_s );
            if( !b )
                break;
        }
        gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_tree_store
        , -1
        );
        g_object_unref( notes_tree_store );
        GtkTreeIter notes_iter;
        if( n = gtk_tree_model_iter_n_children( notes_tree_store, null ))
        {   note_previous = gtk_tree_model_iter_nth_child( notes_tree_store, &notes_iter, null, n - 1 );
            while(empty)
            {   if( note_previous )
                    while( n = gtk_tree_model_iter_n_children( notes_tree_store, &notes_iter ))
                    {   gtk_tree_model_iter_nth_child( notes_tree_store, &new_iter, &notes_iter, n - 1 );
                        notes_iter = new_iter;
                    }
                GtkTextBuffer *text_buffer;
                gtk_tree_model_get( notes_tree_store
                , &notes_iter
                , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
                , -1
                );
                g_object_unref( text_buffer );
                if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
                {   E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                    GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
                    gtk_tree_path_free(path);
                    path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                    gtk_tree_path_free(path);
                    E_search_Q_note_tab_Z_gtk_I_search_previous_I_note_found_ending( text_buffer, note_tab_ext_data );
                    goto End_2;
                }
                char *s;
                gtk_tree_model_get( notes_tree_store
                , &notes_iter
                , E_note_tab_Q_tree_Z_column_S_title, &s
                , -1
                );
                gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
                g_free(s);
                E_string_Q_unistring_P_to_lower( s_u );
                if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
                && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
                && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
                ){  g_free( s_u );
                    GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
                    gtk_tree_path_free(path);
                    path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                    E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                    gtk_tree_path_free(path);
                    goto End_2;
                }
                g_free( s_u );
                bool b = no;
                new_iter = notes_iter;
                if( !( note_previous = gtk_tree_model_iter_previous( notes_tree_store, &new_iter ))
                && !gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter )
                ){  b = yes;
                    break;
                }
                if(b)
                    break;
                notes_iter = new_iter;
            }
        }
        char *s;
        gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_title, &s
        , -1
        );
        gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
        g_free(s);
        E_string_Q_unistring_P_to_lower( s_u );
        if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
        && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
        && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
        ){  g_free( s_u );
            GtkTreePath *path = gtk_tree_model_get_path( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
            gtk_tree_selection_unselect_path( gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] ), path );
            E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ], path );
            gtk_tree_path_free(path);
            goto End_2;
        }
        g_free( s_u );
        if( !start_notes_iter_s ) //czy wyjść już, gdy było to opóźnione dla startowego drzewa notatek, które nie było przeszukiwane, a teraz zostało.
        {   char *books_iter_s = gtk_tree_model_get_string_from_iter( E_note_tab_Q_note_tab_S_books_tree_store, &books_iter );
            int b = strcmp( books_iter_s, start_books_iter_s );
            g_free( books_iter_s );
            if( !b )
                break;
        }
    }
    //etap 3.: końcowe niepełne drzewo notatek.
    if( start_notes_iter_s )
    {   gtk_tree_model_get( E_note_tab_Q_note_tab_S_books_tree_store
        , &books_iter
        , E_note_tab_Q_tree_Z_column_S_object_ref, &notes_tree_store
        , -1
        );
        g_object_unref( notes_tree_store );
        GtkTreeIter notes_iter;
        note_previous = gtk_tree_model_iter_nth_child( notes_tree_store, &notes_iter, null, gtk_tree_model_iter_n_children( notes_tree_store, null ) - 1 );
        while(empty)
        {   if( note_previous )
                while( n = gtk_tree_model_iter_n_children( notes_tree_store, &notes_iter ))
                {   gtk_tree_model_iter_nth_child( notes_tree_store, &new_iter, &notes_iter, n - 1 );
                    notes_iter = new_iter;
                }
            char *notes_iter_s = gtk_tree_model_get_string_from_iter( notes_tree_store, &notes_iter );
            int b = strcmp( notes_iter_s, start_notes_iter_s );
            g_free( notes_iter_s );
            if( !b )
                break;
            GtkTextBuffer *text_buffer;
            gtk_tree_model_get( notes_tree_store
            , &notes_iter
            , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
            , -1
            );
            g_object_unref( text_buffer );
            if( E_search_Q_note_tab_Z_gtk_I_search_I_note( text_buffer, inexact_words, inexact_words_n, exact_words, exact_words_n, exact_words_found, exact_words_bit, exact_chars ))
            {   E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip = yes;
                GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                gtk_tree_path_free(path);
                E_search_Q_note_tab_Z_gtk_I_search_previous_I_note_found_ending( text_buffer, note_tab_ext_data );
                goto End_2;
            }
            char *s;
            gtk_tree_model_get( notes_tree_store
            , &notes_iter
            , E_note_tab_Q_tree_Z_column_S_title, &s
            , -1
            );
            gunichar *s_u = g_utf8_to_ucs4_fast( s, -1, null );
            g_free(s);
            E_string_Q_unistring_P_to_lower( s_u );
            if(( !inexact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_inexact_words_cmp( s_u, inexact_words, inexact_words_n ))
            && ( !exact_words_n || E_search_Q_note_tab_Z_gtk_I_search_I_exact_words_cmp( s_u, exact_words, exact_words_n, exact_words_found ))
            && ( *exact_chars == '\0' || E_search_Q_note_tab_Z_gtk_I_search_I_exact_chars_cmp( s_u, exact_chars ))
            ){  g_free( s_u );
                GtkTreePath *path = gtk_tree_model_get_path( notes_tree_store, &notes_iter );
                E_note_tab_Q_tree_Z_gtk_I_set_cursor( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ], path );
                gtk_tree_path_free(path);
                goto End_2;
            }
            g_free( s_u );
            new_iter = notes_iter;
            if( !( note_previous = gtk_tree_model_iter_previous( notes_tree_store, &new_iter )))
                gtk_tree_model_iter_parent( notes_tree_store, &new_iter, &notes_iter );
            notes_iter = new_iter;
        }
    }
End_2:
    g_free( start_books_iter_s );
End_1:
    g_free( start_notes_iter_s );
End_0:
    g_free( exact_words_found );
    E_string_Q_bit_array_W( exact_words_bit );
    g_strfreev(( char ** ) exact_words );
    g_strfreev(( char ** ) inexact_words );
}
//-----------------------------------------------------------------------------
void
E_note_tab_Q_note_I_clear_search( GtkTextBuffer *text_buffer
){  if( E_note_tab_Q_notes_tree_Z_gtk_X_selection_changed_I_clear_search_U_skip )
        return;
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds( text_buffer, &start, &end );
    gtk_text_buffer_remove_tag( text_buffer, E_note_tab_Q_note_Z_tag_S_search, &start, &end );
}
//-----------------------------------------------------------------------------
_EXPORT_OBFUSCATE
void
E_search_Q_search_entry_Z_gtk_X_icon_press( GtkEntry *entry
, GtkEntryIconPosition icon
, GdkEvent *event
, void *data
){  if( icon == GTK_ENTRY_ICON_SECONDARY )
        gtk_entry_set_text( entry, "" );
}
/******************************************************************************/
