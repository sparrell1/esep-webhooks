#include <string>    // Required for using the std::string type
#include <vector>    // Required for using the std::vector container

struct Header
{
	char idLength;          // Length of the image ID field
	char colorMapType;      // Type of color map (0 = no color map)
	char dataTypeCode;      // Type of image data (e.g., uncompressed RGB)
	short colorMapOrigin;   // First entry index for the color map
	short colorMapLength;   // Number of entries in the color map
	char colorMapDepth;     // Number of bits per entry in the color map
	short xOrigin;          // X-coordinate of the lower-left corner of the image
	short yOrigin;          // Y-coordinate of the lower-left corner of the image
	short width;            // Width of the image in pixels
	short height;           // Height of the image in pixels
	char bitsPerPixel;      // Number of bits per pixel (e.g., 24 for RGB)
	char imageDescriptor;   // Image descriptor byte (e.g., alpha channel depth)

	void print();           // Prints out the header information
};

// Explanation: The `Header` struct holds metadata for the TGA image, storing information
// about the image's dimensions, color map, and other properties. The `print` function
// is used to output this information to the console. Understanding structs and their usage
// is covered in Lesson 8 on "Structures in C++."

struct Pixel {
	unsigned char r;  // Red component of the pixel
	unsigned char g;  // Green component of the pixel
	unsigned char b;  // Blue component of the pixel

	Pixel() {}  // Default constructor

	Pixel(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;  // Initializes the red component
		this->g = g;  // Initializes the green component
		this->b = b;  // Initializes the blue component
	}

	unsigned char& operator[](int index) {  // Overloads the [] operator to access pixel components
		if (index == 0)
			return r;  // Returns the red component if index is 0
		else if (index == 1)
			return g;  // Returns the green component if index is 1
		else
			return b;  // Returns the blue component if index is 2
	}
};

// Explanation: The `Pixel` struct represents a single pixel in the image, with red, green, 
// and blue color components. It includes constructors for easy initialization and an 
// operator overload to access these components using an index. This is fundamental in image 
// processing tasks where individual pixel manipulation is required, as discussed in Lesson 9.

struct TGA {

	Header header;                 // Contains the header of the TGA image
	std::vector<Pixel> pixelData;  // Stores the pixel data of the TGA image


	void read(std::string fname);  // Reads the TGA image from a file
	void write(std::string fname); // Writes the TGA image to a file


	TGA* multiply(TGA& secondImage);  // Multiplies this image with another image
	TGA* subtract(TGA& secondImage);  // Subtracts another image from this image
	TGA* screen(TGA& secondImage);    // Screens this image with another image
	TGA* overlay(TGA& secondImage);   // Overlays this image with another image
	TGA* addGreen(int val);           // Adds a value to the green channel of this image
	TGA* scaleRed(int scaleFactor);   // Scales the red channel of this image by a factor

	static TGA* combine(TGA& imageR, TGA& imageG, TGA& imageB); // Combines the R, G, B channels from three images into one
	static TGA* rotate(TGA& image);  // Rotates the image 180 degrees


	bool compare(TGA& secondImage);  // Compares this image with another image
};

// Explanation: The `TGA` struct encapsulates the entire TGA image, including the header and pixel data.
// It provides methods to read and write TGA files, perform image manipulations (like multiply, subtract, 
// screen, overlay), and compare images. These operations are essential for handling and processing images 
// in C++, as covered in the project's specific lessons on image processing.

