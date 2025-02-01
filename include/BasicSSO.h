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

  ~BasicSSO() { 
    // Delete even on the heap
    if (length_ > BUFFER_SIZE) {
      delete[] data_;
    }
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

  // When creating a obejct with another
  BasicSSO(const BasicSSO& other) : BasicSSO(other.c_str()) { }

  // When assigning a obejct with another
  BasicSSO& operator=(const BasicSSO& original) {
    if (this != &original) {
        // Free any previously allocated memory
        if (original.length() > BUFFER_SIZE) {
          data_ = new char[original.length() + 1];
          std::strcpy(data_, original.c_str());
        } else {
          std::strcpy(buffer_, original.c_str());
          buffer_[original.length()] = '\0';
        }
        length_ = original.length();
    }
    return *this;
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
    // 16 bytes
    char *data_;
    // 4 bytes
  };
  size_t length_;
  // 4 bytes
};
