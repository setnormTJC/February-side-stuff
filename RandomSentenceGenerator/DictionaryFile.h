#pragma once

#include<fstream> 
#include<map> 
#include <iostream>
#include <string>

using std::string;

class DictionaryFile
{
private: 

public: 
	DictionaryFile() = delete; 
	DictionaryFile(const string& filename); 


	std::map<string, string> wordsToPartsOfSpeech;
};

