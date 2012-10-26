#ifndef RENDERER_H
#define RENDERER_H

#include "draw.h"
#include "scene.h"
#include "vec.h"

#include <string>
#include <list>

const int Render_None = 0;
const int Render_Print = 0x01;
const int Render_World = 0x02;

class Frame
{
public:

  enum FrameStatus {
    Approx,
    Sample
  };

  Frame()
    : sizeX(0), sizeY(0), data_(NULL), samples_(NULL), status(Approx) {}

  Frame(int sx, int sy)
    : sizeX(sx), sizeY(sy), data_(NULL), samples_(NULL), status(Approx) { allocate(sx, sy); }

  ~Frame() { if ( data_ ) { delete[] data_; delete[] samples_; } }

  void allocate(int sx, int sy) { sizeX=sx; sizeY=sy; data_ = new Color[sx*sy]; samples_ = new unsigned int[sx*sy]; }

  void clear() { for (int i=0; i<sizeX*sizeY; ++i) { data_[i]=Color(); samples_[i] = 0; } }

  Color& operator()(int ix, int iy) { return data_[ix+sizeX*iy]; }
  const Color& operator()(int ix, int iy) const { return data_[ix+sizeX*iy]; }

  unsigned int& samples(int ix, int iy) { return samples_[ix+sizeX*iy]; }
  const unsigned int& samples(int ix, int iy) const { return samples_[ix+sizeX*iy]; }

  int sizeX, sizeY;

  Color* data_;

  unsigned int* samples_;

  FrameStatus status;
};

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

  void init(int, int, int, int, int, const std::string& scenefile);

  void drawFrame();

  void render();

  void setRenderMode(int m) { renderMode_ = m; }

  int& renderMode() { return renderMode_; }

  void print(std::string text);

  void showFps(float fps);

  void camForward(float v);

  void camClimb(float v);

  void camStrafe(float v);

  void camYaw(float v);

  void clearFrame() { frame.clear(); }

  void screenshot(const std::string& filename);

  void save(SDL_Surface* surf, const std::string& filename);

 private:

  void initFrame();

 private:

  static Renderer instance_;

  int xSize;
    
  int ySize;

  int blocksize;

  int renderMode_;
    
  PrintEngine printEngine;

  Scene scene;

  SDL_Surface* screen;

  Frame frame;
};

#endif
