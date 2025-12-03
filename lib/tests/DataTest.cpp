#include <cstring>
#include <gtest/gtest.h>
#include "../../src/data/Data.h"

class DataTest : public ::testing::Test {

};

TEST(DataTest, SetDataRetutnsValidValues) {
    struct Data::DataStruct dataStruct;

    Data::getData(dataStruct);
    Data::showData(dataStruct);



    dataStruct.start = 2000;
    dataStruct.end = 1900;
    std::strcpy(dataStruct.password, "qwerty");

    // It requries user input that is not accessible in tests,
    // It is not right approach to ask for user input in setData file.
    //Data::setData(dataStruct);
    Data::getData(dataStruct);
    Data::showData(dataStruct);



    struct Data::DataStruct loadedStruct = {};
    Data::getData(loadedStruct);

    EXPECT_FLOAT_EQ(loadedStruct.start, 2000);
    EXPECT_FLOAT_EQ(loadedStruct.end, 1900);
    EXPECT_STREQ(loadedStruct.password, "qwerty");
}