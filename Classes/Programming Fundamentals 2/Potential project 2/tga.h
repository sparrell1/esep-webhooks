#include <string>
#include <vector>

// Structure to represent the header of a TGA file, storing image metadata
struct Header {
    char idLength;           // Length of the image ID field
    char colorMapType;       // Type of color map (0 = no color map)
    char dataTypeCode;       // Image data type (e.g., uncompressed, compressed)
    short colorMapOrigin;    // Offset into the color map table
    short colorMapLength;    // Number of color map entries
    char colorMapDepth;      // Number of bits per color map entry
    short xOrigin;           // X-origin of the image
    short yOrigin;           // Y-origin of the image
    short width;             // Width of the image in pixels
    short height;            // Height of the image in pixels
    char bitsPerPixel;       // Number of bits per pixel (e.g., 24, 32)
    char imageDescriptor;    // Descriptor for image attributes (e.g., alpha channel bits)

    // Function to print out the header attributes of the TGA file
    void displayAttributes();
};

// Structure to represent an individual pixel in the image, with RGB channels
struct Pixel {
    unsigned char r;   // Red channel
    unsigned char g;   // Green channel
    unsigned char b;   // Blue channel

    // Constructor for initializing pixel values
    Pixel() = default;
    Pixel(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

    // Function to allow access to pixel values using an index (0 for red, 1 for green, 2 for blue)
    unsigned char& operator[](int index);
};

// Class to represent a TGA image, containing the header and pixel data
struct TGA {
    Header header;                  // TGA file header
    std::vector<Pixel> pixelData;   // Vector storing pixel data for the image

    // Function to load a TGA image from a file into the TGA object
    void loadImage(const std::string& fname);

    // Function to save the current TGA object as a TGA image file
    void saveImage(const std::string& fname);

    // Function to apply the multiply blending operation on two images
    TGA* applyMultiply(TGA& other);

    // Function to apply the subtract operation on two images
    TGA* applySubtract(TGA& other);

    // Function to apply the screen blending operation on two images
    TGA* applyScreen(TGA& other);

    // Function to apply the overlay blending operation on two images
    TGA* applyOverlay(TGA& other);

    // Function to adjust the green channel by adding a value to it
    TGA* adjustGreenChannel(int value);

    // Function to scale the red channel by multiplying it with a value
    TGA* scaleRedChannel(int scale);

    // Function to compare the pixel data of this TGA image with another
    bool compare(const TGA& other);

    // Static function to combine red, green, and blue layers into a single TGA image
    static TGA* combine(TGA& r, TGA& g, TGA& b);

    // Static function to rotate the TGA image (e.g., 90-degree rotation)
    static TGA* rotate(TGA& image);
};
