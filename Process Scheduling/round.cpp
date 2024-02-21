#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process 
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

double total_tat=0.0,total_wt=0.0;
void calculate(vector<Process> &processes) 
{
    int n = processes.size();
    int total_burst_time = 0;
    for (Process &process : processes) total_burst_time += process.burst_time;

    queue<int> ready_queue;
    int current_time = 0, current_process = -1;
    
    while (current_time < total_burst_time) 
    {
        for (int i = 0; i < n; ++i) 
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) 
                ready_queue.push(i);
        }

        if (ready_queue.empty()) 
        {
            current_time++;
            continue;
        }

        if (current_process != -1 && processes[current_process].remaining_time > 0) 
            ready_queue.push(current_process);

        current_process = ready_queue.front();
        ready_queue.pop();

        int time_slice = min(2, processes[current_process].remaining_time);
        processes[current_process].remaining_time -= time_slice;
        current_time += time_slice;

        if (processes[current_process].remaining_time == 0) 
        {
            processes[current_process].completion_time = current_time;
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
        total_tat+=processes[i].turn_around_time;
        total_wt+=processes[i].waiting_time;
    }
}

int main() 
{
    cout << "Enter the number of processes: ";
    int n; cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) 
    {
        processes[i].process_id = i + 1;
        cout << "Process " << i + 1 << ":\n";
        cout << "Enter arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculate(processes);
    //cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (Process &process : processes) 
    {
        cout << "P"<<process.process_id << " " << process.arrival_time << " " << process.burst_time << " "
                  << process.completion_time << " " << process.turn_around_time << " " << process.waiting_time << "\n";
    }

    cout<<"Average waiting time: " << total_wt/n << endl;
    cout<<"Average turnaround tinme: " << total_tat/n <<endl;
}