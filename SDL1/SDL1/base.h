#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <string>

struct SDL_Window;
struct SDL_Surface;

bool Init();
bool LoadMedia();
void Loop(void(*update)(), void(*close)());
void Update();
void Close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);
SDL_Surface* loadSurface(std::string path);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
extern SDL_Window* g_pWindow;
//The surface contained by the window
extern SDL_Surface* g_pScreenSurface;

#endif