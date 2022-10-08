#pragma once

#include <tuple>
#include <string>

using Row = std::tuple<int, int, int>;

class Matrix{
private:
    Row _rows[8];
    bool _has_error;
public:
    explicit Matrix(const std::string& path);

    [[nodiscard]] bool has_error() const; // Have errors occurred during initialization

    [[nodiscard]] bool is_consistent() const; // Checks inequalities

    [[nodiscard]] const Row& get_row(const std::string& string) const; // receives "CCC", "CCD" ...
};
