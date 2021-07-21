#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

void addScore();
bool checkDate(string month, int day);
bool scoreExistForDate(string month, int day);
bool checkScore(int score1, int score2, int score3);
void viewScore();
void averageScores();

int main()
{
	/*Write a program that uses a file named scores.txt to record sets of bowling scores for different dates.
	You can assume that the user will always record exactly 3 scores for any given date.scores.txt should store the data so that each line has a month, day, and
	the 3 scores the user earned on that date.For example, scores.txt should look something like this:

		January 15 200 300 126
		April 20 125 100 150
		May 17 300 100 215
		When the program first starts, no scores should be recordedand scores.txt should not exist.In a continuous loop, give the user four options :

		1. Quit the program.

		2. View all Scores.If the user selects this option, call a function named viewScores.This function should print the scores in a nicely formatted manner.
		For example :

		"On January 15, you scored 200, 300, and 126"

		etc..

		3. Add a Score.If the user selects this option, call a function named addScore.This function should ask the user for a month, day, and 3 scores.
		The day should be between 1 and 31, and each of the 3 scores should be between 0 and 300. Do not worry about validating the 'month' string.
		When the user submits data to be entered, a separate function named scoreExistsForDate should be called.
		This function returns true if there is already an entry in scores.txt for the given date.In that case, tell the user that a set of scores already existsand do not
		enter the new score.If all input validation passes(i.e.the day is between 1 and 31, the scores are all between 0 and 300, there is no entry for the given date) 
		then append the data to scores.txt.Do not worry about the dates being out of order!

		4. Average Scores.If the user selects this option, call a function named averageScores.
		This function should add up all scores for all of the dates on scores.txtand then calculate the average.
		
		Make sure to perform error handling as well(for example, if the user tries to view scores before scores.txt even exists, the program should not crash!)*/
	cout << "There are four options to you: " << endl;
	cout << "(q)uit the program." << endl;
	cout << "(v)iew all scores." << endl;
	cout << "(a)dd a score." << endl;
	cout << "(c)alculate the average scores. \n\n";
	cout << "The day should be between 1 and 31, and each of the 3 scores should be between 0 and 300\n\n";

	char option;
	do
	{
		cout << "Choose you option: ";
		cin >> option;
		cin.ignore();
		option = tolower(option);
		switch (option)
		{
		case 'v':
			viewScore();
			cout << "\n\n";
			break;
		case 'a':
			addScore();
			cout << "\n\n";
			break;
		case 'c':
			averageScores();
			cout << "\n\n";
			break;
		default:
			break;
		}
	} while (option != 'q');

	return 0;
}

void viewScore()
{
	ifstream inStream;
	inStream.open("scores.txt");

	int day, score1, score2, score3;

	if (inStream.fail())
	{
		cout << "Input file opening failed.";
		inStream.close();
		return;
	}
	else
	{
		while (!inStream.eof())
		{

			string month;
			inStream >> month >> day >> score1 >> score2 >> score3;
			if (month == "")
			{
				return;
			}
			cout << "On " << month << " " << day << ", you scored " << score1 << ", " << score2 << ", and " << score3 << endl;
		}
	}
	
	inStream.close();
}

void addScore()
{
	ofstream outStream;
	outStream.open("scores.txt", ios::app);

	string month;
	int day, score1, score2, score3;

	do
	{
		cout << "\n\n";
		cout << "Enter new scores and date. For example : May 15 300 200 100" << endl;
		cout << "Please enter: " << endl;
		cin >> month >> day >> score1 >> score2 >> score3;
		if (checkScore(score1, score2, score3) == false)
		{
			cout << "Wrong Value of Scores!" << endl;
		}
	} while (((checkDate(month, day) == false) || (scoreExistForDate(month, day) == true)) || (checkScore(score1, score2, score3) == false));
	
	outStream << month << " " << day << " " << score1 << " " << score2 << " " << score3 << endl;
	cout << "Data Successfully Added to Your File";
	outStream.close();
}

bool checkDate(string month, int day)
{
	string monthArr[] = { "January", "February", "March", "April", "May", "June", "July",
							"August", "September", "October", "November", "December" };
	int SIZE = sizeof(monthArr) / sizeof(string);

	for (int i = 0; i < SIZE; i++)
	{
		if (month == monthArr[i] && ((day > 0) && (day < 32)))
		{
			return true;
		}
	}
	cout << "Wrong Value of Date!";
	return false;
}

bool scoreExistForDate(string month, int day)
{
	ifstream inStream;
	inStream.open("scores.txt");

	string monthTest;
	int dayTest, score1, score2, score3;

	while (!inStream.eof())
	{
		inStream >> monthTest >> dayTest >> score1 >> score2 >> score3;
		if ((month == monthTest) && (day == dayTest))
		{
			cout << "A set of scores already exists!";
			return true;
		}
	}
	return false;
}

bool checkScore(int score1, int score2, int score3)
{
	if ((score1 < 0) || (score1 > 300) || (score2 < 0) || (score2 > 300) || (score3 < 0) || (score3 > 300))
	{
		return false;
	}
	return true;
}

void averageScores()
{
	ifstream inStream;
	inStream.open("scores.txt");
	
	int day, score1, score2, score3, countLine = 0;
	int total = 0, totalEachLine = 0;
	double average = 0;
	if (inStream.fail())
	{
		cout << "Input file opening failed.";
		inStream.close();
		return;
	}
	else
		while (!inStream.eof())
		{
			string month;
			inStream >> month >> day >> score1 >> score2 >> score3;
			if (month == "")
			{
				break;
			}
			totalEachLine = score1 + score2 + score3;
			total += totalEachLine;
			countLine++;
		}
	inStream.close();

	int numberofScores = countLine * 3;
	average = (double)total / numberofScores;

	cout << "The averge of the scores in a file is: " << average;
}
