# Desktop Camera Barcode Reader in C/C++
The demo shows how to build a desktop camera barcode reader using C/C++ and CMake.

## Requirements
- [Visual Studio](https://www.visualstudio.com/downloads/)
- [CMake](https://cmake.org/download/)
- [Dynamsoft Barcode Reader v8.0 C/C++ Package](https://www.dynamsoft.com/barcode-reader/downloads) (Windows x86/x64, Linux x64, macOS x64 and Raspberry Pi ARMv7)

## License
Get a [trial license](https://www.dynamsoft.com/customer/license/trialLicense) and set the license key in `BarcodeReader.cxx`:

```cpp
reader.InitLicense("LICENSE-KEY");
```

## Contact Us
https://www.dynamsoft.com/Company/Contact.aspx

## Install OpenCV
Download [OpenCV – 4.5.0](https://opencv.org/releases/)

Configuration for CMake:

```
# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)
```

## Windows
1. Copy `DBRx86.lib/DBRx64.lib` to `platforms\win\lib` and copy `DynamsoftBarcodeReaderx86.dll/DynamsoftBarcodeReaderx64.dll` to `platforms\win\bin` folder.
2. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
3. Configure and build the project:
    ```bash
    // x86
    cmake -DCMAKE_GENERATOR_PLATFORM=x86 ..

    // x64
    cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..
    
    cmake --build . --config release
    ```
6. Run the app:

    ```
    Release\BarcodeReader.exe
    ```

    ![](https://www.dynamsoft.com/CustomerPortal/images/upload/224-big.png)

## Linux and Raspberry Pi OS
1. Install **CMake**:
    ```bash
    sudo apt-get install cmake
    ```
2. Copy **libDynamsoftBarcodeReader.so** to **platforms\linux**.
3. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
4. Configure and build the project:
    ```bash
    cmake ..
    cmake --build . --config release 
    ```
5. Run the app:

    ```
    ./BarcodeReader
    ```

## macOS (contact support@dynamsoft.com to get the library file)
1. Install **CMake**:
    ```bash
    brew install cmake
    ```
2. Copy **libDynamsoftBarcodeReader.dylib** to **platforms\macos**.
3. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

4. Configure and build the project:

    ```bash
    cmake ..
    cmake --build . --config release 
    ```

5. Run the app:

    ```
    ./BarcodeReader
    ```
    
## Blog
[How to Port Visual Studio C++ Project to Linux with CMake](https://www.codepool.biz/port-visual-studio-cpp-linux-cmake.html)
