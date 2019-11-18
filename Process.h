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

class Process {
    public:
    Process(int id, int size);
    ~Process();

    int getFrameNumber(int vAddress);
    int getSwappingAddress(int vAddress);
    int getValid(int vAddress);

    private:
    struct TableEntry {
        int frameNumber;
        int swappingAddress;
        bool valid;

        TableEntry(int f, int s, bool v) {
            frameNumber = f;
            swappingAddress = s;
            valid = v;
        }
    }

    int id;
    int size;
    vector<TableEntry> pageTable;

};

Process::Process(int id, int size) {
    this->id = id;
    this->size = size;
}

int Process::getFrameNumber(int vAddress) {
    return pageTable[vAddress / size].frameNumber;
}

int Process::getSwappingAddress(int vAddress) {
    return pageTable[vAddress / size].swappingAddress;
}

int Process::getValid(int vAddress) {
    return pageTable[vAddress / size].valid;
}