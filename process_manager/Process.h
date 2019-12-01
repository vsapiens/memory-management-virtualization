// Process.h
// The header handles all the input phases of the program from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace sisops {

struct TableEntry {
    int frameNumber;
    bool valid;
    TableEntry() {
        frameNumber = -1;
        valid = false;
    }
    TableEntry(int frame, bool v) {
        frameNumber = frame;
        valid = v;
    }
};

class Process {
 public:
    Process(int id, int size, int f_amount);
    ~Process();

    int getFrameNumber(int vAddress);
    int getValid(int vAddress);

    int getId();
    int getSize();

    void setFrameNumber(int page, int frameNumber);
    void setValid(int page, bool valid);

 private:
    const int id_;
    const int size_;
    std::vector<TableEntry> pageTable;

};


Process::Process(int id, int size, int f_amount):id_(id),size_(size), pageTable(f_amount){}

inline int Process::getFrameNumber(const int vAddress) {
    return pageTable[vAddress / size_].frameNumber;
}

inline int Process::getValid(const int vAddress) {
    return pageTable[vAddress / size_].valid;
}

inline int Process::getId() {
    return id_;
}

inline int Process::getSize() {
    return size_;
}

inline void Process::setFrameNumber(const int page, const int frameNumber) {
    pageTable[page].frameNumber = frameNumber;
}


inline void Process::setValid(const int page, const bool valid) {
    pageTable[page].valid = valid;
}

}
