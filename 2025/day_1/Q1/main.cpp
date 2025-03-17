#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric> 

std::vector<std::vector<int> > read_and_parse_file(std::string file_name) {

    std::ifstream input_file(file_name);

    if (!input_file) {
        std::cerr << "Unable to open file!" << std::endl;
        std::exit(1);
    }

    std::string line;
    std::vector<std::vector<int> > output(2);
    while (std::getline(input_file, line)) {
        std::stringstream ss(line);
        std::string word;
    
        for (auto& inner_vec: output) {
            ss >> word;
            inner_vec.push_back(std::stoi(word));
        }
    }

    input_file.close();

    return output;
}


int main(int argc, char* argv[]) {
    std::string file_name = "file.txt";
    auto parsed_output = read_and_parse_file(file_name);

    for (auto& inner_vec : parsed_output) {
        std::sort(inner_vec.begin(), inner_vec.end());
    }

    std::vector<int> abs_diff(parsed_output[0].size());
    std::transform(parsed_output[0].begin(), parsed_output[0].end(), parsed_output[1].begin(), abs_diff.begin(), 
    [](int a, int b) { return std::abs(a - b); });

    int sum_abs_diff = std::accumulate(abs_diff.begin(), abs_diff.end(), 0);

    std::cout << sum_abs_diff << std::endl;
}