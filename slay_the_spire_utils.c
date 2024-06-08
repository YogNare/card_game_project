#include "slay_the_spire_utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

extern TTF_Font *font;

void render_text(SDL_Renderer *renderer, const char *text, int x, int y) {
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, White);
    if (!surfaceMessage) {
        printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void render_centered_text(SDL_Renderer *renderer, const char *text, SDL_Rect rect) {
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, White);
    if (!surfaceMessage) {
        printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;
    Message_rect.x = rect.x + (rect.w - Message_rect.w) / 2;
    Message_rect.y = rect.y + (rect.h - Message_rect.h) / 2;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void render_multiline_text(SDL_Renderer *renderer, const char *text, SDL_Rect rect) {
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMessage;
    SDL_Texture *Message;
    SDL_Rect Message_rect;
    int line_height = 30; // Высота одной строки текста
    char *line = strtok((char *)text, "\n");

    int y_offset = rect.y + 20; // Смещение для верхней строки

    while (line != NULL) {
        surfaceMessage = TTF_RenderText_Solid(font, line, White);
        if (!surfaceMessage) {
            printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
            return;
        }
        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        Message_rect.w = surfaceMessage->w;
        Message_rect.h = surfaceMessage->h;
        Message_rect.x = rect.x + (rect.w - Message_rect.w) / 2;
        Message_rect.y = y_offset;

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);

        y_offset += line_height;
        line = strtok(NULL, "\n");
    }
}
