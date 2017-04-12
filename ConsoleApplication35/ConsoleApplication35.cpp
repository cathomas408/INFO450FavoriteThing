// ConsoleApplication35.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;

class Airplane
{
private:
	 string planeNumber;
	 string planeName;
	 int capacity;
	 int speed;

public:
	Airplane();
	Airplane(string num, string name, int cap, int sp);
	void CapturePlane();
	void ShowPlane();
	int SavePlane(ofstream &outfile);
	
};

class PlaneList
{
	Airplane **list;
	int numrecords;
	int listsize;
	int ReallocateArray();
public:
	PlaneList();
	~PlaneList();
	void GetUserInput();
	void ShowPlaneList();
	
	int SavePlaneList(string filename);
	int ReadPlaneList(string filename);
};
  Airplane::Airplane()
{
	planeNumber = ""; 
	planeName = ""; 
	capacity = 0;
	speed = 0;
}

 Airplane::Airplane(string num, string name, int cap, int sp)
{
	planeNumber = num;
	planeName = name;
	capacity = cap;
	speed = sp;

}

void Airplane::CapturePlane()
{
	cout << "What is the Plane Number? -->";
	getline(cin, planeNumber);
	cout << "Plane Name? -->";
	getline(cin, planeName);
	cout << "What is the Passenger Capacity -->";
	cin >> capacity;
	cout << "What is the Top speed of the plane -->";
	cin >> speed;
	cin.ignore();
	cin.clear();

}

void Airplane::ShowPlane()
{
	cout << "Number : " << planeNumber << "Name : " << planeName << "Capacity: " << capacity << "Top Speed:" << speed << endl;

}

int Airplane::SavePlane(ofstream& outfile)
{
	if (outfile.is_open())
	{
		outfile << planeNumber << "|" << planeName << "|" << capacity << "|" << speed << endl;
		return 0;
	}
	else
		return WRITEERROR;
}


PlaneList::PlaneList()
{
	
	list = new Airplane*[ARRAYSIZE];
	numrecords = 0;
	listsize = ARRAYSIZE;
}

PlaneList::~PlaneList()
{
	for (int i = 0; i < numrecords; i++)
	{
		delete list[i];
	}
	delete[]list;
}

int PlaneList::ReallocateArray()
{
	Airplane **temp;
	temp = new Airplane*[listsize + ARRAYSIZE];
	listsize = listsize + ARRAYSIZE;
	for (int i = 0; i < numrecords; i++)
	{
		temp[i] = list[i];
	}
	delete[]list;
	list = temp;
	return 0;
}

void PlaneList::GetUserInput()
{
	string answer = "Y";
	cout << "enter item Y/N?" << endl;
	getline(cin, answer);
	while (answer == "Y" || answer == "y")
	{
		list[numrecords] = new Airplane();
		list[numrecords]->CapturePlane();
		numrecords++;
		cout << "enter another item Y/N?" << endl;
		getline(cin, answer);
	}

	
}	

void PlaneList::ShowPlaneList()
{
	

	for (int i = 0; i < numrecords; i++)
		list[i]->ShowPlane();
}

int PlaneList::SavePlaneList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (output)
	{
		for (int i = 0; i < numrecords; i++)
		{
			list[i]->SavePlane(output);
		}
		output.close();
	}
	else
	{
		return WRITEERROR;
	}
	return 0;
}
int PlaneList::ReadPlaneList(string filename)
{
	string inum, iname, icap, isp;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened for reading" << endl;
		return READERROR;
	}
	while (!infile.eof())
	{
		if (numrecords == listsize)
		{
			ReallocateArray();

		}
		getline(infile, inum, '|');
		if (!inum.empty())
		{
			getline(infile, iname, '|');
			getline(infile, icap);

			int cap = stoi(icap);
			getline(infile, isp);
			int sp = stoi(isp);
			list[numrecords] = new Airplane(inum, iname, cap, sp);
			numrecords++;

		}
	}
	infile.close();
	return 0;
}

int main()
{
	


	string filename;
	cout << "enter the full filepath you wish to save to" << endl;
	getline(cin, filename);
	
	

	PlaneList myPlane;
	string answer;
	int error;
	
	error = myPlane.ReadPlaneList(filename);
	if (error)
	{
		cout << "Cannot read inventory - continue creating new list? Y/N -->";
		getline(cin, answer);
		if (answer != "Y" && answer != "y")
		{
			return 1;
		}
	}
	myPlane.GetUserInput();
	myPlane.SavePlaneList(filename);
	myPlane.ShowPlaneList();
	return 0;
}



