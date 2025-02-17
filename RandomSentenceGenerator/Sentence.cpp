#include "Sentence.h"


Subject::Subject(const string& pronoun)
{
	if (pronoun != "pronoun") //modify this somehow ...
	{
		throw std::exception("subject does not meet required parts of speech");
	}
	theSubject = pronoun; 
}

SimpleSentence::SimpleSentence(const Subject& subject, const string& verb)
{
	theSimpleSentence = subject.theSubject + verb; 
}


