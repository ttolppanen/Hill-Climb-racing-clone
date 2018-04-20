#include <cmath>
#include <map>
#include <chrono>
#include <iostream>
#include <vector>

#include "cocos2d.h"
#include "HillClimbLayer.h"
#include "HillClimbUtility.h"
#include "HillClimbRoad.h"

namespace hillclimb {

    std::map<cocos2d::EventKeyboard::KeyCode,
             std::chrono::high_resolution_clock::time_point> HillClimbLayer::keys;

    bool HillClimbLayer::init() {
        if (!Layer::init()) {
            return false;
        }

        const auto director = cocos2d::Director::getInstance();
        const auto winSize = director->getWinSize();
        double winWidth = static_cast<double>(winSize.width);
        double winHeight = static_cast<double>(winSize.height);
    
        double spriteScale = DESIGN_RESOLUTION_SIZE.width / winWidth;
        this->carSprite = cocos2d::Sprite::create("car.png");
        this->carSprite->setScale(spriteScale, spriteScale);

        const auto carSize = this->carSprite->getContentSize();
        double carStartX = carSize.width / 2;
        this->carStartY = winSize.height / 2.0 + carSize.height;
        this->carSprite->setPosition(carStartX, carStartY);
        this->carSprite->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        this->addChild(this->carSprite, 0);
    
        //Initialize car field here. Arguments: carStartX, carStartY, spriteScale
        actualCar = std::unique_ptr<car::HillClimbCar>(new car::HillClimbCar(carStartX, carStartY, spriteScale));
        //Initialize road field here. Arguments: winWidth, winHeight
        actualRoad = std::unique_ptr<road::HillClimbRoad>(new road::HillClimbRoad(winWidth, winHeight));
        actualRoad->addPart(carStartX - 100, carStartY -100);
        actualRoad->addPart(carStartX + 100,  carStartY - 200);
        actualRoad->addPart(carStartX + 300,  carStartY - 100);
        std::cout << "jee\n";
        this->generateRoadParts();

        auto eventListener = cocos2d::EventListenerKeyboard::create();
        director->getOpenGLView()->setIMEKeyboardState(true);
        eventListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
            if (keys.find(keyCode) == keys.end()){
                keys[keyCode] = std::chrono::high_resolution_clock::now();
            }
        };
        eventListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
            keys.erase(keyCode);
        };
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
        this->scheduleUpdate();
    
        return true;
    }

    bool HillClimbLayer::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
        if (keys.find(code) != keys.end())
            return true;
        return false;
    }

    void HillClimbLayer::generateRoadParts() {
        int MIN_ROAD_SIZE = 3;
        int roadCount = actualRoad->getPartCount();
        std::cout << roadCount << "\n";
                
        std::vector<std::vector<double>> roadCoordPairs = actualRoad->getPartCoords();
    
        if(roadCount < MIN_ROAD_SIZE){
            return;
        }

        auto drawNode = cocos2d::DrawNode::create();
        drawNode->setName("drawNode");
        for(int i = 0; i < roadCount - 1; ++i){
            std::vector<double> beginCoords = roadCoordPairs[i];
            std::vector<double> endCoords = roadCoordPairs[i + 1];
            std::cout << beginCoords[0];
            drawNode->drawLine(cocos2d::Point(beginCoords[0], beginCoords[1]),
            cocos2d::Point(endCoords[0], endCoords[1]),
            cocos2d::Color4F::WHITE);
        }
        this->addChild(drawNode);
    }

    void HillClimbLayer::deleteRoadParts() {
        this->removeChildByName("drawNode");
    }

    void HillClimbLayer::update(float dt) {
        cocos2d::Node::update(dt);
        double throttle;
        if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
            throttle = actualCar->updateThrottle(dt * 1000);
            //actualRoad->move(100 * dt);
        } else if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
            throttle = actualCar->updateThrottle(-dt * 1000);
            //Put the brake on with the updateThrottle method
        } else if (throttle > 0){
             throttle = actualCar->updateThrottle(-dt * 200);
        }
            //Slow the car down with the updateThrottle method
        if(throttle < 0){
            throttle = 0;
        }
        else if(throttle > 400){
            throttle = 400;
        }
        actualRoad->move(throttle * dt);
        /*Get car transition
          Get car angle. Use std::fmod for it with STRAIGHT_ANGLE as divisor.
    
          Check if the car is touching the road AND if its angle is over or below some limit, to determine if it has crashed
          Check if the car's transition is below some value to determine if it is reversing
          if the car is either crashed or reversing:
               Reset the car with carStartY as argument
               Reset the road
          else
               Update the car with road and dt as arguments
               Move the road with carTransition as argument
          }*/
        actualRoad->deletePartsBehind();
        actualRoad->generatePartsAhead();
        this->deleteRoadParts();
        this->generateRoadParts();
        //Set carSprite position with setPositionY(y). The argument y should be the y position of the car
        //Set sprite rotation with setRotation(angle / STRAIGHT_ANGLE * 180);
    }

    cocos2d::Scene* HillClimbLayer::createScene() {
        auto scene = cocos2d::Scene::create();
        auto layer = HillClimbLayer::create();

        scene->addChild(layer);
        return scene;
    }
}
