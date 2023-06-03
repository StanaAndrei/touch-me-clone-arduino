#include "Screen.hpp"
#include <stdarg.h>
#include <ctype.h> 

Screen::Screen() : render(true) {}

void Screen::setData(const char *const format, ...) {
  enableRender();
  va_list ptr;
  va_start(ptr, format);
  for (int i = 0; format[i]; i++) {
    String &sref = this->data[i];
    switch (toupper(format[i])) {
      case 'I':
        sref = va_arg(ptr, int);
        break;
      case 'S':
        sref = va_arg(ptr, char*);
        break;
      default:
        abort();
    }
  }
  va_end(ptr);
}//*/