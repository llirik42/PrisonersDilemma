#include "storage.h"

AbstractStorage::AbstractStorage()=default;

EnemiesChoice AbstractStorage::get_last_enemies_choice() const{
    return EnemiesChoice({COOPERATION_STEP, COOPERATION_STEP});
}

void AbstractStorage::append_enemies_choice([[maybe_unused]] EnemiesChoice choice){

}

AbstractStorage::~AbstractStorage()=default;

bool FileStorage::is_empty(){
    return !_history.empty();
}

EnemiesChoice FileStorage::get_last_enemies_choice() const{
    return _history.back();
}

void FileStorage::append_enemies_choice(EnemiesChoice choice){
   _history.push_back(choice);
}
