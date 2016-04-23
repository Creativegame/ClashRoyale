//
//  BattleUILayer.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/29.
//
//

#include "BattleUILayer.hpp"
#include "BattleLayer.hpp"
#include "BattleUICardBoard.hpp"

USING_NS_CC;

BattleUILayer *BattleUILayer::createBattleUILayer(BattleLayer *battleLayer){
    BattleUILayer *battleUILayer = new (std::nothrow) BattleUILayer(battleLayer);
    if (battleUILayer && battleUILayer->init()){
        battleUILayer->autorelease();
        return battleUILayer;
    }
    delete battleUILayer;
    battleUILayer = nullptr;
    return nullptr;
}

bool BattleUILayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _cardBoard = BattleUICardBoard::createBattleUICardBoard(_battleLayer->getCharacterNameList(), _battleLayer);
    _cardBoard->setPosition(visibleSize.width - 526, 0);
    this->addChild(_cardBoard, 1);
    
    return true;
}
