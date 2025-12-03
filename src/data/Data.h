#ifndef CPP_PARENTAL_CONTROLLER_DATA_H
#define CPP_PARENTAL_CONTROLLER_DATA_H

#include <string>

class Data {

public:
    Data();
    ~Data();

    inline static std::string fileName = "C:\\Users\\czuba\\CLionProjects\\cpp-parental-controller\\src\\data\\data.dat";

    struct DataStruct {
        float start;
        float end;
        char password[50];
    };

    static void getData(DataStruct &dataStruct);
    static void setData(DataStruct dataStruct);

    static std::string getPassword(DataStruct &dataStruct);
    static void showData(DataStruct &dataStruct);

    static bool readTime(const std::string &prompt, float& timeValue);

private:
    static void saveData(DataStruct& dataStruct, const std::string& fileName);
    static void loadData(DataStruct& dataStruct, const std::string& fileName);

};

#endif //CPP_PARENTAL_CONTROLLER_DATA_H