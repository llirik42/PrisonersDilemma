#include <fstream>
#include "storage.h"

inline const std::string STRATEGIC_DATA_FILE_NAME = "strategic_data";

void dump_strategic_data(unsigned int id_of_strateg, const std::string& configs_path, const History& history_of_strateg){
    if (id_of_strateg){
        std::ofstream ofstream(configs_path + STRATEGIC_DATA_FILE_NAME, std::ios::app);

        for (const auto& record: history_of_strateg){
            for (const auto& value: record){
                ofstream.put(value);
                ofstream.put(' ');
            }
            ofstream.put('\n');
        }
    }
}
void read_strategic_data(const std::string& configs_path, History& read_history){
    std::ifstream file_with_data(configs_path + STRATEGIC_DATA_FILE_NAME);

    if (!file_with_data.is_open()){
        return;
    }

    while (!file_with_data.eof()){
        std::string str;
        std::getline(file_with_data, str);

        if (!str.empty()){
            read_history.push_back({str[0], str[2]});
        }
    }
}

bool AbstractStorage::is_empty() const{
    return false;
}

Choices AbstractStorage::get_last_enemies_choices([[maybe_unused]] const Strategy& strategy) const{
    return {};
}

void AbstractStorage::append_choices([[maybe_unused]] const Choices& choice){}

History AbstractStorage::get_previous_games_history() const{
    return {};
}

Storage::Storage(const std::string& configs_path){
    _ids_count = 0;
    _id_of_strateg = 0; // 0 - means no strateg, id of strateg would be shifted by 1 (1 instead of 0 etc.)
    _configs_path = configs_path + '/';

    read_strategic_data(_configs_path, _history_of_strateg);
}

bool Storage::is_empty() const{
    return _global_history.empty();
}

Choices Storage::get_last_enemies_choices(unsigned int id) const{
    Choices result;

    const Choices last_choices = _global_history.back();
    for (unsigned int i = 0; i < last_choices.size(); i++){
        if (i != id){
            result.push_back(last_choices[i]);
        }
    }

    return result;
}

Choices Storage::get_last_enemies_choices(const Strategy& strategy) const{
    return get_last_enemies_choices(_ids.at(strategy));
}

History Storage::get_previous_games_history() const{
    return _history_of_strateg;
}

void Storage::register_strategy(const Strategy& strategy){
    _ids[strategy] = _ids_count++;
}

void Storage::append_choices(const Choices& choices){
    _global_history.push_back(choices);

    if (_id_of_strateg){
        _history_of_strateg.push_back(get_last_enemies_choices(_id_of_strateg - 1));
    }
}

Storage::~Storage(){
    try{
        dump_strategic_data(_id_of_strateg, _configs_path, _history_of_strateg);
    }
    catch(...){}
}

void Storage::register_strateg(const Strategy& strategy){
    _id_of_strateg = _ids[strategy] + 1;
    _history_of_strateg = {};
}
