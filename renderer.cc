#include "renderer.h"
#include "event.h"
#include "console.h"

#include <sstream>
#include <iostream>

Renderer Renderer::instance_;

void Renderer::print(std::string text)
{
  printEngine.print(text);
}

void Renderer::PrintEngine::init(std::string fontname, int fontsize, SDL_Surface* screen)
{
  console::dbg() << "Initializing print engine...";
  fontEngine.init(fontname, fontsize);
  screen_ = screen;
  maxLines = 16;
  console::dbg() << " Done. (Font: " << fontname << ", size: " << fontsize << ")" << std::endl;
}

void Renderer::PrintEngine::print(std::string text)
{
  int startPos=0, endPos = 0;
  std::ostringstream out;
  while ( 0 < (endPos = text.find("\n", startPos)) ) {
    if ( endPos > startPos ) printHistory.push_front(text.substr(startPos, endPos-startPos));
    startPos = endPos+1;
  }
  endPos = text.size();
  if ( endPos > startPos ) printHistory.push_front(text.substr(startPos, endPos-startPos));
  
  while ( printHistory.size() > maxLines ) printHistory.pop_back();
}

void Renderer::PrintEngine::draw()
{
  int y = screen_->h -2* fontEngine.fontsize;
  for (std::list<std::string>::const_iterator i = printHistory.begin();
       i!=printHistory.end(); 
       ++i, y-=fontEngine.fontsize) {
    fontEngine.printTextToSurface(*i, screen_, 0, y);
  }

  //draw fps
  if ( 1 ) {
    std::ostringstream out;
    out.precision(0);
    out.setf(std::ios::fixed);
    out << fps_ << "fps";
    int w; int h;
    fontEngine.textSize(out.str(), &w, &h);
    fontEngine.printTextToSurface(out.str(), screen_, screen_->w - w, 0);
  }
}

void Renderer::PrintEngine::FontEngine::init(std::string fontname, int fontsize_)
{
  fontsize = fontsize_;
  if ( TTF_Init() < 0 ) {
    console::err() << "Unable to initialize SDL_TTF." << std::endl;
    exit(1);
  }
  font=TTF_OpenFont(fontname.c_str(), fontsize);
  if(!font) {
    console::err() << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    exit(1);
  }
  fontQuality = blended;
  color.r = color.g = color.b = 255;
}

void Renderer::PrintEngine::FontEngine::setQuality(FontQuality quality)
{
  fontQuality = quality;
}
  
void Renderer::PrintEngine::FontEngine::setColor(SDL_Color col)
{
  color = col;
}

void Renderer::PrintEngine::FontEngine::printTextToSurface(std::string text, SDL_Surface* surface, int x, int y)
{
  SDL_Rect dstrect; dstrect.x = x; dstrect.y = y;
  SDL_Surface* text_surface = NULL;
 
  if (fontQuality == solid) {
    text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
  } else if (fontQuality == shaded) {
    SDL_Color back; back.r = back.g = back.b = 0;
    text_surface = TTF_RenderText_Shaded(font, text.c_str(), color, back);
  } else if (fontQuality == blended) {
    text_surface = TTF_RenderText_Blended(font, text.c_str(), color);
  }

  if( !text_surface ) {
    console::err() << "Unable to print text: " << text << std::endl;
    console::err() << " Reason: " << TTF_GetError() << std::endl;
  } else {
    SDL_BlitSurface(text_surface,NULL,surface,&dstrect);
    SDL_FreeSurface(text_surface);
  }
}

void Renderer::PrintEngine::FontEngine::textSize(std::string text, int* w, int* h)
{
  if ( TTF_SizeText(font, "Hello!", w, h) ) {
    console::err() << "Unable to determine text size: " << TTF_GetError() << std::endl;
    *w=*h=0;
  }
}

void Renderer::init(int xsize, int ysize, int bpp, int fontsize, int bs, const std::string& scenefile)
{
  // screen = SDL_SetVideoMode(xsize, ysize, bpp, SDL_SWSURFACE | SDL_FULLSCREEN);
  screen = SDL_SetVideoMode(xsize, ysize, bpp, SDL_SWSURFACE);
  xSize = xsize; ySize = ysize;
  blocksize = bs;
  if (screen == NULL) {
    console::err() << "Unable to set the video mode." << std::endl;
    exit(1);
  }
  printEngine.init(std::string("FreeMono.ttf"), fontsize, screen);
  scene.init(scenefile, xsize, ysize);
  frame.allocate(xsize, ysize);
  renderMode_ = Render_Print | Render_World;
}

void Renderer::render()
{
  if ( frame.status == Frame::Approx ) {
    for ( int ix=0; ix < xSize-blocksize+1; ix+=blocksize ) {
      for ( int iy=0; iy < ySize-blocksize+1; iy+=blocksize ) {
	Color c = scene.render(ix+blocksize/2, iy+blocksize/2, vec3());
	for ( int jx=0; jx<blocksize; jx++ ) {
	  for ( int jy=0; jy<blocksize; jy++ ) {
	    frame(ix+jx,iy+jy) = c;
	    frame.samples(ix+jx,iy+jy) = 1;
	  }
	}
      }
    }
  } else if ( frame.status == Frame::Sample ) {
    const vec3 r = vec3_rand(1./std::min(xSize, ySize));

    const int cols=8;
    const int col = rand() % cols;
    const int rows=8;
    const int row = rand() % cols;
    for ( int iy=row*(ySize/rows); iy < (row+1)*ySize/rows; ++iy ) {
      for ( int ix=col*(xSize/cols); ix < (col+1)*xSize/cols; ++ix ) {
	frame(ix,iy) += scene.render(ix, iy, r);
	frame.samples(ix,iy)++;
      }
    }

    // random:
    // for ( int i=0; i<1e5; i++ ) {
    //   int ix = rand() % xSize;
    //   int iy = rand() % ySize;
    //   frame(ix,iy) += scene.render(ix, iy, r);
    //   frame.samples(ix,iy)++;
    // }

    // every:
    // for ( int ix=0; ix < xSize; ++ix ) {
    //   for ( int iy=0; iy < ySize; ++iy ) {
    // 	if ( frame.samples(ix,iy) == 0 ) {
    // 	  frame(ix,iy) = scene.render(ix, iy, r);
    // 	  frame.samples(ix,iy) = 1;
    // 	} else {
    // 	  frame(ix,iy) += scene.render(ix, iy, r);
    // 	  frame.samples(ix,iy)++;
    // 	}
    //   }
    // }


  }
}

void Renderer::drawFrame()
{
  initFrame();
  if ( renderMode_ & Render_World ) {
    if ( frame.status == Frame::Approx ) {
      for ( int iy=0; iy < ySize; ++iy ) {
	for ( int ix=0; ix < xSize; ++ix ) {
	  Uint8* pixel = (Uint8*) screen->pixels + iy*screen->pitch + ix*screen->format->BytesPerPixel;
	  for ( int v=0; v<3; v++ ) {
	    pixel[2-v] = (Uint8) std::min(frame(ix,iy)[v]*255, 255.);
	  }
	}
      }
      frame.status = Frame::Sample;
    } else if ( frame.status == Frame::Sample ) {
      for ( int iy=0; iy < ySize; ++iy ) {
	for ( int ix=0; ix < xSize; ++ix ) {
	  Uint8* pixel = (Uint8*) screen->pixels + iy*screen->pitch + ix*screen->format->BytesPerPixel;
	  for ( int v=0; v<3; v++ ) {
	    // pixel[2-v] = (Uint8) std::min(frame(ix,iy)[v]/frame.samples(ix,iy)*255, 255.);
	    pixel[2-v] = (Uint8) std::min(frame(ix,iy)[v]/std::max(frame.samples(ix,iy),(unsigned int)1)*255, 255.);
	  }
	}
      }
    }
  }
  if ( renderMode_ & Render_Print ) printEngine.draw();
}

void Renderer::initFrame()
{
  SDL_Flip(screen);
  SDL_FillRect(screen, NULL, 0);
}

void Renderer::showFps(float fps)
{
  printEngine.setFps(fps);
}

void Renderer::camForward(float v)
{
  scene.camera.move(v);
  frame.status = Frame::Approx;
}

void Renderer::camClimb(float v)
{
  scene.camera.climb(v);
  frame.status = Frame::Approx;
}

void Renderer::camStrafe(float v)
{
  scene.camera.strafe(v);
  frame.status = Frame::Approx;
}

void Renderer::camYaw(float v)
{
  scene.camera.yaw(v);
  frame.status = Frame::Approx;
}
