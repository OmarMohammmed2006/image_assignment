# 🖼️ Image Processing Tool - PhotoShop

A powerful **C++ command-line image editing application** that applies various professional-grade filters and transformations to images. This tool supports multiple image formats and provides an intuitive menu-based interface for easy image manipulation.

---

## 📋 Table of Contents

- [Features](#features)
- [Supported Formats](#supported-formats)
- [System Requirements](#system-requirements)
- [Installation & Setup](#installation--setup)
- [Usage Guide](#usage-guide)
- [Available Filters](#available-filters)
- [Team Members](#team-members)
- [Documentation & Resources](#documentation--resources)
- [Technical Details](#technical-details)
- [Troubleshooting](#troubleshooting)

---

## ✨ Features

### Core Functionality
- ✅ **Load Images**: Support for JPG, PNG, BMP, and TGA formats
- ✅ **Apply Filters**: 18+ professional image filters
- ✅ **Save Images**: Export in multiple formats with overwrite or new file options
- ✅ **Interactive Menu**: Easy-to-use command-line interface
- ✅ **Error Handling**: Robust exception handling for invalid inputs

### Image Transformations
- Geometric transformations (rotate, flip, crop, resize)
- Color adjustments (grayscale, brightness, invert)
- Advanced effects (blur, edge detection, oil painting)
- Bonus filters (infrared, sunlight, night purple, skewing)

---

## 🖥️ Supported Formats

| Format | Extension | Support |
|--------|-----------|---------|
| JPEG   | `.jpg`, `.jpeg` | ✅ Full Support |
| PNG    | `.png` | ✅ Full Support |
| BMP    | `.bmp` | ✅ Full Support |
| TGA    | `.tga` | ✅ Full Support |

---

## 📦 System Requirements

### Minimum Requirements
- **OS**: Windows, macOS, or Linux
- **C++ Compiler**: C++20 or higher
- **CMake**: Version 3.30 or higher
- **RAM**: 2GB minimum
- **Disk Space**: 500MB for application and dependencies

### Recommended Requirements
- **C++ Compiler**: GCC 11+, Clang 12+, or MSVC 2019+
- **RAM**: 4GB or higher
- **Disk Space**: 1GB free space

---

## 🚀 Installation & Setup

### Prerequisites
Before installing, ensure you have:
- CMake installed ([Download CMake](https://cmake.org/download/))
- A C++20 compatible compiler installed

### Step-by-Step Installation

#### 1. Clone the Repository
```bash
git clone https://github.com/OmarMohammmed2006/image_assignment.git
cd image_assignment
```

#### 2. Create Build Directory
```bash
mkdir build
cd build
```

#### 3. Run CMake Configuration
```bash
cmake ..
```

#### 4. Build the Project
```bash
# On Windows (with Visual Studio)
cmake --build . --config Release

# On macOS/Linux (with GCC/Clang)
make
```

#### 5. Run the Application
```bash
# Windows
./Release/Code.exe

# macOS/Linux
./Code
```

---

## 📖 Usage Guide

### Starting the Application

Once you run the program, you'll see the main menu:

```
Welcome to Photoshop

1. Load New Image
2. Save the Image
3. Filter Menu
4. Exit

Enter your choice 1-4:
```

### Step-by-Step Workflow

#### 1. **Load an Image**
```
Enter your choice 1-4: 1
Enter your image path: /path/to/image.jpg
Image loaded successfully! 1920x1080
```
- Provide the full or relative path to your image file
- Supported formats are automatically detected

#### 2. **Apply Filters**
```
Enter your choice 1-4: 3

1. Gray Scale
2. Black and White
3. Invert Image Colors
...
18. Skew Image

Enter your choice 1-18: [select filter number]
```

#### 3. **Save Your Work**
```
Enter your choice 1-4: 2
Do you want to overwrite or save as a new file? (n for new, o for overwrite): n
Please enter the new image name (with extension .jpg, .jpeg, .png, .bmp): output.png
Image saved successfully.
```

---

## 🎨 Available Filters

### Basic Transformations

| # | Filter | Description |
|---|--------|-------------|
| 1 | **Gray Scale** | Converts image to grayscale using luminosity formula |
| 2 | **Black & White** | Converts image to pure black and white (threshold-based) |
| 3 | **Invert Colors** | Inverts all RGB color values (creates negative effect) |
| 5 | **Flip Image** | Flips image horizontally or vertically |
| 6 | **Rotate Image** | Rotates image by 90°, 180°, or 270° |
| 8 | **Crop Image** | Extracts a rectangular region from the image |
| 11 | **Resize Image** | Scales image to new dimensions |

### Color & Brightness

| # | Filter | Description |
|---|--------|-------------|
| 7 | **Darken/Lighten** | Adjusts brightness by 0-100 levels |
| 13 | **Sunlight Effect** | Adds warm sunlight appearance to the image |

### Advanced Effects

| # | Filter | Description |
|---|--------|-------------|
| 4 | **Merge Images** | Merges two images together (with auto-resizing) |
| 9 | **Add Frame** | Adds single, double, or colored frame borders |
| 10 | **Edge Detection** | Detects and highlights edges using Sobel operator |
| 12 | **Blur Image** | Applies blur with Low, Medium, or High intensity |

### Artistic Filters (Bonus)

| # | Filter | Description |
|---|--------|-------------|
| 14 | **Oil Painting** | Creates oil painting effect using histogram analysis |
| 15 | **Television Effect** | Applies retro TV scanline effect |
| 16 | **Night Purple** | Enhances purple tones for nighttime appearance |
| 17 | **Infrared** | Creates thermal/infrared camera appearance |
| 18 | **Skew Image** | Skews image left or right with adjustable angle (5-75°) |

---

## 👥 Team Members

This project was developed collaboratively by three students:

| Name | ID | Contributions |
|------|-----|----------------|
| **Ahmed Mostafa Mahmoud Ellaboudy** | 20240054 | Grayscale, Merge, Brightness, Edge Detection, Infrared, Image Skewing, Final Code Review |
| **Omar Mohamed Abdelgalil Mohamed** | 20240384 | Black & White, Flip, Crop, Resizing, Natural Sunlight Effect, Documentation |
| **Mahmoud Mohamed Hany Mahmoud** | 20240561 | Invert, Rotate, Frame, Blur, Oil Painting, Purple Effect, TV Effect, Video Demo |

---

## 📚 Documentation & Resources

### Project Documentation
📄 **Full Project Documentation**: [View on Google Docs](https://docs.google.com/document/d/1zWIla2SNSW3ugxby1OoAgrqBoGHRd09hk5iGNEaZho4/edit?usp=sharing)

### Video Demonstration
🎥 **Feature Walkthrough**: [Watch on Google Drive](https://drive.google.com/file/d/1zGxjwD19huu4fo9OWMeKgQKYrhZEY5KI/view?usp=sharing)

### Repository
🔗 **GitHub Repository**: [OmarMohammmed2006/image_assignment](https://github.com/OmarMohammmed2006/image_assignment/)

---

## 🛠️ Technical Details

### Architecture

```
PhotoShop (Main Class)
├── Load Image
├── Apply Filters
│   ├── Basic Transformations
│   ├── Color Adjustments
│   ├── Advanced Effects
│   └── Artistic Filters
└── Save Image

Image Class (Header)
├── Image Loading (stb_image)
├── Image Saving (stb_image_write)
├── Pixel Access Operators
└── Memory Management
```

### Key Technologies

- **Language**: C++20
- **Build System**: CMake 3.30+
- **Image Loading**: [stb_image.h](https://github.com/nothings/stb)
- **Image Writing**: [stb_image_write.h](https://github.com/nothings/stb)
- **Compilation**: Standard C++ Library

### File Structure

```
image_assignment/
├── main.cpp                 # Main application and filter implementations
├── Image_Class.h           # Image class definition and utilities
├── stb_image.h             # Image loading library
├── stb_image_write.h       # Image writing library
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
└── cmake-build-debug/      # Build output directory
```

### Image Processing Algorithms

- **Grayscale**: Luminosity formula (0.299*R + 0.587*G + 0.114*B)
- **Edge Detection**: Sobel operator with gradient magnitude
- **Blur**: Box blur with configurable kernel sizes
- **Oil Painting**: Histogram-based intensity binning
- **Resizing**: Nearest-neighbor interpolation

---

## ❓ Troubleshooting

### Common Issues

#### ❌ "CMake not found"
**Solution**: 
- Install CMake from [cmake.org](https://cmake.org/download/)
- Add CMake to your system PATH

#### ❌ "C++20 compiler not available"
**Solution**:
- Update your compiler to a recent version
- GCC 11+, Clang 12+, or MSVC 2019+ are required
- On Ubuntu: `sudo apt-get install g++-11`

#### ❌ "Image file not found"
**Solution**:
- Use absolute path: `/Users/name/images/photo.jpg`
- Or relative path from build directory: `../images/photo.jpg`
- Ensure the file exists and you have read permissions

#### ❌ "Unsupported image format"
**Solution**:
- Only `.jpg`, `.jpeg`, `.png`, `.bmp`, and `.tga` are supported
- Convert your image using an online tool or ImageMagick
- Verify file extension is correct

#### ❌ "Build fails with linking errors"
**Solution**:
- Clean previous build: `rm -rf build/`
- Reconfigure: `cmake ..`
- Rebuild: `cmake --build .`

#### ❌ "Memory error with large images"
**Solution**:
- Resize the image first before applying filters
- Increase available system RAM
- Process on a machine with more memory

---

## 📝 Notes

- **Video**: Prepared by Mahmoud Mohamed Hany Mahmoud (20240561)
- **Documentation**: Prepared by Omar Mohamed Abdelgalil Mohamed (20240384)
- **Code Review & Headers**: Prepared by Ahmed Mostafa Mahmoud Ellaboudy (20240054)
- All team members contributed equally to implementation and testing

---

## 📄 License

This project is developed as a university assignment for the Faculty of Computers and Artificial Intelligence (FCAI), Cairo University.

---

## 🤝 Support & Contributing

For issues, questions, or contributions:
- 📧 Create an issue on [GitHub Issues](https://github.com/OmarMohammmed2006/image_assignment/issues)
- 💬 Refer to the project documentation for detailed information
- 🎥 Check the demo video for usage examples

---

**Happy Image Processing! 🎨✨**
