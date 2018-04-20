#ifndef __HILLCLIMB_LAYER_H__
#define __HILLCLIMB_LAYER_H__

#include <memory>
#include <map>
#include <chrono>
#include "HillClimbRoad.h"
#include "HillClimbCar.h"

#include "cocos2d.h"
// Add missing includes here

namespace hillclimb {

    class HillClimbLayer : public cocos2d::Layer {
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(HillClimbLayer);
        virtual void update(float delta) override;
        bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    private:
        static std::map<cocos2d::EventKeyboard::KeyCode,
            std::chrono::high_resolution_clock::time_point> keys;
    
        //Car field;
        std::unique_ptr<car::HillClimbCar> actualCar;
        //Road field;
        std::unique_ptr<road::HillClimbRoad> actualRoad;
        cocos2d::Sprite* carSprite; // autoreleased by cocos2d so no need to delete
        double carStartY;
    
        void generateRoadParts();
        void deleteRoadParts();
    };

    cocos2d::Scene* createScene();
}
#endif // __HILLCLIMB_LAYER_H__
