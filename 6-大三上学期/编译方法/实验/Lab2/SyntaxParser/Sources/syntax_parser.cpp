/**
 * @File: main.cpp
 * @Brief: SyntaxParser类的实现
 * @Author:
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#include "../Includes/global.h"
#include "../Includes/syntax_parser.h"

SyntaxParser::SyntaxParser()
{
  content_.clear();
  sym2id_.clear();
  id2sym_.clear();
  eps_idx_ = 0;
  sym_num_ = 0;
  productions_.clear();
  idx_table_.clear();
  first_sets_.clear();
  item_set_collection_.clear();
  edge_set_.clear();
  parsing_table_.clear();
  sft_rdc_.clear();
}

SyntaxParser::~SyntaxParser() {}

// Read the file and store the content in the string content_:
int SyntaxParser::ReadIn(const string& terminals, const string& nonterminals,
                         const string& file_path)
{
  ifstream file;

  // Read file of production rules:
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
    content_.push_back(line);
  }
  file.close();

  // Read terminal and non-terminal symbols:
  vector<string> vt = Split(terminals, " ");
  vector<string> vn = Split(nonterminals, " ");
  sym2id_["#"] = 0;
  id2sym_.push_back("#");
  for (string s : vt)
  {
    sym2id_[s] = ++sym_num_;
    id2sym_.push_back(s);
  }
  eps_idx_ = ++sym_num_;
  sym2id_["ε"] = eps_idx_;
  id2sym_.push_back("ε");
  for (string s : vn)
  {
    sym2id_[s] = ++sym_num_;
    id2sym_.push_back(s);
  }

  // Initialize:
  idx_table_.resize(sym_num_ + 1);
  first_sets_.resize(sym_num_ + 1);

  return 0;
}

// Syntax parsing:
void SyntaxParser::Parsing(const string& str)
{
  Preprocess();

  // Print:
  cout << "\nSymbol table:\n";
  for (int i = 0; i < id2sym_.size(); ++i)
    cout << setw(2) << i << "  |  " << id2sym_[i] << '\n';
  cout << "\nProductions:\n";
  for (int i = 0; i < productions_.size(); ++i)
  {
    cout << setw(2) << i << "  |  ";
    for (int j = 0; j < productions_[i].size(); ++j)
    {
      cout << id2sym_[productions_[i][j]] << ' ';
      if (j == 0) cout << "-> ";
    }
    cout << '\n';
  }

  GetAllFirstSets();

  // Print the first sets:
  cout << "\nFirst sets:\n";
  for (int i = eps_idx_ + 1; i < sym_num_ + 1; ++i)
  {
    cout << "FIRST(" << id2sym_[i] << ") =";
    for (int j : first_sets_[i]) cout << ' ' << id2sym_[j];
    cout << "\n";
  }

  GetItemSetCollection();

  // Print the item set collection:
  cout << "\nItem sets:\n";
  for (int i = 0; i < item_set_collection_.size(); ++i)
  {
    cout << "Item set " << i << ":\n";
    for (int j = 0; j < item_set_collection_[i].size(); ++j)
    {
      for (int sym : productions_[item_set_collection_[i][j].prod_idx])
        cout << id2sym_[sym] << ' ';
      cout << " |  " << item_set_collection_[i][j].dot_pos << ' ';
      cout << " |  ";
      for (int sym : item_set_collection_[i][j].first_set)
        cout << id2sym_[sym] << ' ';
      cout << endl;
    }
    cout << endl;
  }
  cout << endl;

  for (int i = 0; i < item_set_collection_.size(); ++i)
  {
    if (head_.count(i) == 0) continue;
    for (int j = head_[i]; j != -1; j = edge_set_[j].next)
    {
      cout << "    " << id2sym_[edge_set_[j].w] << endl;
      cout << setw(2) << i << " ---> " << edge_set_[j].to << endl;
    }
  }

  // Construct the predict table:
  if (GetParsingTable())
  {
    cout << "\nError: Invalid LR(1) grammar!\n";
    exit(-1);
  }

  // Print the parsing table:
  cout << "\nParsing table:\n";
  cout << "     |";
  for (int i = 0; i <= sym_num_; ++i)
  {
    if (i == eps_idx_) continue;
    cout << left << "  " << setw(3) << id2sym_[i] << '|';
  }
  cout << endl;
  for (int i = 0; i < item_set_collection_.size(); ++i)
  {
    cout << left << setw(5) << i << '|';
    for (int j = 0; j <= sym_num_; ++j)
    {
      if (j == eps_idx_) continue;
      if (parsing_table_[i][j] == -3)
        cout << left << setw(5) << " acc" << '|';
      else if (parsing_table_[i][j] == -1)
        cout << "     |";
      else if (sft_rdc_[i][j] == -1)
        cout << left << " s" << setw(3) << parsing_table_[i][j] << '|';
      else if (sft_rdc_[i][j] == -2)
        cout << left << " r" << setw(3) << parsing_table_[i][j] << '|';
    }
    cout << endl;
  }

  cout << "\nParsing of the input string: " << str << endl;
  vector<string> tokens = Split(str, " ");
  tokens.push_back("#");
  cout << "step   state_stack       symbol_stack      input      action"
       << endl;
  stack<int> st_stack;
  stack<int> sym_stack;
  int count = 0;
  st_stack.push(0);
  sym_stack.push(0);

  for (int i = 0;;)
  {
    int cur = st_stack.top();
    if (sym2id_.count(tokens[i]) == 0 ||
        parsing_table_[cur][sym2id_[tokens[i]]] == -1)
    {
      cout << "Error!\n";
      exit(-1);
    }
    if (parsing_table_[cur][sym2id_[tokens[i]]] == -3)
    {
      PrintState(count++, st_stack, sym_stack, tokens, i);
      cout << "Accept!" << endl;
      return;
    }
    if (sft_rdc_[cur][sym2id_[tokens[i]]] == -1)
    {
      PrintState(count++, st_stack, sym_stack, tokens, i);
      int new_state = parsing_table_[cur][sym2id_[tokens[i]]];
      cout << "action[" << cur << "," << sym2id_[tokens[i]]
           << "] = " << new_state;
      cout << ", push " << new_state << endl;
      sym_stack.push(sym2id_[tokens[i]]);
      st_stack.push(new_state);
      ++i;
    }
    else if (sft_rdc_[cur][sym2id_[tokens[i]]] == -2)  // 归约
    {
      PrintState(count++, st_stack, sym_stack, tokens, i);

      int numpro = parsing_table_[cur][sym2id_[tokens[i]]];  // 用该产生式归约
      int len = productions_[numpro].size() - 1;
      for (int ii = 0; ii < len; ii++)  // 出栈
      {
        sym_stack.pop();
        st_stack.pop();
      }
      sym_stack.push(productions_[numpro][0]);  // 新入
      int cur = st_stack.top();
      cout << id2sym_[productions_[numpro][0]] << "->";
      for (int ii = 1; ii <= len; ii++)
        cout << id2sym_[productions_[numpro][ii]];
      cout << ": reduce, goto[" << cur << ", " << sym2id_[tokens[i]]
           << "] = " << parsing_table_[cur][productions_[numpro][0]];
      cout << ", push " << parsing_table_[cur][productions_[numpro][0]] << endl;
      st_stack.push(parsing_table_[cur][productions_[numpro][0]]);
    }
  }
}

// Print the content read from the file:
void SyntaxParser::PrintContent()
{
  cout << "\nTerminal symbols: ";
  for (int i = 1; i < eps_idx_ + 1; ++i) cout << id2sym_[i] << ' ';
  cout << "\nNon-terminal symbols: ";
  for (int i = eps_idx_ + 1; i < sym_num_ + 1; ++i) cout << id2sym_[i] << ' ';
  cout << "\nContext-free grammars:\n"
       << "----------------------------------------\n";
  for (string& line : content_) cout << line << '\n';
  cout << "----------------------------------------\n\n";
}

//////////////////////////////////////////////////////////////////////////

// Preprocess the content:
void SyntaxParser::Preprocess()
{
  for (int i = 0; i < content_.size(); ++i)
  {
    string line = content_[i];
    if (line == "") continue;
    vector<string> line_split = Split(line, "->");
    if (line_split.size() != 2)
    {
      cout << "\nError: Invalid production rule! (line " << i + 1 << ")\n";
      exit(-1);
    }
    vector<int> production;
    production.push_back(sym2id_[line_split[0]]);
    vector<string> right_split = Split(line_split[1], " ");
    for (int i = 0; i < right_split.size(); ++i)
    {
      if (right_split[i] == "")
        continue;
      else if (right_split[i] == "|")
      {
        productions_.push_back(production);
        production.clear();
        production.push_back(sym2id_[line_split[0]]);
      }
      else
        production.push_back(sym2id_[right_split[i]]);
    }
    productions_.push_back(production);
  }
  for (int i = 0; i < productions_.size(); ++i)
    idx_table_[productions_[i][0]].push_back(i);
}

// Split the string with the delimiter:
vector<string> SyntaxParser::Split(const string& str, const string& delim)
{
  vector<string> result;
  string exp_str = str + delim;
  int pos = 0;
  while ((pos = exp_str.find(delim)) != string::npos)
  {
    string temp = exp_str.substr(0, pos);
    RemoveBlanks(temp);
    result.push_back(temp);
    exp_str = exp_str.substr(pos + delim.size());
  }
  return result;
}

// Remove blank spaces in a string(start and end):
void SyntaxParser::RemoveBlanks(string& str)
{
  int start = 0;
  int end = str.size() - 1;
  while (start < str.size() && str[start] == ' ') ++start;
  while (end >= 0 && str[end] == ' ') --end;
  str = str.substr(start, end - start + 1);
}

// Get all first sets:
void SyntaxParser::GetAllFirstSets()
{
  // For terminal symbols, the first set is itself:
  for (int i = 1; i < eps_idx_ + 1; ++i) first_sets_[i].insert(i);

  for (int i = 0; i < productions_.size(); ++i)
  {
    if (productions_[i][0] == productions_[i][1]) continue;
    GetFirstSet(productions_[i][0], i);
  }
}

// Get first set of a non-terminal symbol:
void SyntaxParser::GetFirstSet(const int& sym_id, const int& prod_idx)
{
  int right_first_id = productions_[prod_idx][1];
  if (right_first_id <= eps_idx_)  // First symbol is a terminal
    first_sets_[sym_id].insert(right_first_id);
  else  // First symbol is a non-terminal
  {
    for (int i = 0; i < idx_table_[right_first_id].size(); ++i)
    {
      if (productions_[prod_idx][0] == productions_[prod_idx][1]) continue;
      GetFirstSet(right_first_id, idx_table_[right_first_id][i]);
    }
    first_sets_[sym_id].insert(first_sets_[right_first_id].begin(),
                               first_sets_[right_first_id].end());
  }
}

// Get item set collection:
void SyntaxParser::GetItemSetCollection()
{
  vector<Item> temp;
  Item it;
  it.first_set.insert(0);
  temp = GetClosure(it);
  queue<vector<Item>> q;  // BFS
  q.push(temp);
  item_set_collection_.push_back(temp);
  while (!q.empty())
  {
    vector<Item> cur = q.front();
    q.pop();
    for (int i = 1; i <= sym_num_; i++)
    {
      if (i == eps_idx_) continue;
      temp.clear();
      for (int j = 0; j < cur.size(); j++)
      {
        if (cur[j].dot_pos ==
            productions_[cur[j].prod_idx].size())  // reduction
          continue;
        int dot_next = productions_[cur[j].prod_idx][cur[j].dot_pos];
        if (dot_next == i)
        {
          Item it;
          it.first_set = cur[j].first_set;
          it.dot_pos = cur[j].dot_pos + 1;
          it.prod_idx = cur[j].prod_idx;
          temp = CombineSet(temp, GetClosure(it));
        }
      }
      if (temp.size() == 0) continue;
      int cur_node = FindSetInCollection(cur, item_set_collection_);
      int target_node = FindSetInCollection(temp, item_set_collection_);
      if (target_node == -1)
      {
        item_set_collection_.push_back(temp);
        q.push(temp);
        AddEdge(cur_node, item_set_collection_.size() - 1, i);
      }
      else
        AddEdge(cur_node, target_node, i);
    }
  }
}

// Get closure of an item, using BFS:
vector<Item> SyntaxParser::GetClosure(Item& it)
{
  vector<Item> closure;
  closure.push_back(it);
  queue<Item> stack;
  stack.push(it);
  while (!stack.empty())
  {
    Item top_it = stack.front();
    stack.pop();
    if (top_it.dot_pos ==
        productions_[top_it.prod_idx].size())  // . is at the end
      continue;
    int sym_id_1 =
        productions_[top_it.prod_idx][top_it.dot_pos];  // symbol after .
    if (sym_id_1 <= eps_idx_)                           // terminal
      continue;
    for (int i = 0; i < idx_table_[sym_id_1].size(); i++)
    {
      Item temp_it;
      temp_it.prod_idx = idx_table_[sym_id_1][i];
      if (productions_[top_it.prod_idx].size() - top_it.dot_pos == 1)
        temp_it.first_set += top_it.first_set;
      else
      {
        int sym_id_2 = productions_[top_it.prod_idx][top_it.dot_pos + 1];
        temp_it.first_set.insert(first_sets_[sym_id_2].begin(),
                                 first_sets_[sym_id_2].end());
      }
      if (!IsItemInSet(temp_it, closure))
      {
        stack.push(temp_it);
        closure.push_back(temp_it);
      }
    }
  }
  return closure;
}

// construct an edge:
void SyntaxParser::AddEdge(const int& from, const int& to, const int& w)
{
  int f = head_.count(from) == 0 ? -1 : head_[from];
  Edge e = {f, to, w};
  edge_set_.push_back(e);
  head_[from] = edge_set_.size() - 1;
}

// Construct the parsing table:
// 0: conflict; -1: shift; -2: reduce; -3: accept
bool SyntaxParser::GetParsingTable()
{
  // Initialize:
  int size = item_set_collection_.size() + 1;
  parsing_table_ = vector<vector<int>>(size, vector<int>(size, -1));
  sft_rdc_ = vector<vector<int>>(size, vector<int>(size, -1));

  for (int i = 0; i < item_set_collection_.size(); i++)
  {
    if (head_.count(i) == 0) continue;
    for (int j = head_[i]; j != -1; j = edge_set_[j].next)
    {
      if (parsing_table_[i][edge_set_[j].w] != -1)  // conflict
        return -1;
      parsing_table_[i][edge_set_[j].w] = edge_set_[j].to;
      sft_rdc_[i][edge_set_[j].w] = -1;  // shift
    }
  }

  for (int i = 0; i < item_set_collection_.size(); i++)
    for (int j = 0; j < item_set_collection_[i].size(); j++)
      if (item_set_collection_[i][j].dot_pos ==
          productions_[item_set_collection_[i][j].prod_idx]
              .size())  // reduction
        for (auto& k : item_set_collection_[i][j].first_set)
        {
          if (parsing_table_[i][k] != -1)  // conflict
            return -1;
          if (k == 0 && item_set_collection_[i][j].prod_idx == 0)  // accept
            parsing_table_[i][k] = -3;
          else
          {
            parsing_table_[i][k] = item_set_collection_[i][j].prod_idx;
            sft_rdc_[i][k] = -2;  // reduction
          }
        }

  return 0;
}

// Print one state:
void SyntaxParser::PrintState(const int& count, stack<int> st_stack,
                              stack<int> sym_stack,
                              const vector<string>& tokens, const int& i)
{
  stack<int> temp;
  int cnt = 0;
  cout << left << ' ' << setw(2) << count << "    ";

  while (!st_stack.empty())
  {
    temp.push(st_stack.top());
    st_stack.pop();
  }
  while (!temp.empty())
  {
    cout << left << setw(2) << temp.top() << ' ';
    temp.pop();
    ++cnt;
  }
  for (int j = 0; j < 18 - 3 * cnt; ++j) cout << ' ';

  cnt = 0;
  while (!sym_stack.empty())
  {
    temp.push(sym_stack.top());
    sym_stack.pop();
  }
  while (!temp.empty())
  {
    cout << left << setw(2) << id2sym_[temp.top()] << ' ';
    temp.pop();
    ++cnt;
  }
  for (int j = 0; j < 18 - 3 * cnt; ++j) cout << ' ';

  for (int j = i; j < tokens.size(); ++j) cout << tokens[j];
  for (int j = 0; j < 11 - tokens.size() + i; ++j) cout << ' ';
}
