//Anahel Bour COP3502 4/19/2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    int end;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* newTrie=(struct Trie*)malloc(sizeof(struct Trie));
    newTrie->end=0;
    for (int i=0;i<ALPHABET_SIZE;i++) {
        newTrie->children[i]=NULL;
    }
    return newTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* temp=pTrie;
    while(*word!='\0'){
        int index=*word-'a';
        if(temp->children[index]==NULL){
            temp->children[index]=createTrie();
        }
        temp=temp->children[index];
        word++;
    }
    if (temp->end) {
        temp->end++;
    } else {
        temp->end = 1;
    }
}

// computes the number of occurances of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct Trie* temp=pTrie;
    while(*word!='\0'){
        int index=*word-'a';
        if(temp->children[index]==NULL) {
            return 0;
        }
        temp=temp->children[index];
        word++;
    }
    return temp->end;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie==NULL) {
        exit;
    }
    for(int i=0;i<ALPHABET_SIZE;i++) {
        deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp=fopen(filename, "r");
    int numWords;
    fscanf(fp,"%d",&numWords);
    for (int i=0;i<numWords;i++) {
        pInWords[i]=(char *)malloc(100*sizeof(char)); // Allocate memory for the word
        fscanf(fp,"%s",pInWords[i]);
    }
    fclose(fp);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}