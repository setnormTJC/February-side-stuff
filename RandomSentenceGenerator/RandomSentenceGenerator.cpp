// RandomSentenceGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DictionaryFile.h"
#include "Sentence.h"

int main()
{
	try
	{
		DictionaryFile dictionary("4Kwords_andTheirPartsOfSpeech.csv");

		for (const auto& [word, partOfSpeech] : dictionary.wordsToPartsOfSpeech)
		{
			//if (partOfSpeech =)
			std::cout << word << " is a(n) " << partOfSpeech << "\n";
		}

	}

	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}

}

