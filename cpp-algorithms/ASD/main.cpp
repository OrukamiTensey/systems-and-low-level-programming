#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

struct Node 
{
    unordered_map<char, Node*> children; 
    bool isEndOfWord;

    Node() : isEndOfWord(false) {} 
};

struct Trie
{ 

    Node* root;

    Trie() : root(new Node()) {}

    void insert(string word) 
    {
        Node* current = root;
        for (char c : word)
        {
            if (current->children.find(c) == current->children.end()) 
            {
                current->children[c] = new Node();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    void findByPrefix(string prefix)
    {
        Node* current = root;
        for (char c : prefix) 
        {
            if (current->children.find(c) == current->children.end()) 
            {
                cout << "No words found with the prefix " << prefix << endl;
                return;
            }
            current = current->children[c];
        }
        findWordsFromNode(prefix, current);
    }

    void findWordsFromNode(string prefix, Node* node) 
    {
        if (node->isEndOfWord) 
        {
            cout << prefix << endl;
        }
        for (auto& pair : node->children) 
        {
            findWordsFromNode(prefix + pair.first, pair.second);
        }
    }
};

int main() 
{
    Trie trie;

    ifstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\words_alpha.txt");
    string word;
    while (getline(file, word)) 
    {
        trie.insert(word);
    }
    file.close();

    cout << "Enter a prefix to find words: ";
    string prefix;
    cin >> prefix;

    trie.findByPrefix(prefix);

    return 0;
}