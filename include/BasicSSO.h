#include <iostream>
#include <cstring>
#include <memory>

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

  BasicSSO(const char* new_string) {
    length_ = std::strlen(new_string);
    if (length_ <= BUFFER_SIZE) {
      std::strcpy(buffer_, new_string);
      buffer_[length_] = '\0';
    } else {
      // If not SSO place in data_
      data_ = new char[length_ + 1];
      std::strcpy(data_, new_string);
    }
  }

  // Copy Constructor
  BasicSSO(const BasicSSO& other) : BasicSSO(other.c_str()) { }

  // Copy assignment
  BasicSSO& operator=(const BasicSSO& original) {
    if (this != &original) {
      length_ = original.length_;
      if (length_ <= BUFFER_SIZE) {
        std::strcpy(buffer_, original.buffer_);
      } else {
        data_ = new char[length_ + 1];
        std::strcpy(data_, original.c_str());
      }
    }
    return *this;
  }

  // Move constructor
  BasicSSO(BasicSSO&& original) noexcept {
    length_ = original.length();
    if (length_ > BUFFER_SIZE) {
      data_ = new char[length_ + 1];
      std::strcpy(data_, original.c_str());
    } else {
      std::strcpy(buffer_, original.c_str());
    }
    original.length_ = 0;
  }

  // Move assignment operator
  BasicSSO& operator=(BasicSSO&& old) noexcept {
    // Assign this object from old
    if (this != &old) {
      length_ = old.length();
      if (length_ > BUFFER_SIZE) {
        std::strcpy(data_, old.c_str());
      } else {
        std::strcpy(buffer_, old.c_str());
      }
      buffer_[length_] = '\0';
    }
    return *this;
  }

  // += assignment operator override
  BasicSSO& operator+=(const char* other_string) {
    append(other_string);
    return *this;
  }

  // string append if needed to extend
  void append(const char* other_string) {
    size_t other_length = std::strlen(other_string);
    size_t new_length = length_ + other_length;
    
    if (new_length <= BUFFER_SIZE) {
      std::strcat(buffer_, other_string);
    } else {
      // Reset and move all to char array on heap
      char* new_data = new char[new_length + 1];
      std::strcpy(new_data, c_str());
      std::strcat(new_data, other_string);
      delete[] data_;
      data_ = new_data;
    }
    length_ = new_length;
  }

  // String length
  size_t length() const { return length_; }

  // C style string returned
  const char* c_str() const {
    // Access buffer or pointer array
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
    char* data_;
    // 8 bytes (64 bit machine)
    // Was originally a std::unique_ptr but that
    // fails in a union due to its desttructor design
  };
  size_t length_;
  // 8 bytes
};
