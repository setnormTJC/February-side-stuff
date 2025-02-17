#include "DictionaryFile.h"


DictionaryFile::DictionaryFile(const string& filename)
{
	std::ifstream fin{ filename };
	if (!fin) throw std::exception("could not find dictionary file");

	while (!fin.eof())
	{
		string currentWord, currentPartOfSpeech; 
		std::getline(fin, currentWord, ',');
		std::getline(fin, currentPartOfSpeech, '\n');

		//std::cout << currentWord << "-" << currentPartOfSpeech << "\n";

		wordsToPartsOfSpeech.insert({ currentWord, currentPartOfSpeech });
	}

	fin.close(); 
}
