/************************************
 *  Implementace projektu Breakout  *
 *    Knihovna pro práci se skóre   *
 *             MAT0586              *
 ************************************/

#include "scoreboard.h"

int load_scores(ScoreEntry *scores, int max_scores) {
    FILE *file = fopen(SCORE_FILE, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open score file '%s'.\n", SCORE_FILE);
        return 0;
    }

    int count = 0;
    char line[128];
    while (fgets(line, sizeof(line), file) && count < max_scores) {
        char name[MAX_NAME_LENGTH];
        int score;
        if (sscanf(line, "%49s %d", name, &score) == 2) {  // Read name and score
            strncpy(scores[count].name, name, MAX_NAME_LENGTH);
            scores[count].name[MAX_NAME_LENGTH - 1] = '\0'; // Null-terminate the string
            scores[count].score = score;
            count++;
        } else {
            fprintf(stderr, "Warning: Invalid line in score file: %s", line);
        }
    }

    fclose(file);
    return count;
}

void save_scores(ScoreEntry scores[], int score_count) {
    FILE *file = fopen("score.txt", "w");
    if (!file) return;

    for (int i = 0; i < score_count; i++) {
        fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
    }
    fclose(file);
}

void display_scoreboard(SDL_Renderer *renderer, TTF_Font *font, ScoreEntry scores[], int score_count) {
    SDL_Color white = {255, 255, 255, 255};
    for (int i = 0; i < score_count; i++) {
        char text[128];
        snprintf(text, sizeof(text), "%s: %d", scores[i].name, scores[i].score);
        render_text(renderer, font, text, white, 300, 200 + i * 50);
    }
    SDL_RenderPresent(renderer);
}

void add_score(ScoreEntry scores[], int *count, int max_scores, const char *name, int score) {
    if (*count < max_scores || score > scores[*count - 1].score) {
        if (*count < max_scores) {
            (*count)++;
        }

        scores[*count - 1].score = score;
        strncpy(scores[*count - 1].name, name, MAX_NAME_LENGTH - 1);
        scores[*count - 1].name[MAX_NAME_LENGTH - 1] = '\0';

        for (int i = *count - 1; i > 0 && scores[i].score > scores[i - 1].score; i--) {
            ScoreEntry temp = scores[i];
            scores[i] = scores[i - 1];
            scores[i - 1] = temp;
        }
    }
}
