#include "options.h"
#include "console.h"

#include <sstream>
#include <cstdlib>
#include <ctime>

Options Options::instance_;

Options::Options()
  : sizeX(640), sizeY(480), blocksize(4), sceneFile("scene.tml")
{}

void Options::set(int argc, char** argv)
{
  std::string argname;
  while (--argc) {
    const std::string arg=std::string(*(++argv));
    if ( arg.find("-") == 0 ) {
      if ( argname != "" ) {
	setFlag(argname);
      }
      argname = arg.substr(arg.find_first_not_of('-'));
    } else {
      setArgument(argname, arg);
      argname = "";
    }
  }
  if ( argname != "" ) {
    setFlag(argname);
  }
}

void Options::setArgument(const std::string& argname, const std::string& arg)
{
  if ( argname == "x" || argname == "sizex" || argname == "sizeX" ) {
    std::stringstream s(arg);
    s >> sizeX;
  } else if ( argname == "y" || argname == "sizey" || argname == "sizeY" ) {
    std::stringstream s(arg);
    s >> sizeY;
  } else if ( argname == "blocksize" || argname == "block" ) {
    std::stringstream s(arg);
    s >> blocksize;
  } else if ( argname == "scenefile" || argname == "scene" || argname == "sceneFile" ) {
    sceneFile = arg;
  } else if ( argname == "help" || argname == "?" ) {
    printUsage();
  } else {
    console::err() << "Unknown option: " << argname << " " << arg << std::endl;
    printUsage();
  }
}

void Options::setFlag(const std::string& flagname)
{
  if ( flagname == "?" || flagname == "help" || flagname == "h" ) {
    printUsage();
  } else {
    console::err() << "Unknown flag: " << flagname << std::endl;
    printUsage();
  }
}

void Options::printUsage()
{
  console::out() << "Usage:   burgersStochastic [options]" << std::endl << std::endl
		 << "Options:" << std::endl
		 << " --sizeX <resolution>          Set resolution in x-direction to <resolution>. Default is 128." << std::endl
		 << " --sizeY <resolution>          Set resolution in y-direction to <resolution>. Default is 128." << std::endl
		 << " --blocksize <resolution>      Set blocksize to <resolution> for rendering in movement. Default is 1." << std::endl
		 << " --sceneFile <file>            Set scenefile to <file>. Default is 'scene.tml'" << std::endl
    ;
  exit(1);
}
