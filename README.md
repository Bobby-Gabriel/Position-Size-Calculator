# Position-Size-Calculator

## Windows
Pre Req
install c++ build tools. Just select c++ desktop development in the VS installer. Dont need Windows 11 SDK though
install cmake 4.0
install python
install conan

conan profile detect --force
May need to add msvc to conan profile

### Install
Install deps
conan install . --build=missing
cmake --preset default
cmake --build --preset default