#include <bits/stdc++.h>
using namespace std;

int num_res,num_proc;

void print1D(vector<int> a)
{   
    for(auto x:a) cout<<x<<" ";
    cout<<endl<<endl<<endl;
}

void print2D(vector<vector<int>> a)
{
    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<a[i].size();j++) cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;
}

vector<int> sumCol(vector<vector<int>> a)
{
    vector<int> ans(num_res,0);
    for(int i=0;i<num_res;i++)
    {
        for(int j=0;j<num_proc;j++) ans[i]+=a[j][i];
    }
    return ans;
}

int main()
{   
    cout<<"Enter number of resources: ";
    cin>>num_res;
    cout<<"Enter total number of each resource: ";
    vector<int> total_res(num_res);
    for(int i=0;i<num_res;i++) 
    {
        cout<<"\nTotal resources for R"<<i<<": ";
        cin>>total_res[i];
    }
    cout<<"Enter number of processes: ";
    cin>>num_proc;
    vector<vector<int>> allocated(num_proc,vector<int> (num_res)); 
    for(int i=0;i<num_proc;i++)
    {
        for(int j=0;j<num_res;j++)
        {
            cout<<"\nEnter amount of R"<<j<<" allocated to P"<<i<<": ";
            cin>>allocated[i][j];
        }
    }
    cout<<"Enter max resources: ";
    vector<vector<int>> maxi(num_proc,vector<int> (num_res));
    for(int i=0;i<num_proc;i++)
    {
        for(int j=0;j<num_res;j++)
        {
            cout<<"\nEnter max amount of R"<<j<<" needed by P"<<i<<": ";
            cin>>maxi[i][j];
        }
    }
    vector<int> total_allocated=sumCol(allocated);
    vector<int> available(num_res);
    for(int i=0;i<num_res;i++)
    {
        available[i]=total_res[i]-total_allocated[i];
    }
    vector<vector<int>> need(num_proc,vector<int>(num_res));
    for(int i=0;i<num_proc;i++)
    {
        for(int j=0;j<num_res;j++) need[i][j]=maxi[i][j]-allocated[i][j];
    }
    vector<int> safe_seq;
    bool cmp=true;
    while(cmp)
    {
        cmp=false;
        for(int i=0;i<num_proc;i++)
        {   
            bool is_terminated=false;
            for(int j=0;j<safe_seq.size();j++)
            {
                if(safe_seq[j]==i) is_terminated=true;
            }
            if(is_terminated==false)
            {   
                bool is_safe=true;
                for(int j=0;j<num_res;j++)
                {
                    if(need[i][j]>available[j]) 
                    {
                        is_safe=false;
                        break;
                    }
                }
                if(is_safe) 
                {
                    safe_seq.push_back(i);
                    for(int j=0;j<num_res;j++)
                    {
                        available[j]+=allocated[i][j];
                    }
                    cmp=true;
                }
            }
        }
    }
    cout<<"Total res:"<<endl;; print1D(total_res); 
    cout<<"Allocated:"<<endl; print2D(allocated);
    cout<<"Maxi: "<<endl; print2D(maxi);
    cout<<"Need: "<<endl; print2D(need);
    cout<<"Available: "<<endl; print1D(available);

    if(safe_seq.size()!=num_proc) cout<<"Deadlock..."<<endl;
    else 
    {   
        cout<<"Safe sequence: "<<endl;
        for(auto x:safe_seq) cout<<"P"<<x<<" ";
        cout<<endl;
    }
}

/*
3
10 5 12
5
0 1 4
1 1 3
3 0 0
0 1 3
2 0 1
5 4 5
1 4 6
6 0 0
2 3 3
4 1 2
*/