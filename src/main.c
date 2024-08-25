#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <stdlib.h>
#include <string.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define CELL_SIZE 100
#define TIMER_START 30.0f

typedef struct {
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    int currentPlayer;
    float timer;
    bool gameOver;
} GameState;

void DrawBoard(GameState *game) {
    for (int x = 0; x < BOARD_WIDTH; x++) {  
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            DrawRectangle(x * CELL_SIZE, 
			  y * CELL_SIZE, 
			  CELL_SIZE, 
			  CELL_SIZE, 
			  GRAY);
            if (game->board[x][y] != 0) {
                DrawCircle(x * CELL_SIZE + CELL_SIZE / 2, 
			   y * CELL_SIZE + CELL_SIZE / 2, 
			   CELL_SIZE / 2 - 5, 
			   game->board[x][y] == 1 ? RED : BLUE);
            }
        }
    }
}

void UpdateGame(GameState *game, float deltaTime) {
    if (game->gameOver) return;

    game->timer -= deltaTime;
    if (game->timer <= 0) {
        game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
        game->timer = TIMER_START;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int column = mousePos.x / CELL_SIZE;

        if (column >= 0 && column < BOARD_WIDTH) {
            for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
                if (game->board[column][y] == 0) {
                    game->board[column][y] = game->currentPlayer;
                    game->timer = TIMER_START;  // Reset timer after a move
                    game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
                    break;
                }
	    }
        }
    }

    // TODO: Add logic to detect "2 or 3 in a row" and decrease opponent's timer.
    // TODO: Add win condition and game over state.
}

void DrawGUI(GameState *game) {
    DrawText(TextFormat("Player %d's Turn", game->currentPlayer), 10, 10, 20, BLACK);
    DrawText(TextFormat("Time Left: %.1f", game->timer), 10, 40, 20, BLACK);
    
    if (GuiButton((Rectangle){ 10, 70, 150, 30 }, "Restart Game")) {
        memset(game->board, 0, sizeof(game->board));
        game->currentPlayer = 1;
        game->timer = TIMER_START;
        game->gameOver = false;
    }
}

int main(void) {
    InitWindow(BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE + 100, "Connect 4 with Timer and GUI");
    SetTargetFPS(60);

    GameState game = {
        .currentPlayer = 1,
        .timer = TIMER_START,
        .gameOver = false
    };
    memset(game.board, 0, sizeof(game.board));

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        UpdateGame(&game, deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawBoard(&game);
        DrawGUI(&game);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
