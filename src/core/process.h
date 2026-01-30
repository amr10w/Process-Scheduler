#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include <utility>

enum ProcessState {
    NEW,    // New: Created but not yet arrived
    RDY,    // Ready: In ready queue, waiting for CPU
    RUN,    // Running: Being served by CPU
    BLK,    // Blocked: Waiting for I/O resources
    TRM,    // Terminated: Finished execution
    ORPH    // Orphan: Special state (as noted in your text)
};


class process
{
  private:
    int id; // unique for each process
    int arrival_time; // the time when the process is ready to be scheduled
    int response_time; // the difference between the arrival time and the time at which the process gets the CPU for the FIRST time
    int CPU_time; // total time needed to run the porcess continually
    int termination_time; // time when the process finishes execution
    int turnaround_duration; // the total time a porcess spends in the its termination
    int waiting_time; // total time a porcess spends in the system not being executed by the CPU
    int remaining_time; // time left to finish execution
    int executed_time; // time already executed
    ProcessState state;
    std::vector<std::pair<int, int>> io_list;

    // forking
    int ParentID;
    process* LeftChild;
    process* RightChild;
  public:
    // Constructor
    process(int id, int arrival, int cpu) : 
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
    ~process() {}

    void executeStep() {
        if (remaining_time > 0) {
            remaining_time--;
            executed_time++;
        }
    }
    // --- Setters ---

    void setTerminationTime(int time) {
        termination_time = time;
        calculateStats();
    }

    void setState(ProcessState newState) {
        state = newState;
    }

    // setter for the whole list
    void setIOList(const std::vector<std::pair<int, int>>& list) {
        io_list = list;
    }

    // add just one IO pair instead of replacing the whole list
    void addIO(int start, int duration) {
        io_list.push_back({start, duration});
    }

    void setResponseTime(int currentTime) {
        if (response_time == -1) { // Only set it the FIRST time the process runs
            response_time = currentTime - arrival_time;
        }
    }
    // --- Getters ---

    int getId() {
        return id;
    }

    int getArrivalTime() {
        return arrival_time;
    }

    int getResponseTime() {
        return response_time;
    }

    int getCPUTime() {
        return CPU_time;
    }

    int getTerminationTime() {
        return termination_time;
    }

    int getTurnaroundDuration() {
        return turnaround_duration;
    }

    int getWaitingTime() {
        return waiting_time;
    }

    ProcessState getState() {
        return state;
    }
    

    std::vector<std::pair<int, int>>& getIOList() {
        return io_list;
    }
    int getRemainingTime() { return remaining_time; }

    //----------------stat calculations
    void calculateStats() {
        turnaround_duration = termination_time - arrival_time;
        waiting_time = turnaround_duration - CPU_time;
    }

    // ------- fork -------
    void setParent(int pid) { ParentID = pid; }
    int getParent() const { return ParentID; }

    void setLeftChild(process* p) { LeftChild = p; }
    void setRightChild(process* p) { RightChild = p; }
    process* getLeftChild() const { return LeftChild; }
    process* getRightChild() const { return RightChild; }
};

#endif
