#ifndef __HILLCAR_H__
#define __HILLCAR_H__

#include "HillClimbRoad.h"
#include <vector>

namespace car{

    class HillClimbCar{
        public:
            HillClimbCar(const double x, const double y, const double SCALE);
            void update(road::HillClimbRoad road, double dt);
            double updateThrottle(double dthrottle);
            double getPositionY();
            double getTransitionX(double dt);
            double getAngle();
            bool touchesRoad();
            void reset(double y);
        private:
            double X_POS;
            double SCALE;
            double x;
            double y;
            double v_x;
            double v_y;
            double a_x;
            double a_y;
            double angle;
            double v_ang;
            double a_ang;
            double throttle;
            //leftWheel;
            //rightWheel;
            std::vector<road::HillClimbRoad> roadPartsTouching;

            void updatePosY(double dt);
            void updateVelocityY(double dt);
            void updateVelocityX(double dt);
            void updateAccelerations(double dt);
            void updateAngle(double dt);
            void updateAngularVelocity(double dt);
            void updateAngularAcceleration(double dt);
            void updateRoadPartsTouching();
            void updateWheels(road::HillClimbRoad road);
    };
}

#endif
