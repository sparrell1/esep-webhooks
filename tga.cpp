#include <iostream>   // Required for input/output operations
#include <fstream>    // Required for file operations
#include <string>     // Required for string manipulations

#include "tga.h"      // Includes the header file that defines the TGA class and related structures

using namespace std;  // Allows the use of standard C++ library functions without the std:: prefix

void Header::print() {
	cout << "idLength: " << (int)idLength << endl;
	cout << "colorMapType: " << (int)colorMapType << endl;
	cout << "dataTypeCode: " << (int)dataTypeCode << endl;
	cout << "colorMapOrigin: " << colorMapOrigin << endl;
	cout << "colorMapLength: " << colorMapLength << endl;
	cout << "colorMapDepth: " << (int)colorMapDepth << endl;
	cout << "xOrigin: " << xOrigin << endl;
	cout << "yOrigin: " << yOrigin << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "bitsPerPixel: " << (int)bitsPerPixel << endl;
	cout << "imageDescriptor: " << (int)imageDescriptor << endl;
}

// This function is part of the `Header` structure and is used to print all the header information 
// of a TGA file to the console. Each field of the header is printed in a human-readable format, 
// converting `char` fields to their integer values where necessary.

void TGA::read(string fname) {
	ifstream file(fname, ios_base::binary);  // Opens the file in binary mode for reading

	// Header
	file.read(&header.idLength, 1);  // Reads 1 byte for the ID length
	file.read(&header.colorMapType, 1);  // Reads 1 byte for the color map type
	file.read(&header.dataTypeCode, 1);  // Reads 1 byte for the data type code
	file.read((char*)&header.colorMapOrigin, 2);  // Reads 2 bytes for the color map origin
	file.read((char*)&header.colorMapLength, 2);  // Reads 2 bytes for the color map length
	file.read(&header.colorMapDepth, 1);  // Reads 1 byte for the color map depth
	file.read((char*)&header.xOrigin, 2);  // Reads 2 bytes for the X origin
	file.read((char*)&header.yOrigin, 2);  // Reads 2 bytes for the Y origin
	file.read((char*)&header.width, 2);  // Reads 2 bytes for the image width
	file.read((char*)&header.height, 2);  // Reads 2 bytes for the image height
	file.read(&header.bitsPerPixel, 1);  // Reads 1 byte for bits per pixel
	file.read(&header.imageDescriptor, 1);  // Reads 1 byte for the image descriptor

	// Pixel info
	for (int i = 0; i < (int)header.width * (int)header.height; ++i) {  // Iterates over each pixel
		Pixel newPixel;  // Creates a new Pixel object

		file.read((char*)&newPixel.b, 1);  // Reads 1 byte for the blue channel
		file.read((char*)&newPixel.g, 1);  // Reads 1 byte for the green channel
		file.read((char*)&newPixel.r, 1);  // Reads 1 byte for the red channel

		pixelData.push_back(newPixel);  // Adds the new pixel to the pixel data vector
	}

	// Completed
	file.close();  // Closes the file
}

// This function reads a TGA image from a file, parsing the header and pixel data. The header is read first 
// to obtain the metadata, and then the pixel data is read sequentially. The data is stored in the `pixelData` vector.

void TGA::write(string fname) {
	ofstream file(fname, ios_base::binary);  // Opens the file in binary mode for writing

	// Header
	file.write(&header.idLength, 1);  // Writes 1 byte for the ID length
	file.write(&header.colorMapType, 1);  // Writes 1 byte for the color map type
	file.write(&header.dataTypeCode, 1);  // Writes 1 byte for the data type code
	file.write((char*)&header.colorMapOrigin, 2);  // Writes 2 bytes for the color map origin
	file.write((char*)&header.colorMapLength, 2);  // Writes 2 bytes for the color map length
	file.write(&header.colorMapDepth, 1);  // Writes 1 byte for the color map depth
	file.write((char*)&header.xOrigin, 2);  // Writes 2 bytes for the X origin
	file.write((char*)&header.yOrigin, 2);  // Writes 2 bytes for the Y origin
	file.write((char*)&header.width, 2);  // Writes 2 bytes for the image width
	file.write((char*)&header.height, 2);  // Writes 2 bytes for the image height
	file.write(&header.bitsPerPixel, 1);  // Writes 1 byte for bits per pixel
	file.write(&header.imageDescriptor, 1);  // Writes 1 byte for the image descriptor

	// Pixel info
	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel
		file.write((char*)&pixelData[i].b, 1);  // Writes 1 byte for the blue channel
		file.write((char*)&pixelData[i].g, 1);  // Writes 1 byte for the green channel
		file.write((char*)&pixelData[i].r, 1);  // Writes 1 byte for the red channel
	}

	// Complete File
	file.close();  // Closes the file
}

// This function writes a TGA image to a file. It writes the header information first, followed by the pixel data. 
// This ensures that the image can be saved and later read back correctly.

TGA* TGA::multiply(TGA& secondImage) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = header;  // Copies the header from the current image

	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel in the image
		Pixel newPixel;  // Creates a new Pixel object
		int a = (int)pixelData[i].r;  // Gets the red component of the current pixel
		int b = (int)secondImage.pixelData[i].r;  // Gets the red component of the corresponding pixel in the second image
		unsigned char c = (unsigned char)((a * b / 255.0) + 0.5f);  // Performs the multiply operation on the red channel
		newPixel.r = c;  // Assigns the result to the red channel of the new pixel

		a = (int)pixelData[i].g;  // Gets the green component of the current pixel
		b = (int)secondImage.pixelData[i].g;  // Gets the green component of the corresponding pixel in the second image
		c = (unsigned char)((a * b / 255.0) + 0.5f);  // Performs the multiply operation on the green channel
		newPixel.g = c;  // Assigns the result to the green channel of the new pixel

		a = (int)pixelData[i].b;  // Gets the blue component of the current pixel
		b = (int)secondImage.pixelData[i].b;  // Gets the blue component of the corresponding pixel in the second image
		c = (unsigned char)((a * b / 255.0) + 0.5f);  // Performs the multiply operation on the blue channel
		newPixel.b = c;  // Assigns the result to the blue channel of the new pixel

		resultImage->pixelData.push_back(newPixel);  // Adds the new pixel to the result image
	}

	return resultImage;  // Returns the result image
}

// This function performs a pixel-by-pixel multiplication of two TGA images. Each channel (red, green, blue) of a pixel 
// is multiplied, and the result is stored in a new `TGA` object. This process is essential for tasks involving image blending.

TGA* TGA::subtract(TGA& secondImage) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = header;  // Copies the header from the current image

	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel in the image
		Pixel newPixel;  // Creates a new Pixel object
		int a = (int)pixelData[i].r;  // Gets the red component of the current pixel
		int b = (int)secondImage.pixelData[i].r;  // Gets the red component of the corresponding pixel in the second image
		unsigned char c;
		if (a > b) c = 0;  // Ensures the subtraction does not result in a negative value for the red channel
		else c = (unsigned char)(b - a);  // Subtracts the red component
		newPixel.r = c;  // Assigns the result to the red channel of the new pixel

		a = (int)pixelData[i].g;  // Gets the green component of the current pixel
		b = (int)secondImage.pixelData[i].g;  // Gets the green component of the corresponding pixel in the second image
		if (a > b) c = 0;  // Ensures the subtraction does not result in a negative value for the green channel
		else c = (unsigned char)(b - a);  // Subtracts the green component
		newPixel.g = c;  // Assigns the result to the green channel of the new pixel

		a = (int)pixelData[i].b;  // Gets the blue component of the current pixel
		b = (int)secondImage.pixelData[i].b;  // Gets the blue component of the corresponding pixel in the second image
		if (a > b) c = 0;  // Ensures the subtraction does not result in a negative value for the blue channel
		else c = (unsigned char)(b - a);  // Subtracts the blue component
		newPixel.b = c;  // Assigns the result to the blue channel of the new pixel

		resultImage->pixelData.push_back(newPixel);  // Adds the new pixel to the result image
	}

	return resultImage;  // Returns the result image
}

// This function performs a pixel-by-pixel subtraction of two TGA images. Each channel (red, green, blue) of a pixel 
// is subtracted, and the result is stored in a new `TGA` object. The function ensures that the subtraction does not result in negative values.

TGA* TGA::screen(TGA& secondImage) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = header;  // Copies the header from the current image

	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel in the image
		Pixel newPixel;  // Creates a new Pixel object
		for (int j = 0; j < 3; ++j) {  // Loops over the three color channels
			int a = (int)pixelData[i][j];  // Gets the component of the current pixel
			int b = (int)secondImage.pixelData[i][j];  // Gets the component of the corresponding pixel in the second image
			int c = 255 - ((255 - a) * (255 - b) / 255.0f) + 0.5f;  // Performs the screen operation on the color channel

			newPixel[j] = (unsigned char)c;  // Assigns the result to the corresponding channel of the new pixel
		}
		resultImage->pixelData.push_back(newPixel);  // Adds the new pixel to the result image
	}
	return resultImage;  // Returns the result image
}

// This function performs a screen operation, which is a form of image blending. It calculates the result for each pixel 
// by inverting, multiplying, and then inverting again the values from two images. The final blended pixel is stored in a new `TGA` object.

TGA* TGA::overlay(TGA& secondImage) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = header;  // Copies the header from the current image

	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel in the image
		Pixel newPixel;  // Creates a new Pixel object
		for (int j = 0; j < 3; ++j) {  // Loops over the three color channels
			int a = (int)pixelData[i][j];  // Gets the component of the current pixel
			int b = (int)secondImage.pixelData[i][j];  // Gets the component of the corresponding pixel in the second image
			int c;

			if (b <= 127) c = 2 * (a * b / 255.0f) + 0.5f;  // Applies a multiplication-based operation if the second image's channel is less than or equal to 127
			else c = 255 - 2 * ((255 - a) * (255 - b) / 255.0f) + 0.5f;  // Otherwise applies an inversion-based operation

			newPixel[j] = (unsigned char)c;  // Assigns the result to the corresponding channel of the new pixel
		}
		resultImage->pixelData.push_back(newPixel);  // Adds the new pixel to the result image
	}
	return resultImage;  // Returns the result image
}

// The overlay function blends two images based on the value of the corresponding pixel in the second image. 
// If the value is less than or equal to 127, a multiply-like operation is performed; otherwise, a screen-like operation is performed. 
// The result is stored in a new `TGA` object.

TGA* TGA::addGreen(int val) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = header;  // Copies the header from the current image

	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel in the image
		Pixel newPixel;  // Creates a new Pixel object
		for (int j = 0; j < 3; ++j) {  // Loops over the three color channels
			int a = (int)pixelData[i][j];  // Gets the component of the current pixel

			if (j == 1) {  // If the current channel is green
				a += val;  // Adds the value to the green channel
				if (a > 255) a = 255;  // Ensures the green channel does not exceed 255
			}

			newPixel[j] = (unsigned char)a;  // Assigns the result to the corresponding channel of the new pixel
		}
		resultImage->pixelData.push_back(newPixel);  // Adds the new pixel to the result image
	}
	return resultImage;  // Returns the result image
}

// This function adds a specified value to the green channel of each pixel in the image, 
// ensuring that the value does not exceed 255. This operation is useful for color manipulation tasks.

TGA* TGA::scaleRed(int scaleFactor) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = header;  // Copies the header from the current image

	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel in the image
		Pixel newPixel;  // Creates a new Pixel object
		for (int j = 0; j < 3; ++j) {  // Loops over the three color channels
			int a = (int)pixelData[i][j];  // Gets the component of the current pixel

			if (j == 0) {  // If the current channel is red
				a *= scaleFactor;  // Scales the red channel by the specified factor
				if (a > 255) a = 255;  // Ensures the red channel does not exceed 255
			}
			else if (j == 2) {
				a = 0;  // Sets the blue channel to 0
			}

			newPixel[j] = (unsigned char)a;  // Assigns the result to the corresponding channel of the new pixel
		}
		resultImage->pixelData.push_back(newPixel);  // Adds the new pixel to the result image
	}
	return resultImage;  // Returns the result image
}

// This function scales the red channel of each pixel by a specified factor, capping it at 255, and sets the blue channel to 0. 
// This operation is commonly used in tasks involving color channel manipulation.

TGA* TGA::combine(TGA& imageR, TGA& imageG, TGA& imageB) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = imageR.header;  // Copies the header from the red channel image

	for (unsigned int i = 0; i < imageR.pixelData.size(); ++i) {  // Iterates over each pixel
		resultImage->pixelData.push_back(
			Pixel(imageR.pixelData[i][0],
				imageG.pixelData[i][1],
				imageB.pixelData[i][2]
			)
		);
	}

	return resultImage;  // Returns the result image
}

// This function combines the red, green, and blue channels from three separate images into a single image. 
// Each channel from the respective images is combined to form a new `Pixel` that is added to the result image.

TGA* TGA::rotate(TGA& image) {
	TGA* resultImage = new TGA();  // Allocates memory for the resulting image

	resultImage->header = image.header;  // Copies the header from the original image

	for (unsigned int i = 0; i < image.pixelData.size(); ++i) {  // Iterates over each pixel
		resultImage->pixelData.push_back(
			Pixel(image.pixelData[image.pixelData.size() - 1 - i][0],
				image.pixelData[image.pixelData.size() - 1 - i][1],
				image.pixelData[image.pixelData.size() - 1 - i][2]
			)
		);
	}

	return resultImage;  // Returns the result image
}

// This function rotates the image by reversing the order of the pixels. 
// The last pixel becomes the first, and so on, effectively rotating the image by 180 degrees.

bool TGA::compare(TGA& secondImage) {
	for (unsigned int i = 0; i < pixelData.size(); ++i) {  // Iterates over each pixel
		if (pixelData[i].r != secondImage.pixelData[i].r ||
			pixelData[i].g != secondImage.pixelData[i].g ||
			pixelData[i].b != secondImage.pixelData[i].b
			)
		{
			return false;
		}  // Returns false if any pixel does not match
	}
	return true;  // Returns true if all pixels match
}

// This function compares two TGA images pixel by pixel. If any pixel in the images differs, the function returns `false`; 
// otherwise, it returns `true`. This is crucial for verifying the correctness of image processing tasks.
