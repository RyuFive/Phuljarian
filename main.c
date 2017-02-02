#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "windows.h"
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>
#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event event;
Mix_Music * music[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
Mix_Chunk * sound[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
TTF_Font * font= NULL;
bool running = true;

void logSDLError(const char *  msg){
    printf("%sError: %s\n", msg, SDL_GetError());
    return;
}
SDL_Texture * loadTexture(const char * file){
    SDL_Texture * texture = IMG_LoadTexture(renderer, file);
    if (texture == NULL){
        logSDLError("CreateTexture");
        return NULL;
    }
    return texture;
}
SDL_Texture * renderText(const char * message, const char * fontFile, SDL_Color color, int fontSize, SDL_Renderer * renderer){
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL){
		logSDLError("TTF_OpenFont");
		return NULL;
	}
	SDL_Surface * surface = TTF_RenderText_Blended(font, message, color);
	if (surface == NULL){
		TTF_CloseFont(font);
		logSDLError("TTF_RenderText");
		return NULL;
	}
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL){
		logSDLError("CreateTexture");
	}
	SDL_FreeSurface(surface);
	return texture;
}
void renderTextureScale(SDL_Texture * texture, int x, int y, int w, int h){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void renderTexture(SDL_Texture * texture, int x, int y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void renderTextureClip(SDL_Texture * texture, int x, int y, int w, int h, SDL_Rect * clips){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, texture, clips, &rect);
}
void renderFont(TTF_Font * font, char * msg, int r, int g, int b, int a, int x, int y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_Color color = {r, g, b, a};
    SDL_Surface * surface = TTF_RenderText_Solid(font, msg, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(texture, a);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void initSDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError("Init");
        return;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError("IMG_Init");
        SDL_Quit();
        return;
    }
    if (TTF_Init() != 0){
        logSDLError("TTF_Init");
        SDL_Quit();
        return;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0){
        logSDLError("Mixer_Init");
        SDL_Quit();
        return;
    }
//    font = TTF_OpenFont("res/ttf/electro.ttf", 46);
//    if (font == NULL){
//        logSDLError("TextLoad");
//        return;
//    }
    window = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL){
        logSDLError("CreateWindow");
        SDL_Quit();
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL){
        SDL_DestroyWindow(window);
        logSDLError("CreateRenderer");
        SDL_Quit();
        return;
    }
}
void initEverything(){
    time_t t;
    srand((unsigned) time(&t));
    initSDL(); //INIT SDL,WINDOW,RENDERER
//    loadTextures();
//    sliceTexture(textures[5]);
//    loadMusic();
//    initStatus();
//    initGameScreen();
//    initCredit();
}
void killEverything(){
//    for(int i=0; textures[i] != NULL; i++){
//        SDL_DestroyTexture(textures[i]);
//    }
//    for(int i=0; maps[i] != NULL; i++){
//        fclose(maps[i]);
//    }
//    for(int i=0; sound[i] != NULL; i++){
//        Mix_FreeChunk(sound[i]);
//    }
//    for(int i=0; music[i] != NULL; i++){
//        Mix_FreeMusic(music[i]);
//    }
//    free(screen);
//    free(status);
//    free(bat);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    Mix_CloseAudio();
//    TTF_CloseFont(font);
    IMG_Quit();
    SDL_Quit();
}
void gameLoop(){
    while(running){
//        update();
//        render();
//        handleEvents();
    }
}

int main(int argc, char* argv[]){
    initEverything();
    gameLoop();
    killEverything();
    return 0;
}
