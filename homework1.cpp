//Krishan Chopra
//Credit: code examples used in lecture

#include <cstdlib>
#include <stdio.h>
#include <map>
#include <vector>
#include <string.h>
using namespace std;

typedef struct {
	char *name;
	int age;
	double weight;
	double height;
} newPerson;

int main (int argc, char **argv)
{

	char str[50];
	int a;
	double w, h;
	//store the struct in a vector
	vector <newPerson*> person;
	//store weight, age and height in a map
	map <double, char*> weightCheck;
	map <double, char*> heightCheck;
	map <int, char*, greater<int> > ageCheck;
	//iterator for weight and height
	map <double, char*>::iterator it1;
	//iterator for age
	map <int, char*>::iterator it2;
	newPerson *nP;

	//check command line arguements
	if(argc != 2) {
		fprintf(stderr, "usage: ./a.out filename\n");
		exit(1);
	}
	//open file and error check
	FILE * openFile;
	openFile = fopen(argv[1], "r");
	if (openFile == NULL) {
		perror("Error: could not open file \n");
		exit(1);
	} 
	//for each line in file, read info, store in struct and put in map
	while(fscanf(openFile, "%s %d %lf %lf", str, &a, &w, &h) > 0) {
		nP = (newPerson*) malloc(sizeof(newPerson));
		nP->name = strdup(str);
		nP->age = a;	
		nP->weight = w;
		nP->height = h;
		person.push_back(nP);
		//checks the file for negative numbers
		if(a < 0 || w < 0 || h < 0) {
			printf("%s's age, weight or height must be non-negative\n", str);
			fclose(openFile);
			exit(1);
		} 
	}
	fclose(openFile);
	//order data in pairs
	for(int i = 0; i < person.size(); i++) {
		ageCheck[person[i]->age] = person[i]->name;
	}
	for(int i = 0; i < person.size(); i++) {
		heightCheck[person[i]->height] = person[i]->name;
	}
	for(int i = 0; i < person.size(); i++) {
		weightCheck[person[i]->weight] = person[i]->name;
	}
	//print in order
	printf("%s\n", "-----names-----");
	//no iterator needed for names since we just need to print as it is in the vector
	for(int i = 0; i < person.size(); i++) {
		printf("%s\n", person[i]->name);
	}
	printf("%s\n", "-----height-----");
	for(it1 = heightCheck.begin(); it1 != heightCheck.end(); it1++) {
		printf("%.2f:%s\n", it1->first, it1->second);
	}
	printf("%s\n", "-----weight-----");
	for(it1 = weightCheck.begin(); it1 != weightCheck.end(); it1++) {
		printf("%.2f:%s\n", it1->first, it1->second);
	}
	printf("%s\n", "-----age-----");
	for(it2 = ageCheck.begin(); it2 != ageCheck.end(); it2++) {
		printf("%d:%s\n", it2->first, it2->second);
	}
	//free memory
	for (int i = 0; i < person.size();i++) {
		free (person[i]->name);
		free (person[i]);
	}
}