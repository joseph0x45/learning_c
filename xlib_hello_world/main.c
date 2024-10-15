#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdio.h>

const int SCREEN_NUMBER = 0;

int main() {
  Display *display;
  Window window;
  display = XOpenDisplay(NULL);
  if (display == NULL) {
    perror("XOpenDisplay:");
    return 1;
  }
  int window_width = 300;
  int window_height = 300;
  int window_x = 0;
  int window_y = 0;
  int black_pixel = XBlackPixel(display, SCREEN_NUMBER);
  int white_pixel = XWhitePixel(display, SCREEN_NUMBER);
  int border_width = 0;
  window = XCreateSimpleWindow(display, XRootWindow(display, SCREEN_NUMBER),
                               window_x, window_y, window_width, window_height,
                               border_width, black_pixel, white_pixel);
  XMapWindow(display, window);
  XFlush(display);
  getchar();
  XUnmapWindow(display, window);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  return 0;
}
