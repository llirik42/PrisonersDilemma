#pragma once

#include <array>
#include <map>

inline const unsigned int ELEMENTS_IN_ROW_COUNT = 3; // 3 values in each row

using Row = std::array<int, ELEMENTS_IN_ROW_COUNT>;

class Matrix{
private:
    bool _has_error;
    mutable std::map<std::string, Row> _rows;

    void match_row(const std::string& line); // matcher values of line

    [[nodiscard]] bool input(std::ifstream& ifstream); // inputs matrix from stream

    bool is_symmetric() const; // checks symmetry
public:
    explicit Matrix(const std::string& path); // path to matrix-file

    bool has_error() const; // Have errors occurred during initialization

    bool is_consistent() const; // Checks inequalities and symmetry

    const Row& get_row(const std::string& row_code) const; // receives "CCC", "CCD" ...

    int get_element(const std::string& row_code, unsigned int index_in_row) const; // get element of row
};
