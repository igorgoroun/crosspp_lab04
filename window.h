#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Return_Button.H>
#include "libmessage.h"
#include "liblang.h"


#define W_WIDTH 640
#define W_PADDING 40
#define F_HEIGHT 25
#define F_PADDING 5
#define L_WIDTH (W_WIDTH-W_PADDING*2)

struct FileData {
  Fl_Input *path;
  Fl_Multiline_Input *result;
};


void UItouch(Fl_Widget* b, void* te);
Fl_Window *UIwindow();