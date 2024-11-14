#include <iostream>
#include <fstream>
#include "tga.h"

using namespace std;

int SeanParrell1 = 0;

void SeanParrell8(); void SeanParrell3(); void SeanParrell10(); void SeanParrell5(); 
void SeanParrell2(); void SeanParrell7(); void SeanParrell4(); void SeanParrell9(); 
void SeanParrell11(); void SeanParrell6();


void SeanParrell12(int SeanParrell13, TGA& SeanParrell14, TGA& SeanParrell15);

int main()
{
    SeanParrell2(); SeanParrell3(); SeanParrell4(); SeanParrell5();
    SeanParrell6(); SeanParrell7(); SeanParrell8(); SeanParrell9();
    SeanParrell10(); SeanParrell11();


    cout << "Test results: " << SeanParrell1 << " / 10" << endl;

    return 0;
}

void SeanParrell2() {
    // Initialize and load the pattern first for variety
    TGA SeanParrell15;
    SeanParrell15.read("input/pattern1.tga");

    // Declare and load the layer
    TGA SeanParrell14;
    SeanParrell14.read("input/layer1.tga");

    // Perform multiplication and write the result
    TGA* SeanParrell16 = SeanParrell14.multiply(SeanParrell15);
    SeanParrell16->write("output/part1.tga");

    // Cleanup dynamically allocated memory early
    delete SeanParrell16;

    // Validation check with re-ordered loading
    TGA SeanParrell18;
    SeanParrell18.read("examples/EXAMPLE_part1.tga");

    TGA SeanParrell17;
    SeanParrell17.read("output/part1.tga");

    // Perform validation
    SeanParrell12(1, SeanParrell17, SeanParrell18);
}


void SeanParrell3() {
    // Begin by loading car image for subtraction
    TGA SeanParrell15;
    SeanParrell15.read("input/car.tga");

    // Initialize and load the second layer image
    TGA SeanParrell14;
    SeanParrell14.read("input/layer2.tga");

    // Apply subtraction between layer and car, then save the result
    TGA* SeanParrell16 = SeanParrell14.subtract(SeanParrell15);
    SeanParrell16->write("output/part2.tga");

    // Free dynamically allocated memory immediately after use
    delete SeanParrell16;

    // Prepare images for validation by loading expected and generated outputs
    TGA SeanParrell18;
    SeanParrell18.read("examples/EXAMPLE_part2.tga");

    TGA SeanParrell17;
    SeanParrell17.read("output/part2.tga");

    // Perform the validation check for Task 2
    SeanParrell12(2, SeanParrell17, SeanParrell18);
}


void SeanParrell4() {
    // Load the pattern first for blend preparation
    TGA SeanParrell15;
    SeanParrell15.read("input/pattern2.tga");

    // Load the primary layer and text image
    TGA SeanParrell14;
    SeanParrell14.read("input/layer1.tga");

    TGA SeanParrell16;
    SeanParrell16.read("input/text.tga");

    // Perform multiplication on layer and pattern, then apply screen with text
    TGA* SeanParrell18 = SeanParrell14.multiply(SeanParrell15);
    TGA* SeanParrell17 = SeanParrell16.screen(*SeanParrell18);
    SeanParrell17->write("output/part3.tga");

    // Clean up dynamic allocations to avoid memory leaks
    delete SeanParrell18;
    delete SeanParrell17;

    // Prepare for validation: load generated and example output
    TGA SeanParrell20;
    SeanParrell20.read("examples/EXAMPLE_part3.tga");

    TGA SeanParrell19;
    SeanParrell19.read("output/part3.tga");

    // Compare the output with the example for Task 3
    SeanParrell12(3, SeanParrell19, SeanParrell20);
}


void SeanParrell5() {
    // Load the circles image first, essential for the multiply operation
    TGA SeanParrell15;
    SeanParrell15.read("input/circles.tga");

    // Load primary layer and pattern images
    TGA SeanParrell14;
    SeanParrell14.read("input/layer2.tga");

    TGA SeanParrell16;
    SeanParrell16.read("input/pattern2.tga");

    // Apply multiply on layer and circles, then subtract from pattern
    TGA* SeanParrell18 = SeanParrell14.multiply(SeanParrell15);
    TGA* SeanParrell17 = SeanParrell16.subtract(*SeanParrell18);
    SeanParrell17->write("output/part4.tga");

    // Immediate cleanup of dynamically allocated memory
    delete SeanParrell18;
    delete SeanParrell17;

    // Load output and example images for the validation step
    TGA SeanParrell20;
    SeanParrell20.read("examples/EXAMPLE_part4.tga");

    TGA SeanParrell19;
    SeanParrell19.read("output/part4.tga");

    // Perform validation by comparing generated output to the example
    SeanParrell12(4, SeanParrell19, SeanParrell20);
}

void SeanParrell6() {
    // Begin by loading the pattern for overlay operation
    TGA SeanParrell15;
    SeanParrell15.read("input/pattern1.tga");

    // Load the primary layer image, which will be overlaid with the pattern
    TGA SeanParrell14;
    SeanParrell14.read("input/layer1.tga");

    // Perform the overlay operation and write to output file
    TGA* SeanParrell16 = SeanParrell14.overlay(SeanParrell15);
    SeanParrell16->write("output/part5.tga");

    // Free up the memory used for overlay result
    delete SeanParrell16;

    // Load both the generated and example images for validation
    TGA SeanParrell18;
    SeanParrell18.read("examples/EXAMPLE_part5.tga");

    TGA SeanParrell17;
    SeanParrell17.read("output/part5.tga");

    // Validate the result by comparing with the example output
    SeanParrell12(5, SeanParrell17, SeanParrell18);
}


void SeanParrell7() {
    // Load the car image as the base for green channel adjustment
    TGA SeanParrell14;
    SeanParrell14.read("input/car.tga");

    // Increase the green channel intensity and write the modified output
    TGA* SeanParrell15 = SeanParrell14.addGreen(200);
    SeanParrell15->write("output/part6.tga");

    // Release dynamically allocated memory immediately after use
    delete SeanParrell15;

    // Load the generated output and example images for comparison
    TGA SeanParrell17;
    SeanParrell17.read("examples/EXAMPLE_part6.tga");

    TGA SeanParrell16;
    SeanParrell16.read("output/part6.tga");

    // Execute validation to ensure the green adjustment matches the example
    SeanParrell12(6, SeanParrell16, SeanParrell17);
}


void SeanParrell8() {
    // Load the car image, which will have its red channel scaled
    TGA SeanParrell14;
    SeanParrell14.read("input/car.tga");

    // Amplify the red channel and write the modified image to output
    TGA* SeanParrell15 = SeanParrell14.scaleRed(4);
    SeanParrell15->write("output/part7.tga");

    // Clean up the allocated memory used for red channel scaling
    delete SeanParrell15;

    // Load both the output and example images to prepare for validation
    TGA SeanParrell17;
    SeanParrell17.read("examples/EXAMPLE_part7.tga");

    TGA SeanParrell16;
    SeanParrell16.read("output/part7.tga");

    // Perform validation to confirm the red scaling matches the example
    SeanParrell12(7, SeanParrell16, SeanParrell17);
}


void SeanParrell9() {
    // Load the car image as the base for channel separation
    TGA SeanParrell14;
    SeanParrell14.read("input/car.tga");

    // Initialize the headers for the red and green channel images
    TGA SeanParrell15;
    SeanParrell15.header = SeanParrell14.header;

    TGA SeanParrell16;
    SeanParrell16.header = SeanParrell14.header;

    // Extract red and green channels and store them as grayscale images
    for (unsigned int i = 0; i < SeanParrell14.pixelData.size(); ++i) {
        unsigned char r = SeanParrell14.pixelData[i][0];
        unsigned char g = SeanParrell14.pixelData[i][1];

        SeanParrell15.pixelData.push_back(Pixel(r, r, r)); // Red channel to grayscale
        SeanParrell16.pixelData.push_back(Pixel(g, g, g)); // Green channel to grayscale
    }

    // Write the separated red and green channels to output files
    SeanParrell15.write("output/part8_r.tga");
    SeanParrell16.write("output/part8_g.tga");

    // Load output and example images for validation of the red channel
    TGA SeanParrell18;
    SeanParrell18.read("examples/EXAMPLE_part8_r.tga");

    TGA SeanParrell17;
    SeanParrell17.read("output/part8_r.tga");

    // Compare the generated red channel image to the example
    if (SeanParrell17.compare(SeanParrell18)) {
        SeanParrell12(8, SeanParrell17, SeanParrell18);
    }
    else {
        cout << "Test #8...... Failed!" << endl;
    }
}


void SeanParrell10() {
    // Load the red, green, and blue layers for combination
    TGA SeanParrell14;
    SeanParrell14.read("input/layer_red.tga");

    TGA SeanParrell15;
    SeanParrell15.read("input/layer_green.tga");

    TGA SeanParrell16;
    SeanParrell16.read("input/layer_blue.tga");

    // Combine the RGB layers into a single output image
    TGA* SeanParrell17 = TGA::combine(SeanParrell14, SeanParrell15, SeanParrell16);
    SeanParrell17->write("output/part9.tga");

    // Clean up dynamic memory used for the combined image
    delete SeanParrell17;

    // Load the generated and example images to validate the result
    TGA SeanParrell19;
    SeanParrell19.read("examples/EXAMPLE_part9.tga");

    TGA SeanParrell18;
    SeanParrell18.read("output/part9.tga");

    // Compare the combined image with the example output for validation
    SeanParrell12(9, SeanParrell18, SeanParrell19);
}

void SeanParrell11() {
    // Load the text image for rotation processing
    TGA SeanParrell14;
    SeanParrell14.read("input/text2.tga");

    // Rotate the loaded image and save the result to output
    TGA* SeanParrell15 = TGA::rotate(SeanParrell14);
    SeanParrell15->write("output/part10.tga");

    // Clean up memory allocated for the rotated image
    delete SeanParrell15;

    // Load the generated output and example images for validation
    TGA SeanParrell17;
    SeanParrell17.read("examples/EXAMPLE_part10.tga");

    TGA SeanParrell16;
    SeanParrell16.read("output/part10.tga");

    // Validate by comparing the rotated image to the example
    SeanParrell12(10, SeanParrell16, SeanParrell17);
}


void SeanParrell12(int SeanParrell13, TGA& SeanParrell14, TGA& SeanParrell15) {
    // Display the test number for tracking
    cout << "Executing Test #" << SeanParrell13 << "... ";

    // Compare the two images and report the outcome
    if (SeanParrell14.compare(SeanParrell15)) {
        SeanParrell1++; // Increment success counter
        cout << "Test Passed!" << endl;
    }
    else {
        cout << "Test Failed!" << endl;
    }
}
