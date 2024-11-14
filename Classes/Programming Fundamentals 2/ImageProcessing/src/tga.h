#include <string>
#include <vector>

struct Header    //This comment represents my reference for this struct Header part of code for this assignment, I used the example given on Page 4 of the Project 2 Image Processing guidelines for this assignment.
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    void print();
};

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    // Default constructor
    Pixel() = default;

    // Parameterized constructor
    Pixel(unsigned char SeanParrellR, unsigned char SeanParrellG, unsigned char SeanParrellB)
        : r(SeanParrellR), g(SeanParrellG), b(SeanParrellB) {}

    // Overloaded subscript operator for channel access
    unsigned char& operator[](int SeanParrellIndex) {
        switch (SeanParrellIndex) {
        case 0: return r;
        case 1: return g;
        default: return b;
        }
    }
};


struct TGA {
    // TGA file header
    Header header;

    // Pixel data stored in a vector
    std::vector<Pixel> pixelData;

    // Methods for reading and writing TGA files
    void read(std::string SeanParrellFileName);
    void write(std::string SeanParrellFileName);

    // Blending and modification operations
    TGA* multiply(TGA& SeanParrellImage);
    TGA* subtract(TGA& SeanParrellImage);
    TGA* screen(TGA& SeanParrellImage);
    TGA* overlay(TGA& SeanParrellImage);

    // Color adjustment methods
    TGA* addGreen(int SeanParrellVal);
    TGA* scaleRed(int SeanParrellScaleFactor);

    // Static methods for combining or rotating images
    static TGA* combine(TGA& SeanParrellImageR, TGA& SeanParrellImageG, TGA& SeanParrellImageB);
    static TGA* rotate(TGA& SeanParrellImage);

    // Comparison operation
    bool compare(TGA& SeanParrellImage);
};

