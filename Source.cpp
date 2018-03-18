#include <iostream>
#include <vector>

using namespace std;

class Client
{
private:
	vector<int> data;
	int arrivalTime;
	int serviceTime;
	int allowablewaitingTime;
public:
	friend class MyQueue;
	int GetAT();
	int GetST();
	int GetAWT();
	void input();
	void SetAT(int);
	void SetST(int);
	void SetAWT(int);
};

class MyQueue
{
private:
	vector<Client> clientdata;
	vector<bool> ser;
	vector<int> departureTime;
	bool count = false;
public:
	void push(Client);
	void output(int);
	void swap(int);
};

void Client::SetAT(int arrtime)
{
	arrivalTime = arrtime;
}
void Client::SetST(int sertime)
{
	serviceTime = sertime;
}
void Client::SetAWT(int alltime)
{
	allowablewaitingTime = alltime;
}
int Client::GetAT()
{
	return arrivalTime;
}
int Client::GetST()
{
	return serviceTime;
}
int Client::GetAWT()
{
	return allowablewaitingTime;
}

void MyQueue::push(Client p)
{
	clientdata.push_back(p);
}

void MyQueue::output(int i)
{
	int depTime;
	if (ser[i] == false)
	{
		cout << "No";
		departureTime.push_back(0);
		count = true;
	}
	else
	{
		cout << "Yes" << "\t";
		int nowTime = clientdata[0].arrivalTime;
		for (int j = 1; j <= i; j++)
		{
			nowTime = nowTime + clientdata[j - 1].serviceTime;
		}
		if (count == true)
		{
			for (int k = 0; k < i; k++)
			{
				if (ser[k] == false)
					nowTime = nowTime - clientdata[k].serviceTime;
			}
		}
		depTime = nowTime + clientdata[i].serviceTime;
		departureTime.push_back(depTime);
		if (departureTime[i] != 0)
			cout << departureTime[i];
	}
}

void MyQueue::swap(int i)
{
	int nowTime = clientdata[0].arrivalTime;
	if (i == 0)
	{
		ser.push_back(true);
	}
	else if (i > 0)
	{
		for (int j = 1; j <= i; j++)
		{
			nowTime = nowTime + clientdata[j - 1].serviceTime;
		}
		for (int k = 0; k < ser.size(); k++)
		{
			if (ser[k] == false)
				nowTime = nowTime - clientdata[k].serviceTime;
		}
		if (nowTime - clientdata[i].arrivalTime > clientdata[i].allowablewaitingTime)
		{
			if (nowTime - clientdata[i - 1].serviceTime - clientdata[i].arrivalTime <= clientdata[i - 1].allowablewaitingTime && nowTime - clientdata[i - 1].serviceTime + clientdata[i].serviceTime - clientdata[i - 1].arrivalTime < clientdata[i - 1].allowablewaitingTime)
			{
				clientdata.push_back(clientdata[i - 1]);
				clientdata[i - 1] = clientdata[i];
				clientdata[i] = clientdata[i + 1];
				clientdata.erase(clientdata.end() - 1);
				ser.push_back(true);
			}
			else
				ser.push_back(false);
		}
		else
			ser.push_back(true);
	}
}

void Client::input()
{
	cin >> arrivalTime >> serviceTime >> allowablewaitingTime;
}

void main()
{
	int num;
	MyQueue queue;
	cout << "\tArrival time" << "\tService time" << "\tAllowable waiting time" << endl;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		Client people;
		cout << "Client " << i + 1 << ":" << "\t";
		people.input();
		queue.push(people);
		queue.swap(i);
	}
	cout << "\tServed or not?" << "\tDeparture time" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << "Client " << i + 1 << ":" << "\t";
		queue.output(i);
		cout << endl;
	}
	system("pause");
}

