#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	string words;
	int wordCount = 0; //tracks word count
	int lenghtOfTwo = 0; //tracks word length of 2
	int longestWord = 0; //tracks the number of longest words
	vector<string> longWord;
	
	ifstream file;
	string fileName = "input.txt"; //file for testing
	
	file.open(fileName); //opens the file
	
	//loop to perform calculations
	while(!file.eof())
	{
		file >> words; //reads in file's contents
		wordCount++; //increment word count
		
		if (words.length() == 2)
		{
			lenghtOfTwo++;
		}
		
		if (words.length() == 10)
		{
			longestWord++;
			longWord.push_back(words);
		}
	}
	
	//format output
	cout << fileName << " containes " << wordCount << " words" << endl;
	cout << "words of size 2 occur the most: " << lenghtOfTwo << " times" << endl;
	cout << "the longest words have " << " letters and occur " << longestWord <<" times" << endl;
	
	//printing words length of 10
	for (unsigned int i = 0; i < longWord.size(); i++)
	{
		cout << "\t" << longWord[i] << endl;
	}
	file.close();
    return 0;
}
