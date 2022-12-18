#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"
#include "TimeAndCaseData.h"
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

// TODO: your code goes here

class CovidCaseMap{

private:

      vector<CovidCase> confirmedCases;

public:

      void addCase(CovidCase covidCase){
          confirmedCases.push_back(covidCase);
      }

      vector<CovidCase> getConfirmedCases(){
        return confirmedCases;
      }

      vector<TimeAndCaseData> getCasesOverTime(int time){

            vector<TimeAndCaseData> result;

            for (size_t i = 0; i < confirmedCases.back().getTime()+time; i++) {

                int numberOfActiveCases = 0;

                for (CovidCase covidCase : getConfirmedCases()) {

                    if (i - covidCase.getTime() <= time) {
                        ++numberOfActiveCases;
                    }
                }

                if(i == 0){

                  result.push_back(TimeAndCaseData(numberOfActiveCases,0));
                  
                }
                if (result.size() != 0){

                  if(result.back().getNumberOfCases() > numberOfActiveCases){
                    result.push_back(TimeAndCaseData(numberOfActiveCases,i-1));
                  }
                  else if(result.back().getNumberOfCases() < numberOfActiveCases){
                    result.push_back(TimeAndCaseData(numberOfActiveCases,i));
                  }
                  else if(i == confirmedCases.back().getTime() + time - 1){
                    result.push_back(TimeAndCaseData(0,confirmedCases.back().getTime() + time));
                  }

                }


            }

            return result;

      }

      vector<CovidCase> getActiveCases(int startTime, int isolationTime){

        vector<CovidCase> activeCases;


          for (CovidCase covidCase : getConfirmedCases()) {

              if (covidCase.getTime() <= startTime && startTime - covidCase.getTime() <= isolationTime) {

                 activeCases.push_back(covidCase);

              }
          }


        return activeCases;

      }

      double distanceToFromStartPosition(CovidCase covidCase,double latitude, double longitude){
          double dlon = covidCase.getLongitude() * (M_PI/180) - longitude * (M_PI/180);
          double dlat = covidCase.getLatitude() * (M_PI/180) - latitude * (M_PI/180);
          double a = pow((sin(dlat/2)), 2) + cos(latitude * (M_PI/180)) * cos(covidCase.getLatitude() * (M_PI/180)) * pow((sin(dlon/2)), 2);
          double c = 2 * atan2( sqrt(a), sqrt(1-a) );
          double distance = 3960 * c;

          return distance;
     }

     static bool sort_using_less_than(double u, double v){
         return u < v;
     }

      double supportVisitGreedyTSP(double latitude, double longitude, int time, int lengthOfIsolation){

        // - Start at the start location
        // - Then go to the nearest patient who hasn't been visited yet
        // - Then go to the nearest patient who hasn't been visited yet
        // - etc. etc. until all patients have been visited
        // - Then return to the start location

        vector<CovidCase> visited = {};
        vector<CovidCase> allPatients = getActiveCases(time, lengthOfIsolation);
        vector<double> distToPatients;

        for(CovidCase covidCase : allPatients){
          distToPatients.push_back(distanceToFromStartPosition(covidCase,latitude, longitude));
        }

        double distToClosestPatient = *std::min_element(begin(distToPatients), end(distToPatients));

        CovidCase currentPatient = CovidCase();

        for(CovidCase covidCase : allPatients){
          if (distToClosestPatient == distanceToFromStartPosition(covidCase,latitude, longitude)) {
            currentPatient = covidCase;
            visited.push_back(covidCase);
          }
        }

        while (visited.size() != allPatients.size()) {

          distToPatients.clear();

          for(CovidCase covidCase : allPatients){
            distToPatients.push_back(currentPatient.distanceTo(covidCase));
          }

          sort(distToPatients.begin(), distToPatients.end(), sort_using_less_than);

          vector<double> sortedDistance = distToPatients;

          //while next patient has not been chosen
          //if patient with shortest path has already been visited
          //try next minimum distance on the list
          //set currentPatient to new value
          //change patientChosen to true

          bool patientChosen = false;
          int tryIndex = 0;

          while (patientChosen == false) {
            bool patientAlreadyVisited = false;


            for(CovidCase covidCase : visited){
              if (currentPatient.distanceTo(covidCase) == sortedDistance.at(tryIndex)) {
                patientAlreadyVisited = true;
              }
            }


            if (patientAlreadyVisited == false) {

              for(CovidCase covidCase : allPatients){

                if (currentPatient.distanceTo(covidCase) == sortedDistance.at(tryIndex)) {

                  visited.push_back(covidCase);
                  currentPatient = covidCase;
                  patientChosen = true;
                  tryIndex = 0;
                }

              }

            }
            else{
              tryIndex++;
            }
          }

        }

        double routeLength;

        for (int i = 0; i < visited.size() - 1; i++) {
          routeLength = routeLength + visited.at(i).distanceTo(visited.at(i+1));
        }

        routeLength = routeLength + distanceToFromStartPosition(visited.front(),latitude,longitude)
                                     + distanceToFromStartPosition(visited.back(),latitude, longitude);

        return routeLength;
      }


};


// don't write any code below this line

#endif
