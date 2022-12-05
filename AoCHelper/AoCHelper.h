#ifndef AOCHELPER_H
#define AOCHELPER_H

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include "helper_functions.h"

class AoCHelper
{
public:
    AoCHelper(std::string year, std::string day);
    std::vector<std::string> get_input();

private:
    std::string current_year;
    std::string current_day;
    std::vector<std::string> download_input();
    bool file_exists(const std::string &filename);
    std::string get_token();
};

#endif