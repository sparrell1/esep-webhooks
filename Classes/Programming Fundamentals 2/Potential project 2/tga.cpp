#include <iostream>
#include <fstream>
#include <string>
#include "tga.h"

// Function to print out the header attributes of the image
void Header::displayAttributes() {
    std::cout << "Identifier Length: " << static_cast<int>(idLength) << std::endl;
    std::cout << "Color Map Type: " << static_cast<int>(colorMapType) << std::endl;
    std::cout << "Data Type: " << static_cast<int>(dataTypeCode) << std::endl;
    std::cout << "Origin of Color Map: " << colorMapOrigin << std::endl;
    std::cout << "Length of Color Map: " << colorMapLength << std::endl;
    std::cout << "Depth of Color Map: " << static_cast<int>(colorMapDepth) << std::endl;
    std::cout << "X Origin: " << xOrigin << std::endl;
    std::cout << "Y Origin: " << yOrigin << std::endl;
    std::cout << "Image Width: " << width << std::endl;
    std::cout << "Image Height: " << height << std::endl;
    std::cout << "Bits Per Pixel: " << static_cast<int>(bitsPerPixel) << std::endl;
    std::cout << "Descriptor: " << static_cast<int>(imageDescriptor) << std::endl;
}

// Function to load a TGA image from a file into the TGA object
void TGA::loadImage(const std::string& fileName) {
    std::ifstream inputFile(fileName, std::ios_base::binary);

    // Reading the header fields from the file
    inputFile.read(&header.idLength, 1);
    inputFile.read(&header.colorMapType, 1);
    inputFile.read(&header.dataTypeCode, 1);
    inputFile.read((char*)&header.colorMapOrigin, 2);
    inputFile.read((char*)&header.colorMapLength, 2);
    inputFile.read(&header.colorMapDepth, 1);
    inputFile.read((char*)&header.xOrigin, 2);
    inputFile.read((char*)&header.yOrigin, 2);
    inputFile.read((char*)&header.width, 2);
    inputFile.read((char*)&header.height, 2);
    inputFile.read(&header.bitsPerPixel, 1);
    inputFile.read(&header.imageDescriptor, 1);

    // Reading pixel data and storing it into the pixelData vector
    for (int pixelCount = 0; pixelCount < header.width * header.height; ++pixelCount) {
        Pixel pixelSample;
        inputFile.read((char*)&pixelSample.b, 1);
        inputFile.read((char*)&pixelSample.g, 1);
        inputFile.read((char*)&pixelSample.r, 1);
        pixelData.push_back(pixelSample);
    }

    inputFile.close();  // Close the file after reading
}

// Function to save the TGA object as a TGA image file
void TGA::saveImage(const std::string& fileName) {
    std::ofstream outputFile(fileName, std::ios_base::binary);

    // Writing the header fields to the output file
    outputFile.write(&header.idLength, 1);
    outputFile.write(&header.colorMapType, 1);
    outputFile.write(&header.dataTypeCode, 1);
    outputFile.write((char*)&header.colorMapOrigin, 2);
    outputFile.write((char*)&header.colorMapLength, 2);
    outputFile.write(&header.colorMapDepth, 1);
    outputFile.write((char*)&header.xOrigin, 2);
    outputFile.write((char*)&header.yOrigin, 2);
    outputFile.write((char*)&header.width, 2);
    outputFile.write((char*)&header.height, 2);
    outputFile.write(&header.bitsPerPixel, 1);
    outputFile.write(&header.imageDescriptor, 1);

    // Writing pixel data to the output file
    for (const auto& pixelSample : pixelData) {
        outputFile.write((char*)&pixelSample.b, 1);
        outputFile.write((char*)&pixelSample.g, 1);
        outputFile.write((char*)&pixelSample.r, 1);
    }

    outputFile.close();  // Close the file after writing
}

// Function to apply the multiply blending operation on two TGA images
TGA* TGA::applyMultiply(TGA& otherImage) {
    TGA* outputImage = new TGA();  // Create a new TGA object for the result
    outputImage->header = this->header;  // Copy the header

    // Multiply each pixel channel (R, G, B) from the current image and otherImage
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        Pixel pixelResult;
        pixelResult.r = static_cast<unsigned char>((this->pixelData[pixelIndex].r * otherImage.pixelData[pixelIndex].r) / 255);
        pixelResult.g = static_cast<unsigned char>((this->pixelData[pixelIndex].g * otherImage.pixelData[pixelIndex].g) / 255);
        pixelResult.b = static_cast<unsigned char>((this->pixelData[pixelIndex].b * otherImage.pixelData[pixelIndex].b) / 255);
        outputImage->pixelData.push_back(pixelResult);  // Add the result pixel to the output image
    }

    return outputImage;  // Return the result TGA image
}

// Function to apply the subtract operation on two TGA images
TGA* TGA::applySubtract(TGA& otherImage) {
    TGA* outputImage = new TGA();  // Create a new TGA object for the result
    outputImage->header = this->header;  // Copy the header

    // Subtract each pixel channel (R, G, B) from the current image and otherImage
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        Pixel pixelResult;
        pixelResult.r = std::max(0, this->pixelData[pixelIndex].r - otherImage.pixelData[pixelIndex].r);
        pixelResult.g = std::max(0, this->pixelData[pixelIndex].g - otherImage.pixelData[pixelIndex].g);
        pixelResult.b = std::max(0, this->pixelData[pixelIndex].b - otherImage.pixelData[pixelIndex].b);
        outputImage->pixelData.push_back(pixelResult);  // Add the result pixel to the output image
    }

    return outputImage;  // Return the result TGA image
}

// Function to apply the screen blending operation on two TGA images
TGA* TGA::applyScreen(TGA& otherImage) {
    TGA* outputImage = new TGA();  // Create a new TGA object for the result
    outputImage->header = this->header;  // Copy the header

    // Apply screen blending to each pixel channel (R, G, B)
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        Pixel pixelResult;
        pixelResult.r = static_cast<unsigned char>(255 - (255 - this->pixelData[pixelIndex].r) * (255 - otherImage.pixelData[pixelIndex].r) / 255);
        pixelResult.g = static_cast<unsigned char>(255 - (255 - this->pixelData[pixelIndex].g) * (255 - otherImage.pixelData[pixelIndex].g) / 255);
        pixelResult.b = static_cast<unsigned char>(255 - (255 - this->pixelData[pixelIndex].b) * (255 - otherImage.pixelData[pixelIndex].b) / 255);
        outputImage->pixelData.push_back(pixelResult);  // Add the result pixel to the output image
    }

    return outputImage;  // Return the result TGA image
}

// Function to apply the overlay blending operation on two TGA images
TGA* TGA::applyOverlay(TGA& otherImage) {
    TGA* outputImage = new TGA();  // Create a new TGA object for the result
    outputImage->header = this->header;  // Copy the header

    // Apply overlay blending to each pixel channel (R, G, B)
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        Pixel pixelResult;

        // If the pixel value is below 127, use multiply; otherwise, use screen
        if (otherImage.pixelData[pixelIndex].r <= 127) {
            pixelResult.r = static_cast<unsigned char>(2 * this->pixelData[pixelIndex].r * otherImage.pixelData[pixelIndex].r / 255);
        }
        else {
            pixelResult.r = static_cast<unsigned char>(255 - 2 * (255 - this->pixelData[pixelIndex].r) * (255 - otherImage.pixelData[pixelIndex].r) / 255);
        }

        // Repeat the same for green and blue channels
        if (otherImage.pixelData[pixelIndex].g <= 127) {
            pixelResult.g = static_cast<unsigned char>(2 * this->pixelData[pixelIndex].g * otherImage.pixelData[pixelIndex].g / 255);
        }
        else {
            pixelResult.g = static_cast<unsigned char>(255 - 2 * (255 - this->pixelData[pixelIndex].g) * (255 - otherImage.pixelData[pixelIndex].g) / 255);
        }

        if (otherImage.pixelData[pixelIndex].b <= 127) {
            pixelResult.b = static_cast<unsigned char>(2 * this->pixelData[pixelIndex].b * otherImage.pixelData[pixelIndex].b / 255);
        }
        else {
            pixelResult.b = static_cast<unsigned char>(255 - 2 * (255 - this->pixelData[pixelIndex].b) * (255 - otherImage.pixelData[pixelIndex].b) / 255);
        }

        outputImage->pixelData.push_back(pixelResult);  // Add the result pixel to the output image
    }

    return outputImage;  // Return the result TGA image
}

// Function to adjust the green channel by adding a value to it
TGA* TGA::adjustGreenChannel(int value) {
    TGA* outputImage = new TGA();  // Create a new TGA object for the result
    outputImage->header = this->header;  // Copy the header

    // Adjust the green channel of each pixel by the provided value
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        Pixel pixelResult = pixelData[pixelIndex];
        pixelResult.g = std::min(255, pixelResult.g + value);  // Ensure the value does not exceed 255
        outputImage->pixelData.push_back(pixelResult);  // Add the result pixel to the output image
    }

    return outputImage;  // Return the result TGA image
}

// Function to scale the red channel by multiplying it with a value
TGA* TGA::scaleRedChannel(int scale) {
    TGA* outputImage = new TGA();  // Create a new TGA object for the result
    outputImage->header = this->header;  // Copy the header

    // Scale the red channel of each pixel by the provided scale factor
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        Pixel pixelResult = pixelData[pixelIndex];
        pixelResult.r = std::min(255, pixelResult.r * scale);  // Ensure the value does not exceed 255
        outputImage->pixelData.push_back(pixelResult);  // Add the result pixel to the output image
    }

    return outputImage;  // Return the result TGA image
}

// Function to compare the pixel data of two TGA images
bool TGA::compare(TGA& otherImage) {
    for (size_t pixelIndex = 0; pixelIndex < pixelData.size(); ++pixelIndex) {
        // Compare each pixel channel (R, G, B)
        if (pixelData[pixelIndex].r != otherImage.pixelData[pixelIndex].r ||
            pixelData[pixelIndex].g != otherImage.pixelData[pixelIndex].g ||
            pixelData[pixelIndex].b != otherImage.pixelData[pixelIndex].b) {
            return false;  // Return false if any mismatch is found
        }
    }
    return true;  // Return true if all pixels match
}
