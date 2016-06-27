#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "zbar/zbar.h"

using namespace std;

int main(int argc, char *argv[]) {

    cv::VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened()) {  // check if we succeeded
        std::cout << "Failed to open input video: " << argv[1];
        return -1;
    }

    //cv::Mat img = cv::imread("/home/busta/git/zbar-code/examples/barcode.png");

    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    for(;;) {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        if (frame.empty())
            break;

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // wrap image data
        zbar::Image image(gray.cols, gray.rows, "Y800", gray.data, gray.rows * gray.cols);

        double t = (double) cv::getTickCount();
        // scan the image for barcodes
        int n = scanner.scan(image);
        t = ((double) cv::getTickCount() - t)/ cv::getTickFrequency();
        // extract results
        for(zbar::Image::SymbolIterator symbol = image.symbol_begin();
            symbol != image.symbol_end(); ++symbol) {
            // do something useful with results
            cout << "decoded " << symbol->get_type_name()
            << " symbol \"" << symbol->get_data() << '"' << " in " << t * 1000 << "ms"  << endl;
        }

        cv::imshow("frame", frame);
        int key = cv::waitKey(1);
        if(key == 'q')
            break;
    }

    return 0;
}