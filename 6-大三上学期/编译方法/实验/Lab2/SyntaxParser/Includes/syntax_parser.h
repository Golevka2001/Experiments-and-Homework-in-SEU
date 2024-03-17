/**
 * @File: syntax_parser.h
 * @Brief: 语法分析器类的声明
 * @Author:
 */

#pragma once

class SyntaxParser
{
 public:
  SyntaxParser();
  ~SyntaxParser();

  int ReadIn(const string& terminal, const string& nonterminal,
             const string& file_path);
  void PrintContent();
  void Parsing(const string& str);

 private:
  void Preprocess();
  vector<string> Split(const string& str, const string& delim);
  void RemoveBlanks(string& str);
  void GetAllFirstSets();
  void GetFirstSet(const int& sym_id, const int& prod_idx);
  void GetItemSetCollection();
  vector<Item> GetClosure(Item& t);
  void AddEdge(const int& from, const int& to, const int& sym_id);
  bool GetParsingTable();
  void PrintState(const int& count, stack<int> st_stack, stack<int> sym_stack,
                  const vector<string>& tokens, const int& i);

  vector<string> content_;
  unordered_map<string, int> sym2id_;
  vector<string> id2sym_;
  int eps_idx_;
  int sym_num_;
  vector<vector<int>> productions_;
  vector<vector<int>> idx_table_;
  vector<unordered_set<int>> first_sets_;
  vector<vector<Item>> item_set_collection_;
  vector<Edge> edge_set_;
  unordered_map<int, int> head_;
  vector<vector<int>> parsing_table_;
  vector<vector<int>> sft_rdc_;  // shift or reduce
};
