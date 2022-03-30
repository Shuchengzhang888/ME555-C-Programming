#include "parse.hpp"

#include <exception>
// any other headers you need

class invalid_input : public std::exception {
  // override what() here
};

item_t * parseLine(const std::string & line) {
  // write me
}
