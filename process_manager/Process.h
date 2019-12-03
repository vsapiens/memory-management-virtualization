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
    //Get ID
    int GetId();
    //Get size
    int GetSize();
    //Get size
    double GetTime();

    void SetFrameNumber(int page, int frameNumber);
    void SetValid(int page, bool valid);
    void SetTime(double time);

 private:
    //Id of the process
    const int id_;
    //Size of the process
    const int size_;
    //Stores the time

    double time_;
    //Stores the table entry of the processes
    std::vector<TableEntry> pageTable;

};

/*
Function: Process::Process
    This constructor initializes the variables of the class
Parameters: int id, int size, int f_amount
Return: -
*/
Process::Process(int id, int size, int f_amount):id_(id),size_(size), pageTable(f_amount), time_(0){}
/*
Function: Process::Process
    Empty constructor of the class that initializes in the map constructor
Parameters: -
Return: -
*/
Process::Process():id_(-1),size_(-1), pageTable(0), time_(0){}
/*
Function: Process::GetFrameNumber
    The function gets the frame number of the process
Parameters: const int page
Return: pageTable[page].frame_number_
*/
inline int Process::GetFrameNumber(const int page) {
    return pageTable[page].frame_number_;
}
/*
Function: Process::GetId()
    The function gets the ID
Parameters: -
Return: int id_
*/
inline int Process::GetId() {
    return id_;
}
/*
Function: Process::GetSize()
    The function gets the size
Parameters: -
Return: int size_
*/
inline int Process::GetSize() {
    return size_;
}
/*
Function: Process::GetValid()
    The function gets if the page number is valid
Parameters: const int page
Return: int pageTable[page].valid_
*/
inline int Process::GetValid(const int page) {
    return pageTable[page].valid_;
}
/*
Function: Process::GetTime()
    The function gets the start time of the process given
Parameters: -
Return: double time_
*/
inline double Process::GetTime() {
    return time_;
}
/*
Function: Process::SetFrameNumber()
    The function sets the frame number
Parameters: const int page, const int frameNumber)
Return: =
*/
inline void Process::SetFrameNumber(const int page, const int frameNumber) {
    pageTable[page].frame_number_ = frameNumber;
}
/*
Function: Process::SetValid
    The function sets valid the page
Parameters: const int page, const bool valid
Return: =
*/
inline void Process::SetValid(const int page, const bool valid) {
    pageTable[page].valid_ = valid;
}
/*
Function: Process::SetTime()
    The function sets the start time
Parameters: double time
Return: -
*/
inline void Process::SetTime(double time) {
    time_ = time;
}

}
