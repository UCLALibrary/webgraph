//WRITTEN BY AKILA WELIHINDA


#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <bitset>  
#include <stdlib.h>
#include <sstream>
using namespace std;

const unsigned long long LINE_SIZE=3000000;
	char line[LINE_SIZE];
	char original[LINE_SIZE];

int main(){

	//remove all entries from index file that aren't hosts
	//do this by creating new file "final_index" which has all
	//the host entries that we care about. In order to keep track of
	//which nodes are in our final_index, we use a bitset to save memory.
	//Note that bitsets require compile time constants, so we MUST know 
	//how many nodes are in the graph before compile time.


  //REQUIREMENTS!!!
  /*
      1) You must enter # of arc files
      2) You must enter # of index files
      3) You must enter # of nodes
      4) You must enter the base index file name
      5) You must enter the base arc file name
  */

  //    const unsigned long long int NODE_COUNT; //CHANGE THIS

	//	bitset<NODE_COUNT> node_set;
	
	//	unsigned long long int curr=0;

	FILE * fp;
	FILE * fp2;
    char * l = NULL;
    size_t len = 0;
    ssize_t read;

    const int NUM_INDEX_FILES=83; //CHANGE THIS
    const int NUM_ARC_FILES=2; //CHANGE THIS
    int current_index_count=51;


    while( current_index_count < NUM_INDEX_FILES)
    {
      string base="/home/ubuntu/data/index/index-"; //CHANGE THIS TO BASE INDEX FILE NAME
      stringstream ss;
      ss << current_index_count;
      string numberIndex;//to_string(current_index_count);
      ss >> numberIndex;
      numberIndex=string(5-numberIndex.length(), '0').append(numberIndex);
        string current_index=base+numberIndex;
	stringstream ss_currIndexCount;
	ss_currIndexCount << current_index_count;
	string s_curr_Index_Count;
	ss_currIndexCount >> s_curr_Index_Count;

        int fd_new=open( ("final_index"+s_curr_Index_Count).c_str(), O_RDWR|O_CREAT|O_TRUNC);

        fp = fopen(current_index.c_str(), "r");

        if (fp == NULL){
	  cout << "Unable to open index file: " << current_index << endl;
      		exit(1);
        }

        char* currTok=NULL;

        while ( (read = getline(&l, &len, fp)) != -1 ) //write proper nodes to new index file
        {
          strncpy(original, l, LINE_SIZE);
          strtok(l, "\t");
          
	  char tempString[LINE_SIZE];
	  strncpy(tempString, l, LINE_SIZE);
	  tempString[strlen(l)-1]='\0'; //ignore last character
	  char* noHTTPString=tempString+7; //ignore slashes in http://

          if(strchr(noHTTPString, '/')!=NULL) //ignore if name has a forward slash in it
          {
          		continue;
          }

	  cout << noHTTPString << " : HOST"<<current_index_count<<endl;

          //otherwise we want to write line to new index file
          write(fd_new, original, strlen(original));
          //node_set.set(curr, 1); //set node as present in new index
        }

	cout << "DONE WITH CURRENT INDEX FILE" <<endl;

        close(fd_new);
        fclose(fp);
	//	remove(current_index.c_str()); //remove old index file to save space
        current_index_count++;
    }

    exit(0); //added to only let index files be created. WHEN YOU REMOVE THIS, YOU MUST ALSO CHANGE THE ARC FILE RELATED CONSTANTS.

  	//if this point is reached, then the new index file was created properly
  	//now we must get rid of all edges that include any removed nodes.
  	//We can do this by using the bitset
    /*
    int current_arc_count=0;

    while( current_arc_count < NUM_ARC_FILES)
    {
      string current_arc="example_arc"+to_string(current_arc_count); //CHANGE THIS TO DEFAULT ARC NAME
      int fd_new_arc=open( ("final_arcs"+to_string(current_arc_count)).c_str(), O_RDWR|O_CREAT|O_TRUNC);

        fp2 = fopen(current_arc.c_str(), "r");

        if (fp2 == NULL){
            cout << "Unable to open arc file: " << current_arc;
          exit(1);
        }

       char* pend=NULL;
       unsigned long long n1, n2;
       while ((read = getline(&l, &len, fp2)) != -1) {
       		strcpy(original, l);
       		n1=strtoull(l, &pend, 10);
       		n2=strtoull(pend, &pend, 10);
       		if(node_set.test(n1)==1 && node_set.test(n2)==1)
       			write(fd_new_arc, original, strlen(original));
       }

       fclose(fp2);
       close(fd_new_arc);
       current_arc_count++;
       }*/
    //if this point is reached, then all the unwanted edges will be removed from
    //the graph. 
}
