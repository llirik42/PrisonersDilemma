#pragma once

#include <map>
#include <string>
#include "utils.h"

using Row = Score;
using MatrixContent = std::map<std::string, Row>; // Rows of matrix

class Matrix{
public:
    Matrix(); // Creates default matrix

    explicit Matrix(const std::string& path);

    [[nodiscard]] bool has_error() const; // Have errors occurred during initialization

    [[nodiscard]] bool is_consistent() const; // Checks inequalities and symmetry

    [[nodiscard]] const Row& get_row(const std::string& row_code) const; // receives "CCC", "CCD" ...

    [[nodiscard]] const Row& operator[] (const Choices& choices) const;

    [[nodiscard]] int get_element(const std::string& row_code, unsigned int index_in_row) const; // get element of row
private:
    bool _has_error;
    mutable MatrixContent _content;

    std::string match_row(const std::string& line); // matches values of line and returns code of row

    bool input(std::ifstream& ifstream); // inputs matrix from stream

    [[nodiscard]] bool is_symmetric() const; // checks symmetry
};
