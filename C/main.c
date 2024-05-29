#include "include.h"

void game_reset(game_t *game)
{
    game->player = rand() % 2;
    game->cursor = 0;
    game->pause = false;
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            game->grid[i][j] = ' ';
}

void game_init(game_t *game)
{
    srand(time(NULL));
    game->player1 = 0;
    game->player2 = 0;
    game->key = 0;
    game_reset(game);
}

void exit_game(game_t *game)
{
    endwin();
    printf("Player 1: %d\nPlayer 2: %d\n", game->player1, game->player2);
    if (game->player1 > game->player2)
        printf("Player 1 wins!\n");
    else if (game->player2 > game->player1)
        printf("Player 2 wins!\n");
    else
        printf("It's a draw!\n");
    exit(0);
}

void win(game_t *game)
{
    game->pause = true;
    if (game->player)
        game->player1++;
    else
        game->player2++;
}

void check_win(game_t *game, int height)
{
    int count = 0;
    int cursor = game->cursor;
    char player = game->player ? 'X' : 'O';
    for (size_t i = 0; i < GRID_WIDTH && count < 4; i++){
        if (game->grid[height][i] == player)
            count++;
        else
            count = 0;
    }
    if (count >= 4) {
        win(game);
        return;
    }
    count = 0;
    for (size_t i = 0; i < GRID_HEIGHT && count < 4; i++){
        if (game->grid[i][game->cursor] == player)
            count++;
        else
            count = 0;
    }
    if (count >= 4) {
        win(game);
        return;
    }
    count = 0;
    while (true) {
        if (height < 0 || cursor < 0)
            break;
        height--;
        cursor--;
    }
    for (size_t i = 0; i < GRID_WIDTH && count < 4; i++){
        if (height >= GRID_HEIGHT || cursor >= GRID_WIDTH)
            break;
        if (game->grid[height][cursor] == player)
            count++;
        else
            count = 0;
        height++;
        cursor++;
    }
    if (count >= 4) {
        win(game);
        return;
    }
}

void drop(game_t *game)
{
    int i = GRID_HEIGHT - 1;
    while (i >= 0) {
        if (game->grid[i][game->cursor] == ' ')
            break;
        i--;
    }
    if (i >= 0) {
        game->grid[i][game->cursor] = game->player ? 'X' : 'O';
        check_win(game, i);
        game->player = !game->player;
    }
}

void handle_input(game_t *game)
{
    game->key = getch();
    switch (game->key) {
        case 'q':
            exit_game(game);
            break;
        case 'r':
            game_reset(game);
            break;
        default:
            break;
    }
    if (!game->pause) {
        switch (game->key) {
            case KEY_LEFT:
                if (game->cursor > 0)
                    game->cursor--;
                break;
            case KEY_RIGHT:
                if (game->cursor < GRID_WIDTH - 1)
                    game->cursor++;
                break;
            case KEY_DOWN:
                drop(game);
                break;
            default:
                break;
        }
    }
}

void printing(game_t *game)
{
    clear();
    mvprintw(0, 0, "Player 1: %d", game->player1);
    mvprintw(1, 0, "Player 2: %d", game->player2);
    mvprintw(2, 0 , "PLAYER TURN:%c", game->player ? 'X' : 'O');

    mvprintw(3, 2 * game->cursor, " |");
    mvprintw(4, 2 * game->cursor, " V");
    for (int i = 0; i < GRID_HEIGHT; i++) {
        mvprintw(i + 5, 0 , "|");
        for (int j = 0; j < GRID_WIDTH; j++)
            mvprintw(i + 5, (2 * j) + 1, "%c%c", game->grid[i][j], '|');
    }
    mvprintw(GRID_HEIGHT + 5, 0, "Use arrow keys to move, 'r' to reset, 'q' to quit");
    move(GRID_HEIGHT + 4, game->cursor);
}

int main(void)
{
    game_t game;
    WINDOW *window = initscr();
    keypad(window, true);
    noecho();
    curs_set(0);

    game_init(&game);

    while (true) {
        printing(&game);
        handle_input(&game);
        refresh();
    }
    endwin();
    return 0;
}
