# Build Instructions

This document provides detailed instructions for building the Computer Access Controller application on Windows.

## Prerequisites

### 1. Install Visual Studio or MinGW

**Option A: Visual Studio (Recommended)**
- Download and install Visual Studio 2019 or later
- During installation, select "Desktop development with C++"
- Make sure CMake support is included

**Option B: MinGW-w64**
- Download from https://www.mingw-w64.org/
- Add MinGW bin directory to PATH
- Install make or ninja build tool

### 2. Install CMake

- Download from https://cmake.org/download/
- Version 3.15 or higher required
- During installation, add CMake to system PATH

### 3. Install wxWidgets

**Option A: Using vcpkg (Recommended)**

```powershell
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install wxWidgets
.\vcpkg install wxwidgets:x64-windows

# Integrate with Visual Studio
.\vcpkg integrate install
```

**Option B: Build from source**

1. Download wxWidgets from https://www.wxwidgets.org/downloads/
2. Extract to a directory (e.g., C:\wxWidgets-3.2.0)
3. Open Command Prompt and navigate to wxWidgets directory
4. Build:
   ```
   cd build\msw
   nmake /f makefile.vc BUILD=release
   ```
5. Set environment variable:
   ```
   setx wxWidgets_ROOT_DIR "C:\wxWidgets-3.2.0"
   ```

## Building the Application

### Using Command Line

```powershell
# Navigate to project directory
cd cpp-computer-access-controller

# Create build directory
mkdir build
cd build

# Configure (if using vcpkg)
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]\scripts\buildsystems\vcpkg.cmake

# Or configure (if wxWidgets_ROOT_DIR is set)
cmake ..

# Build
cmake --build . --config Release

# The executable will be in: build\Release\ComputerAccessController.exe
```

### Using Visual Studio

1. Open Visual Studio
2. Select "Open a local folder"
3. Navigate to the cpp-computer-access-controller directory
4. Visual Studio will automatically detect CMakeLists.txt
5. Select build configuration (Release recommended)
6. Build > Build All (Ctrl+Shift+B)
7. The executable will be in the build output directory

### Using CLion

1. Open CLion
2. File > Open > Select cpp-computer-access-controller directory
3. CLion will automatically import the CMake project
4. If wxWidgets is not found:
   - Go to File > Settings > Build, Execution, Deployment > CMake
   - Add to CMake options: `-DCMAKE_TOOLCHAIN_FILE=[vcpkg root]\scripts\buildsystems\vcpkg.cmake`
5. Build > Build Project (Ctrl+F9)
6. The executable will be in cmake-build-release directory

## Running the Application

**Important**: The application must be run with administrator privileges to enable system shutdown functionality.

1. Navigate to the build output directory
2. Right-click on `ComputerAccessController.exe`
3. Select "Run as administrator"

Alternatively, create a shortcut and set it to always run as administrator:
1. Right-click the executable and select "Create shortcut"
2. Right-click the shortcut and select "Properties"
3. Click "Advanced..." button
4. Check "Run as administrator"
5. Click OK

## Troubleshooting

### CMake cannot find wxWidgets

**Solution 1**: If using vcpkg, ensure you specify the toolchain file:
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]\scripts\buildsystems\vcpkg.cmake
```

**Solution 2**: Set wxWidgets_ROOT_DIR environment variable:
```
setx wxWidgets_ROOT_DIR "C:\path\to\wxWidgets"
```

**Solution 3**: Manually specify wxWidgets directory:
```
cmake .. -DwxWidgets_ROOT_DIR=C:\path\to\wxWidgets
```

### Build errors related to Windows.h

Make sure UNICODE and _UNICODE are defined. This is handled automatically in CMakeLists.txt.

### Application doesn't shutdown the system

The application requires administrator privileges. Make sure you run it as administrator.

### Missing DLL errors when running

**If using MinGW**: Copy required DLLs from MinGW\bin to the executable directory

**If using vcpkg**: vcpkg should handle this automatically, but you may need to copy wxWidgets DLLs to the executable directory

## Distribution

To distribute the application:

1. Build in Release mode
2. Copy the executable to a distribution folder
3. Copy required DLLs (if any) to the same folder
4. Include schedule.dat.example as a sample configuration
5. Include README.md for user instructions

### Creating an Installer (Optional)

Consider using tools like:
- NSIS (Nullsoft Scriptable Install System)
- WiX Toolset
- Inno Setup

These can create a professional installer that:
- Installs the application to Program Files
- Creates shortcuts with administrator privileges
- Registers the application to run at startup
- Provides uninstall functionality

## Development Notes

### Code Style
- Use C++17 features
- Follow existing naming conventions
- Keep functions focused and modular
- Add comments for complex logic

### Testing
Since this is a Windows-specific application with system-level operations:
- Test on a virtual machine first
- Verify time checking logic thoroughly
- Test with different time zones
- Ensure proper privilege handling

### Debugging
- Use Debug build configuration for development
- Set breakpoints in time checking logic
- Monitor system calls to Windows API
- Test with short time intervals during development
