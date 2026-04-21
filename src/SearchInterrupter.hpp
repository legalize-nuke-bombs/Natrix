#pragma once


class SearchInterrupter {
public:
    static SearchInterrupter& get() {
        static SearchInterrupter inst;
        return inst;
    }
    SearchInterrupter(const SearchInterrupter &donor) = delete;

    void interrupt();
    void resume();
    bool interrupted() const;
private:
    SearchInterrupter();

    bool halt;
};