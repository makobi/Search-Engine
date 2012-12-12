//***************************************************************************************

// Programadores : Alex Santos e Ivan Jimenez CCOM 3034 SecciÛn 001

// Num. Est. : 801-11-7707, 801-11-3205  Primer Semestre 2012-2013

// Proyecto Final Prof. R. Arce

// Archivo : client.cpp 

// Fecha : 11 de diciembre de 2012 *

//***********************************************************************************************************************

#include "ParsedFile.h"
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string.h>

/*
   Muestra como invocar la funcion getdir para obtener los nombres de los 
   archivos del directorio. Luego muestra como crear un objeto tipo
   ParsedFile para luego obtener las palabras del archivo en un vector
   de strings.
*/

int main(void)
{
	time_t start, end;

    string dir = string("./moviesdb");	// Stores the path of the folder with the files
    
    multimap<int, string> results; // Stores the qualifying files and sorts them
    
    std::tr1::unordered_set<string> stops; // Stores the stop words
    
    std::tr1::unordered_map< string, std::tr1::unordered_map<std::string,int> > files_freq; // Stores the words, files and frequency
    
	vector<string> inputs; // Stores the inputs of the user
	
    vector<ParsedFile> files; // Stores the files of the directory
    
    char searching[256];
    
    int count = 0;
    
    cout << endl << " Building the Search Engine... "<< endl ;
    time (&start);
  	
  	// Starts the engine 
  	setEngine(dir, stops, files, files_freq);
  	
  	time (&end);
    cout << " The search engine finished building. It took: " << difftime(end,start) << " seconds" << endl << endl;
  	
  	do{
  	
  		
  		// Displays the logo
  		displayLogo();
  		
    	// Gets the inputs of the user
    	getWords(inputs, count);
    	
    	//for (int i = 0; i < inputs.size(); i++)
    	//	cout << inputs[i] << " ";
		
		// Gets results of case with two words
		if(inputs.size() == 2){ 
			results = getResults(inputs[0], inputs[1], files_freq);
		}
	
		// Gets results of case with one word
		else if (inputs.size() == 1){
			results = getResults(inputs[0], inputs[0], files_freq);
		}
	
		//Display the three most highest files based on frequency
		displayResults(results);
		
		cout << "Want to keep searching? Enter 'y' if yes or 'n' if no" << endl;
		cin >> searching;
		
		results.clear();
		
		count++;
		
	}while(strcmp(searching, "y") == 0 || strcmp(searching, "Y") == 0);
	
    return 0;
}

