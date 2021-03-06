/*
Caesar cipher
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;
class Shift_Cipher
{
public:
	Shift_Cipher(int shift);
	~Shift_Cipher();

	string encrypt(string message);
	string decrypt(string message);
	
	
	//numberLetters[0] - return A;
	//numberLetters[1] - return B;
private:
	int m_shift;
	string numberLettersSTRING;
	unordered_map<char, int> MAPletterNumbers;
protected:

};

int main()
{
	//string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string text, encoded_message, decoded_message;
	int shift;
	cout << "Enter message: ";
		getline(cin, text);
	cout << "Enter shift " << endl;
	cin >> shift;
	Shift_Cipher cipher(shift);
	encoded_message = cipher.encrypt(text);
	cout <<"Encoded: " << encoded_message << endl;
	decoded_message = cipher.decrypt(encoded_message);
	cout << "Decoded: "<<decoded_message << endl;

	int wait;
	cin >> wait;
    return 0;
}

Shift_Cipher::Shift_Cipher(int shift)
{
	m_shift = shift;
	numberLettersSTRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < numberLettersSTRING.size(); i++)
	{
		//MAPletterNumbers.emplace(numberLettersSTRING[i]);
		char letter = numberLettersSTRING[i];
		MAPletterNumbers.emplace(letter, i);
	}
}

Shift_Cipher::~Shift_Cipher()
{

}

string Shift_Cipher::encrypt(string message)
{
	string encoded_message = "";
	char eachLetter,encodedLetter=' ';
		for (int i = 0; i<message.size(); i++)
	{
			eachLetter = message[i];
			if (eachLetter == ' ')
			{
				encoded_message = encoded_message + eachLetter;
			}
			else
			{
				int number = MAPletterNumbers[eachLetter];
				
				//encoded_message = encoded_message + encodedLetter;
				int shiftedNumber = (number + m_shift) % 26;
				encodedLetter = numberLettersSTRING[shiftedNumber];
				encoded_message = encoded_message + encodedLetter;
			}
	}
		
		
	
		return encoded_message;
}

string Shift_Cipher::decrypt(string message)
{
	string decoded_message = "";
	char eachLetter, decodedLetter=' ';
	for (int i = 0; i<message.size(); i++)
	{
		eachLetter = message[i];
		if (eachLetter == ' ')
		{
			decoded_message = decoded_message + eachLetter;
		}
		else {
			int number = MAPletterNumbers[eachLetter];
			//decoded_message = decoded_message + decodedLetter;
			int shiftedNumber = (number - m_shift) % 26;
			if (shiftedNumber<0)
			{
				shiftedNumber = shiftedNumber + 26;
			}
			decodedLetter = numberLettersSTRING[shiftedNumber];
			decoded_message = decoded_message + decodedLetter;
		}
	}

	return decoded_message;
}
