#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>

Data::Data() = default;

Data::~Data() = default;

void Data::getData(DataStruct &dataStruct) {
    loadData(dataStruct, fileName);
    // std::cout << dataStruct.start << std::endl;
    // std::cout << dataStruct.end << std::endl;
    // std::cout << dataStruct.password << std::endl;
}

void Data::setData(DataStruct dataStruct) {
    try {
        // Save data to structure.
        std::cout << "Enter start time in format HHMM (24h): ";
        std::cin >> dataStruct.start;
        std::cout << "Enter end time in format HHMM (24h): ";
        std::cin >> dataStruct.end;
        std::cout << "Enter password: ";
        std::cin >> dataStruct.password;
        // Save data to the file.
        saveData(dataStruct, fileName);
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

std::string Data::getPassword(DataStruct &dataStruct) {
    return dataStruct.password;
}

/* Open the stream and save data from the structure to the file,
 * close the stream. */
void Data::saveData(DataStruct &dataStruct, const std::string &fileName) {

    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << '\n';
        return;
    }
    try {
        file.clear();   // Clear the file before saving new config.
        file.write(reinterpret_cast<const char*>(&dataStruct), sizeof(dataStruct));
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    file.close();
}

/* Open the stream and open a file with data,
 * save this data to the structure. */
void Data::loadData(DataStruct &dataStruct, const std::string &fileName) {

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << '\n';
        return;
    }
    try {
        file.read(reinterpret_cast<char*>(&dataStruct), sizeof(dataStruct));
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    file.close();
}