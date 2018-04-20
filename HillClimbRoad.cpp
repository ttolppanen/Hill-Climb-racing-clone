#include "HillClimbRoad.h"
#include <vector>
#include "cocos2d.h"

namespace road{

   double ROAD_LENGHT_FACTOR = 5;

   HillClimbRoad::HillClimbRoad (double winWidth, double winHeight)
   :MAX_PART_COUNT(10){}
   
   int HillClimbRoad::getPartCount(){
       int summa = 0;
       for(std::vector<double> coord: partCoords){
           summa += 1;
       }
       return summa;
   }

   std::vector<std::vector<double>> HillClimbRoad::getPartCoords(){
       return partCoords;
   }

   void HillClimbRoad::addPart(double x, double y){
       partCoords.push_back({x, y});
   }
   void HillClimbRoad::move(double x) {
       for(std::vector<double>& coord: partCoords){
           coord[0] -= x;
       }
       /*move the x's of parts
       deletePartsBehind
       generatePartsAhead*/
   }
   void HillClimbRoad::deletePartsBehind() {
      if(partCoords[0][0] < -500){
          partCoords.erase(partCoords.begin());
      }
   }
   double HillClimbRoad::calculateNewPartX() {
       return partCoords.back()[0] + 300 + cocos2d::RandomHelper::random_int(0, 200);
   }

   double HillClimbRoad::calculateNewPartY() {
       return 500 + cocos2d::RandomHelper::random_int(0, 150);
   }

   void HillClimbRoad::generatePartsAhead(){
       int spawnattavaMaara = MAX_PART_COUNT - getPartCount();
       for(int i = spawnattavaMaara; i > 0; --i){
           double newX = calculateNewPartX();
           double newY = calculateNewPartY();
           addPart(newX, newY);
       }
   }

   /*deletePartsBehind() {
      delete parts whose x < -DEFAULT_ROAD_LENGTH * ROAD_LENGTH_FACTOR
   }

   move(x) {
       move the x's of parts
       deletePartsBehind
       generatePartsAhead
   }

   reset
       clear partCoords
       add two horizontal parts
       generatePartsAhead
   }*/
}
