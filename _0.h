#ifndef _MAIN_H
#define _MAIN_H
//=============================================================================
#define J_autogen           _autogen
#define _J_ab(a,b)          a##b
#define J_ab(a,b)           _J_ab(a,b)
#define J_a_b(a,b)          J_ab(J_ab(a,_),b)
//-----------------------------------------------------------------------------
#ifdef __SIZE_TYPE__
#   define N __SIZE_TYPE__
#elif defined( __SIZE_MAX__ )
#   if __SIZE_MAX__ == UINT_MAX
#       define N unsigned
#   elif __SIZE_MAX__ == ULONG_MAX
#       define N unsigned long
#   endif
#endif
#ifndef N
#   error unknown machine
#endif
//-----------------------------------------------------------------------------
#if defined( __SIZE_MAX__ )
#   if __SIZE_MAX__ == UINT_MAX
#       define J_cpu_register_data_suffix U
#   elif __SIZE_MAX__ == ULONG_MAX
#       define J_cpu_register_data_suffix UL
#   endif
#endif
#ifndef J_cpu_register_data_suffix
#   error unknown machine
#endif
//-----------------------------------------------------------------------------
#if ULONG_MAX == J_ab(0xffffffff,J_cpu_register_data_suffix)
#   define J_printf_64d "%lld"
#elif ULONG_MAX == J_ab(0xffffffffffffffff,J_cpu_register_data_suffix)
#   define J_printf_64d "%ld"
#endif
#ifndef J_printf_64d
#   error unknown machine
#endif
//-----------------------------------------------------------------------------
#define zero    ( J_ab(0,J_cpu_register_data_suffix) )
#define one     ( J_ab(1,J_cpu_register_data_suffix) )
#define false   zero
#define true    one
#define no      false
#define yes     true
#define empty   ( ~zero )
#define null    (( void * ) 0 )
//------------------------------------------------------------------------------
#define J_swap(type,a,b)    ({ type tmp = a; a = b; b = tmp; })
#define J_order(type,a,b)   if( a > b ){ J_swap(type,a,b); }
#define J_max(a,b)          ( (a) < (b) ? (b) : (a) )
#define J_min(a,b)          ( (a) > (b) ? (b) : (a) )
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef N bool;
//==============================================================================
// Musi być ta nazwa dla ‘native’, ponieważ ‟gtk+” wykonuje wymagane mechanizmy wewnętrzne podczas obsługi ‘drag & drop’.
#define E_dnd_Q_tree_Z_data_type_S_native_S_atom_name "GTK_TREE_MODEL_ROW"
#define E_dnd_Q_tree_Z_data_type_S_text_S_atom_name "UTF8_STRING"
//==============================================================================
struct E_dnd_Z_gtk_Q_tree_drag_source_I_drag_data_delete_I_Z
{ GtkTreeSelection *selection;
  GtkTreePath *path_;
};
//------------------------------------------------------------------------------
enum E_note_tab_Q_ext_data_Z_tree
{ E_note_tab_Q_ext_data_Z_tree_S_books
, E_note_tab_Q_ext_data_Z_tree_S_notes
, E_note_tab_Q_ext_data_Z_tree_S_n_
};
enum E_note_tab_Q_tree_Z_column
{ E_note_tab_Q_tree_Z_column_S_title
, E_note_tab_Q_tree_Z_column_S_object_ref
, E_note_tab_Q_tree_Z_column_S_ext_data
};
enum E_note_tab_Q_tree_Q_branch_Z_position
{ E_note_tab_Q_tree_Q_branch_Z_position_S_last = -1
, E_note_tab_Q_tree_Q_branch_Z_position_S_first
, E_note_tab_Q_tree_Q_branch_Z_position_S_before
, E_note_tab_Q_tree_Q_branch_Z_position_S_after
};
struct Q_gtk_Q_tree_model_I_foreach_S_data_E_olet
{ bool branch;
  GtkTreeIter *iter;
  char *iter_s;
};
//-----------------------------------------------------------------------------
struct E_note_tab_Q_ext_data_Z
{ GtkTreeView *tree[ E_note_tab_Q_ext_data_Z_tree_S_n_ ];
  GtkCellRendererText *tree_renderer_text[ E_note_tab_Q_ext_data_Z_tree_S_n_ ];
  GtkTextView *note;
  GtkContainer *note_attr;
  GtkLabel *note_date;
  GtkTreeView *new_tab_names_tree;
  GtkEntry *search_inexact, *search_exact, *search_exact_chars;
  GtkButton *search_next, *search_previous;
  bool default_previous;
  bool Q_notes_tree_U_selected;
  GtkWidget *focused;
};
//-----------------------------------------------------------------------------
struct E_note_tab_Q_note_Z_ext_data
{ GArray *undo_array;
  unsigned undo_back;
  gint64 date_uid;
};
enum E_undo_Q_note_Z_action
{ E_undo_Q_note_Z_action_S_text_inserted
, E_undo_Q_note_Z_action_S_text_deleted
};
struct E_undo_Q_note_Z_action_data
{ enum E_undo_Q_note_Z_action type;
  int position;
  union
  { int length;
    char *text;
  } u;
};
//=============================================================================
#define E_debug_I_message(...) \
  ({  GtkWidget *dialog = gtk_message_dialog_new( E_main_Q_window_S \
      , GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT \
      , GTK_MESSAGE_OTHER \
      , GTK_BUTTONS_CLOSE \
      , __VA_ARGS__ \
      ); \
      gtk_dialog_run( GTK_DIALOG(dialog) ); \
      gtk_widget_destroy(dialog); \
  })
#define E_error_J_return(s) \
  for( ; E_error_S; \
    ( E_error_K(s), yes ) \
    && (({ return; }), yes ) \
  )
#define E_error_J_return_0(s) \
  for( ; E_error_S; \
    ( E_error_K(s), yes ) \
    && (({ return no; }), yes ) \
  )
#define E_error_J_return_1(s) \
  for( ; E_error_S; \
    ( E_error_K(s), yes ) \
    && (({ return yes; }), yes ) \
  )
//=============================================================================
//#define E_main_Z_gtk_Q_flow_I_async(proc,obj,...) \
    //E_main_Q_flow_S_async_finish = J_a_b(proc,finish); \
    //J_a_b(proc,async)( obj, ## __VA_ARGS__, G_PRIORITY_DEFAULT, null, E_main_Z_gtk_Q_flow_X_async, obj )
//#define E_main_Z_gtk_Q_flow_I_async_2(proc,obj,...) \
    //E_main_Q_flow_S_async_finish = J_a_b(proc,finish); \
    //J_a_b(proc,async)( obj, ## __VA_ARGS__, G_PRIORITY_DEFAULT, null, E_main_Z_gtk_Q_flow_X_async_2, obj )
//#define E_main_Z_gtk_Q_flow_I_sync \
//({  gtk_main(); \
    //E_main_Q_flow_S_async_finish = null; \
    //E_main_Q_flow_S_async_result; \
//})
//=============================================================================
#define g_application_mark_busy(a)
#define g_application_unmark_busy(a)
#endif
