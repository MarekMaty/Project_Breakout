/************************************
*  Implementace projektu Breakout  *
 *   Knihovna s pomocnými funkcemi  *
 *             MAT0586              *
 ************************************/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scoreboard.h"

/** @fn void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y)
 *  @brief Funkce pro vykreslení textu na obrazovku
 *  @param renderer Ukazatel na SDL renderer
 *  @param font Ukazatel na TTF font
 *  @param text Text, který se má vykreslit
 *  @param color Barva textu
 *  @param x X-ová souřadnice textu
 *  @param y Y-ová souřadnice textu
 */
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y);

/** @fn int compare_scores(const void *a, const void *b)
 *  @brief Porovnávací funkce pro qsort (třídění podle skóre sestupně)
 *  @param a Ukazatel na první strukturu ScoreEntry
 *  @param b Ukazatel na druhou strukturu ScoreEntry
 *  @return Rozdíl skóre
 */
int compare_scores(const void *a, const void *b);

#endif
