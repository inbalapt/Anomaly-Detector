
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;


class TimeSeries {
private:
    std::vector<std::pair<std::string, std::vector<float>>> tableVec;
    int numOfRows;
    int numOfCol;
public:

    TimeSeries(const char *CSVfileName) {

        // Reads a CSV file into a vector of <string, vector<int>> pairs where
        // each pair represents <column name, column values>

        // Create an input filestream
        std::ifstream myFile(CSVfileName);

        // Make sure the file is open
        if (!myFile.is_open()) throw std::runtime_error("Could not open file");

        // Helper vars
        std::string line, colname;
        float val;

        // Read the column names
        if (myFile.good()) {

            // Extract the first line in the file
            std::getline(myFile, line);

            // Create a stringstream from line
            std::stringstream ss(line);

            // Extract each column name
            while (std::getline(ss, colname, ',')) {
                // update the number of columns
                numOfCol = numOfCol + 1;
                // Initialize and add <colname, float vector> pairs to result
                tableVec.push_back({colname, std::vector<float>{}});
            }
        }

        // Read data, line by line
        while (std::getline(myFile, line)) {
            // update the number of rows
            numOfRows = numOfRows + 1;
            // Create a stringstream of the current line
            std::stringstream ss(line);

            // Keep track of the current column index
            int colIdx = 0;

            // Extract each integer
            while (ss >> val) {

                // Add the current integer to the 'colIdx' column's values vector
                tableVec.at(colIdx).second.push_back(val);

                // If the next token is a comma, ignore it and move on
                if (ss.peek() == ',') ss.ignore();

                // Increment the column index
                colIdx++;
            }
        }

        // Close file
        myFile.close();

    }

    std::vector<std::pair<std::string, std::vector<float>>> getVector() const;

    int getNumOfCol() const;
    int getNumOfRows() const;
    std::vector<float> get_feature_by_string(string str) const;

};


#endif /* TIMESERIES_H_ */