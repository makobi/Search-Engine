//***************************************************************************************

// Programadores : Alex Santos e Ivan Jimenez CCOM 3034 SecciÛn 001

// Num. Est. : 801-11-7707, 801-11-3205  Primer Semestre 2012-2013

// Proyecto Final Prof. R. Arce

// Archivo : ParsedFile.cpp 

// Fecha : 11 de diciembre de 2012 *

//***********************************************************************************************************************

#include <algorithm>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include "ParsedFile.h"
#include <vector>
#include <utility>
#include <map>
#include <iterator>

void ParsedFile::readAndTokenize(std::tr1::unordered_set<string>& stops, std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq) {
  	string line;
  	ifstream myfile (name.c_str());
 	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			tokenize(line, " ", stops, files_freq, name); // Receives files_freq and the name of the files to create the unmaps
		}
		myfile.close();
	}
	else cout << "readAndTokenize: Unable to open file, returning empty vector"; 
}


void tokenize(const string & str, const string & delim, std::tr1::unordered_set<string>& stops ,std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq, string& name) {
	//vector<string> tokens;
	size_t p0 = 0, p1 = string::npos;
	while(p0 != string::npos) {
    	p1 = str.find_first_of(delim, p0);
    	if(p1 != p0){
      		string token = str.substr(p0, p1 - p0);
      		clean(token); // Cleans the words
			if(stops.find(token) == stops.end()) // checks if the word is a stop word
				files_freq[token][name]++; // If not it either creates the new relation or it increments the counter
      	}
		p0 = str.find_first_not_of(delim, p1);
	}
	//return tokens;
}

// This is the original tokenize function used to clean and separate the words of the line
vector<string> inputTokenize(const string & str, const string & delim) {

	vector<string> tokens;
	size_t p0 = 0, p1 = string::npos;
	while(p0 != string::npos) {
    	p1 = str.find_first_of(delim, p0);
    	if(p1 != p0) {
      		string token = str.substr(p0, p1 - p0);
      		clean(token);
			tokens.push_back(token);
      	}
		p0 = str.find_first_not_of(delim, p1);
	}
	return tokens;
}

int getdir (string dir, vector<ParsedFile> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(ParsedFile(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void clean(string& tokenized_line){
	for(int i=0; i < tokenized_line.length(); i++){
		if(!(isalpha(tokenized_line[i]))){
			tokenized_line.erase(i, 1); // if it is not a letter, it erases it
			i--;
		}
		else tokenized_line[i] = tolower(tokenized_line[i]); // lowers all letters
	}
}

void stop(std::tr1::unordered_set<string>& stops){

	ifstream entrada ("stopwords.txt");
	string word;
 	if (entrada.is_open()) {
		while ( entrada.good() ) {
			entrada >> word;
			stops.insert(word);
		}
	}
	entrada.close();
}

std::multimap<int, string> getResults(string inputs1, string inputs2, std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq){
		std::multimap<int, string> results;
		std::tr1::unordered_map<std::string,std::tr1::unordered_map<std::string,int> >::iterator it = files_freq.find(inputs1);
		std::tr1::unordered_map<std::string,std::tr1::unordered_map<std::string,int> >::iterator mo = files_freq.find(inputs2);
	 
		if(it != files_freq.end() && mo != files_freq.end()) 
    		for(std::tr1::unordered_map<std::string, int >::iterator re = it->second.begin(); re != it->second.end(); ++re)
				for(std::tr1::unordered_map<std::string, int >::iterator fe = mo->second.begin(); fe != mo->second.end(); ++fe)
					if(re->first == fe->first)
						results.insert(pair<int, string>(re->second + fe->second, re->first)); // inserts qualifying files into the map
		return results;
								
}

void getWords(vector<string>& inputs, int& count){

	inputs.clear();
	char line[256];
	do { 
		cout << "Enter one or two words separated by a space: " << endl;
		cin.getline (line, 256);//Esta linea se esta ejecutando sola.
		if(count >= 1)
			cin.getline (line, 256);
		cout << endl;
		inputs = inputTokenize(line, " ");
	} while(!(inputs.size() <= 2) || inputs[0].size() > 256);
	
	if(inputs.size() == 1){
		clean(inputs[0]);
	}
	
	else{
		clean(inputs[0]);
		clean(inputs[1]);
	}
	
}

void setEngine (string& dir, std::tr1::unordered_set<string>& stops, vector<ParsedFile>& files, std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> >& files_freq){

	stop(stops);
    getdir(dir,files);
    for (unsigned int i = 3;i < files.size();i++)
    		files[i].readAndTokenize(stops, files_freq);
}

void displayResults(multimap<int, string>& results){

	int count  = 0;
	cout << "Your search returned " << results.size() << " results. " << endl;
	if (results.size() >= 3){
		cout << "Showing you the three results with higher frequency: " << endl;
		for(map<int, string>::reverse_iterator bo = results.rbegin(); bo != results.rend(); bo++){
     		std::cout << bo->second << endl;
     		count++;
     		if(count == 3)
     			break;
     	}
	}
	else if(results.size() < 3){
	
		cout << "Showing you all the results: " << endl;
		for(map<int, string>::iterator bo = results.begin(); bo != results.end(); ++bo)
     		std::cout << bo->second << endl;
	}
}

void displayLogo(void){

    /*cout << "WW       WWW       WW EEEEEEE LL        CCCCC   OOOOO   MMMMM    MMMMM EEEEEEE\n";
  	cout << "   WW     WW WW     WW  EE      LL       CC      OO   OO  MM  MM  MM  MM EE\n";
    cout << "    WW   WW   WW   WW   EEEEE   LL      CC      OO     OO MM   MMMM   MM EEEEE\n";
	cout << "     WW WW     WW WW    EE      LL       CC      OO   OO  MM    MM    MM EE\n";
	cout << "      WWW       WWW     EEEEEEE LLLLLLL   CCCCC   OOOOO   MM          MM EEEEEEE\n\n\n";
	
    cout << "   222222      BBBBBB         BBBBBB         AAA       MMMM     MMMM  !!!\n";
    cout << "  22    22     BB   BBB       BB   BBB      AA AA      MM MM   MM MM  !!!\n";
    cout << "       22      BB   BBB       BB   BBB     AA   AA     MM  MM MM  MM  !!!\n";
	cout << "      22       BBBBBB    ===  BBBBBB      AAAAAAAAA    MM   MMM   MM  !!!\n";
    cout << "     22        BB   BBB       BB   BBB   AA       AA   MM    M    MM  !!!\n";
	cout << "   22          BB   BBB       BB   BBB  AA         AA  MM         MM  !!!\n";
    cout << "  22222222     BBBBBBB        BBBBBBB  AA           AA MM         MM   o\n\n\n";
                                  
    cout << "   SSSSS       EEEEEEE NNN     NN   GGGG  IIIIII NNN     NN EEEEEEE\n";
    cout << "  SSS          EE      NN NN   NN  GG       II   NN NN   NN EE\n";
	cout << "    SS         EEEEE   NN  NN  NN GG  GGG   II   NN  NN  NN EEEEE\n";
	cout << "     SSS       EE      NN   NN NN  GG  GG   II   NN   NN NN EE\n";
	cout << "  SSSSS  o     EEEEEEE NN     NNN   GGGG  IIIIII NN     NNN EEEEEEE\n";
	cout << " ____________________________________________________________________________\n\n";
	*/
	
	//cout.width(5);
    cout << "      BBBBBB         BBBBBB         AAA       MMMM     MMMM  !!!\n";
    cout << "      BB   BBB       BB   BBB      AA AA      MM MM   MM MM  !!!\n";
    cout << "      BB   BBB       BB   BBB     AA   AA     MM  MM MM  MM  !!!\n";
	cout << "      BBBBBB    ===  BBBBBB      AAAAAAAAA    MM   MMM   MM  !!!\n";
    cout << "      BB   BBB       BB   BBB   AA       AA   MM    M    MM  !!!\n";
	cout << "      BB   BBB       BB   BBB  AA         AA  MM         MM  !!!\n";
    cout << "      BBBBBBB        BBBBBBB  AA           AA MM         MM   o\n\n\n";
    //cout.width(10);                            
    cout << "    SSSSS       EEEEEEE NNN     NN   GGGG  IIIIII NNN     NN EEEEEEE\n";
    cout << "   SSS          EE      NN NN   NN  GG       II   NN NN   NN EE\n";
	cout << "     SS         EEEEE   NN  NN  NN GG  GGG   II   NN  NN  NN EEEEE\n";
	cout << "      SSS       EE      NN   NN NN  GG  GG   II   NN   NN NN EE\n";
	cout << "   SSSSS  o     EEEEEEE NN     NNN   GGGG  IIIIII NN     NNN EEEEEEE\n";
    cout << "  ___________________________________________________________________\n\n\n";

}