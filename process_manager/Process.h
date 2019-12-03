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
    // Number of the frame
    int frame_number_;
    // Determines if the page is valid 
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

    int GetFrameNumber(const int page);
    int GetValid(const int page);

    int GetId();
    int GetSize();
    double GetTime();

    void SetFrameNumber(int page, int frameNumber);
    void SetValid(int page, bool valid);
    void SetTime(double time);

 private:
    // Identifies the process
    const int id_;
    // Size of process
    const int size_;
    // Time it takes to process
    double time_;
    std::vector<TableEntry> pageTable;

};


Process::Process(int id, int size, int f_amount):id_(id),size_(size), pageTable(f_amount), time_(0){}
Process::Process():id_(-1),size_(-1), pageTable(0), time_(0){}

// Returns the frame number of a page
inline int Process::GetFrameNumber(const int page) {
    return pageTable[page].frame_number_;
}
// Returns the id of the process
inline int Process::GetId() {
    return id_;
}
// Returns the size of a process
inline int Process::GetSize() {
    return size_;
}
// Returns if a process is valid
inline int Process::GetValid(const int page) {
    return pageTable[page].valid_;
}
// Returns the time it takes to process
inline double Process::GetTime() {
    return time_;
}
// Sets the frame number to a page
inline void Process::SetFrameNumber(const int page, const int frameNumber) {
    pageTable[page].frame_number_ = frameNumber;
}
// Sets if a process is valid with the page number
inline void Process::SetValid(const int page, const bool valid) {
    pageTable[page].valid_ = valid;
}
// Sets the time of the process
inline void Process::SetTime(double time) {
    time_ = time;
}

}
