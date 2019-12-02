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
    int frame_number_;
    bool valid_;
    TableEntry() {
        frame_number_ = -1;
        valid_ = false;
    }
    TableEntry(const int frame, const bool v) {
        frame_number_ = frame;
        valid_ = v;
    }
};

class Process {
 public:
    Process(const int id, const int size, const int f_amount);
    Process();

    int GetFrameNumber(const int vAddress);
    int GetValid(const int vAddress);

    int GetId();
    int GetSize();
    double GetTime();

    void SetFrameNumber(int page, int frameNumber);
    void SetValid(int page, bool valid);
    void SetTime(double time);

 private:
    const int id_;
    const int size_;
    double time_;
    std::vector<TableEntry> pageTable;

};


Process::Process(int id, int size, int f_amount):id_(id),size_(size), pageTable(f_amount), time_(0){}
Process::Process():id_(-1),size_(-1), pageTable(0), time_(0){}

inline int Process::GetFrameNumber(const int vAddress) {
    return pageTable[vAddress / size_].frame_number_;
}

inline int Process::GetValid(const int vAddress) {
    return pageTable[vAddress / size_].valid_;
}

inline int Process::GetId() {
    return id_;
}

inline int Process::GetSize() {
    return size_;
}

inline double Process::GetTime() {
    return time_;
}

inline void Process::SetFrameNumber(const int page, const int frameNumber) {
    pageTable[page].frame_number_ = frameNumber;
}


inline void Process::SetValid(const int page, const bool valid) {
    pageTable[page].valid_ = valid;
}

inline void Process::SetTime(double time) {
    time_ = time;
}

}
