/**
 * @File: lexical_analyzer.cpp
 * @Brief: 词法分析器类的实现
 * @Author:
 */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "../Includes/lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer() {}

LexicalAnalyzer::~LexicalAnalyzer() {}

// Read the file and store the content in the string content_:
int LexicalAnalyzer::ReadFile(const string &file_path)
{
  ifstream file;

  file.open(file_path, ios::in);
  if (!file.is_open())
  {
    cout << "\nFailed to open the file!" << endl;
    return -1;
  }
  while (!file.eof())
  {
    string line;
    getline(file, line);
    this->content_ += line + "\n";
  }
  file.close();
  return 0;
}

// Print the content read from the file:
void LexicalAnalyzer::PrintContent()
{
  cout << "\nContent of the file:\n"
       << "----------------------------------------\n"
       << this->content_ << "----------------------------------------\n\n";
}

// Lexical analysis:
void LexicalAnalyzer::Analysis()
{
  // cout << "Lexical analysis:\n";
  // Read the whole content:
  string word = "";
  char ch = this->content_[0];
  int ch_idx = 0;    // Current character index
  int word_len = 0;  // Current word length
  int state = 0;     // Current state
  while (ch_idx < this->content_.length())
  {
    ch = this->content_[ch_idx++];
    ++word_len;
    int next_state = this->transfer_table_[state][GetType(ch)];
    // cout << ch_idx - 1 << ":" << (ch == '\n' ? "\\n" : string(1, ch)) << " ["
    //      << state << "->" << next_state << "]" << endl;
    if (next_state == -1)
    {
      word = this->content_.substr(ch_idx - word_len, word_len - 1);
      GetToken(state, word);
      word_len = 0;
      state = 0;
      --ch_idx;
    }
    else
      state = next_state;
  }
}

// Write the result to a file:
void LexicalAnalyzer::WriteResult(const string &file_path)
{
  ofstream file;
  string result_file_path =
      file_path.substr(0, file_path.length() - 4) + "_result.txt";
  file.open(result_file_path, ios::out);
  if (!file.is_open())
  {
    cout << "\nFailed to open the file!" << endl;
  }
  file << this->result_;
  file.close();
  cout << "\nResult has been written to \"" << result_file_path << "\"\n";
}

// Check if the character is a digit (0-9):
bool LexicalAnalyzer::IsDigit(const char &ch)
{
  if (ch >= '0' && ch <= '9') return true;
  return false;
}

// Check if the character is a letter (A-Z, a-z):
bool LexicalAnalyzer::IsLetter(const char &ch)
{
  if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) return true;
  return false;
}

// Check if the word is a keyword, if so, return the code of the keyword:
int LexicalAnalyzer::IsKeyword(const string &wd)
{
  for (int i = 0; i < 11; ++i)
    if (wd == key_words_[i]) return (i + 701);
  return -1;
}

// Return the type of the character in the transfer table:
int LexicalAnalyzer::GetType(const char &ch)
{
  if (ch == ' ' || ch == '\t') return 0;
  if (ch == '\n') return 1;
  if (IsDigit(ch)) return 2;
  if (ch == '.') return 3;
  if (IsLetter(ch)) return 4;
  if (ch == '_') return 5;
  if (ch == '\'') return 6;
  if (ch == '\\') return 7;
  if (ch == '\"') return 8;
  if (ch == '/') return 9;
  if (ch == '*') return 10;
  if (ch == '+') return 11;
  if (ch == '-') return 12;
  if (ch == '%') return 13;
  if (ch == '=') return 14;
  if (ch == '<') return 15;
  if (ch == '>') return 16;
  if (ch == '!') return 17;
  if (ch == '&') return 18;
  if (ch == '|') return 19;
  if (ch == ',') return 20;
  if (ch == ';') return 21;
  if (ch == '(') return 22;
  if (ch == ')') return 23;
  if (ch == '[') return 24;
  if (ch == ']') return 25;
  if (ch == '{') return 26;
  if (ch == '}') return 27;
  return 28;  // other characters
}

// Analyze the file content and print the result:
void LexicalAnalyzer::GetToken(const int &st, const string &wd)
{
  int code = -1;
  if (st >= 0 && st <= 42) code = this->state_codes_[st];
  switch (code)
  {
    case -1:  // error
      PrintToken("ERROR", -1, wd);
      break;
    case 0:  // blank
      break;
    case 100:  // constant
      PrintToken("CONSTANT", 100, wd);
      break;
    case 200:  // identifier & keyword
    {
      int keyword_code = IsKeyword(wd);
      if (keyword_code != -1)  // keyword
      {
        string keyword_type = "KEYWORD(" + wd + ")";
        PrintToken(keyword_type, keyword_code, wd);
      }
      else  // identifier
      {
        for (int i = 0; i < id_cnt_; ++i)
        {
          if (id_table_[i] == wd)
          {
            // already exists
            PrintToken("IDENTIFIER", 201 + i, wd);
            return;
          }
        }
        // new identifier
        id_table_[id_cnt_] = wd;
        PrintToken("IDENTIFIER", 201 + id_cnt_++, wd);
      }
      break;
    }
    case 300:  // character
      PrintToken("CHARACTER", 300, wd);
      break;
    case 400:  // string
      PrintToken("STRING", 400, wd);
      break;
    case 501:  // inline comment
      PrintToken("INLINE_COMMENT", 501, wd);
      break;
    case 502:  // block comment
      PrintToken("BLOCK_COMMENT", 502, wd);
      break;
    case 601:  // operator
      PrintToken("OPERATOR(+)", 601, wd);
      break;
    case 602:
      PrintToken("OPERATOR(-)", 602, wd);
      break;
    case 603:
      PrintToken("OPERATOR(*)", 603, wd);
      break;
    case 604:
      PrintToken("OPERATOR(%)", 604, wd);
      break;
    case 605:
      PrintToken("OPERATOR(=)", 605, wd);
      break;
    case 606:
      PrintToken("OPERATOR(==)", 606, wd);
      break;
    case 607:
      PrintToken("OPERATOR(<)", 607, wd);
      break;
    case 608:
      PrintToken("OPERATOR(<=)", 608, wd);
      break;
    case 609:
      PrintToken("OPERATOR(>)", 609, wd);
      break;
    case 610:
      PrintToken("OPERATOR(>=)", 610, wd);
      break;
    case 611:
      PrintToken("OPERATOR(!)", 611, wd);
      break;
    case 612:
      PrintToken("OPERATOR(!=)", 612, wd);
      break;
    case 613:
      PrintToken("OPERATOR(&&)", 613, wd);
      break;
    case 614:
      PrintToken("OPERATOR(||)", 614, wd);
      break;
    case 615:  // delimiter
      PrintToken("DELIMETER(,)", 615, wd);
      break;
    case 616:
      PrintToken("DELIMETER(;)", 616, wd);
      break;
    case 617:  // bracket
      PrintToken("BRACKET(()", 617, wd);
      break;
    case 618:
      PrintToken("BRACKET())", 618, wd);
      break;
    case 619:
      PrintToken("BRACKET([)", 619, wd);
      break;
    case 620:
      PrintToken("BRACKET(])", 620, wd);
      break;
    case 621:
      PrintToken("BRACKET({)", 621, wd);
      break;
    case 622:
      PrintToken("BRACKET(})", 622, wd);
      break;
    default:
      PrintToken("OTHER", 800, wd);
  }
}

// Print one token:
void LexicalAnalyzer::PrintToken(const string &tp, const int &cd,
                                 const string &wd)
{
  string token = "<" + tp + "[" + to_string(cd) + "], " + wd + ">\n";
  this->result_ += token;
}
