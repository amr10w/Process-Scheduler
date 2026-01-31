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
    process(int id, int arrival, int cpu);

    // Destructor
    ~process();

    void executeStep();
    
    // --- Setters ---
    void setTerminationTime(int time);
    void setState(ProcessState newState);
    void setIOList(const std::vector<std::pair<int, int>>& list);
    void addIO(int start, int duration);
    void setResponseTime(int currentTime);
    
    // --- Getters ---
    int getId();
    int getArrivalTime();
    int getResponseTime();
    int getCPUTime();
    int getTerminationTime();
    int getTurnaroundDuration();
    int getWaitingTime();
    ProcessState getState();
    std::vector<std::pair<int, int>>& getIOList();
    int getRemainingTime();

    //----------------stat calculations
    void calculateStats();

    // ------- fork -------
    void setParent(int pid);
    int getParent() const;
    void setLeftChild(process* p);
    void setRightChild(process* p);
    process* getLeftChild() const;
    process* getRightChild() const;
};

#endif
