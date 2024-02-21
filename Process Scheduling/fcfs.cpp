#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int id,at,bt,ct,wt,tat;
};
int n;
vector<Process> proc;

bool cmp(Process a,Process b)
{
    return a.at<b.at;
}

void fcfs()
{   
    sort(proc.begin(),proc.end(),cmp);
    int current=proc[0].at;
    double total_wt=0.0,total_tat=0.0;
    for(int i=0;i<n;i++)
    {
        current+=proc[i].bt;
        proc[i].ct=current;
        proc[i].tat=proc[i].ct-proc[i].at; total_tat+=proc[i].tat;
        proc[i].wt=proc[i].tat-proc[i].bt; total_wt+=proc[i].wt;
        if(i<n-1 and current<proc[i+1].at) current=proc[i+1].at;
        printf("p%d %d %d %d %d %d\n", proc[i].id,proc[i].at,proc[i].bt,proc[i].ct,proc[i].wt,proc[i].tat);
    }
    printf("Average waiting time: %.2lf\n", total_wt/n);
    printf("Average turnaround time: %.2lf\n", total_tat/n);
}

int main()
{
    cout<<"Enter the number of processes: "<<endl;
    cin>>n;
    proc.resize(n);
    for(int i=0;i<n;i++) proc[i].id=i+1;
    cout<<"Enter arrival time: "<<endl;
    for(int i=0;i<n;i++) cin>>proc[i].at;
    cout<<"Enter burst time: "<<endl;
    for(int i=0;i<n;i++) cin>>proc[i].bt;

    fcfs();
}

/*
3
0 3 6
5 9 6
*/