#include <iostream>  // Required for input/output operations
#include <fstream>   // Required for file operations

#include "tga.h"     // Includes TGA image processing class

using namespace std;

int testsPassed = 0;  // Variable to keep track of successful tests

void test1();  // Declaration of test function for Task 1
void test2();  // Declaration of test function for Task 2
void test3();  // Declaration of test function for Task 3
void test4();  // Declaration of test function for Task 4
void test5();  // Declaration of test function for Task 5
void test6();  // Declaration of test function for Task 6
void test7();  // Declaration of test function for Task 7
void test8();  // Declaration of test function for Task 8
void test9();  // Declaration of test function for Task 9
void test10(); // Declaration of test function for Task 10

void displayResult(int testNumber, TGA& a, TGA& b);  // Function to display test results

int main()
{
	test1();  // Executes Task 1
	test2();  // Executes Task 2
	test3();  // Executes Task 3
	test4();  // Executes Task 4
	test5();  // Executes Task 5
	test6();  // Executes Task 6
	test7();  // Executes Task 7
	test8();  // Executes Task 8
	test9();  // Executes Task 9
	test10(); // Executes Task 10

	cout << "Test results: " << testsPassed << " / 10" << endl;  // Summary of test results

	return 0;
}

void test1() {
	TGA imageA;  // Declares TGA object for the first image
	TGA imageB;  // Declares TGA object for the second image
	TGA* imageC; // Pointer to store the result of the multiply operation


	imageA.read("input/layer1.tga");  // Reads the first image from file
	imageB.read("input/pattern1.tga");  // Reads the second image from file


	imageC = imageA.multiply(imageB);  // Multiplies the two images
	imageC->write("output/part1.tga");  // Writes the result to an output file
	delete imageC;  // Frees memory allocated for the result image


	TGA resultImage;  // Declares TGA object for the result image
	TGA exampleImage;  // Declares TGA object for the example image
	resultImage.read("output/part1.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part1.tga");  // Reads the example image for comparison
	displayResult(1, resultImage, exampleImage);  // Compares the two images and displays the result
}

void test2() {
	TGA imageA;  // Declares TGA object for the first image
	TGA imageB;  // Declares TGA object for the second image
	TGA* imageC; // Pointer to store the result of the subtract operation


	imageA.read("input/layer2.tga");  // Reads the first image from file
	imageB.read("input/car.tga");  // Reads the second image from file


	imageC = imageA.subtract(imageB);  // Subtracts the second image from the first
	imageC->write("output/part2.tga");  // Writes the result to an output file
	delete imageC;  // Frees memory allocated for the result image


	TGA resultImage;  // Declares TGA object for the result image
	TGA exampleImage;  // Declares TGA object for the example image
	resultImage.read("output/part2.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part2.tga");  // Reads the example image for comparison
	displayResult(2, resultImage, exampleImage);  // Compares the two images and displays the result
}

void test3() {
	TGA imageA;  // Declares TGA object for the first image
	TGA imageB;  // Declares TGA object for the second image
	TGA imageC;  // Declares TGA object for the third image
	TGA* resultImage;  // Pointer to store the result of the screen operation


	imageA.read("input/layer1.tga");  // Reads the first image from file
	imageB.read("input/pattern2.tga");  // Reads the second image from file
	imageC.read("input/text.tga");  // Reads the third image from file


	TGA* tmpImage = imageA.multiply(imageB);  // Multiplies the first two images
	resultImage = imageC.screen(*tmpImage);  // Screens the result with the third image
	resultImage->write("output/part3.tga");  // Writes the result to an output file
	delete tmpImage;  // Frees memory allocated for the temporary image
	delete resultImage;  // Frees memory allocated for the result image


	TGA output;  // Declares TGA object for the output image
	TGA exampleImage;  // Declares TGA object for the example image
	output.read("output/part3.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part3.tga");  // Reads the example image for comparison
	displayResult(3, output, exampleImage);  // Compares the two images and displays the result
}

void test4() {
	TGA imageA;  // Declares TGA object for the first image
	TGA imageB;  // Declares TGA object for the second image
	TGA imageC;  // Declares TGA object for the third image
	TGA* resultImage;  // Pointer to store the result of the subtract operation


	imageA.read("input/layer2.tga");  // Reads the first image from file
	imageB.read("input/circles.tga");  // Reads the second image from file
	imageC.read("input/pattern2.tga");  // Reads the third image from file


	TGA* tmpImage = imageA.multiply(imageB);  // Multiplies the first two images
	resultImage = imageC.subtract(*tmpImage);  // Subtracts the result from the third image
	resultImage->write("output/part4.tga");  // Writes the result to an output file
	delete tmpImage;  // Frees memory allocated for the temporary image
	delete resultImage;  // Frees memory allocated for the result image


	TGA output;  // Declares TGA object for the output image
	TGA exampleImage;  // Declares TGA object for the example image
	output.read("output/part4.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part4.tga");  // Reads the example image for comparison
	displayResult(4, output, exampleImage);  // Compares the two images and displays the result
}

void test5() {
	TGA imageA;  // Declares TGA object for the first image
	TGA imageB;  // Declares TGA object for the second image
	TGA* resultImage;  // Pointer to store the result of the overlay operation


	imageA.read("input/layer1.tga");  // Reads the first image from file
	imageB.read("input/pattern1.tga");  // Reads the second image from file


	resultImage = imageA.overlay(imageB);  // Applies the overlay operation
	resultImage->write("output/part5.tga");  // Writes the result to an output file
	delete resultImage;  // Frees memory allocated for the result image


	TGA output;  // Declares TGA object for the output image
	TGA exampleImage;  // Declares TGA object for the example image
	output.read("output/part5.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part5.tga");  // Reads the example image for comparison
	displayResult(5, output, exampleImage);  // Compares the two images and displays the result
}

void test6() {
	TGA imageA;  // Declares TGA object for the first image
	TGA* resultImage;  // Pointer to store the result of the addGreen operation


	imageA.read("input/car.tga");  // Reads the first image from file


	resultImage = imageA.addGreen(200);  // Adds green to the image
	resultImage->write("output/part6.tga");  // Writes the result to an output file
	delete resultImage;  // Frees memory allocated for the result image


	TGA output;  // Declares TGA object for the output image
	TGA exampleImage;  // Declares TGA object for the example image
	output.read("output/part6.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part6.tga");  // Reads the example image for comparison
	displayResult(6, output, exampleImage);  // Compares the two images and displays the result
}

void test7() {
	TGA imageA;  // Declares TGA object for the first image
	TGA* resultImage;  // Pointer to store the result of the scaleRed operation


	imageA.read("input/car.tga");  // Reads the first image from file


	resultImage = imageA.scaleRed(4);  // Scales the red in the image
	resultImage->write("output/part7.tga");  // Writes the result to an output file
	delete resultImage;  // Frees memory allocated for the result image


	TGA output;  // Declares TGA object for the output image
	TGA exampleImage;  // Declares TGA object for the example image
	output.read("output/part7.tga");  // Reads the generated result image
	exampleImage.read("examples/EXAMPLE_part7.tga");  // Reads the example image for comparison
	displayResult(7, output, exampleImage);  // Compares the two images and displays the result
}

void test8() {
	TGA imageA;  // Declares TGA object for the first image
	TGA imageR;  // Declares TGA object for the red channel image
	TGA imageG;  // Declares TGA object for the green channel image
	TGA imageB;  // Declares TGA object for the blue channel image


	imageA.read("input/car.tga");  // Reads the first image from file
	imageR.header = imageA.header;  // Copies header for red channel
	imageG.header = imageA.header;  // Copies header for green channel
	imageB.header = imageA.header;  // Copies header for blue channel


	for (unsigned int i = 0; i < imageA.pixelData.size(); ++i) {  // Loops through each pixel in the image
		unsigned char r = imageA.pixelData[i][0];  // Retrieves red component
		unsigned char g = imageA.pixelData[i][1];  // Retrieves green component
		unsigned char b = imageA.pixelData[i][2];  // Retrieves blue component

		imageR.pixelData.push_back(Pixel(r, r, r));  // Adds red component to red image
		imageG.pixelData.push_back(Pixel(g, g, g));  // Adds green component to green image
		imageB.pixelData.push_back(Pixel(b, b, b));  // Adds blue component to blue image
	}


	imageR.write("output/part8_r.tga");  // Writes the red channel image
	imageG.write("output/part8_g.tga");  // Writes the green channel image
	imageB.write("output/part8_b.tga");  // Writes the blue channel image


	TGA outputR, outputG, outputB;  // Declares TGA objects for output images
	TGA exampleR, exampleG, exampleB;  // Declares TGA objects for example images
	outputR.read("output/part8_r.tga");  // Reads the generated red channel image
	outputG.read("output/part8_g.tga");  // Reads the generated green channel image
	outputB.read("output/part8_b.tga");  // Reads the generated blue channel image
	exampleR.read("examples/EXAMPLE_part8_r.tga");  // Reads the example red channel image
	exampleG.read("examples/EXAMPLE_part8_g.tga");  // Reads the example green channel image
	exampleB.read("examples/EXAMPLE_part8_b.tga");  // Reads the example blue channel image

	if (outputR.compare(exampleR) &&  // Compares red channel images
		outputG.compare(exampleG)) {  // Compares green channel images
		displayResult(8, outputB, exampleB);  // Displays result for blue channel comparison
	}
	else {
		cout << "Test #8...... Failed!" << endl;  // Outputs failure message
	}
}

void test9() {
	TGA imageR, imageG, imageB;  // Declares TGA objects for the red, green, and blue channel images
	TGA* resultImage;  // Pointer to store the result of the combine operation


	imageR.read("input/layer_red.tga");  // Reads the red channel image
	imageG.read("input/layer_green.tga");  // Reads the green channel image
	imageB.read("input/layer_blue.tga");  // Reads the blue channel image


	resultImage = TGA::combine(imageR, imageG, imageB);  // Combines the RGB channels
	resultImage->write("output/part9.tga");  // Writes the result to an output file
	delete resultImage;  // Frees memory allocated for the result image


	TGA output, example;  // Declares TGA objects for output and example images
	output.read("output/part9.tga");  // Reads the generated result image
	example.read("examples/EXAMPLE_part9.tga");  // Reads the example image for comparison

	displayResult(9, output, example);  // Compares the two images and displays the result
}

void test10() {
	TGA imageA;  // Declares TGA object for the first image
	TGA* resultImage;  // Pointer to store the result of the rotate operation


	imageA.read("input/text2.tga");  // Reads the first image from file


	resultImage = TGA::rotate(imageA);  // Rotates the image
	resultImage->write("output/part10.tga");  // Writes the result to an output file
	delete resultImage;  // Frees memory allocated for the result image


	TGA output, example;  // Declares TGA objects for output and example images
	output.read("output/part10.tga");  // Reads the generated result image
	example.read("examples/EXAMPLE_part10.tga");  // Reads the example image for comparison
	displayResult(10, output, example);  // Compares the two images and displays the result
}

void displayResult(int testNumber, TGA& a, TGA& b) {
	cout << "Test #" << testNumber << "... ";  // Displays the test number
	if (a.compare(b)) {  // Compares the two images pixel by pixel
		testsPassed++;  // Increments the counter if the test passed
		cout << "Success!" << endl;  // Outputs success message
	}
	else {
		cout << "Fail!" << endl;  // Outputs failure message
	}
}