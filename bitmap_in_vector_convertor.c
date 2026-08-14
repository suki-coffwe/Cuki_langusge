#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define GRID_SIZE 8

int main(void) {
    char char_name[64];
    char line[128];
    char grid[GRID_SIZE][GRID_SIZE + 1];

    printf("Enter character letter (e.g., B, D, X): ");
    if (scanf("%63s", char_name) != 1) return 1;

    printf("\nPaste or type 8 lines of 8 binary digits (0s and 1s):\n");

    int r = 0;
    while (r < GRID_SIZE && scanf("%127s", line) == 1) {
        int count = 0;
        char temp[GRID_SIZE + 1];

        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '0' || line[i] == '1') {
                temp[count++] = line[i];
                if (count == GRID_SIZE) break;
            } else {
                count = 0;
            }
        }

        if (count == GRID_SIZE) {
            temp[GRID_SIZE] = '\0';
            strcpy(grid[r], temp);
            r++;
        }
    }

    if (r < GRID_SIZE) {
        fprintf(stderr, "\nError: Expected %d valid lines of 8 binary digits.\n", GRID_SIZE);
        return 1;
    }

    char upper_c = (char)toupper((unsigned char)char_name[0]);
    char lower_c = (char)tolower((unsigned char)char_name[0]);

    printf("\n================ GENERATED C CODE ================\n\n");

    // 1. headers/cuki_bitmaps.h
    printf("/* 1. Paste into headers/cuki_bitmaps.h */\n");
    printf("static const int bitmap_%c[GRID_SIZE][GRID_SIZE] = {\n", upper_c);
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("    {");
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c%s", grid[i][j], (j < GRID_SIZE - 1) ? ", " : "");
        }
        printf("}%s\n", (i < GRID_SIZE - 1) ? "," : "");
    }
    printf("};\n\n");

    // 2. headers/a_cuki_typewriter.h
    printf("/* 2. Paste into headers/a_cuki_typewriter.h */\n");
    printf("        else if (buffer[i] == '%c' || buffer[i] == '%c')\n", upper_c, lower_c);
    printf("        {\n");
    printf("            draw_glyph(display, window, gc, bitmap_%c, cur_x, cur_y, black, white);\n", upper_c);
    printf("        }\n");

    // 3. final_bitmap_renderer_of_cuki_language.c
    printf("/* 3. Paste into final_bitmap_renderer_of_cuki_language.c */\n");
    printf("            else if (keysym == XK_%c || keysym == XK_%c)\n", lower_c, upper_c);
    printf("            {\n");
    printf("                append_char('%c');\n", upper_c);
    printf("            }\n");

    printf("==================================================\n");

    return 0;
}
