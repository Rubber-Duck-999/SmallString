#include "BasicSSO.h"

int main() {
  BasicSSO small_string("Hello");
  // Short string, stored in buffer

  std::cout << "small_string: \"" << small_string.c_str() << "\", length: " << small_string.length() << "\n";
  std::cout << "Size of small_string: " << sizeof(small_string) << " bytes\n";

  BasicSSO large_string("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  // Long string, allocated on heap as larger tha buffer
  std::cout << "large_string: \"" << large_string.c_str() << "\", length: " << large_string.length() << "\n";
  std::cout << "Size of large_string: " << sizeof(large_string) << " bytes\n";
  // Same stack size even if its long string and not stored in buffer as the buffer was already set n the stack
  return 0;
}