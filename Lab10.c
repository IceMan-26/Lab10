#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initializes a trie structure
char trie[5000][26];
int count[5000];

// Inserts the word into the Trie structure
void insert(char *word)
{
    int node = 0; // Start from the root node
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (trie[node][index] == 0)
        {
            trie[node][index] = ++count[0]; // Allocate a new node
        }
        node = trie[node][index]; // Move to the next node
    }
    count[node]++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(char *word)
{
    int node = 0; // Start from the root node
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (trie[node][index] == 0)
        {
            return 0; // Word not found in the Trie
        }
        node = trie[node][index]; // Move to the next node
    }
    return count[node];
}

// Initializes a trie structure
void createTrie()
{
    memset(trie, 0, sizeof(trie));
    memset(count, 0, sizeof(count));
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    int numWords = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(inWords[i]);
    }

    // Parse line by line, and insert each word into the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pWords[i]));
    }

    return 0;
}
