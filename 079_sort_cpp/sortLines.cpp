#include <algorithm>  //sort
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char ** argv) {
  std::vector<std::string> vec;
  std::string str;
  if (argv == NULL) {
    std::cerr << "Wrong number of arguments.\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (argc == 1) {
    while (!std::cin.eof()) {
      std::getline(std::cin, str);
      vec.push_back(str);
    }
    std::sort(vec.begin(), vec.end());
    std::vector<std::string>::iterator it = vec.begin();
    while (it != vec.end()) {
      std::cout << *it << std::endl;
      ++it;
    }
    vec.clear();
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream infile(argv[i]);
      if (infile.fail()) {
        std::cerr << "Can't open file: " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      while (!infile.eof()) {
        std::getline(infile, str);
        vec.push_back(str);
      }
      std::sort(vec.begin(), vec.end());
      std::vector<std::string>::iterator it = vec.begin();
      while (it != vec.end()) {
        std::cout << *it << std::endl;
        ++it;
      }
      vec.clear();
    }
  }

  return EXIT_SUCCESS;
}
