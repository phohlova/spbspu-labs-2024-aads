#include <iostream>
#include <functional>
#include <iterator>
#include <string>
#include "functions.hpp"

namespace A
{
  template< typename T >
  bool less(T left, T right)
  {
    return *left < *right;
  }
  template< typename T >
  bool greater(T left, T right)
  {
    return *left > *right;
  }
}

int main(int argc, char** argv)
{
  if (argc < 4)
  {
    std::cerr << "Error! Empty list\n";
    return 0;
  }
  try
  {
    std::string cmd = argv[1];
    if (cmd != "ascending" && cmd != "descending")
    {
      throw std::runtime_error("Invalid command");
    }
    std::string type = argv[2];
    std::string size_str = argv[3];
    size_t size = std::stoi(size_str);

    if (type == "ints")
    {
      Worker< int >(cmd, size);
    }
    else if (type == "floats")
    {
      Worker< float >(cmd, size);
    }
    else
    {
      throw std::runtime_error("Invalid type");
    }
  }
  catch (const std::exception& err)
  {
    std::cout << err.what();
    return 1;
  }
  return 0;
}
