#include "nltool.h"

// Convert string to upper case letter
std::string toUpper(std::string str)
{
    for (char &c : str) c = toupper(c);
    return str;
}

// Convert string to lowercase letters
std::string toLower(std::string str)
{
    for (char &c : str) c = tolower(c);
    return str;
}

// Test if two consecutive characters are space
bool doubleSpace(char a, char b) { return (a == b) && (a == ' '); }

// Eliminate whitespaces from beginning and end of string
std::string trim(std::string str)
{
    std::string::iterator new_end = std::unique(str.begin(), str.end(), doubleSpace);
    str.erase(new_end, str.end());
    int start = str.find_first_not_of(' ');
    int end = str.find_last_not_of(' ');
    if (start != str.npos)
    {
        str = str.substr(start, end-start+1);
    }
    return str;
}

// Search and replace substrings on given string
std::string replace(std::string str, std::string search, std::string substitute)
{
    std::vector<std::string> token = splitSentence(str, search);
    str = mergeSentence(token, substitute);
    return str;
}

// Clean string from special characters
std::string clean(std::string str)
{
    str = replace(str, ".", " ");
    str = replace(str, "*", " ");
    str = replace(str, "&", " ");
    str = replace(str, "\"", " ");
    str = replace(str, "s/", "s/ ");
    str = replace(str, "p/", "p/ ");
    str = replace(str, "c/", "c/ ");
    str = replace(str, "+", " ");
    str = replace(str, "/", " ");
    str = replace(str, "\\", " ");
    str = replace(str, "(", " ");
    str = replace(str, ")", " ");
    str = std::regex_replace(str, std::regex("[0-9]+")," ");
    return str;
}

// Split a sentence into a vector containing strings, based on a given string delimiter
std::vector<std::string> splitSentence(std::string sentence, std::string delimiter)
{
    std::vector<std::string> token;
    int start = 0;
    std::string line = sentence;
    while (line.find(delimiter) != line.npos)
    {
        int end = line.find(delimiter);
        token.push_back(line.substr(start,end));
        line = line.substr(end+1, line.npos);
    }
    token.push_back(line);
    return token;
}

// Split a sentence into a vector containing strings, considering space as the default delimiter
std::vector<std::string> splitSentence(std::string sentence)
{
    std::vector<std::string> token;
    token = splitSentence(sentence, " ");
    return token;
}

// Merge a vector of strings in a single sentence, adding a givent string delimiter
std::string mergeSentence(std::vector<std::string> token, std::string delimiter)
{
    std::string str;
    str = token[0];
    if (token.size() > 1)
    {
        for (int i = 1; i < token.size(); i++)
        {
            str += delimiter;
            str += token[i];
        }
    }
    return str;
}

// Create word n-grams from sentences
std::vector<std::string> wordToken(std::vector<std::string> token, int n)
{
    std::string str;
    std::vector<std::string> ngram;
    int size = static_cast<int>(token.size());
    if (size==1 || n==1)
    {
        ngram = token;
    }
    else if (size <= n)
    {
        str = token[0];
        for (int j=1; j < size; j++)
        {
            str += " ";
            str += token[j];
        }
        ngram.push_back(str);
    }
    else
    {
        for (int i = 0; i < size - n; i++)
        {
            str = token[i];
            for (int j = 1; j < n; j++)
            {
                str += " ";
                str += token[i+j];
            }
            ngram.push_back(str);
        }
    }
    return ngram;
}

// Splits a word into a vector containing letters
std::vector<std::string> splitWord(std::string word)
{
    std::vector<std::string> token;
    int size = static_cast<int>(word.length());
    for (int i = 0; i < size; i++)
    {
        token.push_back(word.substr(i, 1));
    }
    return token;
}

// Create letter n-grams from words
std::vector<std::string> letterToken(std::string word, int n)
{
    std::vector<std::string> token;
    int size = static_cast<int>(word.length());
    if (size <= n)
    {
        token.push_back(word);
    }
    else
    {
        for (int i = 0; i < size-n; i++)
        {
            token.push_back(word.substr(i,n));
        }
    }
    return token;
}
