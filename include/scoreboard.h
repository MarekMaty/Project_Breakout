/************************************
*  Implementace projektu Breakout  *
 *    Knihovna pro práci se skóre   *
 *             MAT0586              *
 ************************************/

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "utils.h"

// Cesta k souboru se skore
#define SCORE_FILE "score.txt"

/** @def MAX_NAME_LENGTH
 *  @brief Maximální délka jména hráče
 *
 *  @def MAX_SCORES
 *  @brief Maximální počet skóre v souboru
 *
 *  @def MAX_TOP_SCORES
 *  @brief Maximální počet zobrazených nejlepších skóre
 */
#define MAX_NAME_LENGTH 20
#define MAX_SCORES 100
#define MAX_TOP_SCORES 3

/** @struct ScoreEntry
 *  @brief Struktura pro uchování informací o skóre
 */
typedef struct {
    char name[50];
    int score;
} ScoreEntry;

/** @fn int load_scores(ScoreEntry *scores, int max_scores)
 *  @brief Funkce pro načtení skóre ze souboru
 *  @param scores Ukazatel na pole struktur ScoreEntry
 *  @param max_scores Maximální počet skóre
 *  @return Počet načtených skóre
 */
int load_scores(ScoreEntry scores[], int max_scores);

/** @fn void save_scores(ScoreEntry scores[], int score_count)
 *  @brief Funkce pro uložení skóre do souboru
 *  @param scores Pole struktur ScoreEntry
 *  @param score_count Počet skóre
 */
void save_scores(ScoreEntry scores[], int score_count);

/** @fn void display_scoreboard(SDL_Renderer *renderer, TTF_Font *font, ScoreEntry scores[], int score_count)
 *  @brief Funkce pro zobrazení skóre
 *  @param renderer Ukazatel na SDL renderer
 *  @param font Ukazatel na TTF font
 *  @param scores Pole struktur ScoreEntry
 *  @param score_count Počet skóre
 */
void display_scoreboard(SDL_Renderer *renderer, TTF_Font *font, ScoreEntry scores[], int score_count);

/** @fn void add_score(ScoreEntry scores[], int *count, int max_scores, const char *name, int score)
 *  @brief Funkce pro přidání skóre
 *  @param scores Pole struktur ScoreEntry
 *  @param count Ukazatel na počet skóre
 *  @param max_scores Maximální počet skóre
 *  @param name Jméno hráče
 *  @param score Skóre
 */
void add_score(ScoreEntry scores[], int *count, int max_scores, const char *name, int score);

#endif
