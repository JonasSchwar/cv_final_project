#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;


// this function removes fully black borders from images
Mat removeBlackBorder(Mat image) {
    Mat blackMask;
    Mat nonBlackMask;

    // detect fully black pixels = blackMask
    inRange(image, Scalar(0, 0, 0), Scalar(0, 0, 0), blackMask);

    // everything not black sved in nonBlackMask (inverted black mask)
    bitwise_not(blackMask, nonBlackMask); 

    // find all pixel positions that are not black
    vector<Point> points;
    findNonZero(nonBlackMask, points);

    // create smallest rectangle that contains all non black pixels = image without borders
    Rect box = boundingRect(points);  

    // cut out this box from original image and return that
    Mat cropped = image(box).clone(); 
    return cropped;
}


int main() {
    string inputFolder = "CV Final Project";
    string outputFolder = "CV Final Project/augmented_adapted";

    string folders[] = {"Bare soil", "Stones", "Vegetation"};

    for (string folderName : folders) {
        string inputPath = inputFolder + "/" + folderName;
        string outputPath = outputFolder + "/" + folderName;

        // create output folder
        fs::create_directories(outputPath);

        // iterate over every file in current folder (bare soil / stones / vegetation)
        for (auto file : fs::directory_iterator(inputPath)) {
            string filePath = file.path().string();
            string fileName = file.path().stem().string();  // filename without file extension as string

            Mat image = imread(filePath);

            if (image.empty()) {
                cout << "Can not read: " << filePath << endl;
                continue;
            }

            image = removeBlackBorder(image);  // remove black borders before processing

            // 1 save original image
            imwrite(outputPath + "/" + fileName + "_original.png", image);
            
            // 2 horizontally flip image
            Mat flipped;
            flip(image, flipped, 1);  // 1 for horizontal flip (0 = vertical, -1 both)
            imwrite(outputPath + "/" + fileName + "_flip.png", flipped);
            
            // 3 rotate image
            Mat rotated;
            Point2f center(image.cols / 2.0, image.rows / 2.0);  // calculate center the image should rotate around
            Mat rotationMatrix = getRotationMatrix2D(center, 15, 1.0);  // rotate by 15 degrees with scale = 1
            warpAffine(image, rotated, rotationMatrix, image.size(), INTER_LINEAR, BORDER_REFLECT_101);
            imwrite(outputPath + "/" + fileName + "_rotate.png", rotated);
            
            // 4 vertically flip image
            Mat flipped2;
            flip(image, flipped2, 0);  // 0 for vertical flip
            imwrite(outputPath + "/" + fileName + "_flip2.png", flipped2);
            
            // 5 vertically flip and crop image
            int flippedLeft = flipped2.cols * 0.1;  // 10% from the left
            int flippedTop = flipped2.rows * 0.1;  // 10% from the top
            int flippedWidth = flipped2.cols * 0.8;  // keep 80% of the width
            int flippedHeight = flipped2.rows * 0.8;  // keep 80% of the height
            
            Rect flippedCropArea(flippedLeft, flippedTop, flippedWidth, flippedHeight);
            Mat flippedCropped = flipped2(flippedCropArea);
            
            Mat flippedCroppedResized;
            resize(flippedCropped, flippedCroppedResized, flipped2.size());
            imwrite(outputPath + "/" + fileName + "_flip2_crop.png", flippedCroppedResized);
            
            // 6 blur image
            Mat blurred;
            GaussianBlur(image, blurred, Size(5, 5), 0);  // gaussian blur with a 5x5 filter
            imwrite(outputPath + "/" + fileName + "_blur.png", blurred);
            
            // 7 crop image and resize back
            int left = image.cols * 0.1;  // 10% from the left
            int top = image.rows * 0.1;  // 10% from the top
            int width = image.cols * 0.8;  // keep 80% of the width
            int height = image.rows * 0.8;  // keep 80% of the height
            
            Rect cropArea(left, top, width, height);
            Mat cropped = image(cropArea);
            
            Mat croppedResized;
            resize(cropped, croppedResized, image.size());
            imwrite(outputPath + "/" + fileName + "_crop.png", croppedResized);
            cout << "Done: " << fileName << endl;
        }
    }

    cout << "Everything augmented" << endl;
    return 0;
}
