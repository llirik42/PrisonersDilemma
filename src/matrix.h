#pragma once

#include <map>
#include "utils.h"

using Row = Score;

class Matrix{
public:
    explicit Matrix(const std::string& path); // path to matrix-file

    [[nodiscard]] bool has_error() const; // Have errors occurred during initialization

    [[nodiscard]] bool is_consistent() const; // Checks inequalities and symmetry

    [[nodiscard]] const Row& get_row(const std::string& row_code) const; // receives "CCC", "CCD" ...

    [[nodiscard]] const Row& get_row(const Triplet<Step>& row_code) const; // receives (C, C, C), ...

    [[nodiscard]] int get_element(const std::string& row_code, unsigned int index_in_row) const; // get element of row
private:
    bool _has_error;
    mutable std::map<std::string, Row> _rows;

    std::string match_row(const std::string& line); // matches values of line and returns code of row

    bool input(std::ifstream& ifstream); // inputs matrix from stream

    [[nodiscard]] bool is_symmetric() const; // checks symmetry
};
