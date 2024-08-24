#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "threads-samples" ? 0 : 1;
}
