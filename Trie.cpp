#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Each node in the Trie
class TrieNode {
public:
    // Each node has up to 52 children (for each letter)
    TrieNode *children[52];
    
    // Marks if this node completes a word
    bool isEndOfWord;
    
    // Constructor
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 52; i++) {
            children[i] = nullptr;
        }
    }
};

// The Trie class
class Trie {
private:
    TrieNode* root;
    

    static int getIndex(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';          
        } else if (c >= 'A' && c <= 'Z') {
            return 26 + (c - 'A');    
        }
        return -1; 
    }
    static char getChar(int index) {
        if (index >= 0 && index < 26) return 'a' + index;
        if (index >= 26 && index < 52) return 'A' + (index - 26);
        return '?';
    }
    static bool hasNoChildren(const TrieNode* n) {
        for (int i = 0; i < 52; ++i) if (n->children[i]) return false;
        return true;
    }

    static bool eraseHelper(TrieNode*& node, const string& word, int depth) {
        if (!node) return false;                       

        if (depth == (int)word.size()) {           
            if (!node->isEndOfWord) return false; 
            node->isEndOfWord = false;
            if (hasNoChildren(node)) {                
                delete node;
                node = nullptr;
            }
            return true;
        }

        int idx = getIndex(word[depth]);
        if (idx ==-1) return false;        

        bool removed = eraseHelper(node->children[idx], word, depth + 1);
        if (node && depth > 0 && !node->isEndOfWord && hasNoChildren(node)) {
            delete node;
            node = nullptr;
        }
        return removed;
    }
    // Helper function to find all words from a node
    // Input: current node, current word formed so far, results vector to store words
    // Output: none (modifies results vector by reference)
    // Purpose: Recursively find all complete words starting from the given node
    void findAllWords(TrieNode* node, string currentWord, vector<string>& results) {// --ramy--
        if (node->isEndOfWord) {
            results.push_back(currentWord);
        }
        
        for (int i = 0; i < 52; i++) {
            if (node->children[i] != nullptr) {
                char nextChar = getChar(i);
                findAllWords(node->children[i], currentWord + nextChar, results);
            }
        }
    }

public:
    // Constructor
    // Input: none
    // Output: none
    // Purpose: Initialize the Trie with a root node
    Trie() {// --Ramy--
        root = new TrieNode();
    }
    
    // Insert a word into the Trie
    // Input: word to insert (string)
    // Output: none
    // Purpose: Add a word to the Trie by creating nodes for each character
    void insert(string word) {// --Mazen--
        TrieNode *node = root;
        for (char c : word)
        {
            int index = getIndex(c);
            if (node->children[index] == nullptr)
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
    
    // Search for a word in the Trie
    // Input: word to search for (string)
    // Output: boolean indicating if the word exists
    // Purpose: Check if the complete word exists in the Trie
    bool search(string word) {// --Malak--
        TrieNode* node = root;
        for (char c : word) {
            int idx = getIndex(c);
        if (idx == -1 || !node->children[idx]) return false;
            node = node->children[idx];      
        }
        return node->isEndOfWord;
    }
    
    // Check if any word starts with the given prefix
    // Input: prefix to check (string)
    // Output: boolean indicating if any word has this prefix
    // Purpose: Verify if the prefix exists in the Trie (doesn't need to be a complete word)
    bool startsWith(string prefix) {// --Marwan--
       TrieNode* node =root;
        for(char c:prefix){
        int index= getIndex(c);
        if(index==-1||node->children[index]==nullptr) 
        {
            return false;
        }else{
            node=node->children[index];
        }

       }
        return true; 
    }
    
    // Get all words that start with the given prefix
    // Input: prefix to complete (string)
    // Output: vector of strings that start with the prefix
    // Purpose: Find all complete words that begin with the given prefix
    vector<string> autocomplete(string prefix) {// --Karim--
        vector<string> suggestions;
        TrieNode* node = root;

        for (char c : prefix) {
            int idx = getIndex(c);
            if (idx==-1||!node->children[idx]) return suggestions;         
            node = node->children[idx];
        }
        findAllWords(node, prefix, suggestions);
        return suggestions;
    }
    void spellChecker(string word) {
        if (search(word))
        {
            cout << word << " is spelled correctly.\n";
        }
        else
        {
            cout << word << " is NOT found.\n";
         }
    }


    string findLongestWord() {
        vector<string> allWords;
        findAllWords(root, "", allWords);
        
        if (allWords.empty()) {
            return "";
        }
        string longestWord = allWords[0];
        for (const string& word : allWords) {
            if (word.length() > longestWord.length()) {
                longestWord = word;
            }
        }
        return longestWord;
    }
    int countWords(){
        vector<string> allWords;
        findAllWords(root, "", allWords);
        return allWords.size();
    }
    bool removeWord(const string& word) {
        if (word.empty()) return false;
        return eraseHelper(root, word, 0);
    }
};

// Main function
// Input: none
// Output: integer return code
// Purpose: Program entry point, run tests and interactive demo
int main() {
    cout << "=== TRIE DATA STRUCTURE IMPLEMENTATION ===" << endl;
    cout << "Testing all Trie functionalities..." << endl;
    
    Trie trie;
    
    // Test 1: Basic insertion and search
    cout << "\n1. Testing basic insertion and search:" << endl;
    cout << "======================================" << endl;
    
    vector<string> words = {"apple", "banana", "orange", "grape", "kiwi"};
    for (const string& word : words) {
        trie.insert(word);
        cout << "Inserted: " << word << endl;
    }
    
    // Test search for existing words
    for (const string& word : words) {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    // Test search for non-existing words
    vector<string> nonExisting = {"app", "ban", "ora", "graph", "kiwis"};
    for (const string& word : nonExisting) {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << " (expected: NOT FOUND)" << endl;
    }
    
    // Test 2: Prefix checking
    cout << "\n2. Testing prefix checking:" << endl;
    cout << "==========================" << endl;
    
    vector<string> prefixes = {"app", "ban", "ora", "grap", "k"};
    for (const string& prefix : prefixes) {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "': " << (hasPrefix ? "EXISTS" : "DOESN'T EXIST") << endl;
    }
    
    vector<string> nonPrefixes = {"x", "yield", "zed", "micro", "nano"};
    for (const string& prefix : nonPrefixes) {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "': " << (hasPrefix ? "EXISTS" : "DOESN'T EXIST") << " (expected: DOESN'T EXIST)" << endl;
    }
    
    // Test 3: Autocomplete functionality
    cout << "\n3. Testing autocomplete functionality:" << endl;
    cout << "======================================" << endl;
    
    vector<string> testPrefixes = {"a", "b", "o", "g", "k", "ap", "ban", "ora", "gr", "ki"};
    for (const string& prefix : testPrefixes) {
        vector<string> suggestions = trie.autocomplete(prefix);
        cout << "Autocomplete for '" << prefix << "': ";
        if (suggestions.empty()) {
            cout << "No suggestions found";
        } else {
            for (size_t i = 0; i < suggestions.size(); i++) {
                if (i > 0) cout << ", ";
                cout << suggestions[i];
            }
        }
        cout << endl;
    }
    
    // Test 4: Edge cases
    cout << "\n4. Testing edge cases:" << endl;
    cout << "======================" << endl;
    
    // Empty string tests
    bool emptySearch = trie.search("");
    cout << "Search empty string: " << (emptySearch ? "FOUND" : "NOT FOUND") << " (expected: NOT FOUND)" << endl;
    
    bool emptyPrefix = trie.startsWith("");
    cout << "Starts with empty prefix: " << (emptyPrefix ? "EXISTS" : "DOESN'T EXIST") << " (expected: EXISTS)" << endl;
    
    vector<string> emptySuggestions = trie.autocomplete("");
    cout << "Autocomplete for empty string: ";
    if (emptySuggestions.empty()) {
        cout << "No suggestions found";
    } else {
        for (size_t i = 0; i < emptySuggestions.size(); i++) {
            if (i > 0) cout << ", ";
            cout << emptySuggestions[i];
        }
    }
    cout << " (expected: all words)" << endl;
    
    // Test 5: Adding more words and retesting
    cout << "\n5. Testing with additional words:" << endl;
    cout << "================================" << endl;
    
    vector<string> additionalWords = {"application", "appetizer", "banister", "bandana", "oracle", "grapefruit"};
    for (const string& word : additionalWords) {
        trie.insert(word);
        cout << "Inserted: " << word << endl;
    }
    
    // Test search for new words
    for (const string& word : additionalWords) {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    // Test autocomplete with new words
    vector<string> newPrefixes = {"app", "ban", "ora", "gra"};
    for (const string& prefix : newPrefixes) {
        vector<string> suggestions = trie.autocomplete(prefix);
        cout << "Autocomplete for '" << prefix << "': ";
        if (suggestions.empty()) {
            cout << "No suggestions found";
        } else {
            for (size_t i = 0; i < suggestions.size(); i++) {
                if (i > 0) cout << ", ";
                cout << suggestions[i];
            }
        }
        cout << endl;
    }
    
    // Test 6: Case sensitivity (all lowercase expected)
    cout << "\n6. Testing case sensitivity:" << endl;
    cout << "============================" << endl;
    
    trie.insert("Hello");
    trie.insert("WORLD");
    
    vector<string> caseWords = {"hello", "Hello", "WORLD", "world"};
    for (const string& word : caseWords) {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    // ===============================
    // 7. Testing removal operations
    // ===============================
    cout << "\n7. Testing removal operations:" << endl;
    cout << "================================" << endl;

    auto show = [&](const string& w) {
        cout << "Search '" << w << "': " << (trie.search(w) ? "FOUND" : "NOT FOUND") << endl;
    };

    // Sanity before removals
    show("apple"); show("application"); show("appetizer");
    show("banana"); show("bandana"); show("banister");
    show("kiwi");

    // 7.1 Remove a leaf word
    cout << "\n7.1 Remove leaf 'kiwi': ";
    cout << (trie.removeWord("kiwi") ? "REMOVED" : "NOT FOUND") << endl;
    show("kiwi");  // expect NOT FOUND

    // 7.2 Remove a middle word that shares prefix with others
    cout << "\n7.2 Remove 'banana' (prefix siblings exist): ";
    cout << (trie.removeWord("banana") ? "REMOVED" : "NOT FOUND") << endl;
    show("banana");   // expect NOT FOUND
    show("bandana");  // expect FOUND (should remain)
    show("banister"); // expect FOUND (should remain)

    // 7.3 Insert 'app' (prefix of others), then remove only 'app'
    trie.insert("app");
    cout << "\n7.3 Add and remove 'app' (keep longer words):" << endl;
    show("app");          // expect FOUND
    cout << (trie.removeWord("app") ? "REMOVED" : "NOT FOUND") << endl;
    show("app");          // expect NOT FOUND
    show("apple");        // expect FOUND
    show("application");  // expect FOUND
    show("appetizer");    // expect FOUND

    // 7.4 Remove a non-existent word
    cout << "\n7.4 Remove 'berry' (non-existent): ";
    cout << (trie.removeWord("berry") ? "REMOVED" : "NOT FOUND") << endl;

    // 7.5 Remove empty string
    cout << "\n7.5 Remove empty string: ";
    cout << (trie.removeWord("") ? "REMOVED" : "NOT FOUND") << endl;
    
    cout << "\n=== ALL TESTS COMPLETED ===" << endl;
    
    return 0;
}
