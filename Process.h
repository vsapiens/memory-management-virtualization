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
    TableEntry(int frame, bool v) {
        frameNumber = frame;
        valid = v;
    }
};

class Process {
 public:
    Process(int id, int size);
    ~Process();

    int getFrameNumber(int vAddress);
    int getValid(int vAddress);

    void setFrameNumber(int vAddress, int frameNumber);
    void setValid(int vAddress, bool valid);

 private:
    const int id_;
    const int size_;
    std::vector<TableEntry> pageTable;

};


Process::Process(int id, int size):id_(id),size_(size){}

inline int Process::getFrameNumber(const int vAddress) {
    return pageTable[vAddress / size_].frameNumber;
}

inline int Process::getValid(const int vAddress) {
    return pageTable[vAddress / size_].valid;
}

inline void Process::setFrameNumber(const int vAddress, const int frameNumber) {
    pageTable[vAddress / size_].frameNumber = frameNumber;
}


inline void Process::setValid(const int vAddress, const bool valid) {
    pageTable[vAddress / size_].valid = valid;
}

}
