#include <iostream>
#include <fstream>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <string>" << std::endl;
        return 1; // Return non-zero exit code to indicate error
    }

    // Extract filename and string from command-line arguments
    std::string filename = argv[1];
    std::string content = argv[2];

    // Open the file for writing
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return 1; // Return non-zero exit code to indicate error
    }

    // Write the string to the file
    file << content;

    // Close the file
    file.close();

    // Set file permissions to 777
    chmod(filename.c_str(), 0777);

    // Indicate success
    std::cout << "String successfully written to " << filename << std::endl;
    return 0; // Return zero exit code to indicate success
}
