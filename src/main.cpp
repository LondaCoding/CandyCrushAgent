#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>  // Include the Windows header for HDC and related functions

int main() {
    // Define the position of the pixel you want to capture
    int x = 100;  // X-coordinate
    int y = 100;  // Y-coordinate

    // Initialize OpenCV's display window
    cv::namedWindow("Pixel Color", cv::WINDOW_AUTOSIZE);

    while (true) {
        // Capture the screen content
        HDC hScreenDC = GetDC(NULL);
        COLORREF color = GetPixel(hScreenDC, x, y);
        ReleaseDC(NULL, hScreenDC);

        // Extract RGB values from the captured color
        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        // Display the pixel values on the console
        std::cout << "Pixel at (" << x << ", " << y << "): ";
        std::cout << "R=" << r << " G=" << g << " B=" << b << std::endl;

        // Create an image to display the pixel color
        cv::Mat pixelImage(100, 100, CV_8UC3, cv::Scalar(b, g, r));

        // Display the pixel color image using OpenCV
        cv::imshow("Pixel Color", pixelImage);

        // Break the loop if the user presses 'q'
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
