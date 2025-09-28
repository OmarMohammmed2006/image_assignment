#include <functional>
#include <string>
#include <vector>
using namespace std;
#include "Image_Class.h"

class PhotoShop {
    public:
        void load_image();
        void gray_scale(); // 1
        void black_white(); // 2
        void invert_image(); // 3
        void merge_image(); // 4
        void flip_image(); // 5
        void rotate_image(); // 6
        void darker_lighter(); // 7
        void crop_image(); // 8
        void frame_image(); // 9
        void image_edges(); // 10
        void resize_image(); // 11
        void blur_image(); // 12
        void save_image();
            // mahmoud was here.
        // Declare your filter function here --> filer_name();

        Image image;
};

string filename;

void PhotoShop::load_image() {
    cout << "Enter your image path: ";
    cin.ignore();
    getline(cin, filename);

    try {
        image = Image(filename); // load into class member
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
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
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

            avg /= 3; // grayscale value

            // Apply threshold (127 is the midpoint of 0–255)
            unsigned int bw = (avg >= 127) ? 255 : 0;

            // Set all channels to black or white
            image(i, j, 0) = bw;
            image(i, j, 1) = bw;
            image(i, j, 2) = bw;
        }
    }
}

void PhotoShop::invert_image(){ cout << "Invert" << endl; }

void PhotoShop::merge_image(){cout << "Merge" << endl;}

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

void PhotoShop::rotate_image(){cout << "Rotate" << endl;}

void PhotoShop::darker_lighter(){cout << "Darken" << endl;}

void PhotoShop::crop_image(){cout << "Crop" << endl;}

void PhotoShop::frame_image(){cout << "Frame" << endl;}

void PhotoShop::image_edges(){cout << "Edge" << endl;}

void PhotoShop::resize_image(){cout << "Resize" << endl;}

void PhotoShop::blur_image(){cout << "blur" << endl;}

void PhotoShop::save_image() {
    if (image.width == 0 || image.height == 0) {
        cout << "Image is empty or not loaded. You can't save\n";
    }
    else {
        cout << "Pls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";

        cin >> filename;
        image.saveImage(filename);
    }
}

// Write the function's code outside the class so it doesn't become stacked
// Make sure to include this before the function name PhotoShop:: so it understands that this function belongs to the class

bool filter_menu(PhotoShop& ps){
    if (ps.image.width == 0 || ps.image.height == 0) {
        cout << "Image is empty or not loaded. You can't filter on it\n";
        return true;
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

    choices[choice - 1](); // Calls the lambda function, that calls the class method late
    return true;
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


