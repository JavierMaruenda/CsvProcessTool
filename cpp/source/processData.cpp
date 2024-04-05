#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "../ext/Eigen/Dense"

using namespace std;
using namespace Eigen;

class dataset {
public:
    int numRows;
    string filename;
    vector<string> columnNames;
    map<string, VectorXd> dataMap;

public:
    dataset(const string& filename) : filename(filename), numRows(0) {
        // Debug: Print the file being read
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file: " << filename << endl;
            exit(EXIT_FAILURE);
        }

        // Read the first row containing column names
        string line;
        if (!getline(file, line)) {
            cerr << "Error: Empty file or unable to read column names from file: " << filename << endl;
            exit(EXIT_FAILURE);
        }
        columnNames = split(line, ',');

        // Count the number of rows
        while (getline(file, line)) {
            ++numRows;
        }
        file.clear();
        file.seekg(0); // Reset file pointer to the beginning
        getline(file, line); // skip first line

        // Initialize data storage
        dataMap.clear();
        for (size_t i = 0; i < columnNames.size(); ++i) {
            dataMap[columnNames[i]] = VectorXd::Zero(numRows); // Initialize with zero elements
        }

        // Read the rest of the data
        int currentRow = 0;
        while (getline(file, line)) {
            vector<string> tokens = split(line, ',');
            for (size_t i = 0; i < tokens.size(); ++i) {
                try {
                    double value = stod(tokens[i]);
                    dataMap[columnNames[i]][currentRow] = value;
                } catch (const invalid_argument& e) {
                    cerr << "Error: Invalid data format in file: " << filename << ", at row: " << currentRow + 1 << ", column: " << i + 1 << endl;
                    exit(EXIT_FAILURE);
                }
            }
            ++currentRow;
        }

        cerr << "Successfully read data from file: " << filename << endl;
    }

    void addVector(const string& newVectorName) {
        // Add new column name
        columnNames.push_back(newVectorName);
        // Add new data to dataMap
        dataMap[newVectorName] = VectorXd::Zero(numRows);
    }

    void saveToCSV(const string& newFilename) {
        // Generate path of destination fle
        string directory, baseFilename;
        // Get position of last "/"character in file name
        size_t lastSlash = filename.find_last_of("/");
        // Use position to split in directory and file name
        directory = filename.substr(0, lastSlash + 1);
        baseFilename = filename.substr(lastSlash + 1);
        // Create full file name
        string outputPath = directory + "processed/" + baseFilename;

        ofstream outFile(outputPath);
        if (!outFile.is_open()) {
            cerr << "Error: Unable to open file for writing: " << outputPath << endl;
            return;
        }

        // Write column names to the first row
        for (size_t i = 0; i < columnNames.size(); ++i) {
            outFile << columnNames[i];
            if (i != columnNames.size() - 1)
                outFile << ",";
        }
        outFile << endl;

        // Write data to subsequent rows
        int numRows = dataMap.begin()->second.size();
        for (int i = 0; i < numRows; ++i) {
            for (size_t j = 0; j < columnNames.size(); ++j) {
                outFile << dataMap[columnNames[j]][i];
                if (j != columnNames.size() - 1)
                    outFile << ",";
            }
            outFile << endl;
        }

        outFile.close();
        cerr << "Data saved" <<  endl;
    }

private:
    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    cerr << "Attempting to read data from file: " << filename << endl;
    dataset data(filename);
    data.addVector("test");
    data.dataMap["test"] = data.dataMap["chnA"] + data.dataMap["chnB"];
    data.saveToCSV(filename);

    return 0;
}
