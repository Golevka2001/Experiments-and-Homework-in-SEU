/**
 * @File: main.cpp
 * @Brief: 主函数，读取文件和输入内容，调用SyntaxParser类的函数
 * @Author:
 */

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#include "../Includes/global.h"
#include "../Includes/syntax_parser.h"

int main()
{
  SyntaxParser syn;
  string terminal;
  string nonterminal;
  string file_path;
  string str;

  /***** READ IN *****/
  cout << "Please enter terminal symbols(use spaces to separate): ";
  getline(cin, terminal);
  cout << "Please enter non-terminal symbols(use spaces to separate): ";
  getline(cin, nonterminal);
  while (true)
  {
    cout << "Please enter the file path(eg:\".\\Test\\test_1.txt\"): ";
    getline(cin, file_path);
    cout << endl;
    cout << "Please enter a string to parse: ";
    getline(cin, str);
    cout << endl;
    if (!syn.ReadIn(terminal, nonterminal, file_path)) break;
  }

  /***** PRINT CONTENT *****/
  syn.PrintContent();

  /***** SYNTAX PARSING *****/
  syn.Parsing(str);

  return 0;
}
