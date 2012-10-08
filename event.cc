#include "event.h"
#include "console.h"

Event Event::instance_;

void Event::init()
{
  SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);

  // hardcoded standard keymapping
  keyMap[SDLK_w] = KeyDef(Key_MoveForward, true);
  keyMap[SDLK_s] = KeyDef(Key_MoveBackward, true);
  keyMap[SDLK_a] = KeyDef(Key_MoveLeft, true);
  keyMap[SDLK_d] = KeyDef(Key_MoveRight, true);
  keyMap[SDLK_LEFT] = KeyDef(Key_RotateLeft, true);
  keyMap[SDLK_RIGHT] = KeyDef(Key_RotateRight, true);

  keyMap[SDLK_ESCAPE] = KeyDef(Key_Quit, false);

  // array for pressed keys
  for (int i=0; i<Key_Total; i++) keys[i]=false;
}

bool Event::diag(Uint32 ms)
{
  static Uint32 lastTrigger=0;
  Uint32 now;
  now = SDL_GetTicks();
  if ( now - lastTrigger > ms) {
    lastTrigger = now;
    return true;
  }
  return false;
}

void Event::fillFrame()
{
  static Uint32 last_frame;

  Uint32 now = SDL_GetTicks();
  Uint32 frameDur = (now - last_frame);
  if ( frameAim > frameDur ) SDL_Delay( frameAim - frameDur );

  frameDur = (SDL_GetTicks() - last_frame);
  last_frame = now;
  fps = 1000. / frameDur;
  ifps = 1./fps;
}
  
void Event::keyPressed()
{
  // handle continuously pressed keys
  // if ( keys[Key_CamXUp] ) {
  //   renderer.panCamera(-5., -5., 0.);
  // }
  // if ( keys[Key_CamXDown] ) {
  //   renderer.panCamera(5., 5., 0.);
  // }
  // if ( keys[Key_CamYUp] ) {
  //   renderer.panCamera(5., -5., 0.);
  // }
  // if ( keys[Key_CamYDown] ) {
  //   renderer.panCamera(-5., 5., 0.);
  // }
  // if ( keys[Key_CamZUp] ) {
  //   renderer.panCamera(0., 0., -5.);
  // }
  // if ( keys[Key_CamZDown] ) {
  //   renderer.panCamera(0., 0., 5.);
  // }
}

void Event::keyUp(SDL_Event& ev)
{
  SDLKey pressed = ev.key.keysym.sym;
  if ( keyMap.find(pressed) != keyMap.end() ) {
    KeyDef key = keyMap[pressed];
    if ( key.continuous ) {
      keys[key.index] = false;
    } else {
      keySingleUp(key.index);
    }
  }
}

void Event::keyDown(SDL_Event& ev)
{
  SDLKey pressed = ev.key.keysym.sym;

  if ( keyMap.find(pressed) != keyMap.end() ) {
    KeyDef key = keyMap[pressed];
    if ( key.continuous ) {
      keys[key.index] = true;
    } else {
      keySingleDown(key.index);
    }
  }
}

void Event::keySingleDown(KeyIndex key)
{
  switch (key) {
  case Key_Quit:
    running = false;
    break;
  default:
    break;
  }
}

void Event::keySingleUp(KeyIndex key)
{
}

void Event::mouseMove(int x, int y)
{
}

bool Event::poll()
{
  SDL_Event ev;
  
  while ( SDL_PollEvent( &ev ) ) {
    switch (ev.type) {
    case SDL_KEYDOWN:
      keyDown(ev);
      break;
    case SDL_KEYUP:
      keyUp(ev);
      break;
    case SDL_MOUSEBUTTONDOWN:
      {
      }
      break;
    case SDL_MOUSEBUTTONUP:
      break;
    case SDL_MOUSEMOTION:
      mouseMove(ev.button.x, ev.button.y);
      break;
    case SDL_QUIT:
      return false;
    }
  }
  keyPressed();
  
  return running;
}

void Event::finish()
{
  SDL_Quit();
}
