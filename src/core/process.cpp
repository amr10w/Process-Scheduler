#include "process.h"

// Constructor
process::process(int id, int arrival, int cpu) : 
    id(id), 
    arrival_time(arrival),
    CPU_time(cpu) 
{
    this->remaining_time = CPU_time;
    this->executed_time = 0;
    state = NEW;
    
    // calculated later
    response_time = -1;  
    termination_time = 0;
    turnaround_duration = 0;
    waiting_time = 0;

    ParentID = -1;
    LeftChild = nullptr;
    RightChild = nullptr;
}

// Destructor
process::~process() {}

void process::executeStep() {
    if (remaining_time > 0) {
        remaining_time--;
        executed_time++;
    }
}

// --- Setters ---

void process::setTerminationTime(int time) {
    termination_time = time;
    calculateStats();
}

void process::setState(ProcessState newState) {
    state = newState;
}

// setter for the whole list
void process::setIOList(const std::vector<std::pair<int, int>>& list) {
    io_list = list;
}

// add just one IO pair instead of replacing the whole list
void process::addIO(int start, int duration) {
    io_list.push_back({start, duration});
}

void process::setResponseTime(int currentTime) {
    if (response_time == -1) { // Only set it the FIRST time the process runs
        response_time = currentTime - arrival_time;
    }
}

// --- Getters ---

int process::getId() {
    return id;
}

int process::getArrivalTime() {
    return arrival_time;
}

int process::getResponseTime() {
    return response_time;
}

int process::getCPUTime() {
    return CPU_time;
}

int process::getTerminationTime() {
    return termination_time;
}

int process::getTurnaroundDuration() {
    return turnaround_duration;
}

int process::getWaitingTime() {
    return waiting_time;
}

ProcessState process::getState() {
    return state;
}

std::vector<std::pair<int, int>>& process::getIOList() {
    return io_list;
}

int process::getRemainingTime() { 
    return remaining_time; 
}

//----------------stat calculations
void process::calculateStats() {
    turnaround_duration = termination_time - arrival_time;
    waiting_time = turnaround_duration - CPU_time;
}

// ------- fork -------
void process::setParent(int pid) { 
    ParentID = pid; 
}

int process::getParent() const { 
    return ParentID; 
}

void process::setLeftChild(process* p) { 
    LeftChild = p; 
}

void process::setRightChild(process* p) { 
    RightChild = p; 
}

process* process::getLeftChild() const { 
    return LeftChild; 
}

process* process::getRightChild() const { 
    return RightChild; 
}
