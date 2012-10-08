#include "console.h"

#include <limits>

namespace console
{

  static std::ofstream debugStream;
  
  static bool verbose_=false;

  void init()
  {
    // debugStream.open("/dev/null");
    debugStream.open("lpc.log");
  }

  void out(const char* c)
  {
    out() << c << std::endl;
  }

  void err(const char* c)
  {
    err() << c << std::endl;
  }

  void in(bool& b)
  {
    while ( !(std::cin >> b) ) {
      std::cout << "Bad input!" << std::endl;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<int>::max(), '\n'); 
    };
  }

  void in(int& i)
  {
    while ( !(std::cin >> i) ) {
      std::cout << "Bad input!" << std::endl;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<int>::max(), '\n'); 
    };
  }

  void in(char& c)
  {
    while ( !(std::cin >> c) ) {
      std::cout << "Bad input!" << std::endl;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<int>::max(), '\n'); 
    };
  }

  void verbose(bool v)
  {
    verbose_=v;
  }
  
  bool verbose()
  {
    return verbose_;
  }
  
  std::ostream& out()
  {
    return std::cout;
  }

  std::ostream& err()
  {
    return std::cerr;
  }

  std::ostream& dbg()
  {
    return debugStream;
  }
}
