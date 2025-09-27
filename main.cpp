#include <functional>
#include <string>
#include <vector>
using namespace std;
#include "Image_Class.h"

class PhotoShop {
    public:
        void load_image();
        void gray_scale();
        void filter2();
        void filter3();
        void save_image();

        // Declare your filter function here --> filer_name();

    private:
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

void PhotoShop::filter2(){cout << "Filter 2" << endl;}

void PhotoShop::filter3(){cout << "Filter 3" << endl;};

void PhotoShop::save_image() {
        cout << "Pls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";

        cin >> filename;
        image.saveImage(filename);
}

// Write the function's code outside the class so it doesn't become stacked
// Make sure to include this before the function name PhotoShop:: so it understands that this function belongs to the class

bool menu(PhotoShop& ps){

    cout << ""
    "1.Load New Image\n"
    "2.Gray Scale\n"
    "3.Filter 2\n"
    "4.Filter 3\n"
    "5.Save the Image\n"
    "6.Exit\n"
    "enter your choice(number): "
    "" << endl;
    // Menu for choosing the functions -- choose by numbers
    // Add your new filter name and move the numbers down for the other options

    int x; cin >> x; // Choose the number
    vector<function<void()>> choices = { // Instead of If condition we use a vector of lambda functions to call the filters
    [&](){ ps.load_image(); }, // Lamda functions that call the class methods when the lambda function is called
    [&](){ ps.gray_scale(); },
    [&](){ ps.filter2(); },
    [&](){ ps.filter3(); },
    [&](){ ps.save_image(); }
        // copy/paste the format of the lambda function then just change the method you will call from the class
    };
    if (x == 6) { // exits if the value is 6, will be changed later because we will add filters
        return false;
    }
    choices[x - 1](); // Calls the lambda function, that calls the class method late
    return true; // To make the while loop work until we Exit
}

int main() {
    cout << "Welcome, Please enter to Start the program\n";
    string check; bool y = true;
    PhotoShop ps;
    cin >> check;
    while (check == "start" && y) { // Starts the program and calls the menu and loops until the menu return false
        y = menu(ps);
    }
    cout << "Goodbye!" << endl;
    return 0;
}


