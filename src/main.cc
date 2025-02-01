#include <iostream>
#include <string>

#include <cstring>
#include <iostream>

class BasicSSO {
public:
  static const int BUFFER_SIZE = 16;

  BasicSSO() {
    // Assign size to 0 if no string val provided
    length_ = 0;
  }

  BasicSSO(const char* other) {
    length_ = std::strlen(other);
    if (length_ <= BUFFER_SIZE) {
      std::strcpy(buffer_, other);
      buffer_[length_] = '\0';
    } else {
      // If not SSO place in data_
      data_ = new char[length_ + 1];
      std::strcpy(data_, other);
      data_[length_] = '\0';
    }
  }

  ~BasicSSO() {
    // Delete even on the heap
    if (length_ > BUFFER_SIZE) {
      delete[] data_;
    }
  }

  size_t length() const { return length_; }

  const char* c_str() const {
    if (length_ <= BUFFER_SIZE) {
      return buffer_;
    } else {
      return data_;
    }
  }

private:
  union{
    char buffer_[BUFFER_SIZE];
    // 24 bytes
    char *data_;
    // 4 bytes
  };
  size_t length_;
  // 4 bytes
};

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
