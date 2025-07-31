#ifndef CSV_NO_THREAD_H
#define CSV_NO_THREAD_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class CSVRow {
    std::vector<std::string> fields;

public:
    void parse_line(const std::string& line) {
        fields.clear();
        std::string field;
        std::istringstream ss(line);
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }
    }

    const std::string& operator[](std::size_t index) const {
        return fields[index];
    }

    std::size_t size() const {
        return fields.size();
    }
};

class CSVReader {
    std::ifstream file;

public:
    CSVReader(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file " + filename);
        }
    }

    bool read_row(CSVRow& out_row) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            out_row.parse_line(line);
            return true;
        }
        return false;
    }

    void close() {
        if (file.is_open()) file.close();
    }
};

#endif // CSV_NO_THREAD_H
