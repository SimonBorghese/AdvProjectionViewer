//
// Created by Theatre-Simon on 7/22/2024.
//

#define GLAD_GL_IMPLEMENTATION

#include "Window.h"

struct window_t APV_Create_Window() {
    struct window_t newWindow;

    newWindow.bIsFullscreen = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        printf("Failed to Init SDL2!");
    }

    // Fix me: Configure to allow multiple monitor setup and such
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);

    newWindow.Window = SDL_CreateWindow("AdvProjectionViewer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    newWindow.GLCtx = SDL_GL_CreateContext(newWindow.Window);
    SDL_GL_MakeCurrent(newWindow.Window, newWindow.GLCtx);

    gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);

    glViewport(0,0,mode.w,mode.h);

    return newWindow;
}

int APV_Pool_Events(SDL_Event *event) {
    return SDL_PollEvent(event);
}

void APV_Destroy_Window(struct window_t window) {
    SDL_GL_DeleteContext(window.GLCtx);

    SDL_DestroyWindow(window.Window);

    SDL_Quit();
}

void APV_Toggle_Fullscreen(struct window_t window) {
    if (!window.bIsFullscreen) {
        SDL_SetWindowFullscreen(window.Window, SDL_WINDOW_FULLSCREEN);
        window.bIsFullscreen = 1;
    } else {
        SDL_SetWindowFullscreen(window.Window, 0);
        window.bIsFullscreen = 0;
    }
}
