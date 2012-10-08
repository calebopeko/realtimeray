#include "options.h"
#include "scene.h"

int main(int argc, char** argv)
{
  Options& options = Options::instance();
  options.set(argc, argv);

  Scene scene(options.sceneFile);
  return 0;
}
