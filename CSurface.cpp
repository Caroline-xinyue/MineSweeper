#include "iostream"
#include "CSurface.h"

using namespace std;

/*
  Constructor for CSurface
 */
CSurface::CSurface() {
}

/*
  Method to load the Surfaces
 */
SDL_Surface* CSurface::OnLoad(const char* File) {
  SDL_Surface* Surf_Temp = NULL;
  SDL_Surface* Surf_Return = NULL;

  if((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
    return NULL;
  }

  Surf_Return = SDL_DisplayFormat(Surf_Temp);
  SDL_FreeSurface(Surf_Temp);

  return Surf_Return;
}

/*
  Method to draw the Surfaces
 */
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
  if(Surf_Dest == NULL || Surf_Src == NULL) {
    return false;
  }
  SDL_Rect DestR;

  DestR.x = X;
  DestR.y = Y;

  SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

  return true;
}

/*
  Method to draw surface with specified width and height
 */
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
  if(Surf_Dest == NULL || Surf_Src == NULL) {
    return false;
  }
  SDL_Rect DestR;

  DestR.x = X;
  DestR.y = Y;

  SDL_Rect SrcR;

  SrcR.x = X2;
  SrcR.y = Y2;
  SrcR.w = W;
  SrcR.h = H;

  SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

  return true;
}

/*
  Method to make the Surface transparent
 */
bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
  if(Surf_Dest == NULL) {
    return false;
  }
  SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));
  return true;
}
