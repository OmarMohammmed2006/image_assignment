/*==========================================================
                Image Processing Project
============================================================
File Name    : CS213_A1_part1_20240054_20240384_20240561.cpp
Description  : This program implements a simple image editing
               tool that applies various filters ,The program
               uses a menu-based interface where
               users can load, edit, and save images easily.
------------------------------------------------------------
Team Members
------------------------------------------------------------
1. [Ahmed Mostafa Mahmoud Ellaboudy] – [20240054] – Implemented: GrayScale, Merge, Darken and Lighten
2. [Omar Mohamed Abdelgalil Mohamed] – [20240384] – Implemented: Black and White, Flip, Crop, Resizing
3. [Mahmoud Mohamed Hany Mahmoud] – [20240561] – Implemented: Invert, Rotate, Adding Frame, Blur
------------------------------------------------------------
Usage
------------------------------------------------------------
1. Run the program.
2. Load an image (supported formats: .jpg, .png, .bmp, .tga).
3. Choose filters from the menu to apply transformations.
4. Save the edited image as a new file or overwrite the original.
------------------------------------------------------------
Notes
------------------------------------------------------------
- The project used a dedicated Image class for handling image operations.
- The project is still under development, additional filters
  and optimizations will be added in future updates.
- We couldn't register till now so the section number is not included in file name.
*/
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "Image_Class.h"

class PhotoShop {
    public:
        void load_image();
        void gray_scale();
        void black_white();
        void invert_image();
        void merge_image();
        void flip_image();
        void rotate_image();
        void darker_lighter();
        void crop_image();
        void frame_image();
        void image_edges();
        void resize_image();
        void blur_image();
        void sunlight();
        void oil_paint();
        void television();
        void night_purple();
        void infrared();
        void skew();
        void save_image();

        Image image;
};

string filename;

void PhotoShop::load_image() {
    cout << "Enter your image path: ";
    cin.ignore();
    getline(cin, filename);

    try {
        image = Image(filename);
        cout << "Image loaded successfully! "
             << image.width << "x" << image.height << endl;
    }
    catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void PhotoShop::gray_scale(){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned char red = image(i, j, 0);
            unsigned char green = image(i, j, 1);
            unsigned char blue = image(i, j, 2);

            unsigned char avg = (red + green + blue) / 3;

            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    cout << "Grayscale filter applied successfully!" << endl;
}

void PhotoShop::black_white() {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            avg /= 3;
            unsigned int bw = (avg >= 127) ? 255 : 0;

            image(i, j, 0) = bw;
            image(i, j, 1) = bw;
            image(i, j, 2) = bw;
        }
    }
    cout << "Black and White filter applied successfully!" << endl;
}

void PhotoShop::invert_image(){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k)
                image(i, j, k) = 255 - image(i, j, k);
        }
    }
    cout << "Invert_image filter applied successfully!" << endl;
}
void PhotoShop::merge_image() {
    string filename2;
    cout << "Enter the second image path to merge: ";
    cin.ignore();
    getline(cin, filename2);

    try {
        Image image2(filename2);
        cout << "Second image loaded successfully! "
             << image2.width << "x" << image2.height << endl;

        if (image.width == image2.width && image.height == image2.height) {
            for (int i = 0; i < image.width; ++i)
                for (int j = 0; j < image.height; ++j)
                    for (int c = 0; c < 3; ++c)
                        image(i, j, c) = ((int)image(i, j, c) + (int)image2(i, j, c)) / 2;
            cout << "Images merged successfully!" << endl;
            return;
        }

        cout << "Images are different sizes:\n";
        cout << "Image 1: " << image.width << "x" << image.height << endl;
        cout << "Image 2: " << image2.width << "x" << image2.height << endl;
        cout << "Choose option:\n";
        cout << "1. Resize to largest size then merge\n";
        cout << "2. Merge only the common area\n";
        cout << "Enter choice (1 or 2): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int newWidth  = max(image.width, image2.width);
            int newHeight = max(image.height, image2.height);

            Image resized1(newWidth, newHeight);
            Image resized2(newWidth, newHeight);

            float x_ratio1 = image.width  / (float)newWidth;
            float y_ratio1 = image.height / (float)newHeight;
            for (int i = 0; i < newWidth; ++i) {
                for (int j = 0; j < newHeight; ++j) {
                    int srcX = min(int(i * x_ratio1), image.width - 1);
                    int srcY = min(int(j * y_ratio1), image.height - 1);
                    for (int c = 0; c < 3; ++c)
                        resized1(i, j, c) = image(srcX, srcY, c);
                }
            }

            float x_ratio2 = image2.width  / (float)newWidth;
            float y_ratio2 = image2.height / (float)newHeight;
            for (int i = 0; i < newWidth; ++i) {
                for (int j = 0; j < newHeight; ++j) {
                    int srcX = min(int(i * x_ratio2), image2.width - 1);
                    int srcY = min(int(j * y_ratio2), image2.height - 1);
                    for (int c = 0; c < 3; ++c)
                        resized2(i, j, c) = image2(srcX, srcY, c);
                }
            }

            for (int i = 0; i < newWidth; ++i) {
                for (int j = 0; j < newHeight; ++j) {
                    for (int c = 0; c < 3; ++c)
                        resized1(i, j, c) = ((int)resized1(i, j, c) + (int)resized2(i, j, c)) / 2;
                }
            }
            image = resized1;

        } else {
            int mergeW = min(image.width, image2.width);
            int mergeH = min(image.height, image2.height);

            for (int i = 0; i < mergeW; ++i) {
                for (int j = 0; j < mergeH; ++j) {
                    for (int c = 0; c < 3; ++c)
                        image(i, j, c) = ((int)image(i, j, c) + (int)image2(i, j, c)) / 2;
                }
            }
        }
        cout << "Images merged successfully!" << endl;

    } catch (exception& e) {
        cerr << "Error loading second image: " << e.what() << endl;
    }
}
void PhotoShop::flip_image() {
    string choice;
    cout << "Flip horizontally(H) or Vertically(V): ";
    while (true) {
        cin >> choice;
        if (choice.size() == 1 && (tolower(choice[0]) == 'h' || tolower(choice[0]) == 'v')) {
            break;
        }
        cout << "Only choose either H or V\n";
    }
    if (std::tolower(choice[0]) == 'v') {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int temp  = image(i, j, k);
                    image(i, j, k) = image(i, image.height - 1 - j, k);
                    image(i, image.height - 1 - j, k) = temp;
                }
            }
        }
    }
    else if (std::tolower(choice[0]) == 'h') {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int temp  = image(i, j, k);
                    image(i, j, k) = image(image.width - 1 - i, j, k);
                    image(image.width - 1 - i, j, k) = temp;
                }
            }
        }
    }
    cout << "Flip filter applied successfully!" << endl;
}
void PhotoShop::rotate_image() {
    int degree;
    cout << "Available rotations are 90, 180, 270.\n";
    while (true) {
        cout << "Enter your choice: ";
        cin >> degree;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }

        if (degree != 90 && degree != 180 && degree != 270) {
            cout << "Wrong choice number! Enter one of these: 90,180,270.\n";
            continue;
        }
        break;
    }
    if (degree == 180) {
        Image rotated(image.width, image.height);
        for (int i = 0; i < rotated.height; ++i) {
            for (int j = 0; j < rotated.width; ++j) {
                for (int c = 0; c < image.channels; ++c) {
                    rotated(j, i, c) = image(image.width - 1 - j,
                                             image.height - 1 - i, c);
                }
            }
        }
        image = rotated;
    }
    else if (degree == 90) {
        Image rotated(image.width, image.height);

        for (int i = 0; i < rotated.height; i++) {
            for (int j = 0; j < rotated.width; j++) {
                for (int c = 0; c < image.channels; c++) {
                    rotated(j, i, c) = image(i, image.height - 1 - j, c);
                }
            }
        }
        image = rotated;
    }
    else {
        Image rotated(image.width, image.height);

        for (int i = 0; i < rotated.height; i++) {
            for (int j = 0; j < rotated.width; j++) {
                for (int c = 0; c < image.channels; c++) {
                    rotated(j, i, c) = image(image.width - 1 - i, j, c);
                }
            }
        }
        image = rotated;
    }
    cout << "Image rotated successfully!" << endl;
}

void PhotoShop::darker_lighter() {
    string choice;
    cout << "Do you want to make the image (D)arker or (L)ighter: ";

    while (true) {
        cin >> choice;
        if (choice.size() == 1 && (tolower(choice[0]) == 'd' || tolower(choice[0]) == 'l')) {
            break;
        }
        cout << "Only choose either D or L\n";
    }

    int adjustment;
    cout << "Enter adjustment level (0-100): ";
    cin >> adjustment;
    adjustment = min(100, max(0, adjustment));
    int brightnessChange = (tolower(choice[0]) == 'l') ? adjustment : -adjustment;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int newValue = image(i, j, k) + brightnessChange;
                // Clamp to [0, 255]
                newValue = min(255, max(0, newValue));
                image(i, j, k) = (unsigned char)newValue;
            }
        }
    }
    cout << "Brightness adjusted successfully!" << endl;
}

void PhotoShop::crop_image() {
    int x, y, h, w;

    while (true) {
        cout << "Enter x (horizontal start point): ";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        if (x < 0 || x >= image.width) {
            cout << "x must be between 0 and " << image.width - 1 << ".\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter y (vertical start point): ";
        cin >> y;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        if (y < 0 || y >= image.height) {
            cout << "y must be between 0 and " << image.height - 1 << ".\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Enter w (width): ";
        cin >> w;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        if (w <= 0 || x + w > image.width) {
            cout << "Width must be positive and fit within image (max "
                 << (image.width - x) << ").\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Enter h (height): ";
        cin >> h;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        if (h <= 0 || y + h > image.height) {
            cout << "Height must be positive and fit within image (max "
                 << (image.height - y) << ").\n";
            continue;
        }
        break;
    }
    Image cropped_image(w, h);
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < 3; ++k) {
                cropped_image(i, j, k)  = image(i + x, j + y, k);
            }
        }
    }
    image = cropped_image;
    cout << "Crop image filter applied successfully!" << endl;
}
void PhotoShop::frame_image(){
    int choice;
    cout << "Choose frame type:\n";
    cout << "1. Black Frame\n";
    cout << "2. White Frame\n";
    cout << "3. Double Frame\n";

    while (true) {
        cout << "Enter your choice 1-3: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }

        if (choice < 1 || choice > 3) {
            cout << "Wrong choice number! Enter a number from 1-3.\n";
            continue;
        }

        break;
    }

    if (choice == 1)
    {
        cout << "Please enter the frame thickness: ";
        int thickness;
        cin >> thickness;
        int newWidth = image.width + 2 * thickness;
        int newHeight = image.height + 2 * thickness;
        Image framed(newWidth, newHeight);
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                framed(x, y, 0) = 255;
                framed(x, y, 1) = 255;
                framed(x, y, 2) = 255;
            }
        }
        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {
                for (int c = 0; c < 3; c++) {
                    framed(x + thickness, y + thickness, c) = image(x, y, c);
                }
            }
        }
        image = framed;
    }
    else if (choice == 2)
    {
        cout << "Please enter the frame thickness: ";
        int thickness;
        cin >> thickness;
        int newWidth = image.width + 2 * thickness;
        int newHeight = image.height + 2 * thickness;
        Image framed(newWidth, newHeight);
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                framed(x, y, 0) = 0;
                framed(x, y, 1) = 0;
                framed(x, y, 2) = 0;
            }
        }
        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {
                for (int c = 0; c < 3; c++) {
                    framed(x + thickness, y + thickness, c) = image(x, y, c);
                }
            }
        }
        image = framed;
    }
    else
    {
         int thickness1, thickness2;
        std::cout << "Enter inner frame thickness: ";
        std::cin >> thickness1;
        std::cout << "Enter outer frame thickness: ";
        std::cin >> thickness2;

        int newWidth1 = image.width + 2 * thickness1;
        int newHeight1 = image.height + 2 * thickness1;
        Image innerFrame(newWidth1, newHeight1);

        for (int y = 0; y < newHeight1; y++) {
            for (int x = 0; x < newWidth1; x++) {
                innerFrame(x, y, 0) = 0;
                innerFrame(x, y, 1) = 0;
                innerFrame(x, y, 2) = 0;
            }
        }

        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {
                for (int c = 0; c < 3; c++) {
                    innerFrame(x + thickness1, y + thickness1, c) = image(x, y, c);
                }
            }
        }

        int newWidth2 = newWidth1 + 2 * thickness2;
        int newHeight2 = newHeight1 + 2 * thickness2;
        Image outerFrame(newWidth2, newHeight2);

        for (int y = 0; y < newHeight2; y++) {
            for (int x = 0; x < newWidth2; x++) {
                outerFrame(x, y, 0) = 255;
                outerFrame(x, y, 1) = 255;
                outerFrame(x, y, 2) = 255;
            }
        }

        for (int y = 0; y < newHeight1; y++) {
            for (int x = 0; x < newWidth1; x++) {
                for (int c = 0; c < 3; c++) {
                    outerFrame(x + thickness2, y + thickness2, c) = innerFrame(x, y, c);
                }
            }
        }
        image = outerFrame;
    }
    cout << "The Frame applied to image successfully!" << endl;
}
void PhotoShop::image_edges() {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);
            unsigned char gray = 0.299*r + 0.587*g + 0.114*b;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = gray;
        }
    }
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    Image temp = image;

    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            int sumX = 0, sumY = 0;

            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int val = temp(i + x, j + y, 0);
                    sumX += val * Gx[x + 1][y + 1];
                    sumY += val * Gy[x + 1][y + 1];
                }
            }
            int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
            magnitude = min(255, magnitude);

            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = magnitude;
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 0) = 255 - image(i, j, 0);
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }
    cout << "Edge detection applied successfully!" << endl;
}

void PhotoShop::resize_image() {
    double w, h;
    while (true) {
        cout << "Enter Width: ";
        cin >> w;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Height: ";
        cin >> h;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        break;
    }

    const double  scaling_x = image.width / w;
    const double  scaling_y = image.height / h;

    Image resized_image(static_cast<int>(w), static_cast<int>(h));

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            const int src_x = i * scaling_x;
            const int src_y = j * scaling_y;

            for (int k = 0; k < 3; ++k) {
                resized_image(i, j, k) = image(src_x, src_y, k);
            }
        }
    }
    image = resized_image;
    cout << "Image resized successfully!" << endl;
}

void PhotoShop::blur_image()
{
    Image blurred(image.width, image.height);
    int width = blurred.width;
    int height = blurred.height;
    int kernelsize;
    int offset;
    cout << "Available Blur Options:\n";
    cout << "1. Low\n";
    cout << "2. Medium\n";
    cout << "3. High\n";
    int choice;
    while (true) {
        cout << "Enter your choice (1,2,3): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }
        if (choice < 1 || choice > 3) {
            cout << "Please enter 1, 2, 3.\n";
            continue;
        }
        break;
    }
    if (choice == 1) {
        kernelsize = 5;
        offset = 2 ;
    }
    else if (choice == 2) {
        kernelsize = 7;
        offset = 3 ;
    }
    else {
        kernelsize = 9;
        offset = 4 ;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int i = -offset; i <= offset; i++) {
                for (int j = -offset; j <= offset; j++) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx < 0) nx = 0;
                    if (nx >= width) nx = width - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= height) ny = height - 1;

                    int r = image(nx, ny, 0);
                    int g = image(nx, ny, 1);
                    int b = image(nx, ny, 2);

                    sumR += r;
                    sumG += g;
                    sumB += b;
                    count++;
                }
            }
            blurred.setPixel(x, y, 0, sumR / count);
            blurred.setPixel(x, y, 1, sumG / count);
            blurred.setPixel(x, y, 2, sumB / count);
        }
    }
 image = blurred;
    cout << "Image blured successfully!" << endl;
}

void PhotoShop::sunlight() {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            int r = image(i, j, 0);
            int g = image(i, j, 1);
            int b = image(i, j, 2);

            r += 25;
            g += 25;
            b -= 10;

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            if (r < 0) r = 0;
            if (g < 0) g = 0;
            if (b < 0) b = 0;

            image(i, j, 0) = static_cast<unsigned char>(r);
            image(i, j, 1) = static_cast<unsigned char>(g);
            image(i, j, 2) = static_cast<unsigned char>(b);

        }
    }
    cout << "Sunlight filter applied successfully!" << endl;
}
void PhotoShop::oil_paint() {
    int windowsize = 7;
    int intensitylvls = 32;
    int half = windowsize / 2;

    Image oil(image.width, image.height);

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int histogram[intensitylvls] = {0};
            int sumR[intensitylvls] = {0};
            int sumG[intensitylvls] = {0};
            int sumB[intensitylvls] = {0};

            for (int i = -half; i <= half; i++)
            {
                for (int j = -half; j <= half; j++)
                {
                    int nx = x + i;
                    int ny = y + j;

                    if ( nx >=0 && nx < image.width && ny >=0 && ny < image.height )
                    {
                       unsigned char r = image(nx, ny, 0);
                        unsigned char g = image(nx, ny, 1);
                        unsigned char b = image(nx, ny, 2);

                        int intensity = (r + g + b) / 3;
                        int bin = (intensity * intensitylvls) / 256;
                        histogram[bin]++;
                        sumR[bin] += r;
                        sumG[bin] += g;
                        sumB[bin] += b;

                    }
                }
            }


            int dominantBin = std::max_element(histogram, histogram + intensitylvls) - histogram;

           if (histogram[dominantBin] > 0)
           {
               oil(x ,y ,0) = sumR[dominantBin] / histogram[dominantBin];
               oil(x ,y ,1) = sumG[dominantBin] / histogram[dominantBin];
               oil(x ,y ,2) = sumB[dominantBin] / histogram[dominantBin];
           }
            else
            {
                oil(x ,y ,0) = image(x,y,0);
                oil(x ,y ,1) = image(x,y ,1);
                oil(x ,y ,2) = image(x,y ,2);
            }

        }
    }


image = oil;
    cout << "Oil paint filter applied successfully!" << endl;
}
void PhotoShop::television() {
    Image retroTv(image.width, image.height);

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < 3; c++) {
                unsigned char value = image(x, y, c);
                if (c == 0) value = min(255, value + 5);
                if (c == 2) value = min(255, value + 10);

                if (y % 2 == 0) {
                    value = value * 0.5;
                }

                retroTv(x, y, c) = value;
            }
        }
    }
    image = retroTv;
    cout << "Television filter applied successfully!" << endl;
}
void PhotoShop::night_purple() {
    Image nightpurple(image.width, image.height);

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                unsigned char value = image(x, y, c);
                if (c == 0) value = min(255, (int)(value * 1.1));
                if (c == 1) value = min(255, (int)(value * 0.6));
                if (c == 2) value = min(255, (int)(value * 1.3));
                nightpurple(x, y, c) = value;
            }
        }
    }
    image = nightpurple;
    cout << "Night purple filter applied successfully!" << endl;
}
void PhotoShop::infrared() {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned char red = image(i, j, 0);
            unsigned char green = image(i, j, 1);
            unsigned char blue = image(i, j, 2);

            unsigned char luminosity = static_cast<unsigned char>(
                0.299 * red + 0.587 * green + 0.114 * blue
            );

            unsigned char inverted = 255 - luminosity;

            if (inverted > 180) {
                image(i, j, 0) = 240;
                image(i, j, 1) = inverted;
                image(i, j, 2) = inverted;
            } else if (inverted > 100) {
                // Mid-tones → pink/light red shades
                image(i, j, 0) = 255;
                image(i, j, 1) = (inverted + 125) / 2;
                image(i, j, 2) = (inverted + 125) / 2;
            } else {
                // Originally bright areas → deep red shades
                image(i, j, 0) = 200 + (inverted / 2);
                image(i, j, 1) = (inverted + 50) / 3;
                image(i, j, 2) = (inverted + 50) / 3;
            }
        }
    }
    cout << "Infrared filter applied successfully!" << endl;
}
void PhotoShop::skew() {
    cout << "Skew Filter\n";
}

void PhotoShop::save_image() {
    if (image.width == 0 || image.height == 0) {
        cout << "Image is empty or not loaded. You can't save\n";
    }
    else {
        string overwrite;
        cout << "You want to overwrite or new file (n for new, o for overwrite)" << endl;
        cin >> overwrite;
        while (overwrite != "n" && overwrite != "o") {
            cout << "Enter correct values(n or o): " << endl;
            cin >> overwrite;
        }
        if (overwrite == "n") {
            cout << "Pls enter image name to store new image\n";
            cout << "and specify extension .jpg, .bmp, .png, .tga: ";
            string new_filename;
            cin >> new_filename;
            image.saveImage(new_filename);
            cout << "Image saved successfully.\n";
        }
        else {
            image.saveImage(filename);
            cout << "Image saved successfully.\n";
        }

    }
}

void filter_menu(PhotoShop& ps){
    if (ps.image.width == 0 || ps.image.height == 0) {
        cout << "Image is empty or not loaded. You can't filter on it\n";
        return;
    }

    cout << ""
    "1.Gray Scale\n"
    "2.Black and White\n"
    "3.Invert Image Colors\n"
    "4.Merge 2 Images\n"
    "5.Flip the Image\n"
    "6.Rotate the Image\n"
    "7.Darken or Lighten the Image\n"
    "8.Crop the Image\n"
    "9.Add a Frame\n"
    "10.Image Edges\n"
    "11.Resize Image\n"
    "12.Blur Image\n"
    "13.Sunlight\n"
    "14.Oil Painting\n"
    "15.Television Effect\n"
    "16.Night\n"
    "17.Infrared\n"
    "18.Skew Image\n"
    "" << endl;

    int choice;
    while (true) {
        cout << "Enter your choice 1-18: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }

        if (choice < 1 || choice > 18) {
            cout << "Wrong choice number! Enter a number from 1-18.\n";
            continue;
        }

        break;
    }
    vector<function<void()>> choices = {
        [&](){ ps.gray_scale(); },
        [&](){ ps.black_white(); },
        [&](){ ps.invert_image(); },
        [&](){ ps.merge_image(); },
        [&](){ ps.flip_image(); },
        [&](){ ps.rotate_image(); },
        [&](){ ps.darker_lighter(); },
        [&](){ ps.crop_image(); },
        [&](){ ps.frame_image(); },
        [&](){ ps.image_edges(); },
        [&](){ ps.resize_image(); },
        [&](){ ps.blur_image(); },
        [&](){ ps.sunlight(); },
        [&](){ ps.oil_paint(); },
        [&](){ ps.television(); },
        [&](){ ps.night_purple(); },
        [&](){ ps.infrared(); },
        [&](){ ps.skew(); },
    };

    choices[choice - 1]();
}

bool menu(PhotoShop& ps){

    cout << ""
    "1.Load New Image\n"
    "2.Save the Image\n"
    "3.Filter Menu\n"
    "4.Exit\n"
    "" << endl;

    int choice;
    while (true) {
        cout << "Enter your choice 1-4: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }

        if (choice < 1 || choice > 4) {
            cout << "Wrong choice number! Enter a number from 1-4.\n";
            continue;
        }
        break;
    };
    vector<function<void()>> choices = {
    [&](){ ps.load_image(); },
    [&](){ ps.save_image(); },
    [&](){ filter_menu(ps); }

    };
    if (choice == 4) {
        return false;
    }
    choices[choice - 1]();
    return true;
}


int main() {
    cout << "Welcome to Photoshop\n";
    bool running = true;
    PhotoShop ps;
    while (running) { //
        running = menu(ps);
    }
    cout << "Goodbye!" << endl;
    return 0;
}


