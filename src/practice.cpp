// #include <SDL3/SDL.h>
// #include <iostream>
// #include "Matrix.h"
// #include "Vector.h"

// Vec2 ortho(const float& x, const float& y, const float& xScreenSize, const float& yScreenSize)
// {
//     Vec2 result{};
//     float scale = std::min(xScreenSize, yScreenSize);
//     result.x() = (x - 0.5 * xScreenSize) / (0.5 * scale);
//     result.y() = -(y - 0.5 * yScreenSize) / (0.5 * scale);

//     return result;
// }

// Vec2 NDCToScreen(const Vec4& ndc, const float& xScreenSize, const float& yScreenSize)
// {
//     Vec2 result{};
//     result.x() = (xScreenSize > yScreenSize ? 0.5 * (yScreenSize * ndc.x() + xScreenSize) : 0.5 * (ndc.x() + 1) * xScreenSize);
//     result.y() = (xScreenSize < yScreenSize ? result.x() = 0.5 * (ndc.x() + 1) * xScreenSize : result.y() = 0.5 * (-ndc.y() + 1) * yScreenSize);

//     return result;
// }

// int main()
// {
//     if (!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;
    
//     constexpr float xScreenSize{ 600 };
//     constexpr float yScreenSize{ 600 };
//     Vec2 orthoPosition{0, 0};
//     Vec2 screenPosition{0, 0};
//     Vec4 ndc{0, 0, 1, 1};

//     SDL_Window* window = SDL_CreateWindow("new window", xScreenSize, yScreenSize, 0);
//     SDL_Event event;

//     const bool* keys = SDL_GetKeyboardState(nullptr);

//     bool running{ true };
//     while (running)
//     {
//         while (SDL_PollEvent(&event))
//         {
//             if (event.type == SDL_EVENT_QUIT) running = false;
//             else if (event.type == SDL_EVENT_MOUSE_MOTION)
//             {
                
//                 orthoPosition = ortho(event.motion.x, event.motion.y, xScreenSize, yScreenSize);
//                 ndc.x() = orthoPosition.x(); ndc.y() = orthoPosition.y();
//                 std::cout << orthoPosition;
//                 std::cout << NDCToScreen(ndc, xScreenSize, yScreenSize);
//             }
//         }
//     }

//     SDL_Quit();
//     return 0;
// }