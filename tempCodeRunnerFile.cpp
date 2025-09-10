        vector<string> autocomplete(string prefix) {
            vector<string> suggestions;
            TrieNode* node = root;

            for (char c : prefix) {
                int idx = c - 'a';                 // fix: convert char to index
                if (idx < 0 || idx >= 26) return suggestions;
                if (!node->children[idx]) return suggestions;
                node = node->children[idx];
            }

            findAllWords(node, prefix, suggestions);
            return suggestions;
        }
