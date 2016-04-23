//
//  BattleUIWaterBar.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/20.
//
//

#include "BattleUIWaterBar.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

BattleUIWaterBar *BattleUIWaterBar::createBattleUIWaterBar(BattleLayer *battleLayer){
    BattleUIWaterBar *battleUIWaterBar = new (std::nothrow) BattleUIWaterBar(battleLayer);
    if (battleUIWaterBar && battleUIWaterBar->init()){
        battleUIWaterBar->autorelease();
        return battleUIWaterBar;
    }
    
    delete battleUIWaterBar;
    battleUIWaterBar = nullptr;
    return nullptr;
}

bool BattleUIWaterBar::init(){
    if (!Node::init()){
        return false;
    }
    
    _waterBar = Sprite::createWithSpriteFrameName("battle_ui_waterBar.png");
    _waterBar->setAnchorPoint(Vec2(0, 0));
    _waterBar->setPosition(0, 0);
    this->addChild(_waterBar, 0);
    
    _waterNumberLabel = createLabel(int2String(_battleLayer->getPlayerWater()), 30, Color3B(255, 255, 255));
    _waterNumberLabel->enableOutline(Color4B(0, 0, 0, 255), 2);
    _waterNumberLabel->setPosition(68, 33);
    _waterBar->addChild(_waterNumberLabel, 5);
    
    for (int waterInBarIndex = 0; waterInBarIndex < GameData::getInstance()->getMaxWater(); ++waterInBarIndex){
        Sprite *waterInBar = Sprite::createWithSpriteFrameName("battle_ui_waterBar_process.png");
        waterInBar->setAnchorPoint(Vec2(0, 0.5));
        waterInBar->setPosition(48 + waterInBarIndex * 45, 24);
        _waterBar->addChild(waterInBar, 1);
        _waters.push_back(waterInBar);
    }
    
    return true;
}

void BattleUIWaterBar::onEnter(){
    Node::onEnter();
    this->scheduleUpdate();
}

void BattleUIWaterBar::onExit(){
    Node::onExit();
    this->unscheduleUpdate();
}

void BattleUIWaterBar::update(float dt){
    _waterNumberLabel->setString(int2String(_battleLayer->getPlayerWater()));
    
    int waterInBarIndex = 0;
    for (; waterInBarIndex < _battleLayer->getPlayerWater(); ++waterInBarIndex){
        if (waterInBarIndex < _waters.size()){
            _waters[waterInBarIndex]->setVisible(true);
        }
    }
    if (waterInBarIndex < _waters.size()){
        _waters[waterInBarIndex]->setVisible(true);
        _waters[waterInBarIndex]->setScaleX(_battleLayer->getPlayerCurrentWaterProgress());
        if (_battleLayer->getPlayerCurrentWaterProgress() >= 1){
            _waters[waterInBarIndex]->runAction(Sequence::create(ScaleTo::create(0.03, 1.1, 1), ScaleTo::create(0.03, 1, 1), NULL));
        }
        ++waterInBarIndex;
    }
    for (; waterInBarIndex < GameData::getInstance()->getMaxWater(); ++waterInBarIndex){
        if (waterInBarIndex < _waters.size()){
            _waters[waterInBarIndex]->setVisible(false);
        }
    }
}
