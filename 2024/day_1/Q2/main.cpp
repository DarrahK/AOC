#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric> 
#include <unordered_map>

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


std::unordered_map<int, int> create_frequency_map(std::vector<int> vec) {

    std::unordered_map<int, int> freq_map;
    for (int num : vec) {
        freq_map[num]++;
    }
    return freq_map;
}


int main(int argc, char* argv[]) {
    std::string file_name = "file.txt";
    auto parsed_output = read_and_parse_file(file_name);

    auto freq_map = create_frequency_map(parsed_output[1]);


    std::transform(parsed_output[0].begin(), parsed_output[0].end(), parsed_output[0].begin(), 
    [&freq_map](const int& key) { 
        auto it = freq_map.find(key);
        return (it != freq_map.end()) ? it->second * key : 0;
    });

    int similarity_score = std::accumulate(parsed_output[0].begin(), parsed_output[0].end(), 0);

    std::cout << similarity_score << std::endl;
}