/************************************
 *  Implementace projektu Breakout  *
 *     Knihovna pro herní logiku    *
 *             MAT0586              *
 ************************************/

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scoreboard.h"
#include "utils.h"
#include "menu.h"
#define SCORE_FILE "score.txt"

// Konstanty pro hru
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_SIZE 11
#define ROWS 6
#define COLS 10
#define BRICK_WIDTH 70
#define BRICK_HEIGHT 20
#define BALL_SPEED 5
#define PADDLE_SPEED 8

/** @struct Rect
 *  @brief Struktura pro uchování informací o obdélníku
 */
typedef struct {
    int x, y, w, h;
} Rect;

/** @struct Ball
 *  @brief Struktura pro uchování informací o míči
 */
typedef struct {
    float x, y;
    float dx, dy;
} Ball;

/** @struct Brick
 *  @brief Struktura pro uchování informací o cihle
 */
typedef struct {
    int x, y, w, h;
    bool active;
} Brick;

/** @fn void reset_ball(SDL_Rect *ball, int *dx, int *dy)
 *  @brief Funkce pro resetování míče
 *  @param ball Ukazatel na strukturu míče
 *  @param dx Ukazatel na rychlost míče ve směru osy x
 *  @param dy Ukazatel na rychlost míče ve směru osy y
 */
void reset_ball(SDL_Rect *ball, int *dx, int *dy);

/** @fn void check_collision(SDL_Rect *ball, int *dx, int *dy, SDL_Rect *paddle, Brick bricks[ROWS][COLS], int *score)
 *  @brief Funkce pro kontrolu kolizí
 *  @param ball Ukazatel na strukturu míče
 *  @param dx Ukazatel na rychlost míče ve směru osy x
 *  @param dy Ukazatel na rychlost míče ve směru osy y
 *  @param paddle Ukazatel na strukturu pálky
 *  @param bricks Dvourozměrné pole cihel
 *  @param score Ukazatel na skóre
 */
void check_collision(SDL_Rect *ball, int *dx, int *dy, SDL_Rect *paddle, Brick bricks[ROWS][COLS], int *score);

/** @fn void render_bricks(SDL_Renderer *renderer, Brick bricks[ROWS][COLS], SDL_Texture *brick_textures[ROWS])
 *  @brief Funkce pro vykreslení cihel
 *  @param renderer Ukazatel na renderer
 *  @param bricks Dvourozměrné pole cihel
 *  @param brick_textures Pole textur cihel
 */
void render_bricks(SDL_Renderer *renderer, Brick bricks[ROWS][COLS], SDL_Texture *brick_textures[ROWS]);

/** @fn void initialize_bricks(Brick bricks[ROWS][COLS])
 *  @brief Funkce pro inicializaci cihel
 *  @param bricks Dvourozměrné pole cihel
 */
void initialize_bricks(Brick bricks[ROWS][COLS]);

/** @fn void run_game(SDL_Renderer *renderer, TTF_Font *font, ScoreEntry scores[], int *score_count)
 *  @brief Funkce pro spuštění hry
 *  @param renderer Ukazatel na renderer
 *  @param font Ukazatel na font
 *  @param scores Pole skóre
 *  @param score_count Ukazatel na počet skóre
 */
void run_game(SDL_Renderer *renderer, TTF_Font *font, ScoreEntry scores[], int *score_count);

#endif