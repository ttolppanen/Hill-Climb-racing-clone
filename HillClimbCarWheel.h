/*#ifndef __HILLWHEEL_H__
#define __HILLWHEEL_H__
  
#include

namespace wheel{

    struct RoadPartTouching{
        double wheelSubmersion;
        double slope;
    }
    class CarWheel{
      public
        CarWheel(x_offset, y_offset, radius)
        getForceX()
        getForceY()
        getRoadPartsTouching()
        updateState(throttle, carPos, carAngle, road)
        clearPreviousState()
      private:
        OFFSET
        OFFSET_ANGLE
        RADIUS
        x
        y
        force_x
        force_y
        roadPartsTouching
    
        touchesRoad()
        updatePosX(carX, carAngle)
        updatePosY(carY, carAngle)
        updateRoadPartsTouching(road)
        void updateForces(throttle)
    };
}

#endif*/
