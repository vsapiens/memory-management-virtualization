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

private:
const int id_;
const int size_;
std::vector<TableEntry> pageTable;

};

Process::Process(int id, int size):id_(id),size_(size){}

int Process::getFrameNumber(int vAddress) {
    return pageTable[vAddress / size_].frameNumber;
}

int Process::getSwappingAddress(int vAddress) {
    return pageTable[vAddress / size_].swappingAddress;
}

int Process::getValid(int vAddress) {
    return pageTable[vAddress / size_].valid;
}
}
