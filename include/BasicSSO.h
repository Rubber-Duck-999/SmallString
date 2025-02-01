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
      data_.reset();
    }
  }

  BasicSSO(const char* other) {
    length_ = std::strlen(other);
    if (length_ <= BUFFER_SIZE) {
      std::strcpy(buffer_, other);
      buffer_[length_] = '\0';
    } else {
      // If not SSO place in data_
      data_.reset(new char[length_ + 1]);
      std::strcpy(data_.get(), other);
    }
  }

  // When creating a obejct with another
  BasicSSO(const BasicSSO& other) : BasicSSO(other.c_str()) { }

  // When assigning a obejct with another
  BasicSSO& operator=(const BasicSSO& original) {
    if (this != &original) {
        if (original.length() > BUFFER_SIZE) {
            std::strcpy(data_.get(), original.c_str());
        } else {
            std::strcpy(buffer_, original.c_str());
        }
        buffer_[length_] = '\0';
        length_ = original.length();
    }
    return *this;
  }

  BasicSSO(BasicSSO&& other) noexcept : length_(other.length_) {
    if (length_ > BUFFER_SIZE) {
      data_.swap(other.data_);
    } else {
      std::strcpy(buffer_, other.buffer_);
    }
    buffer_[length_] = '\0';
  }

  BasicSSO& operator=(BasicSSO&& other) noexcept {
    if (this != &other) {
        length_ = other.length_;
        if (length_ > BUFFER_SIZE) {
            data_.swap(other.data_);
        } else {
            std::strcpy(buffer_, other.buffer_);
        }
        buffer_[length_] = '\0';
    }
    return *this;
  }

  BasicSSO& operator+=(const char* other_string) {
    append(other_string);
    return *this;
  }

  void append(const char* other_string) {
    size_t other_length = std::strlen(other_string);
    size_t new_length = length_ + other_length;
    if (new_length < BUFFER_SIZE) {
      std::strcat(buffer_, other_string);
    } else {
      std::unique_ptr<char[]> new_data(new char[new_length + 1]);
      std::strcpy(new_data.get(), c_str());
      std::strcat(new_data.get(), other_string);
      data_ = std::move(new_data);
    }
    length_ = new_length;
  }

  size_t length() const { return length_; }

  const char* c_str() const {
    if (length_ <= BUFFER_SIZE) {
      return buffer_;
    } else {
      return data_.get();
    }
  }

private:
  union{
    char buffer_[BUFFER_SIZE];
    // 16 bytes
    std::unique_ptr<char[]> data_;
    // 4 bytes
  };
  size_t length_;
};
