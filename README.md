# Position-Size-Calculator

## Windows

### Requirements
- MSVC C++ Build Tools 18
- CMake 4.0+
- Python 3.9+
- Conan 2.0+

### Setup and Install
1. After installing `Conan`, set up default profile:

```
conan profile detect --force
```

2. Add path to MSVC installation to `~\.conan2\profiles\default`

```
[conf]
tools.microsoft.msbuild:vs_version=18
```

3. Install dependencies

```
conan install . --build=missing
```

4. Configure and Install Project

```
cmake --preset default
cmake --build --preset default
```

## Using the project
Run the .exe file in the `bin` directory at the root of the project.