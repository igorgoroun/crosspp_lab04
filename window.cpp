
#include "window.h"
#include "libtouch.h"


void UItouch(Fl_Widget* b, void* te) {
    void *mlib = get_message_lib();

    // dim button
    b->deactivate();
    // get our struct
    FileData *filedata = (FileData *)te;
    // // get filepath input and results window from struct
    Fl_Input *full_path = filedata->path;
    Fl_Multiline_Input *text_result = filedata->result;

    char *err_message;
    // create file
    signed char err_code = touch(full_path->value());
    switch(err_code) {
        case 1:
            err_message = get_message(mlib, "_M_FCREATED");
            break;
        case 0:
            err_message = get_message(mlib, "_M_FEXIST");
            break;
        default:
            err_message = get_message(mlib, "_M_UNKNOWN");
    }
    // show message
    text_result->value(err_message);

    // activate button and clear input box
    b->activate();
    full_path->value("");
    // re-draw window
    Fl_Window *win = b->window();
    win->redraw();
}

void UIExit(Fl_Widget *widget, void *fd) {
    free(fd);
    exit(0);
}

Fl_Window *UIwindow() {

    // lang
    void *mlib = get_message_lib();
    char *f_label = get_message(mlib, (char *)"_M_HELP");
    char *b_label = get_message(mlib, (char *)"_M_BCREATE");
    char *w_title = get_message(mlib, (char *)"_W_TITLE");

    // prepare form
    Fl_Box *label = new Fl_Box(W_PADDING, W_PADDING, L_WIDTH, F_HEIGHT, f_label);
    label->box(FL_NO_BOX);

    Fl_Input *filepath = new Fl_Input(W_PADDING, label->y()+F_HEIGHT+F_PADDING, L_WIDTH*3/4-W_PADDING/4, F_HEIGHT);

    Fl_Return_Button *execute_touch = new Fl_Return_Button(filepath->x()+filepath->w()+W_PADDING/2, filepath->y(), L_WIDTH/4-W_PADDING/4, F_HEIGHT, b_label);

    Fl_Multiline_Input *text_result = new Fl_Multiline_Input(W_PADDING, filepath->y()+F_HEIGHT+F_PADDING, L_WIDTH, F_HEIGHT);
    text_result->box(FL_NO_BOX);
    text_result->deactivate();

    // prepare window
    Fl_Window *window = new Fl_Window(W_WIDTH, W_PADDING*2+F_HEIGHT*3+F_PADDING*2, w_title);
    window->add(label);
    window->add(filepath);
    window->add(text_result);
    window->add(execute_touch);

    // make structure to pass multiple widgets
    struct FileData *filedata = (struct FileData*)malloc(sizeof(FileData));
    filedata->path = filepath;
    filedata->result = text_result;

    // on click button
    execute_touch->callback(UItouch, filedata);
    window->callback(UIExit, filedata);

    window->end();
    return window;
}

