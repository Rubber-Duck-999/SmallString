# SmallString

```bash
git clone https://github.com/google/googletest.git -b v1.13.0
cd googletest

# Main directory of the cloned repository.
mkdir build

# Create a directory to hold the build output.
cd build
cmake ..
# Generate native build scripts for GoogleTest.

make
make install
# Install gtest files to your usr local build, helps in multiple developments
# https://github.com/google/googletest/blob/main/googletest/README.md
cd ../../
mkdir build
cd build
cmake ..
make
./exeSmallString
./exeSmallString-Test
# Google unit tests
```