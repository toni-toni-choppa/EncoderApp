#include <iostream>

#include "arguments.h"

int main(int argc, char* argv[]) {
  Utils::Arguments args(argc, argv);

  std::cout << "Argument for -input: " << args.get<std::string>("--input") << std::endl;
  return 0;
}