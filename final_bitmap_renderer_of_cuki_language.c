#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "a_cuki_typewriter.h"

int main(void)
{
    Display *display = XOpenDisplay(NULL);
    if (!display) return 1;

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow
    (
        display, RootWindow(display, screen),
        0, 0, 600, 400, 1,
        BlackPixel(display, screen), WhitePixel(display, screen)
    );

    XStoreName(display, window, "Cuki Language Typewriter");
    XSetTransientForHint(display, window, RootWindow(display, screen));

    Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDelete, 1);

    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, NULL);
    XEvent event;

    while (1)
    {
        XNextEvent(display, &event);

        if (event.type == Expose || event.type == ConfigureNotify)
        {
            render(display, window, gc);
        }
        else if (event.type == KeyPress)
        {
            KeySym keysym = XLookupKeysym(&event.xkey, 0);

            if (keysym == XK_c || keysym == XK_C)
            {
                append_char('C');
            }
            else if (keysym == XK_a || keysym == XK_A)
            {
                append_char('A');
            }
            else if (keysym == XK_b || keysym == XK_B)
            {
                append_char('B');
            }
            else if (keysym == XK_d || keysym == XK_D)
            {
                append_char('D');
            }
            else if (keysym == XK_e || keysym == XK_E)
            {
                append_char('E');
            }
            else if (keysym == XK_f || keysym == XK_F)
            {
                append_char('F');
            }
            else if (keysym == XK_g || keysym == XK_G)
            {
                append_char('G');
            }
            else if (keysym == XK_h || keysym == XK_H)
            {
                append_char('H');
            }
            else if (keysym == XK_i || keysym == XK_I)
            {
                append_char('I');
            }
            else if (keysym == XK_j || keysym == XK_J)
            {
                append_char('J');
            }
            else if (keysym == XK_k || keysym == XK_K)
            {
                append_char('K');
            }
            else if (keysym == XK_l || keysym == XK_L)
            {
                append_char('L');
            }
            else if (keysym == XK_m || keysym == XK_M)
            {
                append_char('M');
            }
            else if (keysym == XK_n || keysym == XK_N)
            {
                append_char('N');
            }
            else if (keysym == XK_o || keysym == XK_O)
            {
                append_char('O');
            }
            else if (keysym == XK_p || keysym == XK_P)
            {
                append_char('P');
            }
            else if (keysym == XK_q || keysym == XK_Q)
            {
                append_char('Q');
            }
            else if (keysym == XK_r || keysym == XK_R)
            {
                append_char('R');
            }
            else if (keysym == XK_s || keysym == XK_S)
            {
                append_char('S');
            }
            else if (keysym == XK_t || keysym == XK_T)
            {
                append_char('T');
            }
            else if (keysym == XK_u || keysym == XK_U)
            {
                append_char('U');
            }
            else if (keysym == XK_v || keysym == XK_V)
            {
                append_char('V');
            }
            else if (keysym == XK_w || keysym == XK_W)
            {
                append_char('W');
            }
            else if (keysym == XK_x || keysym == XK_X)
            {
                append_char('X');
            }
            else if (keysym == XK_y || keysym == XK_Y)
            {
                append_char('Y');
            }
            else if (keysym == XK_z || keysym == XK_Z)
            {
                append_char('Z');
            }

            else if (keysym == XK_space)
            {
                append_char(' ');
            }
            else if (keysym == XK_period)
            {
                append_char('.');
            }

            else if (keysym == XK_Return)
            {
                append_char('\n');
            }

            else if (keysym == XK_BackSpace)
            {
                handle_backspace();
            }
            else if (keysym == XK_Delete)
            {
                handle_delete();
            }
            else if (keysym == XK_Left)
            {
                move_cursor_left();
            }
            else if (keysym == XK_Right)
            {
                move_cursor_right();
            }
            else if (keysym == XK_Escape)
            {
                break;
            }

            render(display, window, gc);
        }
        else if (event.type == ClientMessage)
        {
            if ((Atom)event.xclient.data.l[0] == wmDelete) break;
        }
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
