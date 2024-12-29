/************************************
*  Implementace projektu Breakout  *
 *     Knihovna pro načítání menu   *
 *             MAT0586              *
 ************************************/

#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scoreboard.h"
#include "utils.h"

// Cesta k souboru se skore
#define SCORE_FILE "score.txt"

/** @def SCREEN_WIDTH
 *  @brief Šířka okna
 *
 *  @def SCREEN_HEIGHT
 *  @brief Výška okna
 *
 *  @def MAX_TOP_SCORES
 *  @brief Maximální počet zobrazených nejlepších skóre
 *
 *  @def MAX_SCORES
 *  @brief Maximální počet skóre v souboru
 */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_TOP_SCORES 3
#define MAX_SCORES 100

/** @enum MenuOption
 *  @brief Výčet možností menu
 */
typedef enum {
    MENU_START_GAME,
    MENU_SHOW_SCOREBOARD,
    MENU_EXIT
} MenuOption;

/** @fn MenuOption display_menu(SDL_Renderer *renderer, TTF_Font *font)
 *  @brief Funkce pro zobrazení menu
 *  @param renderer Ukazatel na SDL renderer
 *  @param font Ukazatel na TTF font
 *  @return Vrací vybranou možnost menu
 */
MenuOption display_menu(SDL_Renderer *renderer, TTF_Font *font);

#endif
