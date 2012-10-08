#include "options.h"
#include "scene.h"
#include "event.h"
#include "renderer.h"

int main(int argc, char** argv)
{
  Options& options = Options::instance();
  options.set(argc, argv);

  Event& event = Event::instance();
  Renderer& renderer = Renderer::instance();

  event.init();
  renderer.init(options.sizeX, options.sizeY, 32, 20);

  Scene scene(options.sceneFile);
  while (event.poll()) {
    renderer.drawFrame();
    event.fillFrame();
    if ( event.diag(1000) ) { // every second
      renderer.showFps(event.getFps());
    }
  }
  
  event.finish();
  return 0;
}
