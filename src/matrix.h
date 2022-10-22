#pragma once

#include <map>
#include "utils.h"

using Row = Triplet<int>;

class Matrix{
private:
    bool _has_error;
    mutable std::map<std::string, Row> _rows;

    std::string match_row(const std::string& line); // matches values of line and returns code of row

    [[nodiscard]] bool input(std::ifstream& ifstream); // inputs matrix from stream

    bool is_symmetric() const; // checks symmetry
public:
    explicit Matrix(const std::string& path); // path to matrix-file

    bool has_error() const; // Have errors occurred during initialization

    bool is_consistent() const; // Checks inequalities and symmetry

    const Row& get_row(const std::string& row_code) const; // receives "CCC", "CCD" ...

    const Row& get_row(const Triplet<Step>& row_code) const; // receives (C, C, C), ...

    int get_element(const std::string& row_code, unsigned int index_in_row) const; // get element of row
};
