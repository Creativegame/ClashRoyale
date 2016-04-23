//
//  HealthBar.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/26.
//
//

#include "HealthBar.hpp"

USING_NS_CC;

HealthBar *HealthBar::createHealthBar(const HealthBarType &type){
    HealthBar *healthBar = new (std::nothrow) HealthBar(type);
    if (healthBar && healthBar->init()){
        healthBar->autorelease();
        return healthBar;
    }
    
    delete healthBar;
    healthBar = nullptr;
    return nullptr;
}

HealthBar *HealthBar::createHealthBar(const HealthBarType &type, const int *fullValuePointer, const int *currentValuePointer){
    HealthBar *healthBar = new (std::nothrow) HealthBar(type, fullValuePointer, currentValuePointer);
    if (healthBar && healthBar->init()){
        healthBar->autorelease();
        return healthBar;
    }
    
    delete healthBar;
    healthBar = nullptr;
    return nullptr;
}

bool HealthBar::init(){
    if (!Node::init()){
        return false;
    }
    
    _initHealthBar();
    
    return true;
}

Size HealthBar::getHealthBarSize(){
    Size selfSize = _barBackground->getContentSize();
    return selfSize;
}

void HealthBar::refresh(){
    if (*_currentValuePointer > *_fullValuePointer){
        return;
    }
    
    if (*_fullValuePointer < 0){
        return;
    }
    
    float scaleXValue = static_cast<float>(*_currentValuePointer) / static_cast<float>(*_fullValuePointer);
    if (scaleXValue < 0){
        scaleXValue = 0;
    }
    _bar->setScaleX(scaleXValue);
    _valueLabel->setString(int2String(*_currentValuePointer));
    
}

void HealthBar::_initHealthBar(){
    if (_type == HealthBarType::TowerBig){
        
        _barBackground = Sprite::createWithSpriteFrameName("tower_healthBar_big_background.png");
        _barBackground->setAnchorPoint(Vec2(0, 0));
        _barBackground->setPosition(0, 0);
        this->addChild(_barBackground, 1);
        
        _bar = Sprite::createWithSpriteFrameName("tower_healthBar_big.png");
        _bar->setAnchorPoint(Vec2(0, 0));
        _bar->setPosition(30, 6);
        this->addChild(_bar, 5);
        
        _valueLabel = createLabel(int2String(*_currentValuePointer), 30, Color3B(0, 0, 0));
        _valueLabel->setPosition(80, 20);
        this->addChild(_valueLabel, 10);
        
    }else if (_type == HealthBarType::TowerSmall){
        
        _barBackground = Sprite::createWithSpriteFrameName("tower_healthBar_small_background.png");
        _barBackground->setAnchorPoint(Vec2(0, 0));
        _barBackground->setPosition(0, 0);
        this->addChild(_barBackground, 1);
        
        _bar = Sprite::createWithSpriteFrameName("tower_healthBar_small.png");
        _bar->setAnchorPoint(Vec2(0, 0));
        _bar->setPosition(21, 5);
        this->addChild(_bar, 5);
        
        _valueLabel = createLabel(int2String(*_currentValuePointer), 25, Color3B(0, 0, 0));
        _valueLabel->setPosition(55, 12);
        this->addChild(_valueLabel, 10);
        
    }else if (_type == HealthBarType::Character){
        
        _barBackground = Sprite::createWithSpriteFrameName("character_healthBar_background.png");
        _barBackground->setAnchorPoint(Vec2(0, 0));
        _barBackground->setPosition(0, 0);
        this->addChild(_barBackground, 1);
        
        _bar = Sprite::createWithSpriteFrameName("character_healthBar.png");
        _bar->setAnchorPoint(Vec2(0, 0));
        _bar->setPosition(14, 6);
        this->addChild(_bar, 5);
        
        _valueLabel = createLabel(int2String(*_currentValuePointer), 15, Color3B(0, 0, 0));
        _valueLabel->setPosition(30, 15);
        this->addChild(_valueLabel, 10);
        
    }else {
        CCLOG("%s, type is wrong!", __func__);
    }
    
    refresh();
}