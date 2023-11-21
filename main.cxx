#include "window.h"


int main(int argc, char **argv) {
    Fl_Window *window = UIwindow();
    window->show(argc, argv);
    return Fl::run();
}