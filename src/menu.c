/************************************
 *  Implementace projektu Breakout  *
 *     Knihovna pro načítání menu   *
 *             MAT0586              *
 ************************************/

#include "menu.h"

MenuOption display_menu(SDL_Renderer *renderer, TTF_Font *font) {
    ScoreEntry scores[MAX_TOP_SCORES];

    int score_count = load_scores(scores, MAX_SCORES);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};

    // Rect for the START button
    SDL_Rect start_rect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 80, 200, 50};

    // Render menu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Title
    TTF_Font *fontBRK = TTF_OpenFont("assets/Audiowide-Regular.ttf", 60);
    render_text(renderer, fontBRK, "BREAKOUT", red, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);

    // Scoreboard
    render_text(renderer, font, "SCOREBOARD", white, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 80);

	// Sort
    qsort(scores, score_count, sizeof(ScoreEntry), compare_scores);

    // Scoreboard TOP3
	for (int i = 0; i < MAX_TOP_SCORES; i++) {
        char score_text[200];
        TTF_Font *fontBOARD = TTF_OpenFont("assets/Audiowide-Regular.ttf", 20);
    	snprintf(score_text, sizeof(score_text), "%.30s .................... %d", scores[i].name, scores[i].score);
    	render_text(renderer, fontBOARD, score_text, white, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 120 + i * 30);
	}

    // START button
    TTF_Font *fontSTART = TTF_OpenFont("assets/Audiowide-Regular.ttf", 50);
    render_text(renderer, fontSTART, "START", green, start_rect.x + start_rect.w / 2, start_rect.y + start_rect.h / 2 - 20);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return MENU_EXIT;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;
                if (x >= start_rect.x && x <= start_rect.x + start_rect.w &&
                    y >= start_rect.y && y <= start_rect.y + start_rect.h) {
                    return MENU_START_GAME;
                }
            }
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return MENU_EXIT;
            }
        }
    }
    return MENU_EXIT;
}
