/************************************
 *  Implementace projektu Breakout  *
 *   Knihovna s pomocnými funkcemi  *
 *             MAT0586              *
 ************************************/

#include "utils.h"

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x - surface->w / 2, y , surface->w, surface->h}; // Zarovnání na střed
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// třídění podle skóre sestupně
int compare_scores(const void *a, const void *b) {
    ScoreEntry *scoreA = (ScoreEntry *)a;
    ScoreEntry *scoreB = (ScoreEntry *)b;

    // Porovnáme skóre v sestupném pořadí
    return scoreB->score - scoreA->score;
}
