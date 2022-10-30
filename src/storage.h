#pragma once

#include <vector>
#include <array>
#include <string>
#include <map>
#include "utils.h"
#include "strategies/abstract_strategy.h"

class AbstractStorage{
public:
    [[nodiscard]] virtual bool is_empty() const;
    [[nodiscard]] virtual Choices get_last_enemies_choices(const Strategy& strategy) const;
    [[nodiscard]] virtual History get_previous_games_history() const;

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
    [[nodiscard]] History get_previous_games_history() const override;

    void register_strategy(const Strategy& strategy);
    void register_strateg(const Strategy& strategy);
    void append_choices(const Choices& choices) override;

    ~Storage() override;
private:
    mutable std::map<Strategy, unsigned int> _ids;
    History _history_of_strateg; // History for StrategStrategy
    unsigned int _id_of_strateg;
    std::string _configs_path;
    unsigned int _ids_count;
    History _global_history;

    [[nodiscard]] Choices get_last_enemies_choices(unsigned int id) const;
};
