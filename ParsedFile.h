//***************************************************************************************

// Programadores : Alex Santos e Ivan Jimenez CCOM 3034 SecciÛn 001

// Num. Est. : 801-11-7707, 801-11-3205  Primer Semestre 2012-2013

// Proyecto Final Prof. R. Arce

// Archivo : ParsedFile.h

// Fecha : 11 de diciembre de 2012 *

//***********************************************************************************************************************

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <vector>
#include <utility>
#include <map>
#include <iterator>

typedef unsigned int uint;

using namespace std;

class ParsedFile {
private:	
	string name;
public:
	ParsedFile() {};
	ParsedFile(string n) {name = string("./moviesdb/").append(n);}
	string getName() {return name;}
	/*
	   This function reads every line in an archive, separates them
	   into words and returns them as a vector of strings.

	   Pre-condition:  The ParsedFile class object has been asigned a name.
	   Post-condition: Returns results as a vector of strings.
	*/
	
	void readAndTokenize(std::tr1::unordered_set<string>& stops ,std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq);
};


/*
   getdir:
   Receives the name of a directory as a parameter and returns (via a second parameter) a
   vector of strings that contains the names for each archive in the directory. The whole
   value that is returned indicates if the operation was successfull: 0 indicates that there
   were no errors, any other value indicates that an error occured.
   
   Pre-condition:  None
   Post-condition: Changes the content of the previous vector as a second parameter.
*/
int getdir (string, vector<ParsedFile> &);


/*
   tokenize:
    Recieves two strings as a parameters:
	- str:   the string we wish to break up into words
	- delim: the string deliminator we use to determine
			 where we break str, usually a space, comma, etc.
	
	Returns a vector of strings obtained from str.
	
	Pre-condition:  str and delim are nor empty strings.
	Post-condition: Does not modify str nor delim. 
					Returns the vector of strings.
*/
void tokenize(const string & str, const string & delim, std::tr1::unordered_set<string>& stops ,std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq, string& name);

/*
	clean:
	Receives a string as a parameter:
	- tokenized_line: the word that was read from the file
	
	Modify the recieved word. Does not return anything.
	
	Pre-condition:  tokenized_line is not an empty string
	Post-condition: - Eliminates every character of the word that is not a letter.
					- Converts every character into lower case.
*/
void clean(string& tokenized_line);

/*
	stop:
	stop:
	Recieves an unordered_set as a parameter:
	- stops: the unordered_set of the stop words.
	
	Modify the recieved word. Does not return anything.
	
	Pre-condition:  tokenized_line is not an empty string
	Post-condition: - Eliminates every character of the word that are not letters
					- Converts every character into lower case.
	
	Pre-condicion: tokenized_line no es un string vacio
	Post-condition: - Elimina todos los caracteres de la palabra que no sean letras
					- Convierte todos los caracteres en "lower case"
*/
void stop(std::tr1::unordered_set<string>& );

/*
	inputTokenize:
	Receives an input line and a delim:
	 - line: contains the words
	 
	Receives a line and return a vector with the words
*/
vector<string> inputTokenize(const string & str, const string & delim);

/*
	getResults:
	Receives word one, word two, files_freq, results:
	 - word one and two: user input
	 - files_freq: contains the words, files, frequency, word => files => frequency
	 - results: contains the qualifying files
	 
	Searches for all the files related to the two words. Then it looks for the files 
	that have the two words and finally it stores them in a map, that later sorts the files
*/
std::multimap<int, string> getResults(string inputs1, string inputs2, std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq);

/*
	displayResults:
	Receives results:
	 - results: contains qualifying files
	 
	Displays the three higher files based on frequency
*/
void displayResults(multimap<int, string>&);

/*
	getWords:
	Receives a empty vector of strings:
	 - inputs: stores the inputs of the user
	 - breaks down the input into separate words
*/
void getWords(vector<string>&, int&);

/*
	setEngine:
	
	- Calls all the necessary functions to set the engine and allow the search 
*/
void setEngine (string&, std::tr1::unordered_set<string>&, vector<ParsedFile>&, std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >&);

//Displays the logo
void displayLogo(void);