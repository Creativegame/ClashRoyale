//
//  BattleElement.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/12.
//
//

#include "BattleElement.hpp"
#include "BattleLayer.hpp"

BattleElement::~BattleElement(){
    
}

bool BattleElement::init(){
    if (!Node::init()){
        return false;
    }
    
    return true;
}

void BattleElement::onEnter(){
    Node::onEnter();
}

void BattleElement::onExit(){
    Node::onExit();
}

void BattleElement::resetSelfZOrder(){
    this->setLocalZOrder(_battleLayer->getBattleElementZOrderOnBattleMap(this));
}

void BattleElement::resetSelfZOrder(int zorder){
    this->setLocalZOrder(zorder);
}