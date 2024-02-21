#include<bits/stdc++.h>
using namespace std;


struct Process
{
    int id,at,bt,ct,wt,tat;
};
int n;
vector<Process> proc;

void sjf()
{
    vector<int> rt(n);
    for(int i=0;i<n;i++) rt[i]=proc[i].bt;
    int p=0,time=0,mn=INT_MAX,shortest=0;
    bool flag=false;
    while(p!=n)
    {
        for(int i=0;i<n;i++)
        {
            if(proc[i].at<=time and rt[i]<mn and rt[i]>0)
            {
                mn=rt[i];
                shortest=i;
                flag=true;
            }
        }
        time++;
        if(!flag) continue;
        rt[shortest]--;
        mn=rt[shortest];
        if(rt[shortest]==0)
        {   
            mn=INT_MAX;
            p++;
            flag=false;
            proc[shortest].wt=max(time-proc[shortest].at-proc[shortest].bt,0);
            proc[shortest].ct=time;
        }
    }

    for(int i=0;i<n;i++) proc[i].tat=proc[i].bt+proc[i].wt;
    double total_wt=0,total_tat=0;
    for(int i=0;i<n;i++) 
    {
        total_wt+=proc[i].wt;
        total_tat+=proc[i].tat;
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

    sjf();
}

/*
4
0 1 2 3
8 4 9 5
*/