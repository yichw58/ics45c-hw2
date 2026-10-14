// ------------------------- Your tests - student_gtests.cpp ----------------------------- //
// Your own GoogleTest suite for the word_count module. It is graded: the autograder runs it
// against a correct implementation and against several with one bug each. A test is worth
// something only when it passes on the correct implementation and fails on a broken one, so a
// test that always fails (or that tests nothing) earns nothing.
//
// Two examples are given. Add tests of your own for to_lowercase, load_stopwords, count_words
// and output_word_counts, and for the edges: an empty document, a document that is all stop
// words, stop words written in mixed case, and the same word in several cases.
// --------------------------------------------------------------------------------------- //

#include <gtest/gtest.h>

#include <sstream>

#include "word_count.hpp"

using namespace std;

TEST(WordCountTests, StopwordsAreLoadedCaseInsensitively) {
    std::stringstream stopwords{"The OVER\n"};
    const auto loaded = load_stopwords(stopwords);
    EXPECT_TRUE(loaded.contains("the"));
    EXPECT_TRUE(loaded.contains("over"));
}

TEST(WordCountTests, WordsAreCountedCaseInsensitively) {
    std::stringstream document{"Apple apple APPLE pear"};
    const auto counts = count_words(document, {});
    EXPECT_EQ(counts.at("apple"), 3);
    EXPECT_EQ(counts.at("pear"), 1);
}

// ADD YOUR TESTS HERE:
TEST(WordCountTests, LowercaseMixedCase) {
    std::string word = "ABC123xyz";
    to_lowercase(word);
    EXPECT_EQ(word, "abc123xyz");
}

TEST(WordCountTests, LowercaseEmptyString) {
    std::string word = "";
    to_lowercase(word);
    EXPECT_EQ(word, "");
}

TEST(WordCountTests, AllWordsAreStopwords) {
    istringstream document("The AND the");
    set<string> stopwords = {"the", "and"};
    auto counts = count_words(document, stopwords);
    EXPECT_TRUE(counts.empty());
}

TEST(WordCountTests, EmptyDocument) {
    istringstream document("");
    set<string> empty = {};
    auto counts = count_words(document, empty);
    EXPECT_TRUE(counts.empty());
}

TEST(WordCountTests, SingleWord) {
    istringstream document("banana");
    set<string> stopwords = {};
    auto counts = count_words(document, stopwords);
    EXPECT_EQ(counts.at("banana"), 1);
    EXPECT_EQ(counts.size(),1);
}

TEST(WordCountTests, StopwordExcluded) {
    istringstream document("Apple THE banana apple the");
    set<string> stopwords = {"the"};

    auto counts = count_words(document, stopwords);

    EXPECT_FALSE(counts.contains("the"));
    EXPECT_EQ(counts.at("apple"), 2);
    EXPECT_EQ(counts.at("banana"), 1);
    EXPECT_EQ(counts.size(), 2);
}

TEST(WordCountTests, RepeatedWords) {
    istringstream document("apple banana apple apple banana");
    set<string> stopwords = {};

    auto counts = count_words(document, stopwords);

    EXPECT_EQ(counts.at("apple"), 3);
    EXPECT_EQ(counts.at("banana"), 2);
    EXPECT_EQ(counts.size(), 2);
}

TEST(WordCountTests, MixedCaseStopwords) {
    istringstream input("ThE AND aNd Is");

    auto stopwords = load_stopwords(input);

    EXPECT_TRUE(stopwords.contains("the"));
    EXPECT_TRUE(stopwords.contains("and"));
    EXPECT_TRUE(stopwords.contains("is"));
    EXPECT_EQ(stopwords.size(), 3);
}

TEST(WordCountTests, EmptyStopwords) {
    istringstream document("Apple apple banana");
    set<string> stopwords = {};

    auto counts = count_words(document, stopwords);

    EXPECT_EQ(counts.at("apple"), 2);
    EXPECT_EQ(counts.at("banana"), 1);
    EXPECT_EQ(counts.size(), 2);
}

TEST(WordCountTests, OutputAlphabeticalOrder) {
    map<string, int> counts = {
        {"zebra", 1},
        {"apple", 3},
        {"banana", 2}
    };

    ostringstream output;
    output_word_counts(counts, output);

    EXPECT_EQ(output.str(), "apple 3\nbanana 2\nzebra 1\n");
}

TEST(WordCountTests, OutputEmptyMap) {
    map<string, int> counts = {};

    ostringstream output;
    output_word_counts(counts, output);

    EXPECT_EQ(output.str(), "");
}

TEST(WordCountTests, OutputExactFormat) {
    map<string, int> counts = {
        {"computer", 20},
        {"hello", 1}
    };

    ostringstream output;
    output_word_counts(counts, output);

    EXPECT_EQ(output.str(), "computer 20\nhello 1\n");
}