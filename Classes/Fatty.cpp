//
//  Fatty.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/4.
//
//

#include "Fatty.hpp"
#include "CharacterActor.hpp"
#include "Tower.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

Fatty *Fatty::createFatty(const Side &side, BattleLayer *battleLayer){
    Fatty *fatty = new (std::nothrow) Fatty(side, battleLayer);
    if (fatty && fatty->init()){
        fatty->autorelease();
        return fatty;
    }
    CCLOG("%s, Fail!", __func__);
    delete fatty;
    fatty = nullptr;
    return nullptr;
}

bool Fatty::init(){
    if (!Character::init()){
        return false;
    }
    
    _findAttackTargetBehavior = FindAttackTargetBehaviorOnlyFindTower::createFindAttackTargetBehaviorOnlyFindTower(this, _battleLayer);
    this->addChild(_findAttackTargetBehavior);
    
    return true;
}

void Fatty::onEnter(){
    Character::onEnter();
    
    this->scheduleUpdate();
    
}

void Fatty::onExit(){
    Character::onExit();
    this->unscheduleUpdate();
}

void Fatty::update(float dt){
    
//    CCLOG("Fatty, %s, state:%d", __func__, _state);
    
    if (_state == CharacterState::Wait){
        return;
    }
    
    if (_state == CharacterState::Die){
        return;
    }
    
    if (_state == CharacterState::WalkUp){
        _characterActor->playWalkUpAnimation();
    }
    
    if (_state == CharacterState::WalkDown){
        _characterActor->playWalkDownAnimation();
    }
    
    if (_state == CharacterState::AttackUp){
        return;
    }
    
    if (_state == CharacterState::AttackDown){
        return;
    }
    
    if (_state == CharacterState::FindTarget){
        this->checkAttackTarget();
    }
    
}

void Fatty::checkAttackTarget(){
    //    _state = CharacterState::Wait;
    
    for (int column = currentTile.column - _range; column <= currentTile.column + _range; ++column){
        for (int row = currentTile.column - _range; row <= currentTile.row + _range; ++row){
            
            if (column < 0 || row < 0 || column >= _battleLayer->getMapTileSize().width || row >= _battleLayer->getMapTileSize().height){
                continue;
            }
            
            if (column == currentTile.column && row == currentTile.row){
                continue;
            }
            
            BattleElement *battleElement = _battleLayer->battleElements[column][row];
            
            if (battleElement){
                if (battleElement->isTower() && battleElement->isCanAttack()){
                    if (battleElement->getSide() != _side){
                        attackTarget = dynamic_cast<Tower *>(battleElement);
                        this->attackOnce();
                        return;
                    }
                }
            }
            
        }
    }
    
    walk();
}

