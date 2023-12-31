// imageProc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//leaving lots of comments to myself given im not an image processing master xD
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Image {
    int width, height;
    int maxValue;
    unsigned char* pixels;//pixel data(rgb values)
};


Image readPPM(const char* filename) {

    std::ifstream file(filename, std::ios::binary);
        //A binary stream is an ordered sequence of characters that can transparently record internal data. Data read in from a binary stream always equal the data that were earlier written out to that stream, except that an implementation is allowed to append an indeterminate number of null characters to the end of the stream.// this basically opens the file as is instead of converting stuff into different stuff according to operating systems and such. such as, for instance, when a file is opened in text mode, newline sequences might be automatically converted from the windows \r\n to unix/linux \n format upon reading and vice-versa upon writing. when in binary mode, these translations are disables, THUS NO CONVERSIONS :)

        Image img;

        if (file.is_open()) {
            std::string line;//used to manipulate strings of characters

            std::getline(file, line);//read a line from file and store it in the line variable
            //P3 for ASCII, P6 for binary PPM

            if (line == "P6") {//assuming binary PPM format
                //skip comment lines if any
                std::getline(file, line);
                while (line[0] == '#') {//in many file formats, lines starting with '#' are often considered comments or metadata and are skipped during processing,
                    std::getline(file, line);
                }

                //read image dimensions -- >> is a stream extraction operator
                std::istringstream dimensions(line);
                dimensions >> img.width >> img.height;
                file >> img.maxValue;
                file.ignore();

                //read pixel data

                img.pixels = new unsigned char[img.width * img.height * 3];//dynamically allocates memory for an array of unsigned characters (unsigned char) and assigns the address of the allocated memory to the pointer img.pixels.
                file.read(reinterpret_cast<char*>(img.pixels), img.width * img.height * 3);
                //

            }
            else {
                std::cout << "Invalid PPM format. Only binary P6 format is supported.";
            }

            file.close();

        }
        else {
            std::cout << "Unable to open file: " << filename << std::endl;
        }

        return img;
};


int main()
{

    const char* filename = "C:/Users/olihb/Desktop/projects/imageProc/imgSrc/img1.ppm";

    Image image = readPPM(filename);

    if (image.pixels != nullptr) {
        std::cout << "Image width: " << image.width << std::endl;
        std::cout << "Image height: " << image.height << std::endl;
        std::cout << "Maximum color value: " << image.maxValue << std::endl;

        delete[] image.pixels;
    }

    return 0;

}

