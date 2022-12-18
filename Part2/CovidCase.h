#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;


// TODO: your code  goes here


class CovidCase{

 private:

         double latitude;
         double longitude;
         string patientName;
         int age;
         int testedPositiveHours;

  public:
          CovidCase(){}

          CovidCase(double latitudeIn, double longitudeIn, string patientNameIn, int ageIn, int testedPositiveHoursIn):
                    latitude(latitudeIn),longitude(longitudeIn),patientName(patientNameIn),age(ageIn),testedPositiveHours(testedPositiveHoursIn){

                    }

          CovidCase(string patientInfo){
                stringstream ss(patientInfo);
                vector<string> result;

                while( ss.good() )
                {
                    string substr;
                    getline( ss, substr, ',' );
                    result.push_back( substr );
                }

                latitude = stod(result.at(0));
                longitude = stod(result.at(1));
                patientName =  result.at(2).substr(2, result.at(2).size() - 3);;
                age = stoi(result.at(3));
                testedPositiveHours = stoi(result.at(4));

          }

           double distanceTo(CovidCase covidCase){
               double dlon = covidCase.longitude * (M_PI/180) - longitude * (M_PI/180);
               double dlat = covidCase.latitude * (M_PI/180) - latitude * (M_PI/180);
               double a = pow((sin(dlat/2)), 2) + cos(latitude * (M_PI/180)) * cos(covidCase.latitude * (M_PI/180)) * pow((sin(dlon/2)), 2);
               double c = 2 * atan2( sqrt(a), sqrt(1-a) );
               double distance = 3960 * c;

               return distance;
          }

          double getLatitude(){
            return latitude;

          }

          double getLongitude(){
            return longitude;
          }

          string getName(){
            return patientName;
          }

          int getAge(){
            return age;
          }

          int getTime(){
            return testedPositiveHours;
          }

          friend ostream& operator<<(ostream& o, const CovidCase& patientCase);
          friend bool operator==(const CovidCase& lhs, const CovidCase& rhs);


};

bool compare_double(double x, double y, double epsilon = 0.0000001f){
   if(fabs(x - y) < epsilon)
      return true;
      return false;
}

bool operator==(CovidCase& lhs,  CovidCase& rhs){

  if (lhs.getLatitude() == rhs.getLatitude() &&
      lhs.getLongitude() == rhs.getLongitude() &&
      lhs.getName() == rhs.getName()  &&
      lhs.getAge() == rhs.getAge() &&
      lhs.getTime() == rhs.getTime()) {

      return true;
  }
  else{
      return false;
  }

};

ostream& operator<<(ostream& o, const CovidCase& patientCase){

    o <<"{"
      << patientCase.latitude
      << ", "
      << patientCase.longitude
      << ", "
      <<"\""
      << patientCase.patientName
      <<"\""
      << ", "
      << patientCase.age
      << ", "
      << patientCase.testedPositiveHours
      << "}";

      return o;

}




// don't write any code below this line

#endif
