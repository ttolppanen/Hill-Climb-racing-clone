#ifndef __HILLCLIMBROAD_H__
#define __HILLCLIMBROAD_H__

#include <vector>

namespace road{
    class HillClimbRoad{
        public:
            int MAX_PART_COUNT;
            double X_ROAD_START;
            double Y_ROAD_START;
            double DEFAULT_ROAD_LENGTH;
            HillClimbRoad(double winWidth, double winHeight);
            void move(double x);
            std::vector<std::vector<double>> getPartCoords();
            int getPartCount();
            void reset();
            void addPart(double x, double y);
            void generatePartsAhead();
            void deletePartsBehind();
        private:
            std::vector<std::vector<double>> partCoords;
            double calculateNewPartX();
            double calculateNewPartY();
    };
}
#endif