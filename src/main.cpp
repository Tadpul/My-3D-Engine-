#include "engine/Engine.h"

int main()
{
    SDLApplication app("myWindow",1400, 700 , SDL_WINDOW_RESIZABLE);
    app.MainLoop();
    return 0;
}