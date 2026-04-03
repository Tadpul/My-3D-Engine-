#include <SDL3/SDL.h>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Hello SDL3", 640, 480, 0);
    SDL_Delay(3000); // Wait 3 seconds
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
