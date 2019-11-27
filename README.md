# Desktop Camera Barcode Reader in C/C++
The demo shows how to build a desktop camera barcode reader using C/C++ and CMake.

## Download
- [OpenCV 3.4.7](https://github.com/opencv/opencv/archive/3.4.7.zip)
- [Dynamsoft Barcode Reader SDK v7.1](https://github.com/dynamsoft-dbr/desktop-camera-barcode-reader/releases/tag/v7.1)

## Build OpenCV
### Windows
1. Install [Visual Studio 2017](https://www.visualstudio.com/downloads/) and [cmake-3.15.2-win64-x64.msi](https://github.com/Kitware/CMake/releases/download/v3.15.2/cmake-3.15.2-win64-x64.msi):
2. Extract the OpenCV source code and create a temporary directory:

    ```
    cd opencv-3.4.7
    mkdir build
    cd build
    ```

3. Build the OpenCV libraries:

    ```
    cmake -G"Visual Studio 15 2017 Win64" ..
    cmake --build . --target install
    ```

### Linux 
1. Install [required packages](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html):

    ```
    sudo apt install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libjpeg-dev libpng-dev libtiff-dev
    ```

2. Extract the OpenCV source code and create a temporary directory:

    ```
    cd opencv-3.4.7
    mkdir build
    cd build
    ```

3. Build the OpenCV libraries:

    ```
    cmake ..
    cmake --build . --target install
    ```

### macOS
1. Install required packages:

    ```
    sudo xcode-select --install
    brew install cmake pkg-config
    ```

2. Extract the OpenCV source code and create a temporary directory:

    ```
    cd opencv-3.4.7
    mkdir build
    cd build
    ```

3. Build the OpenCV libraries:

    ```
    cmake ..
    cmake --build . --target install
    ```

## License Key
Get a [FREE 30-day trial license](https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx) of [Dynamsoft Barcode Reader](https://www.dynamsoft.com/Products/Dynamic-Barcode-Reader.aspx).

Set the license key in ``BarcodeReader.cxx``:

```c
reader.InitLicense("LICENSE-KEY");
```


## How to Build and Run the Project

### Windows
1. From `C:\Program Files (x86)\Dynamsoft\Barcode Reader 7.1\Components\C_C++\Lib`, copy `DBRx64.lib` to `platforms\win\lib`. 

    From `opencv-3.4.7\build\lib`, copy `opencv_core347d.lib`, `opencv_highgui347d.lib`, `opencv_videoio347d.lib` to `platforms\win\lib`. 
    
    From `C:\Program Files (x86)\Dynamsoft\Barcode Reader 7.1\Components\C_C++\Redist\x64`, copy all DLL files to `platforms\win\bin`.

    From `opencv-3.4.7\build\bin\Debug`, copy `opencv_imgproc347d.dll`, `opencv_videoio347d.dll`, `opencv_highgui347d.dll` and `opencv_imgcodecs347d.dll` to `platforms\win\bin`. 
    
    Alternatively, you can extract the dependent [library files](https://github.com/dynamsoft-dbr/desktop-camera-barcode-reader/releases/download/v0.1-alpha/win.zip) to **platforms\win** folder.

2. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

3. Edit **CMakeLists.txt** to replace the installation path with yours:
    ```
    set(CMAKE_INSTALL_PREFIX "e:/${PROJECT_NAME}")
    ```
4. Generate project configuration files.
     
    x86:
    ```bash
    cmake ..
    ```

    x64:
    ```bash
    cmake -G"Visual Studio 15 2017 Win64" ..
    ```
5. Build and install the project:
    ```
    cmake --build . --target install
    ```
6. Run the app:
    ```
    build\Debug\BarcodeReader.exe
    ```

    ![](https://www.dynamsoft.com/CustomerPortal/images/upload/224-big.png)

## Linux
1. Copy `Dynamsoft/BarcodeReader/lib/WITHOUTSTDC++LIB/libDynamsoftBarcodeReader.so` to `platforms/linux/`.
2. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

2. Generate project configuration files.

    ```bash
    cmake ..
    ```

3. Build the project:

    ```
    cmake --build . 
    ```

4. Run the app:

    ```
    ./BarcodeReader
    ```

## macOS

1. Copy `Dynamsoft/lib/libDynamsoftBarcodeReader.dylib` to `platforms/macos/`.
2. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

3. Generate project configuration files.

    ```bash
    cmake ..
    ```

4. Build the project:

    ```
    cmake --build . 
    ```

5. Run the app:

    ```
    ./BarcodeReader
    ```

    Note: the command line app will fail to run if the OS version is 10.14 or higher. 

    ```
    OpenCV: not authorized to capture video (status 0), requesting...
    ```

    You can check the OS version with `sw_vers -productVersion `.
    
  ## Blog
  [How to Port Visual Studio C++ Project to Linux with CMake](https://www.codepool.biz/port-visual-studio-cpp-linux-cmake.html)
