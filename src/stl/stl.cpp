#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    // variant 1
    // split user input (cin) string by delimiter (space))
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    while (std::getline(tokenStream, token, ' '))
        tokens.push_back(token);

    // iterate over tokens and print them
    for (auto t : tokens)
        std::cout << t << std::endl;

    // variant 2
    std::string s;
    std::getline(std::cin, s);
    size_t last = 0;
    size_t next = 0;
    while ((next = s.find(' ', last)) != std::string::npos)
    {
        std::cout << s.substr(last, next - last) << std::endl;
        last = next + 1;
    }
    std::cout << s.substr(last) << std::endl;

    // get user input string
    std::string input;
    std::getline(std::cin, input);

    // reverse input string and print it
    // std::reverse(input.begin(), input.end());
    // std::cout << input << std::endl;

    // replace first character of every word in input string to upper and print it 
    std::string result;
    std::istringstream iss(input);
    for (std::string s; iss >> s;)
    {
        s[0] = std::toupper(s[0]);
        result += s + " ";
    }
    std::cout << result << std::endl;


    // find the longest word in input string and print it
    // using stl
    std::string longestWord;
    std::istringstream iss2(input);
    for (std::string s; iss2 >> s;)
        if (s.length() > longestWord.length())
            longestWord = s;
    std::cout << longestWord << std::endl;

    // count words number in input string and print it
    // using stl
    std::istringstream iss3(input);
    std::cout << std::distance(std::istream_iterator<std::string>(iss3), std::istream_iterator<std::string>()) << std::endl;
}
