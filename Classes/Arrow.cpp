//
//  Arrow.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/15.
//
//

#include "Arrow.hpp"
#include "BattleElement.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

Arrow *Arrow::createArrow(BattleElement *from, BattleElement *to, BattleLayer *battleLayer){
    Arrow *arrow = new (std::nothrow) Arrow(from, to, battleLayer);
    if (arrow && arrow->init()){
        arrow->autorelease();
        return arrow;
    }
    
    delete arrow;
    arrow = nullptr;
    return nullptr;
}

Arrow *Arrow::createArrow(const cocos2d::Vec2 &fromPoint, const cocos2d::Vec2 &toPoint, BattleLayer *battleLayer){
    Arrow *arrow = new (std::nothrow) Arrow(fromPoint, toPoint, battleLayer);
    if (arrow && arrow->init()){
        arrow->autorelease();
        return arrow;
    }
    
    delete arrow;
    arrow = nullptr;
    return nullptr;
}

bool Arrow::init(){
    if (!Sprite::initWithSpriteFrameName("arrow.png")){
        return false;
    }
    
    this->setAnchorPoint(Vec2(0, 0.5));
    float tanTheta = (_fromPoint.y - _toPoint.y) / (_fromPoint.x - _toPoint.x);
    float theta = atanf(tanTheta);
    float thetaAngle = (180 / M_PI) * theta;
    if (_fromPoint.y >= _toPoint.y){
        if (_fromPoint.x >= _toPoint.x){
            thetaAngle = -thetaAngle;
        }else {
            thetaAngle = (180 - thetaAngle);
        }
    }else {
        if (_fromPoint.x >= _toPoint.x){
            thetaAngle = -thetaAngle;
        }else {
            thetaAngle = (180 - thetaAngle);
        }
    }
    
    this->setRotation(thetaAngle);
    
    CCLOG("%s, Angle: %f", __func__, thetaAngle);
    
    return true;
}
