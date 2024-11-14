#include <iostream>
#include <fstream>
#include "tga.h"

// Global variable to keep track of how many tests have passed
int passedTests = 0;

// Function declarations for each test case
void executeTestAlpha_SP();
void runTestBeta();
void runTestGamma();
void runTestDelta();
void runTestEpsilon();
void runTestZeta();
void runTestEta();
void runTestTheta();
void runTestIota();
void runTestKappa();

// Function to display the result of each test
void displayFinalResults(int testID, TGA& imgOne, TGA& imgTwo);

int main() {
    // Running all test cases one by one
    runTestAlpha();
    runTestBeta();
    runTestGamma();
    runTestDelta();
    runTestEpsilon();
    runTestZeta();
    runTestEta();
    runTestTheta();
    runTestIota();
    runTestKappa();

    // Display how many tests passed
    std::cout << "Summary: " << passedTests << " tests passed out of 10." << std::endl;
    return 0;
}

void runTestAlpha() {
    // Initialize two TGA images and a pointer for the blended result
    TGA MrRomeo, MsJulie;
    TGA* finalBlendedImage;

    // Load the images for blending
    MrRomeo.loadImage("input/layer1.tga");
    MsJulie.loadImage("input/pattern1.tga");

    // Multiply both images and save the result
    finalBlendedImage = MrRomeo.applyMultiply(MsJulie);
    finalBlendedImage->saveImage("output/scene1.tga");
    delete finalBlendedImage;  // Free memory

    // Load the generated result and the reference image for comparison
    TGA resultScene, referenceScene;
    resultScene.loadImage("output/scene1.tga");
    referenceScene.loadImage("examples/EXAMPLE_part1.tga");

    // Display whether the test passed or failed
    displayFinalResults(1, resultScene, referenceScene);
}

void runTestBeta() {
    // Initialize images for subtraction
    TGA bgLayer, carLayer;
    TGA* subtractionResult;

    // Load the background and car images
    bgLayer.loadImage("input/layer2.tga");
    carLayer.loadImage("input/car.tga");

    // Subtract car from background and save result
    subtractionResult = bgLayer.applySubtract(carLayer);
    subtractionResult->saveImage("output/scene2.tga");
    delete subtractionResult;  // Free memory

    // Compare generated output with expected output
    TGA outcomeScene, expectedScene;
    outcomeScene.loadImage("output/scene2.tga");
    expectedScene.loadImage("examples/EXAMPLE_part2.tga");

    // Display test result
    displayFinalResults(2, outcomeScene, expectedScene);
}

void runTestGamma() {
    // Initialize images for a blend operation
    TGA Sean, Is, Cool;
    TGA* blendedImage;

    // Load three images for blending operations
    Sean.loadImage("input/layer1.tga");
    Is.loadImage("input/pattern2.tga");
    Cool.loadImage("input/text.tga");

    // Multiply and screen the images
    TGA* tempImage = Sean.applyMultiply(Is);
    blendedImage = Cool.applyScreen(*tempImage);
    blendedImage->saveImage("output/scene3.tga");
    delete tempImage;
    delete blendedImage;  // Free memory

    // Compare the final output with the reference
    TGA finalOutput, exampleScene;
    finalOutput.loadImage("output/scene3.tga");
    exampleScene.loadImage("examples/EXAMPLE_part3.tga");

    // Display test result
    displayFinalResults(3, finalOutput, exampleScene);
}

void runTestDelta() {
    // Initialize two images for a blend operation
    TGA Mustang, FordGT, result;

    // Load images for blending
    Mustang.loadImage("input/layer2.tga");
    FordGT.loadImage("input/circles.tga");

    // Multiply the images and save the result
    TGA* tmpImage = Mustang.applyMultiply(FordGT);
    result = *tmpImage;
    result.saveImage("output/scene4.tga");
    delete tmpImage;  // Free memory

    // Compare output with expected result
    TGA output, exampleImage;
    output.loadImage("output/scene4.tga");
    exampleImage.loadImage("examples/EXAMPLE_part4.tga");

    // Display test result
    displayFinalResults(4, output, exampleImage);
}

void runTestEpsilon() {
    // Initialize images for an overlay operation
    TGA SDP, pattern$;
    TGA* overlayResult;

    // Load the images for overlay
    SDP.loadImage("input/layer1.tga");
    pattern$.loadImage("input/pattern1.tga");

    // Apply the overlay and save the result
    overlayResult = SDP.applyOverlay(pattern$);
    overlayResult->saveImage("output/scene5.tga");
    delete overlayResult;  // Free memory

    // Compare the output with expected output
    TGA finalScene, expectedScene;
    finalScene.loadImage("output/scene5.tga");
    expectedScene.loadImage("examples/EXAMPLE_part5.tga");

    // Display test result
    displayFinalResults(5, finalScene, expectedScene);
}

void runTestZeta() {
    // Initialize image for green adjustment
    TGA carLayer;
    TGA* greenAdditionResult;

    // Load car image and adjust the green channel
    carLayer.loadImage("input/car.tga");
    greenAdditionResult = carLayer.adjustGreenChannel(200);
    greenAdditionResult->saveImage("output/scene6.tga");
    delete greenAdditionResult;  // Free memory

    // Compare the output with expected output
    TGA finalScene, exampleScene;
    finalScene.loadImage("output/scene6.tga");
    exampleScene.loadImage("examples/EXAMPLE_part6.tga");

    // Display test result
    displayFinalResults(6, finalScene, exampleScene);
}

void runTestEta() {
    // Initialize image for red scaling
    TGA Money;
    TGA* redScaledResult;

    // Load image and scale the red channel
    Money.loadImage("input/car.tga");
    redScaledResult = Money.scaleRedChannel(4);
    redScaledResult->saveImage("output/scene7.tga");
    delete redScaledResult;  // Free memory

    // Compare the output with expected output
    TGA outputScene, referenceScene;
    outputScene.loadImage("output/scene7.tga");
    referenceScene.loadImage("examples/EXAMPLE_part7.tga");

    // Display test result
    displayFinalResults(7, outputScene, referenceScene);
}

void runTestTheta() {
    // Initialize image layers for color separation
    TGA carLayer, redChannel, greenChannel, blueChannel;

    // Load car image and separate RGB channels
    carLayer.loadImage("input/car.tga");
    redChannel.header = carLayer.header;
    greenChannel.header = carLayer.header;
    blueChannel.header = carLayer.header;

    for (unsigned int i = 0; i < carLayer.pixelData.size(); ++i) {
        unsigned char r = carLayer.pixelData[i].r;
        unsigned char g = carLayer.pixelData[i].g;
        unsigned char b = carLayer.pixelData[i].b;

        // Create red, green, and blue channel images
        redChannel.pixelData.push_back(Pixel(r, r, r));
        greenChannel.pixelData.push_back(Pixel(g, g, g));
        blueChannel.pixelData.push_back(Pixel(b, b, b));
    }

    // Save individual channels as separate files
    redChannel.saveImage("output/scene8_r.tga");
    greenChannel.saveImage("output/scene8_g.tga");
    blueChannel.saveImage("output/scene8_b.tga");

    // Compare results with reference files
    TGA finalR, finalG, finalB, exampleR, exampleG, exampleB;
    finalR.loadImage("output/scene8_r.tga");
    finalG.loadImage("output/scene8_g.tga");
    finalB.loadImage("output/scene8_b.tga");

    exampleR.loadImage("examples/EXAMPLE_part8_r.tga");
    exampleG.loadImage("examples/EXAMPLE_part8_g.tga");
    exampleB.loadImage("examples/EXAMPLE_part8_b.tga");

    if (finalR.compare(exampleR) && finalG.compare(exampleG) && finalB.compare(exampleB)) {
        passedTests++;  // Test passed
        std::cout << "Success in test 8!" << std::endl;
    }
    else {
        std::cout << "Failed test 8!" << std::endl;
    }
}

void runTestIota() {
    // Initialize three image layers for combining
    TGA redLayer, greenLayer, blueLayer;
    TGA* combinedImage;

    // Load RGB layers
    redLayer.loadImage("input/layer_red.tga");
    greenLayer.loadImage("input/layer_green.tga");
    blueLayer.loadImage("input/layer_blue.tga");

    // Combine the layers and save the result
    combinedImage = TGA::combine(redLayer, greenLayer, blueLayer);
    combinedImage->saveImage("output/scene9.tga");
    delete combinedImage;  // Free memory

    // Compare the output with expected result
    TGA finalScene, exampleScene;
    finalScene.loadImage("output/scene9.tga");
    exampleScene.loadImage("examples/EXAMPLE_part9.tga");

    // Display test result
    displayFinalResults(9, finalScene, exampleScene);
}

void runTestKappa() {
    // Initialize image for rotation
    TGA GTA;
    TGA* rotatedImage;

    // Load the image and apply rotation
    GTA.loadImage("input/text2.tga");
    rotatedImage = TGA::rotate(GTA);
    rotatedImage->saveImage("output/scene10.tga");
    delete rotatedImage;  // Free memory

    // Compare output with expected result
    TGA finalScene, exampleScene;
    finalScene.loadImage("output/scene10.tga");
    exampleScene.loadImage("examples/EXAMPLE_part10.tga");

    // Display test result
    displayFinalResults(10, finalScene, exampleScene);
}

// Function to compare two images and print success/failure message
void displayFinalResults(int testID, TGA& imgOne, TGA& imgTwo) {
    std::cout << "Evaluating test case #" << testID << " ... ";
    if (imgOne.compare(imgTwo)) {
        passedTests++;  // Test passed
        std::cout << "Success!" << std::endl;
    }
    else {
        std::cout << "Failed!" << std::endl;
    }
}
