#include <stdio.h>
#include <windows.h>
#include "ui.h"
#include "board.h"

#define RESET "\033[0m"

void ui_init() {}

int back_color(int i, int j)
{
    if (i % 2 == j % 2)
    {
        return 40;
    }
    else
    {
        return 47;
    }
}

int front_color(char piece)
{
    if (piece >= 'A'&& piece <= 'Z' )
    {
        return 34;
    }
    else if (piece >= 'a' && piece <= 'z')
    {
        return 31;
    }
    else
    {
        return 36;
    }
}

const char* color_code(int i, int j, char piece)
{
    static char color[64];
    snprintf(color, sizeof(color), "\033[1;%d;%dm", front_color(piece), back_color(i, j));
    return color;
}


void enable_ansi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void ui_draw_board()
{
    enable_ansi(); //if using .exe file to run the game, need to enable it to show color
    //printf("\033[2J\033[H"); //to refresh the chess board, optional, but the output message would also be refreshed
    printf("    a   b   c   d   e   f   g   h\n");
    printf("  ---------------------------------\n");
    for (int i = 7; i >= 0; i--)
    {
        printf("%d ", i+1);
        for (int j = 0; j < 8; j++)
        {
            printf("|%s %c %s", color_code(i, j, board[i][j]), board[i][j], RESET); 
        }
        printf(" |%d\n", i+1);
        printf("  ----------------------------------\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
}

void ui_show_message(const char* msg) {
    printf("%s\n", msg);
}

void ui_cleanup()
{
    //clean the output, no one use it just for ui output debug
    printf("\033[2J\033[H");
    fflush(stdout);
    return ;
}
