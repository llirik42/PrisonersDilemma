#pragma once

#include <vector>
#include <array>
#include <string>
#include <map>
#include "utils.h"
#include "strategies/abstract_strategy.h"

using History = std::vector<Choices>;

class AbstractStorage{
public:
    [[nodiscard]] virtual bool is_empty() const;
    [[nodiscard]] virtual Choices get_last_enemies_choices(const Strategy& strategy) const;
    [[nodiscard]] virtual unsigned int get_free_id();

    virtual void append_choices(const Choices& choices);

    virtual ~AbstractStorage()=default;
protected:
    AbstractStorage()=default;
private:
};

class Storage:public AbstractStorage{
public:
    Storage()=default;
    explicit Storage(const std::string& configs_path);

    [[nodiscard]] bool is_empty() const override;
    [[nodiscard]] Choices get_last_enemies_choices(const Strategy& strategy) const override;

    void register_strategy(const Strategy& strategy);
    void append_choices(const Choices& choices) override;
private:
    mutable std::map<Strategy, unsigned int> _ids;
    std::string _configs_path;
    unsigned int _ids_count;
    History _history;
};
