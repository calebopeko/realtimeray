#ifndef RENDERER_H
#define RENDERER_H

#include "draw.h"
#include <string>
#include <list>

const int Render_None = 0;
const int Render_Print = 0x01;
const int Render_World = 0x02;

class Renderer
{
 private:
  
  class PrintEngine
  {
  public:

    void init(std::string fontname, int fontsize, SDL_Surface* screen);

    void print(std::string text);

    void setFps(float fps) { fps_ = fps; }

    void draw();

  private:

    std::list<std::string> printHistory;

    class FontEngine
    {
    public:

      enum FontQuality
      {
	solid,
	shaded,
	blended
      };

      FontEngine() {}

      void init(std::string fontname, int fontsize);

      void setQuality(FontQuality quality);

      void setColor(SDL_Color col);

      void printTextToSurface(std::string text, SDL_Surface* surface, int x, int y);

      void textSize(std::string text, int* w, int* h);

      int fontsize;

    private:

      TTF_Font* font;

      FontQuality fontQuality;

      SDL_Color color;

    };

    FontEngine fontEngine;

    SDL_Surface* screen_;

    unsigned int maxLines;

    float fps_;
  };


 public:

  static Renderer& instance() { return instance_; }

  Renderer() 
    : xSize(-1), ySize(-1), renderMode_(Render_Print) {}

  void init(int, int, int, int);

  void drawFrame();

  void setRenderMode(int m) { renderMode_ = m; }

  int& renderMode() { return renderMode_; }

  void print(std::string text);

  void showFps(float fps);

 private:

  void initFrame();

 private:

  static Renderer instance_;

  int xSize;
    
  int ySize;

  int renderMode_;
    
  PrintEngine printEngine;

  SDL_Surface* screen;
};

#endif
