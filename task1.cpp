/*CHATBOT WITH RULE-BASEDRESPONSES
Build a simple chatbot that responds to user inputs based onpredefined rules. Use if-else statements or pattern matchingtechniques to identify user queries and provide appropriateresponses. This will give you a basic understanding of naturallanguage processing and conversation flow.*/
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool contains(const string& str, const string& substring) {
    return str.find(substring) != string::npos;
}

string chatbot() {
    cout << "Hello! I'm a rule-based chatbot. How can I assist you today?" << endl;

    while (true) {
        string userInput;
        getline(cin, userInput);
        string lowercaseInput = toLowerCase(userInput);

        if (contains(lowercaseInput, "hello") || contains(lowercaseInput, "hi")) {
            return "Chatbot: Hello! How can I help you?";
        } else if (contains(lowercaseInput, "how are you")) {
            return "Chatbot: I'm doing well, thank you for asking!";
        } else if (contains(lowercaseInput, "what is your name")) {
            return "Chatbot: My name is Chatbot.";
        } else if (contains(lowercaseInput, "bye") || contains(lowercaseInput, "goodbye")) {
            return "Chatbot: Goodbye! Have a great day.";
        } else {
            return "Chatbot: I'm sorry, I didn't understand your query. Could you please rephrase it?";
        }
    }
}

int main() {
    string response = chatbot();
    cout << response << endl;
    return 0;
}