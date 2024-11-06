#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct Process{
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

void displayQueue(queue<int> q, vector<Process>& processes){
    if(q.empty()){
        cout<<"Empty!";
    }else{
        queue<int> temp = q;
        while(!temp.empty()){
            cout<<" P"<<processes[temp.front()].pid;
            temp.pop();
        }
    }
    cout<<endl;
}

void rr(vector<Process> processes, int n, int quantum){
    queue<int> readyQueue;
    int completedP = 0;
    int currTime = 0;
    vector<int> ganttChart;
    vector<int> ganttChartTime;
    int totalWT = 0;
    int totalTAT = 0;
    
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2){
        return p1.at < p2.at;
    });
    
    int i=0; 
    while(i<n && processes[i].at <= currTime){
        readyQueue.push(i);
        i++;
    }
    
    cout<<"Time\tRunning\t\tReadyQueue"<<endl;
    
    while(completedP < n){
        if(!readyQueue.empty()){
            int currIdx = readyQueue.front();
            readyQueue.pop();
            
            if(processes[currIdx].rt > 0){
                ganttChart.push_back(currIdx);
                ganttChartTime.push_back(currTime);
                
                cout<<currTime<<"\tP"<<processes[currIdx].pid<<"\t\t";
                displayQueue(readyQueue, processes);
                
                if(processes[currIdx].rt > quantum){
                    currTime += quantum;
                    processes[currIdx].rt -= quantum;
                    //check for any waiting process
                    while(i < n && processes[i].at <= currTime){
                        readyQueue.push(i);
                        i++;
                    }
                    readyQueue.push(currIdx);
                }else{
                    currTime += processes[currIdx].rt;
                    processes[currIdx].rt = 0;
                    completedP++;
                    
                    processes[currIdx].ct = currTime;
                    processes[currIdx].tat = processes[currIdx].ct - processes[currIdx].at;
                    processes[currIdx].wt = processes[currIdx].tat - processes[currIdx].bt;
                    
                    totalWT += processes[currIdx].wt;
                    totalTAT += processes[currIdx].tat;
                    
                    while(i < n && processes[i].at <= currTime){
                        readyQueue.push(i);
                        i++;
                    }
                }
            }
        }else{
            //queue is empty , go to first processes
            currTime = processes[i].at;
            readyQueue.push(i);
            i++;
        }
    }
    ganttChartTime.push_back(currTime);
    
    cout<<"Average Waiting Time : "<<fixed<<setprecision(2)<<((float)totalWT/n)<<endl;
    cout<<"Average TurnAround Time : "<<fixed<<setprecision(2)<<((float)totalTAT/n)<<endl;
    
    //Printing Gantt Chart
    cout<<"Gantt Chart: "<<endl;
    int j=0;
    while(j < ganttChart.size()){
        cout<<"| P"<<ganttChart[j++]+1<<" ";
    }
    cout<<"|"<<endl;
    
    j=0;
    while(j < ganttChartTime.size()){
        cout<<ganttChartTime[j++]<<"    ";
    }
    cout<<endl;
    
    for(int z=0; z<n; z++){
        cout<<ctt[z]<<" ";
    }
    
}

int main(){
    int n = 4;
    int quantum = 2;
    vector<Process> processes = {
        {1, 0, 5, 5, 0, 0, 0},
        {2, 1, 3, 3, 0, 0, 0},
        {3, 2, 4, 4, 0, 0, 0},
        {4, 3, 5, 5, 0, 0, 0}
    };
    
    rr(processes, n, quantum);
    
    return 0;
}