// Process.h
// The header handles all the input phases of the program
// from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada
// Moisés Fernández
// Version: 1.0 last modified 14/11/2019
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace sisops {
namespace {
struct TableEntry {
    int frameNumber;
    int swappingAddress;
    bool valid;
    TableEntry(int frame, int sAddress, bool v) {
        frameNumber = frame;
        swappingAddress = sAddress;
        valid = v;
    }
};
}
class Process {
 public:
    Process(int id, int size);
    ~Process();

    int getFrameNumber(int vAddress);
    int getSwappingAddress(int vAddress);
    int getValid(int vAddress);

    void setFrameNumber(int vAddress, int frameNumber);
    void setSwappingAddress(int vAddress, int swappingAddress);
    void setValid(int vAddress, bool valid);

 private:
    const int id_;
    const int size_;
    std::vector<TableEntry> pageTable;

};


Process::Process(int id, int size):id_(id),size_(size){}

inline int Process::getFrameNumber(int vAddress) {
    return pageTable[vAddress / size_].frameNumber;
}

inline int Process::getSwappingAddress(int vAddress) {
    return pageTable[vAddress / size_].swappingAddress;
}

inline int Process::getValid(int vAddress) {
    return pageTable[vAddress / size_].valid;
}

inline void Process::setFrameNumber(int vAddress, int frameNumber) {
    pageTable[vAddress / size_].frameNumber = frameNumber;
}

inline void Process::setSwappingAddress(int vAddress, int swappingAddress) {
    pageTable[vAddress / size_].swappingAddress = swappingAddress;
}

inline void Process::setValid(int vAddress, bool valid) {
    pageTable[vAddress / size_].valid = valid;
}

}
