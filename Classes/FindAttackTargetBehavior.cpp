//
//  FindAttackTargetBehavior.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/7.
//
//

#include "FindAttackTargetBehavior.hpp"
#include "ToolFunction.hpp"
#include "Character.hpp"
#include "Tower.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

#pragma mark - FindAttackTargetBehavior

FindAttackTargetBehavior::~FindAttackTargetBehavior(){
    
}

#pragma mark - FindAttackTargetBehaviorEmpty

FindAttackTargetBehaviorEmpty *FindAttackTargetBehaviorEmpty::createFindAttackTargetBehaviorEmpty(Character *character, BattleLayer *battleLayer){
    FindAttackTargetBehaviorEmpty *findAttackTargetBehaviorEmpty = new (std::nothrow) FindAttackTargetBehaviorEmpty(character, battleLayer);
    if (findAttackTargetBehaviorEmpty && findAttackTargetBehaviorEmpty->init()){
        findAttackTargetBehaviorEmpty->autorelease();
        return findAttackTargetBehaviorEmpty;
    }
    delete findAttackTargetBehaviorEmpty;
    findAttackTargetBehaviorEmpty = nullptr;
    return nullptr;
}

#pragma mark - FindAttackTargetBehaviorOnlyFindTower

FindAttackTargetBehaviorOnlyFindTower *FindAttackTargetBehaviorOnlyFindTower::createFindAttackTargetBehaviorOnlyFindTower(Character *character, BattleLayer *battleLayer){
    FindAttackTargetBehaviorOnlyFindTower *findAttackTargetBehaviorOnlyFindTower = new (std::nothrow) FindAttackTargetBehaviorOnlyFindTower(character, battleLayer);
    if (findAttackTargetBehaviorOnlyFindTower && findAttackTargetBehaviorOnlyFindTower->init()){
        findAttackTargetBehaviorOnlyFindTower->autorelease();
        return findAttackTargetBehaviorOnlyFindTower;
    }
    
    delete findAttackTargetBehaviorOnlyFindTower;
    findAttackTargetBehaviorOnlyFindTower = nullptr;
    return nullptr;
}

bool FindAttackTargetBehaviorOnlyFindTower::init(){
    if (!FindAttackTargetBehavior::init()){
        return false;
    }
    
    return true;
}

void FindAttackTargetBehaviorOnlyFindTower::findAttackTarget(){
    
    _character->attackTarget = nullptr;
    
    if (_character->getPosition().x < _battleLayer->getMapSize().width / 2){
//        CCLOG("I'll Find Left Tower");
        if (_character->getSide() == Side::NPC){
            if (_battleLayer->playerDefendLeftTower->isCanAttack()){
                _character->attackTarget = _battleLayer->playerDefendLeftTower;
            }else {
                _character->attackTarget = _battleLayer->playerKingTower;
            }
        }else {
            if (_battleLayer->npcDefendLeftTower->isCanAttack()){
                _character->attackTarget = _battleLayer->npcDefendLeftTower;
            }else {
                _character->attackTarget = _battleLayer->npcKingTower;
            }
        }
    }else {
//        CCLOG("I'll Find Right Tower");
        if (_character->getSide() == Side::NPC){
            if (_battleLayer->playerDefendRightTower->isCanAttack()){
                _character->attackTarget = _battleLayer->playerDefendRightTower;
            }else {
                _character->attackTarget = _battleLayer->playerKingTower;
            }
        }else {
            if (_battleLayer->npcDefendRightTower->isCanAttack()){
                _character->attackTarget = _battleLayer->npcDefendRightTower;
            }else {
                _character->attackTarget = _battleLayer->npcKingTower;
            }
        }
    }
}

#pragma mark - FindAttackTargetBehaviorFlyCharacterPriority

#pragma mark - FindAttackTargetBehaviorGroundCharacterPriority
