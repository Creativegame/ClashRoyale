//
//  Knight.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/23.
//
//

#include "Knight.hpp"
#include "CharacterActor.hpp"

USING_NS_CC;

Knight *Knight::createKnight(const Side &side, BattleLayer *battleLayer){
    Knight *knight = new (std::nothrow) Knight(side, battleLayer);
    if (knight && knight->init()){
        knight->autorelease();
        return knight;
    }
    
    delete knight;
    knight = nullptr;
    return nullptr;
}

bool Knight::init(){
    if (!Character::init()){
        return false;
    }
    
    return true;
}

void Knight::onEnter(){
    Character::onEnter();
    
//    _characterActor->playDieAnimation();
}
