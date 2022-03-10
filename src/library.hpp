#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#include <iostream>
#include <fstream>
#include <string>

typedef struct inputParameter{
        inputParameter(){
                inputPath = new char[300];      // input data path
                dataPath = new char[300];       // intermediate data path
                outputPath = new char[300];     // result data path
        }
        ~inputParameter(){
                delete[] inputPath;
                delete[] dataPath;
                delete[] outputPath;
        }

        void printInputParameter()
        {
                std::cout << "<Files>" << std::endl;
                std::cout << "input: " << inputPath << std::endl;
                std::cout << "intermediate: " << dataPath << std::endl;
                std::cout << "result: " << outputPath << std::endl;
        }

        char *inputPath;
        char *dataPath;
        char *outputPath;
}inputParameter;

void print_data(std::ofstream& out, int sid, std::string str);
bool readInputParameter(int argc, char*argv[], inputParameter *input);

#endif /* LIBRARY_HPP_ */
