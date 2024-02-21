#include<bits/stdc++.h>
using namespace std;

struct process
{   
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int processed_time = 0;
    int starting_time = -1;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

double total_tat=0.0,total_wt=0.0;
void print(struct process current_process, int time)
{
    current_process.completion_time = time;
    current_process.turn_around_time = current_process.completion_time - current_process.arrival_time;
    current_process.waiting_time = current_process.turn_around_time - current_process.burst_time;
    total_tat+=current_process.turn_around_time;
    total_wt+=current_process.waiting_time;

    cout << "Process Id: " << current_process.process_id << endl;
    cout << "Starting time: " << current_process.starting_time << endl;
    cout << "Completion time: " << current_process.completion_time << endl;
    cout << "Turn around time: " << current_process.turn_around_time << endl;
    cout << "Waiting time: " << current_process.waiting_time << endl << endl;
}

bool comp(struct process p1, struct process p2)
{
    return p1.priority < p2.priority;
}


int main()
{
    cout << "Enter the number of process: ";
    int n; cin >> n;
    vector<process> process_list(n);
    for(int i = 0; i < n; i++) process_list[i].process_id=i+1;  
    cout << "Enter arrival time: ";
    for(int i=0;i<n;i++) cin >> process_list[i].arrival_time;
    cout << "Enter priority: ";
    for(int i=0;i<n;i++) cin >> process_list[i].priority;
    cout << "Enter burst time: ";
    for(int i=0;i<n;i++) cin >> process_list[i].burst_time;
    cout<<endl;

    sort(process_list.begin(), process_list.end(), comp);
    int p = 0, time=0;
    vector<int> finished(n, 0);
    while(p < n)
    {
        int min_priority = INT_MAX;
        int index = -1;

        for(int i = 0; i < n; i++)
        {
            if(process_list[i].arrival_time > time or finished[i]) continue;

            if(process_list[i].priority < min_priority)
            {
                min_priority = process_list[i].priority;
                index = i;
                if(process_list[i].starting_time == -1) process_list[i].starting_time=time;
            }
        }
        
        time++;
        if(index == -1) continue;
        process_list[index].processed_time++;
        if(process_list[index].burst_time == process_list[index].processed_time)
        {
            finished[index] = 1;
            p++;
            print(process_list[index], time);
        }
    }
    cout<<"Average waiting time: " << total_wt/n << endl;
    cout<<"Average turnaround time: " << total_tat/n <<endl;
}
