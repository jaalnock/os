#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct Process
{
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int findMinJob(vector<Process> processes, int n, int currTime)
{
    int minJobIndex = -1;
    int minJobRT = 1e9;

    for (int i = 0; i < n; i++)
    {
        if (processes[i].rt > 0 && processes[i].rt < minJobRT && processes[i].at <= currTime)
        {
            minJobIndex = i;
            minJobRT = processes[i].rt;
        }
    }

    return minJobIndex;
}

void sjf(vector<Process> processes, int n)
{
    int currTime = 0;
    int totalWT = 0;
    int totalTAT = 0;
    vector<int> ganttChart;
    vector<int> ganttChartTime;
    int completedP = 0;

    while (completedP < n)
    {
        int shortestJobIdx = findMinJob(processes, n, currTime);

        if (shortestJobIdx == -1)
        {
            currTime++;
            continue;
        }

        ganttChart.push_back(shortestJobIdx);
        ganttChartTime.push_back(currTime);

        processes[shortestJobIdx].rt--;
        currTime++;

        if (processes[shortestJobIdx].rt == 0)
        {
            completedP++;
            processes[shortestJobIdx].ct = currTime;
            processes[shortestJobIdx].tat = processes[shortestJobIdx].ct - processes[shortestJobIdx].at;
            processes[shortestJobIdx].wt = processes[shortestJobIdx].tat - processes[shortestJobIdx].bt;

            totalTAT += processes[shortestJobIdx].tat;
            totalWT += processes[shortestJobIdx].wt;
        }
    }

    ganttChartTime.push_back(currTime);

    cout << "Average Waiting TIme : " << fixed << setprecision(2) << (float)totalWT / n << endl;
    cout << "Average TurnAround TIme : " << fixed << setprecision(2) << (float)totalTAT / n << endl;

    cout << "Gantt Chart : " << endl;
    int j = 0;
    while (j < ganttChart.size())
    {
        cout << "| P" << ganttChart[j++] + 1 << " ";
    }
    cout << "|" << endl;
    j = 0;
    while (j < ganttChartTime.size())
    {
        cout << ganttChartTime[j++] << "    ";
    }
    cout << endl;
}

int main()
{
    int n = 4;

    vector<Process> processes = {
        {1, 2, 3, 3, 0, 0, 0},
        {2, 5, 1, 1, 0, 0, 0},
        {3, 3, 6, 6, 0, 0, 0},
        {4, 1, 4, 4, 0, 0, 0}};

    sjf(processes, n);
    return 1;
}