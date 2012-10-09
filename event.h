#ifndef EVENT_H
#define EVENT_H

#include "SDL/SDL.h"
#include "vec.h"
#include <map>

class Event
{
 private:

  enum KeyIndex {
    Key_None=0,
    Key_MoveForward,
    Key_MoveBackward,
    Key_MoveUp,
    Key_MoveDown,
    Key_MoveLeft,
    Key_MoveRight,
    Key_RotateLeft,
    Key_RotateRight,
    
    Key_Quit,
    Key_Total // <- last
  };

  struct KeyDef {

    KeyDef() : index(Key_None), continuous(false) {}
    
    KeyDef(KeyIndex idx, bool c) : index(idx), continuous(c) {}

    KeyIndex index;
    
    bool continuous;
  };

 public:

  Event() : fpsCap(100), frameAim(1000./fpsCap), fps(1), running(true) {}

  static Event& instance() { return instance_; }

  void init();
  
  bool poll();

  void fillFrame();
  
  bool diag(Uint32 ms);

  real getFps() { return fps; }

  real invFps() { return ifps; }

  void shutdown() { running = false; }

  void finish();

 private:

  void keyPressed();

  void keyUp(SDL_Event& ev);
  
  void keyDown(SDL_Event& ev);

  void keySingleDown(KeyIndex key);

  void keySingleUp(KeyIndex key);

  void mouseMove(int x, int y);

 private:

  static Event instance_;

  std::map<SDLKey, KeyDef> keyMap;

  int fpsCap;

  real frameAim;

  real fps;

  real ifps;

  bool running;

  bool keys[Key_Total];

};

#endif
