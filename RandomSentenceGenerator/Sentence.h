#pragma once

#include<set> 
#include <string>

using std::string; 

class Subject
{
private: 
	string theSubject; 
public: 
	Subject() = delete; 
	Subject(const string& pronoun);
	Subject(const string& article, const string& noun);

	friend class SimpleSentence; 
};

class SimpleSentence
{
protected: //so that child class, CompoundSentence can use directly  
	std::set<string> partsOfSpeech =
	{
		"adjective",
		"adverb",
		"conjunction",
		"noun", 
		"preposition", //at, in, under 
		"pronoun", //he, it, they, she
		"verb", 
	};

	string theSimpleSentence; 

public: 
	SimpleSentence() = delete; 
	/*For examples, see: https://en.wikipedia.org/wiki/Sentence_clause_structure#Typology_of_clauses*/
	SimpleSentence(const Subject& subject, const string& verb);
	SimpleSentence(const string& subject, const string& verb, const string& object);
	//SimpleSentence(const string& subject, const string& verb, const string& subjectComplement);
	SimpleSentence(const string& subject, const string& verb, const string& indirectObject, const string& directObject);
	//SimpleSentence(const string& subject, const string& verb, const string& object, const string& objectComplement);

	friend class CompoundSentence; 
	friend class ComplexSentence;
};

/*Roughly - a simple sentence joined by a conjunction*/
class CompoundSentence
{
private: 
	SimpleSentence firstIndependentClause; 
	SimpleSentence secondIndependentClause;

	string theCompoundSentence; 
public: 
	CompoundSentence() = delete; 
	CompoundSentence(const SimpleSentence& firstIndependentClause, const string& conjunction,
		const SimpleSentence& secondIndependentClause);
};

class ComplexSentence
{

};
