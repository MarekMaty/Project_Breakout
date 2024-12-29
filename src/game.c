/************************************
 *  Implementace projektu Breakout  *
 *     Knihovna pro herní logiku    *
 *             MAT0586              *
 ************************************/

#include "game.h"

void reset_ball(SDL_Rect *ball, int *dx, int *dy) {
    ball->x = 400;
    ball->y = 300;
    *dx = 4;
    *dy = -4;
}

void check_collision(SDL_Rect *ball, int *dx, int *dy, SDL_Rect *paddle, Brick bricks[ROWS][COLS], int *score) {
    // Kolize s hranami obrazovky
    if (ball->x <= 0 || ball->x + BALL_SIZE >= 800) *dx = -*dx;
    if (ball->y <= 0) *dy = -*dy;

    // Kolize s pálkou
    if (SDL_HasIntersection(ball, paddle)) {
        *dy = -*dy;
        ball->y = paddle->y - BALL_SIZE; // Umístění míče nad pálku
    }

    // Kolize s cihlami
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Brick *brick = &bricks[i][j];
            if (brick->active && SDL_HasIntersection(ball, &(SDL_Rect){brick->x, brick->y, brick->w, brick->h})) {
                brick->active = false;
                *dy = -*dy;
                *score += 10; //+10
            }
        }
    }
}

void render_bricks(SDL_Renderer *renderer, Brick bricks[ROWS][COLS], SDL_Texture *brick_textures[ROWS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (bricks[i][j].active) {
                SDL_Rect rect = {bricks[i][j].x, bricks[i][j].y, bricks[i][j].w, bricks[i][j].h};
                SDL_RenderCopy(renderer, brick_textures[i], NULL, &rect);
            }
        }
    }
}

void initialize_bricks(Brick bricks[ROWS][COLS]) {
    int brick_padding = 5;
    int total_brick_width = (BRICK_WIDTH + brick_padding) * COLS - brick_padding;
    int x_offset = (SCREEN_WIDTH - total_brick_width) / 2;
    int y_offset = 50;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            bricks[i][j].x = x_offset + j * (BRICK_WIDTH + brick_padding);
            bricks[i][j].y = y_offset + i * (BRICK_HEIGHT + brick_padding);
            bricks[i][j].w = BRICK_WIDTH;
            bricks[i][j].h = BRICK_HEIGHT;
            bricks[i][j].active = true;
        }
    }
}

void run_game(SDL_Renderer *renderer, TTF_Font *font, ScoreEntry scores[], int *score_count) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color purple = {128, 0, 128, 255};
    SDL_Color gold = {255, 215, 0, 255};

    SDL_Rect paddle = {350, 550, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_Rect ball = {400, 300, BALL_SIZE, BALL_SIZE};
    int dx = 4, dy = -4;
    int score = 0;
    int lives = 3;
    bool running = true;
    bool paused = false;
    bool ball_on_paddle = true; // Jestli je balon na palce
    // Načtení textur
    SDL_Texture *paddle_texture = IMG_LoadTexture(renderer, "assets/paddle.svg");
    SDL_Texture *ball_texture = IMG_LoadTexture(renderer, "assets/ball.svg");
    SDL_Texture *brick_textures[ROWS];
    for (int i = 0; i < ROWS; i++) {
        char path[20];
        snprintf(path, sizeof(path), "assets/brick%d.png", i + 1);
        brick_textures[i] = IMG_LoadTexture(renderer, path);
    }

    Brick bricks[ROWS][COLS];
    initialize_bricks(bricks);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    paused = !paused; // Pauza
                } else if (event.key.keysym.sym == SDLK_SPACE && ball_on_paddle) {
                    ball_on_paddle = false; // Odpal
                }
            }
        }

        // PAUZA
        if (paused) {
            render_text(renderer, font, "PAUSED - Press ESC to continue", yellow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            continue;
        }

        // Pohyb pálkou
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && paddle.x > 0) {
            paddle.x -= 8;
        }
        if (state[SDL_SCANCODE_RIGHT] && paddle.x + PADDLE_WIDTH < 800) {
            paddle.x += 8;
        }

        // Pohyb míče na pálce
        if (ball_on_paddle) {
            ball.x = paddle.x + PADDLE_WIDTH / 2 - BALL_SIZE / 2;
            ball.y = paddle.y - BALL_SIZE;
        } else {
            // Pohyb míče
            ball.x += dx;
            ball.y += dy;
        }

        // Collision check
        check_collision(&ball, &dx, &dy, &paddle, bricks, &score);

        // Zivot minus
        if (ball.y > 600) {
            lives--;
            if (lives > 0) {
                ball_on_paddle = true;
            } else {
                render_text(renderer, font, "GAME OVER!", purple, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                SDL_RenderPresent(renderer);
                SDL_Delay(2000);
                break;
            }
        }

        // Vyhra check
        bool all_bricks_destroyed = true;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (bricks[i][j].active) {
                    all_bricks_destroyed = false;
                    break;
                }
            }
            if (!all_bricks_destroyed) break;
        }

        if (all_bricks_destroyed) {
            render_text(renderer, font, "YOU WIN!", gold, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            break; // Exit the game loop
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Paddle
        SDL_RenderCopy(renderer, paddle_texture, NULL, &paddle);

        // Ball
        SDL_RenderCopy(renderer, ball_texture, NULL, &ball);

        // Bricks
        render_bricks(renderer, bricks, brick_textures);

        // Skore a životy
        char info_text[50];
        snprintf(info_text, sizeof(info_text), "SCORE: %d	\t	LIVES: %d", score, lives);
        render_text(renderer, font, info_text, white, (SCREEN_WIDTH - 20)  / 2, 10);

        // Vzkreslení okraje
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, 0, 0, SCREEN_WIDTH, 0);
		SDL_RenderDrawLine(renderer, 0, 0, 0, SCREEN_HEIGHT);
		SDL_RenderDrawLine(renderer, SCREEN_WIDTH - 1, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limit FPS
    }
        // Uložení skóre
		if (score > 0) {
        if (*score_count < MAX_SCORES) {
            (*score_count)++;
        }
        char name[MAX_NAME_LENGTH];
        printf("Enter your name: ");
        scanf("%19s", name);
        add_score(scores, score_count, MAX_SCORES, name, score);
        save_scores(scores, *score_count);
    }

    SDL_DestroyTexture(paddle_texture);
    SDL_DestroyTexture(ball_texture);
    for (int i = 0; i < ROWS; i++) {
        SDL_DestroyTexture(brick_textures[i]);
    }
}
