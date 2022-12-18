#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {

private:
    std::string solution;
    int value;

public:

    CountdownSolution() : solution(), value(0) {}

    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }

    const std::string & getSolution() const {
        return solution;
    }

    int getValue() const {
        return value;
    }

};

// Do not edit above this line

// TODO: write code here:

double evaluateCountdown(std::string RPN){

  std::string input = RPN;

  std::vector<std::string> words{};
  std::stack<double> evalStack;
  size_t position = 0;

  std::string word = "";
  for (auto x : input)
    {
        if (x == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }

    words.push_back(word);

  for (const auto &str : words) {

    if ( str == "+" || str == "-" || str == "/" || str == "*") {

      if (evalStack.size() < 2) {
        return 0;
      }
      if (evalStack.size() >= 2) {
        double value1 = evalStack.top();
        evalStack.pop();


        double value2 = evalStack.top();
        evalStack.pop();

        if ((value2 == 0 || value1 == 0)) {

          return 0;

        }
        else{
          if (str == "+") {
            evalStack.push(value2 + value1);
          }
          else if(str == "-"){
            evalStack.push(value2 - value1);
          }
          else if(str == "/"){
            evalStack.push(value2 / value1);
          }
          else if(str == "*"){
            evalStack.push(value2 * value1);
          }
        }
      }
    }
    else{

        evalStack.push(std::stod(str));
    }

  }

  return evalStack.top();

}

CountdownSolution solveCountdownProblem(std::vector<int> numbers,int target){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::string> operators = {"+","-","/","*"};

    std::string finalSolution = "";
    std::string solution = "";

    int counter = 0;
    int attempt_counter = 0;
    std::vector<int> alreadyUsedIndex = {};

    while (finalSolution == "") {
        attempt_counter++;
        //select 1st and 2nd number
        if (counter < 2) {

          std::uniform_int_distribution<> distr(0, 5);
          int randomValue = distr(gen);

          if (!(std::find(alreadyUsedIndex.begin(), alreadyUsedIndex.end(), randomValue) != alreadyUsedIndex.end())) {
            solution.append(intToString(numbers.at(randomValue))+ " ");
            alreadyUsedIndex.push_back(randomValue);
            counter = counter + 1;
          }
        }
        else if(counter >= 2 && counter <= 10 ){

          std::uniform_int_distribution<> distr(1, 2);
          int randomValue = distr(gen);

          if (randomValue == 1) {

            std::uniform_int_distribution<> distr(0, 5);
            int randomValue = distr(gen);

            if (!(std::find(alreadyUsedIndex.begin(), alreadyUsedIndex.end(), randomValue) != alreadyUsedIndex.end())) {
              solution.append(intToString(numbers.at(randomValue)));
              alreadyUsedIndex.push_back(randomValue);

              if (counter < 10) {
                solution.append(" ");
              }

              counter = counter + 1;
            }
          }
          else if(randomValue == 2){

            std::uniform_int_distribution<> distr(0, 3);

            solution.append(operators.at(distr(gen)));
            if (counter < 10) {
              solution.append(" ");
            }

            counter = counter + 1;
          }


        }

        else{

            std::vector<bool> allNumbers;
            int opcounter = 0;
            int numCounter = 0;
            for(char c : solution) {
              if(c == '+' || c == '-' || c == '*' || c=='/'){
                opcounter++;
              }
            }
            for(int number : numbers){
              if(typeid(number) == typeid(int)){
                numCounter++;
              }
            }

            if (opcounter == numCounter - 1 ) {

                if (evaluateCountdown(solution) == target) {
                    finalSolution = solution;
                    //std::cout << "Correct solution: "<<solution << '\n';
                  }
            }

          solution = "";
          counter = 0;
          alreadyUsedIndex = {};

        }

      }

    //std::cout << "Solutions evaluated: "<< attempt_counter << '\n';
    return CountdownSolution(finalSolution,evaluateCountdown(finalSolution));



}

// Do not edit below this line


#endif
