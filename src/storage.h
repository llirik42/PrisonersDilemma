#pragma once

#include <vector>
#include <array>
#include "utils.h"

using EnemiesChoice = std::array<Step, 2>;
using History = std::vector<EnemiesChoice>;

class AbstractStorage{
public:
    [[nodiscard]] virtual EnemiesChoice get_last_enemies_choice() const;
    virtual void append_enemies_choice(EnemiesChoice choice);
    virtual ~AbstractStorage();
protected:
    AbstractStorage();
private:
};

class FileStorage: public AbstractStorage{
public:
    bool is_empty();
    [[nodiscard]] EnemiesChoice get_last_enemies_choice() const override;
    void append_enemies_choice(EnemiesChoice choice) override;
private:
    History _history;
};
