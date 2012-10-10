#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

class Options
{
 public:

  Options();

  static Options& instance() { return instance_; }
  
  void set(int argc, char** argv);

  int sizeX, sizeY;

  int blocksize;

  std::string sceneFile;

 private:

  static Options instance_;

  void printUsage();

  void setArgument(const std::string& argname, const std::string& arg);

  void setFlag(const std::string& flagname);
};

#endif
