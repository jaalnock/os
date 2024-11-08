#include<iostream>
#include<vector>

using namespace std;

void printFrame(vector<int>& frame, int capacity) {
	cout<<"Frame: ";
	for(int i=0; i<capacity; i++) {
		if(frame[i] == -1) {
			cout<<" -";
		} else {
			cout<<" "<<frame[i];
		}
	}
	cout<<endl;
}

void fifo(vector<int>& pages, int capacity, int n) {
	vector<int> frame(capacity, -1);
	int faults= 0;
	int index = 0;
	for(int i=0; i<n; i++) {
		bool found = false;
		for(int j=0; j<capacity; j++) {
			if(pages[i] == frame[j]) {
				found = true;
				break;
			}
		}

		if(!found) {
			frame[index] = pages[i];
			faults++;
			index = (index + 1)%capacity;
		}

		printFrame(frame, capacity);
	}
	cout<<"Total Page faults in FIFO : "<<faults<<endl;
	cout<<"Total Page  hits in  FIFO : "<<(n-faults)<<endl;
	cout<<endl;
}

void lru(vector<int> pages, int capacity, int n) {
	vector<int> frame(capacity, -1);
	vector<int> timeUsed(capacity, 0);
	int faults=0, countTime=0;

	for(int i=0; i<n; i++) {
		bool found = false;
		for(int j=0; j<capacity; j++) {
			if(pages[i] == frame[j]) {
				timeUsed[j] = countTime++;
				found = true;
				break;
			}
		}

		if(!found) {
			for(int j=0; j<capacity; j++) {
				if(frame[j] == -1) {
					frame[j] = pages[i];
					timeUsed[j] = countTime++;
					faults++;
					found = true;
					break;
				}
			}
		}

		int leastUsedIndex = 0;

		if(!found) {
			for(int j=1; j<capacity; j++) {
				if(timeUsed[j] < timeUsed[leastUsedIndex]) {
					leastUsedIndex = j;
				}
			}

			frame[leastUsedIndex] = pages[i];
			timeUsed[leastUsedIndex] = countTime++;
			faults++;
		}

		printFrame(frame, capacity);
	}
	cout<<"Total Page faults in LRU : "<<faults<<endl;
	cout<<"Total Page  hits in  LRU : "<<(n-faults)<<endl;
	cout<<endl;
}

void optimal(vector<int> pages, int capacity, int n) {
	vector<int> frame(capacity, -1);
	int faults=0;

	for(int i=0; i<n; i++) {
		bool found = false;
		for(int j=0; j<capacity; j++) {
			if(pages[i] == frame[j]) {
				found = true;
				break;
			}
		}

		if(!found) {
			for(int j=0; j<capacity; j++) {
				if(frame[j] == -1) {
					frame[j] = pages[i];
					faults++;
					found = true;
					break;
				}
			}
		}

		int farthest = 0;
    int rep_idx = 0;

		if(!found) {
			for(int j=0; j<capacity; j++) {
			    int k;
				for(k=i+1; k<n; k++) {
					if(frame[j] == pages[k]){
					    if(k > farthest){
					        farthest = k;
					        rep_idx = j;
					    }
					    break;
					}
				}
				if(k==n) {
					rep_idx = j;
					break;
				}
			}
			frame[rep_idx] = pages[i];
			faults++;
		}


		printFrame(frame, capacity);
	}
	cout<<"Total Page faults in Optimal : "<<faults<<endl;
	cout<<"Total Page  hits in  Optimal : "<<(n-faults)<<endl;
	cout<<endl;
}

int main() {

	int n, capacity;
	cout<<"Enter the number of pages: ";
	cin >> n;
	vector<int> pages(n);
	cout<<"Enter the pages with space in between : ";
	for(int i=0; i<n; i++) {
		cin >> pages[i];
	}
	cout<<"Enter the capacity of frame : ";
	cin>>capacity;

	int choice = -1;

	do {
		cout<<"1.FIFO\n2.LRU\n3.Optimal\n4.Exit\nEnter the choice : ";
		cin >> choice;
		switch(choice) {
		case 1 :
			fifo(pages, capacity, n);
			break;

		case 2 :
			lru(pages, capacity, n);
			break;

		case 3 :
		    optimal(pages, capacity, n);
		    break;

		case 4 :
			cout<<"Exiting the program";
			break;

		default :
			cout << "Invalid Choice";

		}
	} while(choice != 4);

	return 0;
}