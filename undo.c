/******************************************************************************/
unsigned E_undo_Q_note_I_idle_join_break_S_timeout = 2000;
unsigned E_undo_Q_note_I_idle_join_break_S = 0;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool E_undo_S_join_broken = no;
//=============================================================================
void
E_undo_Q_note_Z_gtk_X_insert_text( GtkTextBuffer *text_buffer
, GtkTextIter *location
, char *text
, int length_
, void *data_
){  GtkTreeView *tree_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ];
    GtkTreeSelection *selection = gtk_tree_view_get_selection( tree_view );
    GtkTreeModel *tree_store;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected( selection, &tree_store, &iter );
    struct E_note_tab_Q_note_Z_ext_data *data;
    gtk_tree_model_get( tree_store
    , &iter
    , E_note_tab_Q_tree_Z_column_S_ext_data, &data
    , -1
    );
    if( !data->undo_array )
    {   data->undo_array = g_array_new( no, no, sizeof( struct E_undo_Q_note_Z_action_data ));
        data->undo_back = 0;
    }else if( data->undo_back )
    {   for( unsigned i = data->undo_array->len - data->undo_back + 1; i < data->undo_array->len; i++ )
        {   struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, i );
            if( undo->type == E_undo_Q_note_Z_action_S_text_inserted )
                g_free( undo->u.text );
        }
        g_array_remove_range( data->undo_array, data->undo_array->len - data->undo_back, data->undo_back );
        data->undo_back = 0;
    }
    int length = g_utf8_strlen( text, -1 );
    int p = gtk_text_iter_get_offset(location);
    bool join_broken = E_undo_S_join_broken;
    E_undo_S_join_broken = no;
    if( E_undo_Q_note_I_idle_join_break_S )
        g_source_remove( E_undo_Q_note_I_idle_join_break_S );
    E_undo_Q_note_I_idle_join_break_S = g_timeout_add( E_undo_Q_note_I_idle_join_break_S_timeout, E_undo_Q_note_I_idle_join_break, null );
    if( data->undo_array->len
    && !join_broken
    ){  struct E_undo_Q_note_Z_action_data *undo_1 = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, data->undo_array->len - 1 );
        if( undo_1->type == E_undo_Q_note_Z_action_S_text_inserted
        && p >= undo_1->position
        && p <= undo_1->position + undo_1->u.length
        ){  if( data->undo_array->len >= 2 )
            {   struct E_undo_Q_note_Z_action_data *undo_2 = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, data->undo_array->len - 2 );
                if( undo_2->type == E_undo_Q_note_Z_action_S_text_deleted
                && undo_1->position == undo_2->position
                && g_utf8_strlen( undo_2->u.text, -1 ) == undo_1->u.length + length
                ){  GtkTextIter start, end;
                    gtk_text_buffer_get_iter_at_offset( text_buffer, &start, undo_1->position );
                    gtk_text_buffer_get_iter_at_offset( text_buffer, &end, undo_1->position + undo_1->u.length );
                    char *text = gtk_text_iter_get_text( &start, &end );
                    if( !memcmp( undo_2->u.text
                        , text
                        , g_utf8_offset_to_pointer( text, p - undo_1->position ) - text
                        )
                    && !memcmp( g_utf8_offset_to_pointer( undo_2->u.text, p - undo_2->position ), text, length_ )
                    && !strcmp( g_utf8_offset_to_pointer( undo_2->u.text, p - undo_2->position ) + length_
                        , g_utf8_offset_to_pointer( text, p - undo_1->position )
                        )
                    ){  g_free(text);
                        g_free( undo_2->u.text );
                        g_array_remove_range( data->undo_array, data->undo_array->len - 2, 2 );
                        return;
                    }
                    g_free(text);
                }
            }
            undo_1->u.length += length;
            return;
        }
        if( undo_1->type == E_undo_Q_note_Z_action_S_text_deleted
        && p == undo_1->position
        && !strcmp( text, undo_1->u.text )
        ){  g_free( undo_1->u.text );
            g_array_remove_index( data->undo_array, data->undo_array->len - 1 );
            return;
        }
    }
    g_array_append_val( data->undo_array
    , (( struct E_undo_Q_note_Z_action_data )
      { .type = E_undo_Q_note_Z_action_S_text_inserted
      , .position = p
      , .u.length = length
      })
    );
}
void
E_undo_Q_note_Z_gtk_X_delete_range( GtkTextBuffer *text_buffer
, GtkTextIter *start
, GtkTextIter *end
, void *data_
){  GtkTreeView *tree_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ];
    GtkTreeSelection *selection = gtk_tree_view_get_selection( tree_view );
    GtkTreeModel *tree_store;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected( selection, &tree_store, &iter );
    struct E_note_tab_Q_note_Z_ext_data *data;
    gtk_tree_model_get( tree_store
    , &iter
    , E_note_tab_Q_tree_Z_column_S_ext_data, &data
    , -1
    );
    if( !data->undo_array )
    {   data->undo_array = g_array_new( no, no, sizeof( struct E_undo_Q_note_Z_action_data ));
        data->undo_back = 0;
    }else if( data->undo_back )
    {   for( unsigned i = data->undo_array->len - data->undo_back + 1; i < data->undo_array->len; i++ )
        {   struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, i );
            if( undo->type == E_undo_Q_note_Z_action_S_text_inserted )
                g_free( undo->u.text );
        }
        g_array_remove_range( data->undo_array, data->undo_array->len - data->undo_back, data->undo_back );
        data->undo_back = 0;
    }
    int a = gtk_text_iter_get_offset(start);
    int b = gtk_text_iter_get_offset(end);
    J_order(int,a,b);
    char *text = gtk_text_iter_get_text( start, end );
    bool join_broken = E_undo_S_join_broken;
    E_undo_S_join_broken = no;
    if( E_undo_Q_note_I_idle_join_break_S )
        g_source_remove( E_undo_Q_note_I_idle_join_break_S );
    E_undo_Q_note_I_idle_join_break_S = g_timeout_add( E_undo_Q_note_I_idle_join_break_S_timeout, E_undo_Q_note_I_idle_join_break, null );
    if( data->undo_array->len
    && !join_broken
    ){  struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, data->undo_array->len - 1 );
        if( undo->type == E_undo_Q_note_Z_action_S_text_deleted
        && ( a == undo->position || b == undo->position )
        ){  char *t;
            if( a == undo->position )
                t = g_strconcat( undo->u.text, text, null );
            else
            {   undo->position -= g_utf8_strlen( text, -1 );
                t = g_strconcat( text, undo->u.text, null );
            }
            g_free(text);
            g_free( undo->u.text );
            undo->u.text = t;
            return;
        }
    }
    g_array_append_val( data->undo_array
    , (( struct E_undo_Q_note_Z_action_data )
      { .type = E_undo_Q_note_Z_action_S_text_deleted
      , .position = a
      , .u.text = text
      })
    );
}
gboolean
E_undo_Q_note_I_idle_join_break(
  gpointer data
){  E_undo_S_join_broken = yes;
    E_undo_Q_note_I_idle_join_break_S = 0;
    return G_SOURCE_REMOVE;
}
void
E_undo_Q_note_Z_gtk_I_undo( GSimpleAction *action
, GVariant *param
, void *data_
){  GtkTreeSelection *selection = gtk_tree_view_get_selection( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] );
    GtkTreeModel *notes_store;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected( selection, &notes_store, &iter );
    GtkTextBuffer *text_buffer;
    struct E_note_tab_Q_note_Z_ext_data *data;
    gtk_tree_model_get( notes_store
    , &iter
    , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
    , E_note_tab_Q_tree_Z_column_S_ext_data, &data
    , -1
    );
    g_object_unref( text_buffer );
    if( !data->undo_array
    || data->undo_back >= data->undo_array->len
    )
        return;
    data->undo_back++;
    struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, data->undo_array->len - data->undo_back );
    GtkTextIter start, end;
    gtk_text_buffer_get_iter_at_offset( text_buffer, &start, undo->position );
    GtkTextView *text_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).note;
    switch( undo->type )
    { case E_undo_Q_note_Z_action_S_text_inserted:
          gtk_text_view_scroll_to_iter( text_view, &start, 0, no, 0, 0 );
          gtk_text_buffer_select_range( text_buffer, &start, &start );
          gtk_text_buffer_get_iter_at_offset( text_buffer, &end, undo->position + undo->u.length );
          undo->u.text = gtk_text_iter_get_text( &start, &end );
          g_signal_handlers_block_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_delete_range, null );
          gtk_text_buffer_delete( text_buffer, &start, &end );
          g_signal_handlers_unblock_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_delete_range, null );
          break;
      case E_undo_Q_note_Z_action_S_text_deleted:
          g_signal_handlers_block_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_insert_text, null );
          gtk_text_buffer_insert( text_buffer, &start, undo->u.text, -1 );
          g_signal_handlers_unblock_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_insert_text, null );
          unsigned length = g_utf8_strlen( undo->u.text, -1 );
          g_free( undo->u.text );
          undo->u.length = length;
          gtk_text_buffer_get_iter_at_offset( text_buffer, &start, undo->position );
          gtk_text_buffer_get_iter_at_offset( text_buffer, &end, undo->position + undo->u.length );
          gtk_text_view_scroll_to_iter( text_view, &end, 0, no, 0, 0 );
          gtk_text_buffer_select_range( text_buffer, &start, &end );
          break;
    }
}
void
E_undo_Q_note_Z_gtk_I_redo( GSimpleAction *action
, GVariant *param
, void *data_
){  GtkTreeSelection *selection = gtk_tree_view_get_selection( g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] );
    GtkTreeModel *notes_store;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected( selection, &notes_store, &iter );
    GtkTextBuffer *text_buffer;
    struct E_note_tab_Q_note_Z_ext_data *data;
    gtk_tree_model_get( notes_store
    , &iter
    , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
    , E_note_tab_Q_tree_Z_column_S_ext_data, &data
    , -1
    );
    g_object_unref( text_buffer );
    if( !data->undo_array
    || !data->undo_back
    )
        return;
    struct E_undo_Q_note_Z_action_data *undo = &g_array_index( data->undo_array, struct E_undo_Q_note_Z_action_data, data->undo_array->len - data->undo_back );
    data->undo_back--;
    GtkTextIter start, end;
    gtk_text_buffer_get_iter_at_offset( text_buffer, &start, undo->position );
    GtkTextView *text_view = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).note;
    switch( undo->type )
    { case E_undo_Q_note_Z_action_S_text_inserted:
          g_signal_handlers_block_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_insert_text, null );
          gtk_text_buffer_insert( text_buffer, &start, undo->u.text, -1 );
          g_signal_handlers_unblock_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_insert_text, null );
          unsigned length = g_utf8_strlen( undo->u.text, -1 );
          g_free( undo->u.text );
          undo->u.length = length;
          gtk_text_buffer_get_iter_at_offset( text_buffer, &start, undo->position );
          gtk_text_buffer_get_iter_at_offset( text_buffer, &end, undo->position + undo->u.length );
          gtk_text_view_scroll_to_iter( text_view, &end, 0, no, 0, 0 );
          gtk_text_buffer_select_range( text_buffer, &start, &end );
          break;
      case E_undo_Q_note_Z_action_S_text_deleted:
          gtk_text_view_scroll_to_iter( text_view, &start, 0, no, 0, 0 );
          gtk_text_buffer_select_range( text_buffer, &start, &start );
          gtk_text_buffer_get_iter_at_offset( text_buffer, &end, undo->position + undo->u.length );
          undo->u.text = gtk_text_iter_get_text( &start, &end );
          g_signal_handlers_block_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_delete_range, null );
          gtk_text_buffer_delete( text_buffer, &start, &end );
          g_signal_handlers_unblock_by_func( text_buffer, E_undo_Q_note_Z_gtk_X_delete_range, null );
          break;
    }
}
/******************************************************************************/
