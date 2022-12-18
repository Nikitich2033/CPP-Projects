#ifndef COVIDCASE_H
#define COVIDCASE_H



#include <string>
using std::string;

#include <cmath>

#include <iostream>
using namespace std;
using std::ostream;
using std::cout;
using std::endl;

// TODO: your code  goes here


class CovidCase{

 private:

         double latitude;
         double longitude;
         string patientName;
         int age;
         int testedPositiveHours;

  public:
          CovidCase(float latitudeIn, float longitudeIn, string patientNameIn, int ageIn, int testedPositiveHoursIn):
                    latitude(latitudeIn),longitude(longitudeIn),patientName(patientNameIn),age(ageIn),testedPositiveHours(testedPositiveHoursIn){

                    }

          double distanceTo(CovidCase covidCase){
                double dlon = covidCase.longitude * (M_PI/180) - longitude * (M_PI/180);
                double dlat = covidCase.latitude * (M_PI/180) - latitude * (M_PI/180);
                double a = pow((sin(dlat/2)), 2) + cos(latitude * (M_PI/180)) * cos(covidCase.latitude * (M_PI/180)) * pow((sin(dlon/2)), 2);
                double c = 2 * atan2( sqrt(a), sqrt(1-a) );
                double distance = 3960 * c;

               return distance;
          }


          friend ostream& operator<<(ostream& o, const CovidCase& patientCase);



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
