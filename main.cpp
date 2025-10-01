#include <functional>
#include <string>
#include <vector>
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
}

void PhotoShop::invert_image()
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
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
    if (degree == 180)
    {
        Image rotated(image.width, image.height);
        for (int i = 0; i < rotated.height; ++i)
        {
            for (int j = 0; j < rotated.width; ++j)
            {
                for (int c = 0; c < image.channels; ++c)
                {
                    rotated(j, i, c) = image(image.width - 1 - j,
                                             image.height - 1 - i, c);
                }
            }
        }
        image = rotated;
    }
    else if (degree == 90)
    {
        Image rotated(image.height, image.width);

        for (int i = 0; i < rotated.height; i++)   // i = row index
        {
            for (int j = 0; j < rotated.width; j++) // j = col index
            {
                for (int c = 0; c < image.channels; c++)
                {
                    rotated(j, i, c) = image(i, image.height - 1 - j, c);
                }
            }
        }
        image = rotated;
    }
    else
    {
        Image rotated(image.height, image.width);

        for (int i = 0; i < rotated.height; i++)   // i = row index
        {
            for (int j = 0; j < rotated.width; j++) // j = col index
            {
                for (int c = 0; c < image.channels; c++)
                {
                    rotated(j, i, c) = image(image.width - 1 - i, j, c);
                }
            }
        }
        image = rotated;
    }
}

void PhotoShop::darker_lighter(){cout << "Darken" << endl;}

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
                framed(x, y, 0) = 255; // Red
                framed(x, y, 1) = 255; // Green
                framed(x, y, 2) = 255; // Blue
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

        // Step 1: Create image with inner frame
        int newWidth1 = image.width + 2 * thickness1;
        int newHeight1 = image.height + 2 * thickness1;
        Image innerFrame(newWidth1, newHeight1);

        // Fill with inner frame color
        for (int y = 0; y < newHeight1; y++) {
            for (int x = 0; x < newWidth1; x++) {
                innerFrame(x, y, 0) = 0;
                innerFrame(x, y, 1) = 0;
                innerFrame(x, y, 2) = 0;
            }
        }

        // Copy original image into center
        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {
                for (int c = 0; c < 3; c++) {
                    innerFrame(x + thickness1, y + thickness1, c) = image(x, y, c);
                }
            }
        }

        // Step 2: Create image with outer frame
        int newWidth2 = newWidth1 + 2 * thickness2;
        int newHeight2 = newHeight1 + 2 * thickness2;
        Image outerFrame(newWidth2, newHeight2);

        // Fill with outer frame color
        for (int y = 0; y < newHeight2; y++) {
            for (int x = 0; x < newWidth2; x++) {
                outerFrame(x, y, 0) = 255;
                outerFrame(x, y, 1) = 255;
                outerFrame(x, y, 2) = 255;
            }
        }

        // Copy innerFrame into the center
        for (int y = 0; y < newHeight1; y++) {
            for (int x = 0; x < newWidth1; x++) {
                for (int c = 0; c < 3; c++) {
                    outerFrame(x + thickness2, y + thickness2, c) = innerFrame(x, y, c);
                }
            }
        }
        image = outerFrame;

    }
}
void PhotoShop::image_edges(){cout << "Edge" << endl;}

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
}

void PhotoShop::blur_image(){cout << "blur" << endl;}

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
        }
        else image.saveImage(filename);
    }
}

// Write the function's code outside the class so it doesn't become stacked
// Make sure to include this before the function name PhotoShop:: so it understands that this function belongs to the class

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
    "" << endl;
    // Menu for choosing the functions -- choose by numbers
    // Add your new filter name and move the numbers down for the other options

    int choice;
    while (true) {
        cout << "Enter your choice 1-12: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Only numbers are allowed.\n";
            continue;
        }

        if (choice < 1 || choice > 12) {
            cout << "Wrong choice number! Enter a number from 1-12.\n";
            continue;
        }

        break;
    }
    // Choose the number
    vector<function<void()>> choices = { // Instead of If condition we use a vector of lambda functions to call the filters
        [&](){ ps.gray_scale(); }, // Lamda functions that call the class methods when the lambda function is called
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
        [&](){ ps.blur_image(); }
        // copy/paste the format of the lambda function then just change the method you will call from the class
    };

    choices[choice - 1](); // Calls the lambda function, that calls the class method later
}

bool menu(PhotoShop& ps){

    cout << ""
    "1.Load New Image\n"
    "2.Save the Image\n"
    "3.Filter Menu\n"
    "4.Exit\n"
    "" << endl;

    // Menu for choosing the functions -- choose by numbers
    // Add your new filter name and move the numbers down for the other options

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
    }; // Choose the number
    vector<function<void()>> choices = { // Instead of If condition we use a vector of lambda functions to call the filters
    [&](){ ps.load_image(); }, // Lamda functions that call the class methods when the lambda function is called
    [&](){ ps.save_image(); },
    [&](){ filter_menu(ps); }
        // copy/paste the format of the lambda function then just change the method you will call from the class
    };
    if (choice == 4) { // exits if the value is 6, will be changed later because we will add filters
        return false;
    }
    choices[choice - 1](); // Calls the lambda function, that calls the class method late
    return true; // To make the while loop work until we Exit
}


int main() {
    cout << "Welcome to Photoshop\n";
    bool running = true;
    PhotoShop ps;
    while (running) { // Starts the program and calls the menu and loops until the menu return false
        running = menu(ps);
    }
    cout << "Goodbye!" << endl;
    return 0;
}


