#ifndef A_CUKI_TYPEWRITER_H
#define A_CUKI_TYPEWRITER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuki_bitmaps.h"
//
#define MAX_CHARS 1024
#define SCALE 2
#define CHAR_SIZE (GRID_SIZE * SCALE)
#define GAP SCALE
#define PADDING 20

// Text State
static char buffer[MAX_CHARS];
static int len = 0;
static int cursor = 0;

// Append a character at current cursor position
static inline void append_char(char c)
{
    if (len < MAX_CHARS - 1)
    {
        for (int i = len; i > cursor; i--)
        {
            buffer[i] = buffer[i - 1];
        }
        buffer[cursor] = c;
        len++;
        cursor++;
    }
}

// Delete character before cursor
static inline void handle_backspace(void)
{
    if (cursor > 0)
    {
        for (int i = cursor - 1; i < len - 1; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        len--;
        cursor--;
    }
}

// Delete character at cursor position
static inline void handle_delete(void)
{
    if (cursor < len)
    {
        for (int i = cursor; i < len - 1; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        len--;
    }
}

static inline void move_cursor_left(void)
{
    if (cursor > 0) cursor--;
}

static inline void move_cursor_right(void)
{
    if (cursor < len) cursor++;
}

// Draw character bitmap to window
static inline void draw_glyph(Display *display, Window window, GC gc, 
                              const int bitmap[GRID_SIZE][GRID_SIZE], 
                              int x, int y, int black, int white)
{
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            int color = (bitmap[r][c] == 1) ? black : white;
            XSetForeground(display, gc, color);
            XFillRectangle(display, window, gc,
                           x + (c * SCALE),
                           y + (r * SCALE),
                           SCALE, SCALE);
        }
    }
}

// Main Render Loop
static inline void render(Display *display, Window window, GC gc)
{
    XWindowAttributes gwa;
    XGetWindowAttributes(display, window, &gwa);

    int white = WhitePixel(display, DefaultScreen(display));
    int black = BlackPixel(display, DefaultScreen(display));

    // Clear background
    XSetForeground(display, gc, white);
    XFillRectangle(display, window, gc, 0, 0, gwa.width, gwa.height);

    int cur_x = PADDING;
    int cur_y = PADDING;
    int cursor_draw_x = PADDING;
    int cursor_draw_y = PADDING;
    int max_x = gwa.width - PADDING;

    for (int i = 0; i <= len; i++)
    {
        if (cur_x + CHAR_SIZE > max_x && cur_x > PADDING)
        {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        }

        if (i == cursor)
        {
            cursor_draw_x = cur_x;
            cursor_draw_y = cur_y;
        }

        if (i == len) break;

        if (buffer[i] == '\n') {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
            continue; // Skip drawing and don't add horizontal spacing
        }

        // Map characters to their respective bitmaps
        if (buffer[i] == 'A' || buffer[i] == 'a')
        {
            draw_glyph(display, window, gc, bitmap_A, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'B' || buffer[i] == 'b')
        {
            draw_glyph(display, window, gc, bitmap_B, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'C' || buffer[i] == 'c')
        {
            draw_glyph(display, window, gc, bitmap_C, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'D' || buffer[i] == 'd')
        {
            draw_glyph(display, window, gc, bitmap_D, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'E' || buffer[i] == 'e')
        {
            draw_glyph(display, window, gc, bitmap_E, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'F' || buffer[i] == 'f')
        {
            draw_glyph(display, window, gc, bitmap_F, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'G' || buffer[i] == 'g')
        {
            draw_glyph(display, window, gc, bitmap_G, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'H' || buffer[i] == 'h')
        {
            draw_glyph(display, window, gc, bitmap_H, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'I' || buffer[i] == 'i')
        {
            draw_glyph(display, window, gc, bitmap_I, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'J' || buffer[i] == 'j')
        {
            draw_glyph(display, window, gc, bitmap_J, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'K' || buffer[i] == 'k')
        {
            draw_glyph(display, window, gc, bitmap_K, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'L' || buffer[i] == 'l')
        {
            draw_glyph(display, window, gc, bitmap_L, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'M' || buffer[i] == 'm')
        {
            draw_glyph(display, window, gc, bitmap_M, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'N' || buffer[i] == 'n')
        {
            draw_glyph(display, window, gc, bitmap_N, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'O' || buffer[i] == 'o')
        {
            draw_glyph(display, window, gc, bitmap_O, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'P' || buffer[i] == 'p')
        {
            draw_glyph(display, window, gc, bitmap_P, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'Q' || buffer[i] == 'q')
        {
            draw_glyph(display, window, gc, bitmap_Q, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'R' || buffer[i] == 'r')
        {
            draw_glyph(display, window, gc, bitmap_R, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'S' || buffer[i] == 's')
        {
            draw_glyph(display, window, gc, bitmap_S, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'T' || buffer[i] == 't')
        {
            draw_glyph(display, window, gc, bitmap_T, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'U' || buffer[i] == 'u')
        {
            draw_glyph(display, window, gc, bitmap_U, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'V' || buffer[i] == 'v')
        {
            draw_glyph(display, window, gc, bitmap_V, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'W' || buffer[i] == 'w')
        {
            draw_glyph(display, window, gc, bitmap_W, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'X' || buffer[i] == 'x')
        {
            draw_glyph(display, window, gc, bitmap_X, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'Y' || buffer[i] == 'y')
        {
            draw_glyph(display, window, gc, bitmap_Y, cur_x, cur_y, black, white);
        }
        else if (buffer[i] == 'Z' || buffer[i] == 'z')
        {
            draw_glyph(display, window, gc, bitmap_Z, cur_x, cur_y, black, white);
        }

        else if (buffer[i] == ' ')
        {
            draw_glyph(display, window, gc, bitmap_space, cur_x, cur_y, black, white);
        }

        else if (buffer[i] == '.')
        {
            draw_glyph(display, window, gc, bitmap_dot, cur_x, cur_y, black, white);
        }

        cur_x += CHAR_SIZE + GAP;
    }

    // Draw Cursor
    XSetForeground(display, gc, black);
    XFillRectangle(display, window, gc, cursor_draw_x, cursor_draw_y, 3, CHAR_SIZE);
}

//
// Helper to get exact (x, y) coordinates for any cursor/character index
static inline void get_char_pos(Display *display, Window window, int target_index, int *out_x, int *out_y) {
    XWindowAttributes gwa;
    XGetWindowAttributes(display, window, &gwa);
    int max_x = gwa.width - PADDING;

    int cur_x = PADDING;
    int cur_y = PADDING;

    for (int i = 0; i <= len; i++) {
        if (cur_x + CHAR_SIZE > max_x && cur_x > PADDING) {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        }

        if (i == target_index) {
            *out_x = cur_x;
            *out_y = cur_y;
            return;
        }

        if (i == len) break;

        if (buffer[i] == '\n') {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        } else {
            cur_x += CHAR_SIZE + GAP;
        }
    }
}

static inline void move_cursor_up(Display *display, Window window) {
    if (cursor <= 0) return;

    int cur_x_pos, cur_y_pos;
    get_char_pos(display, window, cursor, &cur_x_pos, &cur_y_pos);

    int target_y = cur_y_pos - (CHAR_SIZE + GAP);
    if (target_y < PADDING) return; // Already on top line

    XWindowAttributes gwa;
    XGetWindowAttributes(display, window, &gwa);
    int max_x = gwa.width - PADDING;

    int best_i = -1;
    int min_dist = 999999;
    int cur_x = PADDING;
    int cur_y = PADDING;

    for (int i = 0; i <= len; i++) {
        if (cur_x + CHAR_SIZE > max_x && cur_x > PADDING) {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        }

        if (cur_y == target_y) {
            int dist = abs(cur_x - cur_x_pos);
            if (dist < min_dist) {
                min_dist = dist;
                best_i = i;
            }
        }

        if (i == len) break;

        if (buffer[i] == '\n') {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        } else {
            cur_x += CHAR_SIZE + GAP;
        }
    }

    if (best_i != -1) cursor = best_i;
}

static inline void move_cursor_down(Display *display, Window window) {
    int cur_x_pos, cur_y_pos;
    get_char_pos(display, window, cursor, &cur_x_pos, &cur_y_pos);

    int target_y = cur_y_pos + (CHAR_SIZE + GAP);

    XWindowAttributes gwa;
    XGetWindowAttributes(display, window, &gwa);
    int max_x = gwa.width - PADDING;

    int best_i = -1;
    int min_dist = 999999;
    int cur_x = PADDING;
    int cur_y = PADDING;

    for (int i = 0; i <= len; i++) {
        if (cur_x + CHAR_SIZE > max_x && cur_x > PADDING) {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        }

        if (cur_y == target_y) {
            int dist = abs(cur_x - cur_x_pos);
            if (dist < min_dist) {
                min_dist = dist;
                best_i = i;
            }
        }

        if (i == len) break;

        if (buffer[i] == '\n') {
            cur_x = PADDING;
            cur_y += CHAR_SIZE + GAP;
        } else {
            cur_x += CHAR_SIZE + GAP;
        }
    }

    if (best_i != -1) cursor = best_i;
}
//

#endif
