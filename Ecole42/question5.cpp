#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
#include <algorithm>
using namespace std;



/**
 * @param n_gears An integer representing the number of gears in the system (numbered from 0 to N-1).
 * @param connections An array representing all pairs of gears connected together.
 * @return An array of two integers representing the number of gears rotating clockwise and counterclockwise respectively, or [-1, -1] if the configuration is invalid.
 */
vector<int> gearBalance(int gears, vector<vector<int>> VEC) {
  int left = 0;
  int right = 0;
  map<int, int>::iterator it;
  map<int, int>::iterator ite;
  map<int, int> end; // <Sayı, left/right>
  map<int, vector<int>>map; // <Sayı, <Next, Next, Next>>
  size_t vectorSize = VEC.size();
  size_t size;

  for (size_t i = 0; i < vectorSize; ++i)
  {
    map[VEC[i][0]].push_back(VEC[i][1]);
    map[VEC[i][1]].push_back(VEC[i][0]);
  }

  end[0] = 0;
  int value = 0;
  for (auto it = map.begin(); it != map.end(); ++it)
  {
    ite = end.find(it->first);
    if (ite != end.end())
    {
      if (end[ite->first] == 1)
        value = 0;
      else
        value = 1;
      size = it->second.size();
      for (int i = 0; i < size; ++i)
        end[it->second[i]] = value;
    }
    if (std::next(it) == map.end() && end.size() != gears)
    {
      it = map.begin();
    }
  }


  for (size_t i = 0; i < vectorSize; ++i)
  {
    it = end.find(VEC[i][0]);
    ite = end.find(VEC[i][1]);
    if (it->second == ite->second)
      return {-1, -1};
   }

  // for (auto it = map.begin(); it != map.end(); ++it)
  // {
  //   std::cout << it->first << "-> ";
  //   size = it->second.size();
  //   for (size_t i = 0; i < size; ++i)
  //   {
  //     std::cout << it->second[i] << " * ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << "------------------" << std::endl;
  for (auto it = end.begin(); it != end.end(); ++it)
  {
    // std::cout << "->:" << it->first << "-" << it->second << std::endl;
    if (it->second == 0)
      right++;
    else if (it->second == 1)
      left++;
  }

  return {right, left};


}

  /* Ignore and do not change the code below */

  void trySolution(vector<int> output) {
    Json::Value output_json;

    output_json = Json::Value(Json::arrayValue);
    Json::Value current_value;
    for (int i = 0 ; i < output.size() ; i++) {
      current_value = Json::Value(output[i]);
      output_json.append(current_value);
    }

    Json::FastWriter fastWriter;
    std::string output_str = fastWriter.write(output_json);
    cout << "" << output_str.c_str();
  }

  int main () {
    setlocale(LC_ALL, "en_US.UTF-8");
    Json::Reader reader;
    string line;
    Json::Value parsed_json;
    std::getline(std::cin, line, '\n');
    reader.parse(line, parsed_json);
    int n_gears = parsed_json.asInt();
    std::getline(std::cin, line, '\n');
    reader.parse(line, parsed_json);

    vector<vector<int>> array;
    for (int i = 0 ; i < parsed_json.size() ; i++) {
    
      vector<int> array2;
      for (int j = 0 ; j < parsed_json[i].size() ; j++) {
        array2.push_back(parsed_json[i][j].asInt());
      }
      array.push_back(array2);
    }
    vector<vector<int>> connections = array;

    vector<int> output = gearBalance(n_gears, connections);
    trySolution(output);
  }
  /* Ignore and do not change the code above */
