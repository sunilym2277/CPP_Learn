#include <iostream>
#include <string>
using namespace std;

// Subject Interface
class IImage {
public:
    virtual void display() const = 0;
    virtual ~IImage() = default;
};

// Real Subject - Heavy object
class RealImage : public IImage {
private:
    string filename;
    void loadFromDisk() const {
        cout << "[RealImage] Loading image from disk: " << filename << endl;
    }
public:
    RealImage(const string& file) : filename(file) {
        loadFromDisk(); // Expensive operation
    }
    void display() const override {
        cout << "[RealImage] Displaying image: " << filename << endl;
    }
};

// Proxy - Controls access to RealImage
class ProxyImage : public IImage {
private:
    string filename;
    mutable RealImage* realImage; // Mutable so we can lazy-load in const method
public:
    ProxyImage(const string& file) : filename(file), realImage(nullptr) {}

    void display() const override {
        if (!realImage) { // Load only when needed
            cout << "[ProxyImage] Creating RealImage object...\n";
            realImage = new RealImage(filename);
        }
        realImage->display();
    }

    ~ProxyImage() {
        delete realImage;
    }
};

// Client code
int main() {
    IImage* image = new ProxyImage("test_photo.png");

    cout << "Image object created, but not loaded yet.\n\n";

    cout << "First display call:\n";
    image->display(); // Loads and displays

    cout << "\nSecond display call:\n";
    image->display(); // Uses already loaded image

    delete image;
    return 0;
}
