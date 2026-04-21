#include "SearchInterrupter.hpp"


void SearchInterrupter::interrupt() {
    this->halt = true;
}
void SearchInterrupter::resume() {
    this->halt = false;
}
bool SearchInterrupter::interrupted() const {
    return this->halt;
}
SearchInterrupter::SearchInterrupter() {
    this->halt = false;
}