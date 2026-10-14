#include "word_count.hpp"
#include <cctype>
#include <istream>
#include <ostream>

using namespace std;

void to_lowercase(string& str) {
    for (char& c: str){
        c = tolower(c);
    }
}

set<string> load_stopwords(istream& stopwords){
    set<string> words;
    string word;
    while (stopwords >> word) {
        to_lowercase(word);
        words.insert(word);
}
    return words;
}

map<string, int> count_words(istream& document, const set<string>& stopwords) {

    map<string, int> counts;
    string word;

    while(document >> word){
        to_lowercase(word);
        if (!stopwords.contains(word)){
            counts[word]++;
        }
    }

    return counts;
}

void output_word_counts(const map<string, int>& word_counts, ostream& output) {

    for (const auto& [word, count] : word_counts) {
        output << word << ' ' << count << endl;
    }
}