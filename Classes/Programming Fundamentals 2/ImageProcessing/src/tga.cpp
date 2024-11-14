#include <iostream>
#include <fstream>
#include <string>

#include "tga.h"

using namespace std;

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

void TGA::read(string SeanParrell1) {
    ifstream SeanParrell2(SeanParrell1, ios_base::binary);

    // Header
    SeanParrell2.read(&header.idLength, 1);
    SeanParrell2.read(&header.colorMapType, 1);
    SeanParrell2.read(&header.dataTypeCode, 1);
    SeanParrell2.read((char*)&header.colorMapOrigin, 2);
    SeanParrell2.read((char*)&header.colorMapLength, 2);
    SeanParrell2.read(&header.colorMapDepth, 1);
    SeanParrell2.read((char*)&header.xOrigin, 2);
    SeanParrell2.read((char*)&header.yOrigin, 2);
    SeanParrell2.read((char*)&header.width, 2);
    SeanParrell2.read((char*)&header.height, 2);
    SeanParrell2.read(&header.bitsPerPixel, 1);
    SeanParrell2.read(&header.imageDescriptor, 1);

    // Pixel info
    for (int SeanParrell3 = 0; SeanParrell3 < (int)header.width * (int)header.height; ++SeanParrell3) {
        Pixel SeanParrell4;
        SeanParrell2.read((char*)&SeanParrell4.b, 1);
        SeanParrell2.read((char*)&SeanParrell4.g, 1);
        SeanParrell2.read((char*)&SeanParrell4.r, 1);
        pixelData.push_back(SeanParrell4);
    }

    SeanParrell2.close();
}

void TGA::write(string SeanParrell5) {
    // Open the file in binary mode for writing
    ofstream SeanParrell6;
    SeanParrell6.open(SeanParrell5, ios_base::binary);

    // Write header information in sequence
    SeanParrell6.write(&header.idLength, 1);
    SeanParrell6.write(&header.colorMapType, 1);
    SeanParrell6.write(&header.dataTypeCode, 1);
    SeanParrell6.write(reinterpret_cast<char*>(&header.colorMapOrigin), 2);
    SeanParrell6.write(reinterpret_cast<char*>(&header.colorMapLength), 2);
    SeanParrell6.write(&header.colorMapDepth, 1);
    SeanParrell6.write(reinterpret_cast<char*>(&header.xOrigin), 2);
    SeanParrell6.write(reinterpret_cast<char*>(&header.yOrigin), 2);
    SeanParrell6.write(reinterpret_cast<char*>(&header.width), 2);
    SeanParrell6.write(reinterpret_cast<char*>(&header.height), 2);
    SeanParrell6.write(&header.bitsPerPixel, 1);
    SeanParrell6.write(&header.imageDescriptor, 1);

    // Write each pixel’s data in BGR order
    for (const auto& pixel : pixelData) {
        SeanParrell6.write(reinterpret_cast<const char*>(&pixel.b), 1);
        SeanParrell6.write(reinterpret_cast<const char*>(&pixel.g), 1);
        SeanParrell6.write(reinterpret_cast<const char*>(&pixel.r), 1);
    }

    // Close the output file stream
    SeanParrell6.close();
}

TGA* TGA::multiply(TGA& SeanParrell8) {
    // Create a new TGA object for storing multiplication results
    TGA* SeanParrell9 = new TGA();
    SeanParrell9->header = header;

    // Iterate over each pixel for multiplication on RGB channels
    for (unsigned int SeanParrell10 = 0; SeanParrell10 < pixelData.size(); ++SeanParrell10) {
        // Set up a temporary pixel to store blended values
        Pixel SeanParrell11;

        // Red channel multiplication and assignment
        SeanParrell11.r = static_cast<unsigned char>((static_cast<int>(pixelData[SeanParrell10].r) * static_cast<int>(SeanParrell8.pixelData[SeanParrell10].r) / 255.0f) + 0.5f);

        // Green channel multiplication and assignment
        SeanParrell11.g = static_cast<unsigned char>((static_cast<int>(pixelData[SeanParrell10].g) * static_cast<int>(SeanParrell8.pixelData[SeanParrell10].g) / 255.0f) + 0.5f);

        // Blue channel multiplication and assignment
        SeanParrell11.b = static_cast<unsigned char>((static_cast<int>(pixelData[SeanParrell10].b) * static_cast<int>(SeanParrell8.pixelData[SeanParrell10].b) / 255.0f) + 0.5f);

        // Append the processed pixel to the result image data
        SeanParrell9->pixelData.push_back(SeanParrell11);
    }

    // Return the completed result image pointer
    return SeanParrell9;
}


TGA* TGA::subtract(TGA& SeanParrell15) {
    // Initialize a new TGA object to hold the result
    TGA* SeanParrell16 = new TGA();
    SeanParrell16->header = header;

    // Loop through each pixel and apply subtraction operation per channel
    for (unsigned int SeanParrell17 = 0; SeanParrell17 < pixelData.size(); ++SeanParrell17) {
        Pixel SeanParrell18;

        // Red channel: conditional subtraction with clamping to zero
        SeanParrell18.r = (pixelData[SeanParrell17].r > SeanParrell15.pixelData[SeanParrell17].r)
            ? 0
            : static_cast<unsigned char>(SeanParrell15.pixelData[SeanParrell17].r - pixelData[SeanParrell17].r);

        // Green channel: conditional subtraction with clamping to zero
        SeanParrell18.g = (pixelData[SeanParrell17].g > SeanParrell15.pixelData[SeanParrell17].g)
            ? 0
            : static_cast<unsigned char>(SeanParrell15.pixelData[SeanParrell17].g - pixelData[SeanParrell17].g);

        // Blue channel: conditional subtraction with clamping to zero
        SeanParrell18.b = (pixelData[SeanParrell17].b > SeanParrell15.pixelData[SeanParrell17].b)
            ? 0
            : static_cast<unsigned char>(SeanParrell15.pixelData[SeanParrell17].b - pixelData[SeanParrell17].b);

        // Store the computed pixel in the result image
        SeanParrell16->pixelData.push_back(SeanParrell18);
    }

    // Return the pointer to the resulting image after subtraction
    return SeanParrell16;
}


TGA* TGA::screen(TGA& SeanParrell22) {
    // Allocate a new TGA object for the result of the screen blend
    TGA* SeanParrell23 = new TGA();
    SeanParrell23->header = header;

    // Iterate through each pixel to apply screen blend on RGB channels
    for (unsigned int SeanParrell24 = 0; SeanParrell24 < pixelData.size(); ++SeanParrell24) {
        Pixel SeanParrell25;

        // Process each channel (r, g, b) using the screen formula
        SeanParrell25.r = static_cast<unsigned char>(255 - ((255 - pixelData[SeanParrell24].r) * (255 - SeanParrell22.pixelData[SeanParrell24].r) / 255.0f) + 0.5f);
        SeanParrell25.g = static_cast<unsigned char>(255 - ((255 - pixelData[SeanParrell24].g) * (255 - SeanParrell22.pixelData[SeanParrell24].g) / 255.0f) + 0.5f);
        SeanParrell25.b = static_cast<unsigned char>(255 - ((255 - pixelData[SeanParrell24].b) * (255 - SeanParrell22.pixelData[SeanParrell24].b) / 255.0f) + 0.5f);

        // Add the computed pixel to the result image's data
        SeanParrell23->pixelData.push_back(SeanParrell25);
    }

    // Return the pointer to the resulting image after applying screen blend
    return SeanParrell23;
}


TGA* TGA::overlay(TGA& SeanParrell30) {
    // Create a new TGA object to store the overlay result
    TGA* SeanParrell31 = new TGA();
    SeanParrell31->header = header;

    // Loop through each pixel for overlay blending on each color channel
    for (unsigned int SeanParrell32 = 0; SeanParrell32 < pixelData.size(); ++SeanParrell32) {
        Pixel SeanParrell33;

        // Apply overlay formula to each channel (r, g, b)
        SeanParrell33.r = (SeanParrell30.pixelData[SeanParrell32].r <= 127)
            ? static_cast<unsigned char>(2 * (pixelData[SeanParrell32].r * SeanParrell30.pixelData[SeanParrell32].r / 255.0f) + 0.5f)
            : static_cast<unsigned char>(255 - 2 * ((255 - pixelData[SeanParrell32].r) * (255 - SeanParrell30.pixelData[SeanParrell32].r) / 255.0f) + 0.5f);

        SeanParrell33.g = (SeanParrell30.pixelData[SeanParrell32].g <= 127)
            ? static_cast<unsigned char>(2 * (pixelData[SeanParrell32].g * SeanParrell30.pixelData[SeanParrell32].g / 255.0f) + 0.5f)
            : static_cast<unsigned char>(255 - 2 * ((255 - pixelData[SeanParrell32].g) * (255 - SeanParrell30.pixelData[SeanParrell32].g) / 255.0f) + 0.5f);

        SeanParrell33.b = (SeanParrell30.pixelData[SeanParrell32].b <= 127)
            ? static_cast<unsigned char>(2 * (pixelData[SeanParrell32].b * SeanParrell30.pixelData[SeanParrell32].b / 255.0f) + 0.5f)
            : static_cast<unsigned char>(255 - 2 * ((255 - pixelData[SeanParrell32].b) * (255 - SeanParrell30.pixelData[SeanParrell32].b) / 255.0f) + 0.5f);

        // Add the computed pixel to the result image's pixel data
        SeanParrell31->pixelData.push_back(SeanParrell33);
    }

    // Return the pointer to the resulting image after overlay operation
    return SeanParrell31;
}


TGA* TGA::addGreen(int SeanParrell38) {
    // Initialize a new TGA object for the modified result
    TGA* SeanParrell39 = new TGA();
    SeanParrell39->header = header;

    // Process each pixel, modifying only the green channel as specified
    for (unsigned int SeanParrell40 = 0; SeanParrell40 < pixelData.size(); ++SeanParrell40) {
        Pixel SeanParrell41;

        // Modify each channel based on whether it is green or not
        SeanParrell41.r = pixelData[SeanParrell40].r;
        SeanParrell41.g = static_cast<unsigned char>(min(255, (int)pixelData[SeanParrell40].g + SeanParrell38));
        SeanParrell41.b = pixelData[SeanParrell40].b;

        // Store the adjusted pixel in the result image's pixel data
        SeanParrell39->pixelData.push_back(SeanParrell41);
    }

    // Return the pointer to the resulting image with adjusted green values
    return SeanParrell39;
}


TGA* TGA::scaleRed(int SeanParrell44) {
    // Create a new TGA object for the scaled red channel result
    TGA* SeanParrell45 = new TGA();
    SeanParrell45->header = header;

    // Loop through each pixel and adjust channels
    for (unsigned int SeanParrell46 = 0; SeanParrell46 < pixelData.size(); ++SeanParrell46) {
        Pixel SeanParrell47;

        // Scale red channel, set blue to zero, and leave green unchanged
        SeanParrell47.r = static_cast<unsigned char>(min(255, pixelData[SeanParrell46].r * SeanParrell44));
        SeanParrell47.g = pixelData[SeanParrell46].g;
        SeanParrell47.b = 0;

        // Store the adjusted pixel in the result image data
        SeanParrell45->pixelData.push_back(SeanParrell47);
    }

    // Return the pointer to the resulting image with scaled red values
    return SeanParrell45;
}


TGA* TGA::combine(TGA& SeanParrell50, TGA& SeanParrell51, TGA& SeanParrell52) {
    // Create a new TGA object to store the combined result
    TGA* SeanParrell53 = new TGA();
    SeanParrell53->header = SeanParrell50.header;

    // Combine each channel from the respective images into a single pixel
    for (unsigned int SeanParrell54 = 0; SeanParrell54 < SeanParrell50.pixelData.size(); ++SeanParrell54) {
        unsigned char red = SeanParrell50.pixelData[SeanParrell54].r;
        unsigned char green = SeanParrell51.pixelData[SeanParrell54].g;
        unsigned char blue = SeanParrell52.pixelData[SeanParrell54].b;

        // Construct the pixel with channels from each image and add it to the result
        SeanParrell53->pixelData.emplace_back(Pixel(red, green, blue));
    }

    // Return the pointer to the newly created combined image
    return SeanParrell53;
}


TGA* TGA::rotate(TGA& SeanParrell55) {
    // Create a new TGA object for the rotated result
    TGA* SeanParrell56 = new TGA();
    SeanParrell56->header = SeanParrell55.header;

    // Rotate the image by reversing the pixel order
    size_t totalPixels = SeanParrell55.pixelData.size();
    for (size_t SeanParrell57 = 0; SeanParrell57 < totalPixels; ++SeanParrell57) {
        size_t reverseIndex = totalPixels - 1 - SeanParrell57;

        // Construct and insert the reversed pixel order into the result image
        SeanParrell56->pixelData.emplace_back(
            Pixel(SeanParrell55.pixelData[reverseIndex].r,
                SeanParrell55.pixelData[reverseIndex].g,
                SeanParrell55.pixelData[reverseIndex].b)
        );
    }

    // Return the pointer to the rotated image
    return SeanParrell56;
}


bool TGA::compare(TGA& SeanParrell58) {
    // Loop through each pixel to check if all RGB channels match
    for (size_t SeanParrell59 = 0; SeanParrell59 < pixelData.size(); ++SeanParrell59) {
        const Pixel& thisPixel = pixelData[SeanParrell59];
        const Pixel& otherPixel = SeanParrell58.pixelData[SeanParrell59];

        // Compare the RGB channels of each corresponding pixel
        if (thisPixel.r != otherPixel.r || thisPixel.g != otherPixel.g || thisPixel.b != otherPixel.b) {
            return false; // Return false if any channel differs
        }
    }

    // Return true if all pixels match in RGB values
    return true;
}

