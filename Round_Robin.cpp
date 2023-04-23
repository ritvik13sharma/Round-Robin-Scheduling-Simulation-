#include<bits/stdc++.h>
#include<cstdlib>
#include<time.h>

using namespace std;

struct process{ // a structure called process for storing process id , its arrival time and its 
    string pid;     // burst time.
    int arrival;
    int burst;
    int turnaround;
    int waiting;
    int completion;

    process(string x) //constructor to initialize process arrival and burst times
    {
        pid=x;
        arrival=0;
        burst=0;
        completion=0;
        turnaround=0;
        waiting=0;
    }
};

static bool sort_arrival(process* p1, process*p2) //function to sort processes according to arrival
{                                                 //timings
    return p1->arrival<p2->arrival;
}

void initialize_random(vector<process> &arr) //function for initializing random values for 
{                                            //arrival and burst time.
    int n1=20;
    int tq_least=2, tq_highest=20;

    srand(time(0));

    for(int i=0;i<arr.size();i++)
    {
        arr[i].arrival=(rand() % n1);
        arr[i].burst=((rand() %( tq_highest - tq_least +1)) + tq_least);
    }
    cout<<endl<<"Process id |  Arrival  | Burst"<<endl;
    cout<<"---------------------------------- "<<endl;
    for(int i=0;i<arr.size();i++)
    {
        cout<<"    "<<arr[i].pid<<"\t\t  "<<arr[i].arrival<<"\t    "<<arr[i].burst<<endl;
    }
}

void fcfs(vector<process> arr)
{
    vector<process*> arrival_timings;
    vector<int> completions,tat,wt;

    for(int i=0;i<arr.size();i++)
    {
        arrival_timings.push_back(&arr[i]);
    }

    sort(arrival_timings.begin(),arrival_timings.end(),&sort_arrival);

    int twt=0, ttt=0;
    int time=arrival_timings[0]->arrival;

    for(int i=0;i<arrival_timings.size();i++)
    {
        time+=arrival_timings[i]->burst;
        arrival_timings[i]->completion=time;
        arrival_timings[i]->turnaround=(arrival_timings[i]->completion-arrival_timings[i]->arrival);
        arrival_timings[i]->waiting=(arrival_timings[i]->turnaround - arrival_timings[i]->burst);
        ttt+=arrival_timings[i]->turnaround;
        twt+=arrival_timings[i]->waiting;
    }

    cout<<endl<<"The turnaround and waiting times in FCFS algorithm are shown below: "<<endl<<endl;
    cout<<"Process id  |  Turnaround Time |  Waiting time"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    
    for(int i=0;i<arr.size();i++)
    {
      cout<<"    "<<(arr[i].pid)<<"\t\t     "<<(arr[i].turnaround)<<"\t\t    "<<(arr[i].waiting)<<endl;
    }
    cout<<endl;
    cout<<"Average Turnaround Time: "<<(float(ttt)/arr.size())<<" ms"<<endl;
    cout<<"Average Waiting Time : "<<(float(twt)/arr.size())<<" ms"<<endl;

}

void round_robin(vector<process> &arr) // function for execution of round robin algorithm.
{
    vector<process*> arrival_timings;
    vector<int> original_bursts;

    for(int i=0;i<arr.size();i++)
    {
        arrival_timings.push_back(&arr[i]);
        original_bursts.push_back(arrival_timings[i]->burst);
    }

    sort(arrival_timings.begin(),arrival_timings.end(),&sort_arrival);

    queue<process*> ready_queue;
    queue<process*> execution_queue;

    int x=1;
    int currtime=arrival_timings[0]->arrival;

    ready_queue.push(arrival_timings[0]);  

    while(currtime <= currtime+100 and (ready_queue.empty()==false))
    {
        execution_queue.push(ready_queue.front());

        if(execution_queue.back()->burst>2)
        {
            execution_queue.back()->burst-=2;
            currtime+=2;
            for(int i=x;i<arrival_timings.size();i++)
            {
                if(arrival_timings[i]->arrival<=currtime)
                {
                    ready_queue.push(arrival_timings[i]);
                    x++;
                }
            }
            ready_queue.push(execution_queue.back());
            ready_queue.pop();
        }
        else
        {
            currtime+=execution_queue.back()->burst;
            execution_queue.back()->completion=currtime;
            ready_queue.pop();
        }
    }

    { //printing block
    cout<<endl<<"Note: Unit of time used is milisecond (ms)"<<endl<<endl;
    cout<<endl<<"The Order in which processes have been executed in Round Robin Scheduling are: "<<endl;
    cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

    while(execution_queue.empty()!=true)
    {
        cout<<" "<<execution_queue.front()->pid<<" | ";
        execution_queue.pop();
    }
    cout<<endl<<"----------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    
    cout<<"The turnaround and waiting times in Round Robin algorithm with time quantum = 2ms are shown below: "<<endl<<endl;
    cout<<"Process id  |  Turnaround Time |  Waiting time"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    int totalt=0;
    int totalw=0;

    for(int i=0;i<arr.size();i++)
    {
        arr[i].turnaround=arr[i].completion - arr[i].arrival;
        arr[i].waiting=arr[i].turnaround- original_bursts[i];
        cout<<"    "<<(arr[i].pid)<<"\t\t     "<<(arr[i].turnaround)<<"\t\t    "<<(arr[i].waiting)<<endl;
        totalt+=arr[i].turnaround;
        totalw+=arr[i].waiting;
    }
    cout<<endl;
    cout<<"Average Turnaround Time: "<<(float(totalt)/arr.size())<<" ms"<<endl;
    cout<<"Average Waiting Time : "<<(float(totalw)/arr.size())<<" ms";
    }

    
}

int main()
{
    int n;
    vector<process> arr;
    cout<<"Enter Number of Processes: ";
    cin>>n;
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter Process Name: ";
        string x;
        cin>>x;
        arr.push_back(process(x));
    }
    initialize_random(arr);
    fcfs(arr); //call for first come first serve
    round_robin(arr); //call for round robin

    return 0;
    
}