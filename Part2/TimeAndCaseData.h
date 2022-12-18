#ifndef TIMEANDCASEDATA_H
#define TIMEANDCASEDATA_H

#include "CovidCase.h"

using namespace std;

class TimeAndCaseData{

private:

        int currentTime;
        int numberOfActiveCases;

public:

        TimeAndCaseData(int caseNumber, int time)
                        :numberOfActiveCases(caseNumber),currentTime(time){
                      }


        int getTime(){
          return currentTime;
        };

        int getNumberOfCases(){
          return numberOfActiveCases;
        };

};



#endif
