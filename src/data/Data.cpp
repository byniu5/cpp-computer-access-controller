#include "Data.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
#include <windows.h>

Data::Data() = default;

Data::~Data() = default;

void Data::getData(DataStruct &dataStruct) {
    loadData(dataStruct, getFileName());

}

// Save data to structure
void Data::setData(DataStruct dataStruct) {

        do {
        // Start time
        readTime("Enter START time in format HHMM (24h): ", dataStruct.start);
        // End time
        readTime("Enter END time in format HHMM (24h): ", dataStruct.end);
        } while (dataStruct.start >= dataStruct.end);


        // Password
        std::cout << "Enter password: ";
        std::cin >> std::setw(sizeof(dataStruct.password)) >> dataStruct.password;
        // Save data to the file.
        saveData(dataStruct, getFileName());
}

std::string Data::getPassword(DataStruct &dataStruct) {
    return dataStruct.password;
}

void Data::showData(DataStruct &dataStruct) {
    std::cout << "Start: " << dataStruct.start << std::endl;
    std::cout << "End: " << dataStruct.end << std::endl;
    std::cout << "Password: " << dataStruct.password << std::endl;
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

// Check if the input contains only digits.
auto isNumber = [](const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
};

// Function to validate the start and end time inputs.
bool Data::readTime(const std::string &prompt, float& timeValue) {
    while (true) {

        std::cout << prompt;

        std::string input;
        std::cin >> input;

        // Check if the input contains ONLY digits
        if (isNumber(input)) {
            // Input was a number, now Convert to int safely
            int time = std::stoi(input);

            // Check logical range
            if (time >= 0 && time <= 2359) {

                // Valid! SAVE value. Remove the leftover 'Enter' key. Return true.
                timeValue = static_cast<float>(time);
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;

            }
        }
        // If we get here, it was either not a number OR a number was out of range.
        std::cout << "Invalid time format. Please enter time in HHMM format (0000-2359).\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Find the data.dat file according to the path of the executable file.
std::string Data::getFileName() {
        // 1. Get the full path to the currently running executable
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::filesystem::path exePath(buffer);
        std::filesystem::path exeDirectory = exePath.parent_path();

        // 2. Define potential paths for data.dat
        std::filesystem::path pathSameDir = exeDirectory / "data.dat";
        std::filesystem::path pathParentDir = exeDirectory.parent_path() / "data.dat"; // ../data.dat (Project Root)

        // 3. Check where the file actually exists
        if (std::filesystem::exists(pathSameDir)) {
            return pathSameDir.string();
        }
        if (std::filesystem::exists(pathParentDir)) {
            return pathParentDir.string();
        }

        // 4. Fallback: If creating a NEW file, use the exe directory (keeps it self-contained)
        // Or use pathParentDir.string() if you prefer it in the project root.
        return pathParentDir.string();
    }