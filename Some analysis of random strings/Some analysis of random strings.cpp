//REQUIRES C++17 - "structured bindings" used in `getLettersWithFrequencies` function

#include<fstream> 
#include <iostream>
#include <map>
#include <random>
#include<string> 
#include <unordered_set>
#include <vector>

/*returns unordered_set (not vector) for faster lookup (O(1)) instead of O(N)*/
std::unordered_set<std::string> getDictionaryWords()
{
	std::ifstream fin{ "25Kdictionary.txt" };
	std::string word; 
	std::unordered_set<std::string> words;

	while (std::getline(fin, word))
	{
		words.insert(word); 
	}

	return words; 
}

void printListOfStrings(const std::vector<std::string>& words)
{
	for (const auto& word : words)
	{
		std::cout << word << "\n";
	}
}

std::map<char, int> getLetterFrequencyMap()
{
	std::map<char, int> letterFrequencyMap;

	// Approximate letter frequencies in English words (values are percentage * 10)
	letterFrequencyMap['e'] = 130;  // 13.0%
	letterFrequencyMap['t'] = 91;   // 9.1%
	letterFrequencyMap['a'] = 82;   // 8.2%
	letterFrequencyMap['o'] = 75;   // 7.5%
	letterFrequencyMap['i'] = 70;   // 7.0%
	letterFrequencyMap['n'] = 67;   // 6.7%
	letterFrequencyMap['s'] = 63;   // 6.3%
	letterFrequencyMap['h'] = 61;   // 6.1%
	letterFrequencyMap['r'] = 59;   // 5.9%
	letterFrequencyMap['d'] = 43;   // 4.3%
	letterFrequencyMap['l'] = 40;   // 4.0%
	letterFrequencyMap['c'] = 28;   // 2.8%
	letterFrequencyMap['u'] = 28;   // 2.8%
	letterFrequencyMap['m'] = 24;   // 2.4%
	letterFrequencyMap['p'] = 22;   // 2.2%
	letterFrequencyMap['b'] = 19;   // 1.9%
	letterFrequencyMap['g'] = 18;   // 1.8%
	letterFrequencyMap['v'] = 10;   // 1.0%
	letterFrequencyMap['k'] = 8;    // 0.8%
	letterFrequencyMap['w'] = 7;    // 0.7%
	letterFrequencyMap['f'] = 6;    // 0.6%
	letterFrequencyMap['y'] = 6;    // 0.6%
	letterFrequencyMap['z'] = 1;    // 0.1%
	letterFrequencyMap['x'] = 1;    // 0.1%
	letterFrequencyMap['j'] = 1;    // 0.1%
	letterFrequencyMap['q'] = 1;    // 0.1%

	return letterFrequencyMap;
}


std::vector<char> getLettersWithFrequencies()
{
	std::vector<char> availableLetters;

	std::map<char, int> lettersToFrequencies = getLetterFrequencyMap(); 

	for (const auto& [letter, frequency] : lettersToFrequencies)
	{
		for (int i = 0; i < frequency; ++i)
		{
			availableLetters.push_back(letter);
		}
	}

	return availableLetters;
}

std::string getARandomString(const int desiredNumberOfLettersInString)
{
	std::vector<char> availableLetters = getLettersWithFrequencies();

	//randomly pick N letters from those available - then make all scrambles: 
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<> distribution(0, availableLetters.size() - 1);

	/*Using unordered_set here because it has the `count` method - allows for "convenient" search*/
	std::unordered_set<char> allowedDuplicateLetters = { 'e', 't', 'a', 'o' };

	std::string randomString;
	while(randomString.size() < desiredNumberOfLettersInString)
	{
		char randomChar = availableLetters[distribution(rng)];

		//only allow 4 most common letters to get inserted into the string more than once: 		
		if (randomString.find(randomChar) == std::string::npos)
		{
			randomString.push_back(randomChar);
		}
		else
		{
			//check if letter is one of those allowed duplicates: 
			if (allowedDuplicateLetters.count(randomChar) != 0)
			{
				randomString.push_back(randomChar);
			}
		}
	}

	return randomString;
}

std::vector<std::string> getRandomStringsOfLengthN(const int N)
{
	std::string randomString = getARandomString(N);

	std::vector<std::string> randomStringsOfLengthN; 

	randomStringsOfLengthN.push_back(randomString); //add the first permutation
	while (std::next_permutation(randomString.begin(), randomString.end()))
	{
		randomStringsOfLengthN.push_back(randomString);
	}

	return randomStringsOfLengthN;
}


int main()
{
	std::unordered_set<std::string> dictionaryWords = getDictionaryWords(); 
	//printListOfStrings(words); 

	while (true)
	{
		constexpr int N = 7;
		std::vector<std::string> randomStringsOfLengthN = getRandomStringsOfLengthN(N);

		//printListOfStrings(randomStringsOfLengthN); 
		//std::cout << "Number of random strings: " << randomStringsOfLengthN.size() << "\n";

		for (const std::string& randomString : randomStringsOfLengthN)
		{
			if (dictionaryWords.find(randomString) != dictionaryWords.end())
			{
				std::cout << randomString << " was found in dictionary\n";
			}

			//check if substring from 0 to N - 2 is in dictionary: 
			std::string firstSubstring = randomString.substr(0, N - 2);
			if (dictionaryWords.find(firstSubstring) != dictionaryWords.end())
			{
				std::cout << "Substring of " << randomString << " = "
					<< firstSubstring << " was found in dictionary\n";
			}
		}
		system("pause"); 
	}

}

