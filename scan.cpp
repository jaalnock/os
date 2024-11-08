#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int n;
  cout << "No. of requests : ";
  cin >> n;

  vector<int> req(n);
  cout << "Enter the requests: ";
  for (int i = 0; i < n; i++)
  {
    cin >> req[i];
  }

  int currHead;
  cout << "Enter the initial head : ";
  cin >> currHead;

  int direction;
  cout << "Enter 0 for right, 1 for left : ";
  cin >> direction;

  int boundary;
  cout << "Enter the boundary : ";
  cin >> boundary;

  int totalHeadMov = 0;

  req.push_back(currHead);
  n++;

  sort(req.begin(), req.end());

  int head_idx = -1;
  for (int i = 0; i < n; i++)
  {
    if (req[i] == currHead)
    {
      head_idx = i;
      break;
    }
  }

  if (!direction)
  {
    cout << currHead;
    for (int i = head_idx + 1; i < n; i++)
    {
      totalHeadMov += abs(currHead - req[i]);
      currHead = req[i];
      cout << " -> " << currHead;
    }

    if (currHead != boundary - 1)
    {
      totalHeadMov += abs(currHead - (boundary - 1));
      currHead = boundary - 1;
      cout << " -> " << currHead;
    }

    for (int i = head_idx - 1; i >= 0; i--)
    {
      totalHeadMov += abs(currHead - req[i]);
      currHead = req[i];
      cout << " -> " << currHead;
    }
  }
  else
  {
    cout << currHead;
    for (int i = head_idx - 1; i >= 0; i--)
    {
      totalHeadMov += abs(currHead - req[i]);
      currHead = req[i];
      cout << " -> " << currHead;
    }

    if (currHead != 0)
    {
      totalHeadMov += abs(currHead);
      currHead = 0;
      cout << " -> " << currHead;
    }

    for (int i = head_idx + 1; i < n; i++)
    {
      totalHeadMov += abs(currHead - req[i]);
      currHead = req[i];
      cout << " -> " << currHead;
    }
  }

  cout << endl;
  cout << "Total Head Movement : " << totalHeadMov;
  cout << endl;
}