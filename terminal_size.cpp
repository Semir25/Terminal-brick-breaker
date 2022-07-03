#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int getWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_col;
}
int getHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_row;
}
