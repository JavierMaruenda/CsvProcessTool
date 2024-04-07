#include <iostream>
#include <fstream>
#include <sstream>

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for reading." << std::endl;
        return ""; // Return an empty string to indicate error
    }

    std::ostringstream content;
    content << file.rdbuf(); // Read the entire file into the stringstream

    return content.str();
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; // Return non-zero exit code to indicate error
    }

    // Extract filename from command-line arguments
    std::string filename = argv[1];

    // Read the file content into a string
    std::string fileContent = readFileToString(filename);
    if (fileContent.empty()) {
        return 1; // Return non-zero exit code to indicate error
    }

    // Print the file content
    std::cout << fileContent << std::endl;

    return 0; // Return zero exit code to indicate success
}

