#pragma once

#include <vector>
#include <array>
#include <string>
#include "utils.h"

using Choices = std::vector<Step>;
using History = std::vector<Choices>;

class AbstractStorage{
public:
    [[nodiscard]] virtual Choices get_last_enemies_choices(unsigned int id) const;
    virtual void append_choices(Choices choices);
    virtual ~AbstractStorage()=default;
protected:
    AbstractStorage()=default;
private:
};

class Storage:public AbstractStorage{
public:
    Storage()=default;
    explicit Storage(const std::string& configs_path);

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] Choices get_last_enemies_choices(unsigned int id) const override;
    [[nodiscard]] unsigned int get_free_id();

    void append_choices(Choices choices) override;
private:
    unsigned int _ids_count;
    std::string _configs_path;
    History _history;
};
