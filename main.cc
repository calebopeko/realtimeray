#include "options.h"

int main(int argc, char** argv)
{
  Options::instance().set(argc, argv);
  return 0;
}
