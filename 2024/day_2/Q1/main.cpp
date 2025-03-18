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
    std::vector<std::vector<int> > output;
    while (std::getline(input_file, line)) {
        std::vector<int> inner_vec;
        std::stringstream ss(line);
        int value;
    
        while (ss >> value) {
            inner_vec.push_back(value);
        }
        output.push_back(inner_vec);
    }

    input_file.close();

    return output;
}


int main(int argc, char* argv[]) {
    std::string file_name = "file.txt";
    auto parsed_output = read_and_parse_file(file_name);


    std::vector<int> vals;
    vals.reserve(parsed_output.size());
    std::transform(parsed_output.begin(), parsed_output.end(), std::back_inserter(vals),
        [](const std::vector<int>& inner_vec) {
            bool valid = true, increasing = true, decreasing = true;

            for (size_t i = 0; i < inner_vec.size() - 1; ++i) {
                int diff = std::abs(inner_vec[i] - inner_vec[i + 1]);
                valid &= (diff > 0) && (diff < 4);

                if (inner_vec[i + 1] <= inner_vec[i]) increasing = false;
                if (inner_vec[i + 1] >= inner_vec[i]) decreasing = false;
            }

            return (valid && (increasing || decreasing)) ? 1 : 0;
        });

    int number_of_safe = std::accumulate(vals.begin(), vals.end(), 0);

    std::cout << number_of_safe << std::endl;
}