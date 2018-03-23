//=============================================================================
GtkClipboard *E_clipboard_S_0, *E_clipboard_S_1, *E_clipboard_S_2;
GdkAtom E_dnd_Q_tree_Z_data_type_S_native, E_dnd_Q_tree_Z_data_type_S_text;
const GtkTargetEntry E_clipboard_Q_tree_Q_1_S_data_types[1] =
{ { E_dnd_Q_tree_Z_data_type_S_text_S_atom_name, 0, 0 }
};
const GtkTargetEntry E_dnd_Q_tree_S_data_types[2] =
{ { E_dnd_Q_tree_Z_data_type_S_native_S_atom_name, GTK_TARGET_SAME_APP, 0 }
, { E_dnd_Q_tree_Z_data_type_S_text_S_atom_name, GTK_TARGET_OTHER_WIDGET, 0 }
};
//=============================================================================
GtkTreeModel *E_dnd_Z_gtk_Q_tree_drag_source_S_store;
int E_dnd_Z_gtk_Q_tree_drag_source_S_tab;
GtkTreeIter E_dnd_Z_gtk_Q_tree_drag_source_S_books_iter;
bool E_dnd_Z_gtk_Q_tree_drag_dest_U_gave_data_into_native; ///użycie trybu “move” ‘drag & drop’, ale usuwanie danych źródłowych tylko wtedy, gdy umieszczono je w kształtce notatnika ·w tym· programie.
bool E_dnd_Z_gtk_Q_tree_drag_source_U_native_checked, E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result; ///odwraca sprawdzanie, czy można upuścić dane— ze sprawdzania celu na sprawdzanie źródła ‘natywnego’, ale w jedynie dostępnej procedurze wywoływanej dla celu.
//=============================================================================
///NDFN dostarcza wszystkie teksty z wiersza, który jest powiązany, a nie tylko widoczne.
void
E_dnd_Z_gtk_Q_tree_Q_clipboard_S_1_I_supply_data( GtkClipboard *clipboard
, GtkSelectionData *data
, guint data_type
, void *tree_view
){  GtkTreeModel *tree_store;
    GtkTreeIter iter;
    if( !gtk_tree_selection_get_selected( gtk_tree_view_get_selection( tree_view ), &tree_store, &iter ))
        return;
    int n = gtk_tree_model_get_n_columns( tree_store );
    if(n)
    {   GPtrArray *a = g_ptr_array_new();
        g_ptr_array_set_free_func( a, g_free );
        for( int i = 0; i < n; i++ )
            if( gtk_tree_model_get_column_type( tree_store, i ) == G_TYPE_STRING )
            {   char *t;
                gtk_tree_model_get( tree_store, &iter, i, &t, -1 );
                g_ptr_array_add( a, t );
            }
        if( a->len )
        {   GString *str = g_string_new(null);
            for( int i = 0; i < a->len; i++ )
            {   g_string_append( str, g_ptr_array_index( a, i ));
                g_string_append( str, "; " );
            }
            str->str[ str->len - 2 ] = '\0';
            gtk_selection_data_set_text( data, str->str, -1 );
            g_string_free( str, yes );
        }
        g_ptr_array_free( a, yes );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
gboolean
E_dnd_Z_gtk_Q_tree_drag_source_I_row_draggable( GtkTreeDragSource *store
, GtkTreePath *path
){  E_dnd_Z_gtk_Q_tree_drag_source_S_store = ( void * )store;
    E_dnd_Z_gtk_Q_tree_drag_source_U_native_checked = no;
    E_dnd_Z_gtk_Q_tree_drag_source_S_tab = E_note_tab_Q_note_tab_S_current_tab;
    struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab );
    GtkTreeModel *books_model = gtk_tree_view_get_model( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
    if( GTK_TREE_MODEL(store) != books_model )
    {   GtkTreeSelection *selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
        gtk_tree_selection_get_selected( selection, null, &E_dnd_Z_gtk_Q_tree_drag_source_S_books_iter );
    }
    return yes;
}
gboolean
E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_get( GtkTreeDragSource *store
, GtkTreePath *path
, GtkSelectionData *data
){  E_dnd_Z_gtk_Q_tree_drag_dest_U_gave_data_into_native = no;
    GdkAtom type = gtk_selection_data_get_target(data);
    if( type == E_dnd_Q_tree_Z_data_type_S_native )
    {   char *s = gtk_tree_path_to_string(path);
        size_t n = strlen(s) + 1;
        unsigned char *d = ( unsigned char * )g_strndup( s, n );
        g_free(s);
        struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_dnd_Z_gtk_Q_tree_drag_source_S_tab );
        ///‘uid’ grupy drzew wymieniającej wewnątrz dane w formacie ‘natywnym’.
        if(( void * )store == gtk_tree_view_get_model( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] )
        || ( void * )store == gtk_tree_view_get_model( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] )
        )
            d[n] = 1; ///grupa drzew ksiąg i notatek
        //else ///już ma wartość ‛0’ nadaną przez “g_strndup”.
            //d[n] = 0; ///domyślnie– ‘uid’ nieistniejącej grupy (którą też są wszystkie większe od maksymalnej posiadającej implementację obsługi), co oznacza, że “drag & drop” w formacie ‘natywnym’ jest realizowane tylko wewnątrz jednego drzewa, a inne “drop” nie są realizowane.
        gtk_selection_data_set( data
        , E_dnd_Q_tree_Z_data_type_S_native
        , 8
        , d
        , n + 1
        );
        g_free(d);
    }else if( type == E_dnd_Q_tree_Z_data_type_S_text )
    ///NDFN dostarcza wszystkie teksty z wiersza, który jest powiązany, a nie tylko widoczne.
    {   GtkTreeIter iter;
        gtk_tree_model_get_iter(( void * )store, &iter, path );
        int n = gtk_tree_model_get_n_columns(( void * )store );
        if(n)
        {   GPtrArray *a = g_ptr_array_new();
            g_ptr_array_set_free_func( a, g_free );
            for( int i = 0; i < n; i++ )
                if( gtk_tree_model_get_column_type(( void * )store, i ) == G_TYPE_STRING )
                {   char *t;
                    gtk_tree_model_get(( void * )store, &iter, i, &t, -1 );
                    g_ptr_array_add( a, t );
                }
            if( a->len )
            {   GString *str = g_string_new(null);
                for( int i = 0; i < a->len; i++ )
                {   g_string_append( str, g_ptr_array_index( a, i ));
                    g_string_append( str, "; " );
                }
                str->str[ str->len - 2 ] = '\0';
                gtk_selection_data_set_text( data, str->str, -1 );
                g_string_free( str, yes );
            }
            g_ptr_array_free( a, yes );
        }
    }else
        return no;
    return yes;
}
gboolean
E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete( GtkTreeDragSource *store
, GtkTreePath *path
){  GtkTreeIter iter;
    if( G_OBJECT_TYPE(store) == GTK_TYPE_TREE_STORE )
    {   int n = gtk_notebook_get_n_pages( E_note_tab_Q_note_tab_S );
        for( int i = 0; i != n; i++ )
        {   bool continue_ = false;
            struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, i );
            GtkTreeSelection *selection;
            GtkTreeModel *model;
            GtkTreePath *selected_path;
            model = gtk_tree_view_get_model( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
            if( GTK_TREE_MODEL(store) != model )
            {   selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ]);
                gtk_tree_selection_get_selected( selection, null, &iter );
                selected_path = gtk_tree_model_get_path( model, &iter );
                GtkTreePath *books_path = gtk_tree_model_get_path( model, &E_dnd_Z_gtk_Q_tree_drag_source_S_books_iter );
                if( gtk_tree_path_compare( selected_path, books_path ) == 0 )
                    continue_ = true;
                gtk_tree_path_free( books_path );
                gtk_tree_path_free( selected_path );
            }else
                continue_ = true;
            if( continue_ )
            {   selection = gtk_tree_view_get_selection( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ]);
                gtk_tree_selection_get_selected( selection, &model, &iter );
                selected_path = gtk_tree_model_get_path( model, &iter );
                GtkTreePath *path_ = gtk_tree_path_copy(path);
                if(( gtk_tree_path_compare( selected_path, path ) == 0
                  || gtk_tree_path_is_descendant( selected_path, path )
                )
                && gtk_tree_path_up( path_ )
                )
                {   struct E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete_I_Z *data = g_new( struct E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete_I_Z, 1 );
                    data->selection = selection;
                    data->path_ = path_;
                    g_idle_add( E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete_I, data );
                }
                gtk_tree_path_free( selected_path );
            }
        }
    }
    if( !E_dnd_Z_gtk_Q_tree_drag_dest_U_gave_data_into_native )
        return no;
    gtk_tree_model_get_iter(( void * )store, &iter, path );
    if( G_OBJECT_TYPE(store) == GTK_TYPE_LIST_STORE )
        gtk_list_store_remove(( void * )store, &iter );
    else
        gtk_tree_store_remove(( void * )store, &iter );
    return yes;
}
gboolean
E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete_I( void *data
){  struct E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete_I_Z *data_ = data;
    gtk_tree_selection_select_path( data_->selection, data_->path_ );
    gtk_tree_path_free( data_->path_ );
    g_free( data_ );
    return G_SOURCE_REMOVE;
}
//-----------------------------------------------------------------------------
gboolean
E_dnd_Z_gtk_Q_tree_drag_dest_I_row_drop_possible( GtkTreeDragDest *store
, GtkTreePath *path
, GtkSelectionData *data
){  GdkAtom type = gtk_selection_data_get_target(data);
    int n;
    const unsigned char *d = gtk_selection_data_get_data_with_length( data, &n );;
    switch( d[ n - 1 ] )
    { case 1:
          if( type == E_dnd_Q_tree_Z_data_type_S_native )
          {   struct E_note_tab_Q_ext_data_Z *note_tab_ext_data = &g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_dnd_Z_gtk_Q_tree_drag_source_S_tab );
              if(( void * )store != gtk_tree_view_get_model( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_books ] )
              && ( void * )store != gtk_tree_view_get_model( note_tab_ext_data->tree[ E_note_tab_Q_ext_data_Z_tree_S_notes ] )
              )
                  return no;
          }
          GtkTreeView *books_tree = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ];
          if(( void * )store != E_note_tab_Q_note_tab_S_books_tree_store
          && !gtk_tree_selection_get_selected( gtk_tree_view_get_selection( books_tree ), null, null )
          )
              return no;
          if( type == E_dnd_Q_tree_Z_data_type_S_native )
          {   if(( void * )store == E_note_tab_Q_note_tab_S_books_tree_store )
              {   GtkTreeIter iter;
                  GtkTreePath *p = gtk_tree_path_copy(path);
                  if( !gtk_tree_model_get_iter(( void * )store, &iter, path ))
                      gtk_tree_path_up(p);
                  gtk_tree_view_set_cursor( books_tree, p, null, no );
                  gtk_tree_path_free(p);
              }
              if( E_dnd_Z_gtk_Q_tree_drag_source_S_store == ( void * )store )
              {   GtkTreePath *from_path = gtk_tree_path_new_from_string(( char * )d );
                  if( gtk_tree_path_is_ancestor( from_path, path ))
                  {   gtk_tree_path_free( from_path );
                      return no;
                  }
                  gtk_tree_path_free( from_path );
              }else
              {   GtkTreeIter from_iter;
                  gtk_tree_model_get_iter_from_string( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &from_iter, ( char * )d );
                  if( E_dnd_Z_gtk_Q_tree_drag_source_S_store == E_note_tab_Q_note_tab_S_books_tree_store )
                  {   GtkTreeIter iter;
                      GtkTreeSelection *selection = gtk_tree_view_get_selection( books_tree );
                      gtk_tree_selection_get_selected( selection, null, &iter );
                      if( gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &from_iter, &iter ))
                          return no;
                      char *s = gtk_tree_model_get_string_from_iter( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &iter );
                      if( !strcmp(( char * )d, s ))
                      {   g_free(s);
                          return no;
                      }
                      g_free(s);
                  }
                  if( E_dnd_Z_gtk_Q_tree_drag_source_S_store != E_note_tab_Q_note_tab_S_books_tree_store
                  && ( void * )store != E_note_tab_Q_note_tab_S_books_tree_store
                  )
                      return yes;
                  if( E_dnd_Z_gtk_Q_tree_drag_source_U_native_checked )
                      return E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result;
                  E_dnd_Z_gtk_Q_tree_drag_source_U_native_checked = yes;
                  if( E_dnd_Z_gtk_Q_tree_drag_source_S_store == E_note_tab_Q_note_tab_S_books_tree_store )
                  {   GtkTreeIter new_from_iter;
                      GtkTreeStore *tree_store_;
                      gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                      , &from_iter
                      , E_note_tab_Q_tree_Z_column_S_object_ref, &tree_store_
                      , -1
                      );
                      g_object_unref( tree_store_ );
                      new_from_iter = from_iter;
                      if( gtk_tree_model_get_iter_first(( void * )tree_store_, &new_from_iter ))
                          return E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result = no;
                      GtkTreeIter start_iter = from_iter;
                      if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                          while(empty)
                          {   from_iter = new_from_iter;
                              gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                              , &from_iter
                              , E_note_tab_Q_tree_Z_column_S_object_ref, &tree_store_
                              , -1
                              );
                              g_object_unref( tree_store_ );
                              if( gtk_tree_model_get_iter_first(( void * )tree_store_, &new_from_iter ))
                                  return E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result = no;
                              if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                                  continue;
                              new_from_iter = from_iter;
                              while( !gtk_tree_model_iter_next( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter ))
                              {   gtk_tree_model_iter_parent( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter );
                                  if( !gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &start_iter, &new_from_iter ))
                                      goto End_1;
                                  from_iter = new_from_iter;
                              }
                          }
End_1:                ;
                  }else
                  {   GtkTextBuffer *text_buffer;
                      gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                      , &from_iter
                      , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
                      , -1
                      );
                      g_object_unref( text_buffer );
                      GtkTextIter text_iter;
                      gtk_text_buffer_get_end_iter( text_buffer, &text_iter );
                      if( gtk_text_iter_get_offset( &text_iter ) > 0 )
                          return E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result = no;
                      GtkTreeIter start_iter = from_iter, new_from_iter;
                      if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                          while(empty)
                          {   from_iter = new_from_iter;
                              gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                              , &from_iter
                              , E_note_tab_Q_tree_Z_column_S_object_ref, &text_buffer
                              , -1
                              );
                              g_object_unref( text_buffer );
                              gtk_text_buffer_get_end_iter( text_buffer, &text_iter );
                              if( gtk_text_iter_get_offset( &text_iter ) > 0 )
                                  return E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result = no;
                              if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                                  continue;
                              new_from_iter = from_iter;
                              while( !gtk_tree_model_iter_next( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter ))
                              {   gtk_tree_model_iter_parent( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter );
                                  if( !gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &start_iter, &new_from_iter ))
                                      goto End_2;
                                  from_iter = new_from_iter;
                              }
                          }
End_2:                ;
                  }
                  E_dnd_Z_gtk_Q_tree_drag_source_S_native_check_result = yes;
              }
          }else if( type != E_dnd_Q_tree_Z_data_type_S_text )
              return no;
          break;
      default:
          if( type == E_dnd_Q_tree_Z_data_type_S_native )
          {   if( E_dnd_Z_gtk_Q_tree_drag_source_S_store != ( void * )store )
                  return no;
              if( G_OBJECT_TYPE(store) == GTK_TYPE_TREE_STORE )
              {   GtkTreePath *from_path = gtk_tree_path_new_from_string(( char * )d );
                  if( gtk_tree_path_is_ancestor( from_path, path ))
                  {   gtk_tree_path_free( from_path );
                      return no;
                  }
                  gtk_tree_path_free( from_path );
              }else if( G_OBJECT_TYPE(store) != GTK_TYPE_LIST_STORE )
                  return no;
          }else
              return no;
          break;
    }
    return yes;
}
gboolean
E_dnd_Z_gtk_Q_tree_drag_dest_I_drag_data_received( GtkTreeDragDest *store
, GtkTreePath *path
, GtkSelectionData *data
){  g_signal_handlers_block_matched( store, G_SIGNAL_MATCH_DATA, 0, 0, null, null, null );
    E_dnd_Z_gtk_Q_tree_drag_dest_U_gave_data_into_native = yes;
    GdkAtom type = gtk_selection_data_get_target(data);
    int n;
    const unsigned char *d = gtk_selection_data_get_data_with_length( data, &n );
    switch( d[ n - 1 ] )
    { case 1:
      {   GtkTreeView *books_tree = g_array_index( E_note_tab_Q_note_tab_S_ext_data, struct E_note_tab_Q_ext_data_Z, E_note_tab_Q_note_tab_S_current_tab ).tree[ E_note_tab_Q_ext_data_Z_tree_S_books ];
          if(( void * )store != E_note_tab_Q_note_tab_S_books_tree_store
            && !gtk_tree_selection_get_selected( gtk_tree_view_get_selection( books_tree ), null, null )
          )
          {   g_signal_handlers_unblock_matched( store, G_SIGNAL_MATCH_DATA, 0, 0, null, null, null );
              return no;
          }
          GtkTreeIter from_iter;
          char *title;
          if( type == E_dnd_Q_tree_Z_data_type_S_native )
              gtk_tree_model_get_iter_from_string( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &from_iter, ( char * )d );
          else if( type == E_dnd_Q_tree_Z_data_type_S_text )
              title = ( char * )gtk_selection_data_get_text(data);
          else
          {   g_signal_handlers_unblock_matched( store, G_SIGNAL_MATCH_DATA, 0, 0, null, null, null );
              return no;
          }
          GtkTreeIter before_iter, *before_iter_ = &before_iter, iter;
          if( gtk_tree_model_get_iter(( void * )store, &before_iter, path ))
              gtk_tree_store_insert_before(( void * )store, &iter, null, &before_iter );
          else
          {   if( gtk_tree_path_get_depth(path) > 1 )
              {   gtk_tree_path_up(path);
                  gtk_tree_model_get_iter(( void * )store, &before_iter, path );
              }else
                  before_iter_ = null;
              gtk_tree_store_insert_after(( void * )store, &iter, before_iter_, null );
          }
          void *object;
          if( type == E_dnd_Q_tree_Z_data_type_S_text )
          {   struct E_note_tab_Q_note_Z_ext_data *ext_data;
              if(( void * )store == E_note_tab_Q_note_tab_S_books_tree_store )
              {   object = E_note_tab_Q_tree_Q_store_M();
                  ext_data = null;
              }else
              {   object = E_note_tab_Q_note_Q_buffer_M(null);
                  ext_data = E_note_tab_Q_note_Z_ext_data_M();
                  ext_data->date_uid = g_get_real_time(); //NDFN brak zabezpieczenia przed powtórzeniem jednej wartości.
              }
              gtk_tree_store_set(( void * )store
              , &iter
              , E_note_tab_Q_tree_Z_column_S_title, title
              , E_note_tab_Q_tree_Z_column_S_object_ref, object
              , E_note_tab_Q_tree_Z_column_S_ext_data, ext_data
              , -1
              );
              g_free(title);
              g_object_unref(object);
          }else
          {   GtkTreeIter start_iter = from_iter;
              if( E_dnd_Z_gtk_Q_tree_drag_source_S_store == ( void * )store //w tym samym drzewie.
                || ( E_dnd_Z_gtk_Q_tree_drag_source_S_store != E_note_tab_Q_note_tab_S_books_tree_store
                  && ( void * )store != E_note_tab_Q_note_tab_S_books_tree_store
              )) //lub z drzewa notatek do innego drzewa notatek.
              {   void *data;
                  gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                  , &from_iter
                  , E_note_tab_Q_tree_Z_column_S_title, &title
                  , E_note_tab_Q_tree_Z_column_S_object_ref, &object
                  , E_note_tab_Q_tree_Z_column_S_ext_data, &data
                  , -1
                  );
                  g_object_unref(object);
                  gtk_tree_store_set(( void * )store
                  , &iter
                  , E_note_tab_Q_tree_Z_column_S_title, title
                  , E_note_tab_Q_tree_Z_column_S_object_ref, object
                  , E_note_tab_Q_tree_Z_column_S_ext_data, data
                  , -1
                  );
                  g_free(title);
                  GtkTreeIter new_from_iter;
                  if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                      while(empty)
                      {   from_iter = new_from_iter;
                          GtkTreeIter new_iter;
                          gtk_tree_store_append(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                          , &from_iter
                          , E_note_tab_Q_tree_Z_column_S_title, &title
                          , E_note_tab_Q_tree_Z_column_S_object_ref, &object
                          , E_note_tab_Q_tree_Z_column_S_ext_data, &data
                          , -1
                          );
                          g_object_unref(object);
                          gtk_tree_store_set(( void * )store
                          , &iter
                          , E_note_tab_Q_tree_Z_column_S_title, title
                          , E_note_tab_Q_tree_Z_column_S_object_ref, object
                          , E_note_tab_Q_tree_Z_column_S_ext_data, data
                          , -1
                          );
                          g_free(title);
                          if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                              continue;
                          gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          new_from_iter = from_iter;
                          while( !gtk_tree_model_iter_next( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter ))
                          {   gtk_tree_model_iter_parent( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter );
                              if( !gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &start_iter, &new_from_iter ))
                                  goto End;
                              gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                              iter = new_iter;
                              from_iter = new_from_iter;
                          }
                      }
              }else if(( void * )store == E_note_tab_Q_note_tab_S_books_tree_store ) //z drzewa notatek do drzewa ksiąg.
              {   struct E_note_tab_Q_note_Z_ext_data *note_data;
                  gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                  , &from_iter
                  , E_note_tab_Q_tree_Z_column_S_title, &title
                  , E_note_tab_Q_tree_Z_column_S_ext_data, &note_data
                  , -1
                  );
                  E_note_tab_Q_note_Z_ext_data_W( note_data );
                  object = E_note_tab_Q_tree_Q_store_M();
                  gtk_tree_store_set(( void * )store
                  , &iter
                  , E_note_tab_Q_tree_Z_column_S_title, title
                  , E_note_tab_Q_tree_Z_column_S_object_ref, object
                  , E_note_tab_Q_tree_Z_column_S_ext_data, null
                  , -1
                  );
                  g_free(title);
                  g_object_unref(object);
                  GtkTreeIter new_from_iter;
                  if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                      while(empty)
                      {   from_iter = new_from_iter;
                          GtkTreeIter new_iter;
                          gtk_tree_store_append(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                          , &from_iter
                          , E_note_tab_Q_tree_Z_column_S_title, &title
                          , E_note_tab_Q_tree_Z_column_S_ext_data, &note_data
                          , -1
                          );
                          E_note_tab_Q_note_Z_ext_data_W( note_data );
                          object = E_note_tab_Q_tree_Q_store_M();
                          gtk_tree_store_set(( void * )store
                          , &iter
                          , E_note_tab_Q_tree_Z_column_S_title, title
                          , E_note_tab_Q_tree_Z_column_S_object_ref, object
                          , E_note_tab_Q_tree_Z_column_S_ext_data, null
                          , -1
                          );
                          g_free(title);
                          g_object_unref(object);
                          if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                              continue;
                          gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          new_from_iter = from_iter;
                          while( !gtk_tree_model_iter_next( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter ))
                          {   gtk_tree_model_iter_parent( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter );
                              if( !gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &start_iter, &new_from_iter ))
                                  goto End;
                              gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                              iter = new_iter;
                              from_iter = new_from_iter;
                          }
                      }
              }else //z drzewa ksiąg do drzewa notatek.
              {   void *tree_data;
                  gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                  , &from_iter
                  , E_note_tab_Q_tree_Z_column_S_title, &title
                  , E_note_tab_Q_tree_Z_column_S_ext_data, &tree_data
                  , -1
                  );
                  object = E_note_tab_Q_note_Q_buffer_M(null);
                  struct E_note_tab_Q_note_Z_ext_data *ext_data = E_note_tab_Q_note_Z_ext_data_M();
                  ext_data->date_uid = 0;
                  gtk_tree_store_set(( void * )store
                  , &iter
                  , E_note_tab_Q_tree_Z_column_S_title, title
                  , E_note_tab_Q_tree_Z_column_S_object_ref, object
                  , E_note_tab_Q_tree_Z_column_S_ext_data, ext_data
                  , -1
                  );
                  g_free(title);
                  g_object_unref(object);
                  GtkTreeIter new_from_iter;
                  if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                      while(empty)
                      {   from_iter = new_from_iter;
                          GtkTreeIter new_iter;
                          gtk_tree_store_append(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          gtk_tree_model_get( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                          , &from_iter
                          , E_note_tab_Q_tree_Z_column_S_title, &title
                          , E_note_tab_Q_tree_Z_column_S_ext_data, &tree_data
                          , -1
                          );
                          object = E_note_tab_Q_note_Q_buffer_M(null);
                          struct E_note_tab_Q_note_Z_ext_data *ext_data = E_note_tab_Q_note_Z_ext_data_M();
                          ext_data->date_uid = 0;
                          gtk_tree_store_set(( void * )store
                          , &iter
                          , E_note_tab_Q_tree_Z_column_S_title, title
                          , E_note_tab_Q_tree_Z_column_S_object_ref, object
                          , E_note_tab_Q_tree_Z_column_S_ext_data, ext_data
                          , -1
                          );
                          g_free(title);
                          g_object_unref(object);
                          if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                              continue;
                          gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          new_from_iter = from_iter;
                          while( !gtk_tree_model_iter_next( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter ))
                          {   gtk_tree_model_iter_parent( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter );
                              if( !gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &start_iter, &new_from_iter ))
                                  goto End;
                              gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                              iter = new_iter;
                              from_iter = new_from_iter;
                          }
                      }
              }
          }
      }
          break;
      default:
      {   GtkTreeIter from_iter, before_iter, iter;
          gtk_tree_model_get_iter_from_string( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &from_iter, ( char * )d );
          if( G_OBJECT_TYPE(store) == GTK_TYPE_LIST_STORE )
          {   if( gtk_tree_model_get_iter(( void * )store, &before_iter, path ))
                  gtk_list_store_insert_before(( void * )store, &iter, &before_iter );
              else
                  gtk_list_store_insert_before(( void * )store, &iter, null );
              n = gtk_tree_model_get_n_columns( E_dnd_Z_gtk_Q_tree_drag_source_S_store );
              for( int i = 0; i < n; i++ )
              {   GValue v = G_VALUE_INIT;
                  gtk_tree_model_get_value( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                  , &from_iter
                  , i
                  , &v
                  );
                  gtk_list_store_set_value(( void * )store
                  , &iter
                  , i
                  , &v
                  );
                  g_value_unset( &v );
              }
          }else
          {   GtkTreeIter *before_iter_ = &before_iter;
              if( gtk_tree_model_get_iter(( void * )store, &before_iter, path ))
                  gtk_tree_store_insert_before(( void * )store, &iter, null, &before_iter );
              else
              {   if( gtk_tree_path_get_depth(path) > 1 )
                  {   gtk_tree_path_up(path);
                      gtk_tree_model_get_iter(( void * )store, &before_iter, path );
                  }else
                      before_iter_ = null;
                  gtk_tree_store_insert_after(( void * )store, &iter, before_iter_, null );
              }
              GtkTreeIter start_iter = from_iter;
              n = gtk_tree_model_get_n_columns( E_dnd_Z_gtk_Q_tree_drag_source_S_store );
              for( int i = 0; i < n; i++ )
              {   GValue v = G_VALUE_INIT;
                  gtk_tree_model_get_value( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                  , &from_iter
                  , i
                  , &v
                  );
                  gtk_tree_store_set_value(( void * )store
                  , &iter
                  , i
                  , &v
                  );
                  g_value_unset( &v );
              }
              GtkTreeIter new_from_iter;
              if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                  while(empty)
                  {   from_iter = new_from_iter;
                      GtkTreeIter new_iter;
                      gtk_tree_store_append(( void * )store, &new_iter, &iter );
                      iter = new_iter;
                      n = gtk_tree_model_get_n_columns( E_dnd_Z_gtk_Q_tree_drag_source_S_store );
                      for( int i = 0; i < n; i++ )
                      {   GValue v = G_VALUE_INIT;
                          gtk_tree_model_get_value( E_dnd_Z_gtk_Q_tree_drag_source_S_store
                          , &from_iter
                          , i
                          , &v
                          );
                          gtk_tree_store_set_value(( void * )store
                          , &iter
                          , i
                          , &v
                          );
                          g_value_unset( &v );
                      }
                      if( gtk_tree_model_iter_nth_child( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter, 0 ))
                          continue;
                      gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                      iter = new_iter;
                      new_from_iter = from_iter;
                      while( !gtk_tree_model_iter_next( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter ))
                      {   gtk_tree_model_iter_parent( E_dnd_Z_gtk_Q_tree_drag_source_S_store, &new_from_iter, &from_iter );
                          if( !gtk_tree_store_is_ancestor(( void * )E_dnd_Z_gtk_Q_tree_drag_source_S_store, &start_iter, &new_from_iter ))
                              goto End;
                          gtk_tree_model_iter_parent(( void * )store, &new_iter, &iter );
                          iter = new_iter;
                          from_iter = new_from_iter;
                      }
                  }
          }
      }
          break;
    }
End:g_signal_handlers_unblock_matched( store, G_SIGNAL_MATCH_DATA, 0, 0, null, null, null );
    return yes;
}
//=============================================================================
