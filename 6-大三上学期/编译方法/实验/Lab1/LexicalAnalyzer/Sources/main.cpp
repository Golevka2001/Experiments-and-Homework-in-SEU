/**
 * @File: main.cpp
 * @Brief: 主函数：读取文件、进行词法分析、输出Token序列到文件
 * @Author:
 */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "../Includes/lexical_analyzer.h"

int main()
{
  LexicalAnalyzer lex;
  string file_path;

  /***** READ FILE *****/
  while (true)
  {
    cout << "Please enter the file path(eg:\".\\Test\\test_1.txt\"): ";
    getline(cin, file_path);
    if (!lex.ReadFile(file_path)) break;
  }

  /***** PRINT CONTENT *****/
  // lex.PrintContent();

  /***** LEXICAL ANALYSIS *****/
  lex.Analysis();

  /***** WRITE RESULT*****/
  lex.WriteResult(file_path);

  system("pause");
  return 0;
}
