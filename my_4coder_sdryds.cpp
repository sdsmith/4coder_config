/*
4coder_default_bidings.cpp - Supplies the default bindings used for default 4coder behavior.

Ref: https://4coder.handmade.network/wiki/6818-customization_layer_-_getting_started
*/

// TOP

#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.cpp"

CUSTOM_COMMAND_SIG(my_git_status)
CUSTOM_DOC("Runs 'git status' at hot directory") {
    directory_get_hot(app, hot_directory_space, sizeof(hot_directory_space));
    
    String out_buf = make_string_slowly("*git*");
    String cmd = make_string_slowly("git status");
    String hot_dir = make_string_slowly(hot_directory_space);
    if (hot_dir.size <= 0) { return; }
    
    uint32_t access = AccessAll;
    View_Summary view = get_active_view(app, access);
    
    exec_system_command(app, &view,
                        buffer_identifier(out_buf.str, out_buf.size),
                        hot_dir.str, hot_dir.size, cmd.str, cmd.size,
                        CLI_OverlapWithConflict | CLI_CursorAtEnd);
    lock_jump_buffer(out_buf.str, out_buf.size);
}

// NOTE(allen|a4.0.22): This no longer serves as very good example code.
// Good example code will be coming soon, but in the mean time you can go
// to 4coder_remapping_commands.cpp for examples of what binding code looks like.

#if !defined(NO_BINDING)
extern "C" int32_t
get_bindings(void *data, int32_t size){
    Bind_Helper context_ = begin_bind_helper(data, size);
    Bind_Helper *context = &context_;
    
    set_all_default_hooks(context);
#if defined(__APPLE__) && defined(__MACH__)
    mac_default_keys(context);
#else
    default_keys(context);
#endif
    
    // TODO(sdryds): 
    // - clean_all_lines on save hook
    // - beginning/end of file
    // - remap page_up/down to C-v M-v
    // - select_all
    // - suppress_mouse
    // - modify handmade hero theme to be like mine.
    // - bind list_all_functions_current_buffer
    // - org-mode
    // - open file start dir from current file dir
    // - command history
    //   - C-up/down or S-up/down?
    // - line delete should be yank (C-k, not C-D)
    // - highlight background between mark and cursor
    // - save registers
    // - line move by p/n, f/b
    //   - might have to use other keys, they are already bound to the standard stuff. Mess with it???
    // - rectangle text insert/edit
    // - kill buffer rebind to C-x k or something similar, not C-k
    // - buffer modes
    // - move panels with S-arrow
    // - kill other panels C-1 (?)
    // - git integration
    // - rememeber the last seen file and make it first suggestion when switching buffers
    // - list all bound keys and their commands
    
    // Custom key bindings to override defaults
    //
    {
        begin_map(context, mapid_file);
        
        bind(context, 'l', MDFR_CTRL, center_view);
        bind(context, 'a', MDFR_CTRL, seek_beginning_of_line);
        bind(context, 'e', MDFR_CTRL, seek_end_of_textual_line);
        
        // Panel management
        bind(context, '0', MDFR_CTRL, close_panel); // TODO(sdryds): not working???? bound to default initializer insert??
        bind(context, '%', MDFR_CTRL, open_panel_vsplit);
        bind(context, '^', MDFR_CTRL, open_panel_hsplit);
        
        end_map(context);
    }
    
    int32_t result = end_bind_helper(context);
    return(result);
}
#endif //NO_BINDING

#endif //FCODER_DEFAULT_BINDINGS

// BOTTOM
