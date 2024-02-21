#include<bits/stdc++.h>
using namespace std;

int main()
{
    cout<<"Enter the number of processes: "<<endl;
    int n; cin>>n;
    vector<int> id(n),at(n),bt(n);
    for(int i=0;i<n;i++) id[i]=i+1;
    cout<<"Enter arrival time: "<<endl;
    for(int i=0;i<n;i++) cin>>at[i];
    cout<<"Enter burst time: "<<endl;
    for(int i=0;i<n;i++) cin>>bt[i];

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(bt[i]>bt[j])
            {
                swap(at[i],at[j]);
                swap(bt[i],bt[j]);
                swap(id[i],id[j]);
            }
        }
    }

    int mn=INT_MAX,min_ind=-1;
    for(int i=0;i<n;i++)
    {
        if(at[i]<mn) mn=at[i],min_ind=i;
    }
    vector<int> ct(n),wt(n),tat(n);
    double total_wt=0,total_tat=0;
    ct[min_ind]=bt[min_ind]+mn;
    int curr=ct[min_ind];
    cout<<"p"<<id[min_ind]<<" "<<at[min_ind]<<" "<<bt[min_ind]<<" "<<ct[min_ind]<<" "<<wt[min_ind]<<" "<<ct[min_ind]<<endl;
    
    for(int i=0;i<n;i++)
    {
        if(at[i]==mn) continue;
        ct[i]=curr+bt[i],curr=ct[i];
        tat[i]=ct[i]-at[i]; total_tat+=tat[i];
        wt[i]=tat[i]-bt[i]; total_wt+=wt[i];
        cout<<"p"<<id[i]<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "<<wt[i]<<" "<<tat[i]<<endl;
    }
    printf("Average waiting time: %.2lf\n", total_wt/n);
    printf("Average turnaround time: %.2lf\n", total_tat/n);
}

/*
4
0 1 2 3
8 4 9 5
*/