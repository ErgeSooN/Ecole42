#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param instructions The list of instructions as memorized by the mutant.
 * @param target The coordinates (x, y) of the target.
 * @return A string respecting the given format to fix the mutant's path.
 */
string findCorrectPath(vector<string> instructions, vector<int> target) {
  // Write your code here
  // Şu şekilde çalışıyor:
    //return "Replace instruction 3 with FORWARD"; // 3.indexi FORWARD ile değiştir.

  //Mutant belirli bir pathi biliyor lakin yanlış biliyor,
  //  Bizim mutant'ın bildiği pathi değiştirip, hedefe götürmemiz gerekiyor.
  vector<int> loc; // Mutantın konumu
  loc.push_back(0); // x
  loc.push_back(0); // y
  std::string direc = "E"; // Mutant sağa bakmaktadır
  // Kuzey, Güney, Doğu, Batı değerlerini alabilir.
  // N, S, E, W

  // ilk cevap: "Replace instruction 1 with TURN RIGHT"

  vector<std::string> ac;
  ac.push_back("FORWARD");
  ac.push_back("BACK");
  ac.push_back("TURN LEFT");
  ac.push_back("TURN RIGHT");

  std::string index;
  std::string action;
  bool run = true;
  vector<std::string> old = instructions;
  size_t size = old.size();

  for (size_t k = 0; k < size && run != false; ++k) // adımları tek tek değiştirip deneyecek
  {
    for (size_t l = 0; l < 4 && run != false; ++l) // 4 farklı durum var, herbirini koyup tek tek deneyecek
    {
      instructions[k] = ac[l];
      loc[0] = 0;
      loc[1] = 0;
      direc = "E";
      for (size_t i = 0; i < size && run != false; ++i)
      {
        if (instructions[i] == "FORWARD"){
          if (direc == "N")
            loc[1]++;
          else if (direc == "S")
            loc[1]--;
          else if (direc == "E")
            loc[0]++;
          else
            loc[0]--;
        }
        else if (instructions[i] == "BACK"){
          if (direc == "N")
            loc[1]--;
          else if (direc == "S")
            loc[1]++;
          else if (direc == "E")
            loc[0]--;
          else
            loc[0]++;
        }
        else if (instructions[i] == "TURN LEFT"){
          if (direc == "N")
            direc = "W";
          else if (direc == "S")
            direc = "E";
          else if (direc == "E")
            direc = "N";
          else
            direc = "S";
        }
        else if (instructions[i] == "TURN RIGHT"){
          if (direc == "N")
            direc = "E";
          else if (direc == "S")
            direc = "W";
          else if (direc == "E")
            direc = "S";
          else
            direc = "N";
        }

        if (i + 1 == size && target[0] == loc[0] && target[1] == loc[1])
        {
          action = ac[l];
          index = std::to_string(k + 1);
          return ("Replace instruction " + index + " with " + action);
          run = false;
        }
      }
      instructions[k] = old[k];
      loc[0] = 0;
      loc[1] = 0;
      direc = "E";

    }
  }

  // std::cout << loc[0] << "-" << loc[1] << std::endl;

  // std::string index = "1"; // döngü kontrolü için indexi 8 yap.
  // std::string action = "TURN RIGHT";
  return ("Replace instruction " + index + " with " + action);
}

/* Ignore and do not change the code below */

void trySolution(string recipe) {
  Json::Value output_json;
  output_json = Json::Value(recipe);

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

  vector<string> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array.push_back(parsed_json[i].asString());
  }
  vector<string> instructions = array;
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<int> array_2;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array_2.push_back(parsed_json[i].asInt());
  }
  vector<int> target = array_2;

  string output = findCorrectPath(instructions, target);
  trySolution(output);
}
/* Ignore and do not change the code above */
