/*
 * timeseries.h
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdexcept>

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;


class TimeSeries {
private:
    std::vector<std::pair<std::string, std::vector<float>>> tableVec;
public:
    /*
     * Reads a CSV file into a vector of <string, vector<float>> pairs where
     * each pair represents <column name, column values>.
     */
    TimeSeries(const char *CSVfileName) {
        // Create an input filestream
        std::ifstream myFile(CSVfileName);
        // Make sure the file is open
        if (!myFile.is_open()) throw std::runtime_error("");
        // Helper vars
        std::string line, columnName;
        float val = 0;
        // Read the column names
        if (myFile.good()) {
            // Extract the first line in the file
            std::getline(myFile, line);
            // Create a string stream from line
            std::stringstream ss(line);
            // Extract each column name
            while (std::getline(ss, columnName, ',')) {
                // Initialize and add <columnName, float vector> pairs to result
                tableVec.push_back({columnName, std::vector<float>{}});
            }
        }

        // Read data, line by line
        while (std::getline(myFile, line)) {
            // Create a string stream of the current line
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

    /*
     * getter of the tableVec
     */
    std::vector<std::pair<std::string, std::vector<float>>> getVector() const;

    /*
     * this function returns the number of columns in the table.
     */
    int getNumOfCol() const;

    /*
     * this function returns the number of the features.
     */
    int getNumOfRows() const;

    /*
     * this function gets a name of feature and returns its values.
     */
    std::vector<float> get_feature_by_string(string str) const;

};


#endif /* TIMESERIES_H_ */