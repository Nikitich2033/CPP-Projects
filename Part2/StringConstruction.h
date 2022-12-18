#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

// TODO: your code goes here:
static string find_longest_string(std::vector<std::string> lines) {
    size_t max = 0;
    string output = "";
    for (auto line : lines) {
        if (line.length() > max) {
            max = line.length();
            output = line;
        }
    }
    return output;
}

int stringConstruction(string& target, int cloneCost, int appendCost){

  string result = "";
  int totalCost = 0;
  std::unordered_set<string> resultSubstrings;

  while (result.size() != target.size()) {

      if (result.length() == 0) {
        result.push_back(target.at(0));
        totalCost += appendCost;
        // std::cout << "Appended: " << target.at(0) << '\n';
        // std::cout << "Cost: " << appendCost << '\n';
        // std::cout << "Result:"<< result << '\n';
      }
      else{
        //check for all possibe combinations of substrings from result in remainder of target that
        // has not been written yet
        for (int i = 0; i < result.length(); i++){
          for (int len = 1; len <= result.length() - i; len++){
              //resultSubstrings.push_back(result.substr(i, len));
              resultSubstrings.insert(result.substr(i, len));
            //  std::cout << "Set size: "<< resultSubstrings.size() << '\n';
          }
        }

        string substrRemainder = target.substr(result.length() - 1);

        map<int,string> relevantSubstrings;

        int maxLengthKey = 0;

        for(string substring : resultSubstrings){
          size_t found =substrRemainder.find(substring);
          if (found!=std::string::npos){

             if (substring.length() > maxLengthKey) {

               relevantSubstrings[substring.length()] = substring;
               maxLengthKey = substring.length();
             }

          }
        }

        string longestFoundSubstr = relevantSubstrings[maxLengthKey];

        if (target.at(result.length()) == longestFoundSubstr.at(0) && longestFoundSubstr != "" && cloneCost <= appendCost * longestFoundSubstr.length()){
          result.append(longestFoundSubstr);
          totalCost += cloneCost;
          // std::cout << "Cloned: " << longestFoundSubstr << '\n';
          // std::cout << "Cost: " <<  cloneCost << '\n';
          // std::cout << "Result:"<< result << '\n';
        }
        else{
          result.push_back(target.at(result.size() - 1));
          totalCost += appendCost;
          // std::cout << "Appended: " << target.at(result.size() - 1) << '\n';
          // std::cout << "Cost: " << appendCost << '\n';
          // std::cout << "Result:"<< result << '\n';
        }

      }
      //std::cout << "Result length: " << result.length() << '\n';
  }
  //std::cout << "Result:"<< result << '\n';
  return totalCost;
}


// do not write or edit anything below this line

#endif
