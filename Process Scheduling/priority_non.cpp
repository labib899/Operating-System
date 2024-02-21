#include<bits/stdc++.h>
using namespace std;

struct Process 
{
   int id,at,bt,priority,ct,wt,tat;
};
int n;
vector<Process> proc;

bool cmp(Process a, Process b) 
{
   return a.priority<b.priority;
}

void priority()
{  
   sort(proc.begin(),proc.end(),cmp);
   int mn=INT_MAX,min_ind=-1;
   for(int i=0;i<n;i++)
   {
      if(proc[i].at<mn) mn=proc[i].at,min_ind=i; 
   }
   proc[min_ind].ct=mn+proc[min_ind].bt;
   proc[min_ind].tat=proc[min_ind].bt;
   proc[min_ind].wt=0;
   int curr=proc[min_ind].ct;
   printf("p%d %d %d %d %d %d %d\n", 
   proc[min_ind].id,proc[min_ind].at,proc[min_ind].bt,proc[min_ind].priority,
   proc[min_ind].ct,proc[min_ind].wt,proc[min_ind].tat);

   double total_wt=0.0,total_tat=0.0;
   total_wt+=proc[min_ind].wt,total_tat+=proc[min_ind].tat;
   for(int i=0;i<n;i++)
   {
      if(proc[i].at==mn) continue;
      proc[i].ct=curr+proc[i].bt,curr=proc[i].ct;
      proc[i].tat=proc[i].ct-proc[i].at; total_tat+=proc[i].tat;
      proc[i].wt=proc[i].tat-proc[i].bt; total_wt+=proc[i].wt;
      printf("p%d %d %d %d %d %d %d\n", 
      proc[i].id,proc[i].at,proc[i].bt,proc[i].priority,proc[i].ct,proc[i].wt,proc[i].tat);
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
   cout<<"Enter Priority: "<<endl;
   for(int i=0;i<n;i++) cin>>proc[i].priority;

   priority();
}

/*
5
1 2 3 4 5
3 5 1 7 4
3 4 1 7 8
*/