/*Author : Abdallah Hemdan */
/***********************************************/
/*
*  ___  __
* |\  \|\  \
* \ \  \_\  \
*  \ \   ___ \EMDAN
*   \ \  \\ \ \
*    \ \__\\ \_\
*     \|__| \|__|
*/

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

#define  GridSize   9
#define  UnAssigned  0

bool FindUnAssignedLocation(int Grid[GridSize][GridSize], int& Row, int& Col);
bool IsSafe(int Grid[GridSize][GridSize], int Row, int Col, int Num);


bool SolveSudoku(int Grid[GridSize][GridSize])
{
	int Row, Col;

	// If there is no unassigned location, we are done
	if (!FindUnAssignedLocation(Grid, Row, Col))
	{
		return true; // success!
	}

	// consider digits 1 to 9
	for (int Num = 1; Num <= 9; Num++)
	{
		// if looks promising
		if (IsSafe(Grid, Row, Col, Num))
		{
			// make an assignment
			Grid[Row][Col] = Num;

			// return, if success, yay!
			if (SolveSudoku(Grid))
			{
				return true;
			}

			// failure, unmake & try again
			Grid[Row][Col] = UnAssigned;
		}
	}
	return false;
}

// Searches to find an entry that is still unassigned
bool FindUnAssignedLocation(int Grid[GridSize][GridSize], int& Row, int& Col)
{
	for (Row = 0; Row < GridSize; Row++)
	{
		for (Col = 0; Col < GridSize; Col++)
		{
			if (Grid[Row][Col] == UnAssigned)
			{
				return true;
			}
		}
	}
	return false;
}

bool UsedInRow(int Grid[GridSize][GridSize], int Row, int Num)
{
	for (int Col = 0; Col < GridSize; Col++)
	{
		if (Grid[Row][Col] == Num)
		{
			return true;
		}
	}
	return false;
}

bool UsedInCol(int Grid[GridSize][GridSize], int Col, int Num)
{
	for (int Row = 0; Row < GridSize; Row++)
	{
		if (Grid[Row][Col] == Num)
		{
			return true;
		}
	}
	return false;
}

bool UsedInBox(int Grid[GridSize][GridSize], int BoxStartRow, int BoxStartCol, int Num)
{
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Col = 0; Col < 3; Col++)
		{
			if (Grid[Row + BoxStartRow][Col + BoxStartCol] == Num)
			{
				return true;
			}
		}
	}
	return false;
}

bool IsSafe(int Grid[GridSize][GridSize], int Row, int Col, int Num)
{
	return (!UsedInRow(Grid, Row, Num) && !UsedInCol(Grid, Col, Num)
		&& !UsedInBox(Grid, Row - Row % 3, Col - Col % 3, Num) && Grid[Row][Col] == UnAssigned);
}


void PrintGrid(int Grid[GridSize][GridSize])
{
	cout << endl;
	cout << "\t\t\t\t\t\t   [ The Solved Grid ]" << endl;
	cout << "--------------------------------------------------------------------------------------"
		"---------------------------------"
		<< endl;
	cout << "--------------------------------------------------------------------------------------"
		"---------------------------------"
		<< endl;

	for (int r = 0; r < GridSize; r++)
	{
		cout << "\t\t\t\t\t\t";
		for (int c = 0; c < GridSize; c++)
		{
			cout << Grid[r][c] << "  ";
		}
		cout << endl;
	}
	cout << "--------------------------------------------------------------------------------------"
		"---------------------------------"
		<< endl;
	cout << "--------------------------------------------------------------------------------------"
		"---------------------------------"
		<< endl;
}

void Intro()
{

	cout << "--------------------------------------------------------------------------------------"
		"---------------------------------"
		<< endl;
	cout << "---------------------------------------------"
		"Welcome To Sudoku Solver--"
		"-----------------------------------------------"
		<< endl;
	cout << endl << endl;

	cout << "Select The Type Of Input : " << endl << endl;
	cout << "\t\t1- File" << endl << endl;
	cout << "\t\t2- input Console" << endl;
}

int main()
{
	Intro();
	int Type;
	cout << "\t\t\t\t\t\t The Choose is : ";
	cin >> Type;


	int Grid[GridSize][GridSize];

	if (Type == 1)
	{
		cout << "\t\t\t\t\tPlease input The File Name : ";
		string FileName;
		cin >> FileName;

		ifstream InFile;
		InFile.open(FileName);

		// Check For The Correct Openning of The File
		if (!InFile)
		{
			cout << "Unable To Open The File " + FileName << endl;
			cout << "Please Check From The File Name Or File The File Location" << endl;
			return 0;
		}
		for (int r = 0; r < GridSize; r++)
		{
			for (int c = 0; c < GridSize; c++)
			{
				InFile >> Grid[r][c];
			}
		}
	}
	else
	{
		for (int Row = 0; Row < GridSize; Row++)
		{
			for (int Col = 0; Col < GridSize; Col++)
			{
				cin >> Grid[Row][Col];
			}
		}
	}

	if (SolveSudoku(Grid))
	{
		PrintGrid(Grid);
	}
	else
	{
		cout << "Sorry..! " << endl;
		cout << "No Solution Exist" << endl;
	}
}