//
// Created by Theatre-Simon on 7/22/2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <gl.h>

#include <SDL.h>
#include <stdio.h>

struct window_t {
    SDL_Window *Window;
    SDL_GLContext *GLCtx;
    int bIsFullscreen;
};

struct window_t APV_Create_Window();

int APV_Pool_Events(SDL_Event *event);

void APV_Destroy_Window(struct window_t window);

void APV_Toggle_Fullscreen(struct window_t window);

#endif //WINDOW_H
