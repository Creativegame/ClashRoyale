//
//  TowerShooterSmall.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/15.
//
//

#include "TowerShooterSmall.hpp"
#include "CharacterActor.hpp"
#include "HealthBar.hpp"
#include "Tower.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

TowerShooterSmall *TowerShooterSmall::createTowerShooterSmall(const Side &side, BattleLayer *battleLayer){
    TowerShooterSmall *towerShooterSmall = new (std::nothrow) TowerShooterSmall(side, battleLayer);
    if (towerShooterSmall && towerShooterSmall->init()){
        towerShooterSmall->autorelease();
        return towerShooterSmall;
    }
    
    delete towerShooterSmall;
    towerShooterSmall = nullptr;
    return nullptr;
}

bool TowerShooterSmall::init(){
    if (!Character::init()){
        return false;
    }
    
    _characterActor->setActorRestoreOriginalFrame(true);
    
    _findAttackTargetBehavior = FindAttackTargetBehaviorEmpty::createFindAttackTargetBehaviorEmpty(this, _battleLayer);
    this->addChild(_findAttackTargetBehavior);
    
    return true;
}

void TowerShooterSmall::onEnter(){
    Character::onEnter();
    
    _healthBar->setVisible(false);
    _state = CharacterState::FindTarget;
    
    this->scheduleUpdate();
}

void TowerShooterSmall::onExit(){
    Character::onExit();
    
    this->unscheduleUpdate();
}

void TowerShooterSmall::update(float dt){
    
    if (_state == CharacterState::Die){
        return;
    }
    
    if (_state == CharacterState::Wait || _state == CharacterState::WalkUp || _state == CharacterState::WalkDown){
        _state = CharacterState::Wait;
        return;
    }
    
    if (_state == CharacterState::FindTarget){
        this->checkAttackTarget();
    }
    
    if (_state == CharacterState::AttackUp){
        return;
    }
    
    if (_state == CharacterState::AttackDown){
        return;
    }
}

void TowerShooterSmall::checkAttackTarget(){
    if (_state == CharacterState::Die){
        return;
    }
    _state = CharacterState::Wait;
    
    if (attackTarget && !attackTarget->isCanAttack()){
        attackTarget = nullptr;
    }
    
    if (attackTarget && attackTarget->isCanAttack() && _isCanShoot()){
        this->attackOnce();
        return;
    }
    
    std::vector<Character *> &enemys = (_side == Side::Player) ? _battleLayer->npcCharacters : _battleLayer->playerCharacters;
    
    for (int enemyIndex = 0; enemyIndex < enemys.size(); ++enemyIndex){
        Character *enemy = enemys[enemyIndex];
        if (enemy && enemy->isCanAttack()){
            attackTarget = enemy;
            if (_isCanShoot()){
                this->attackOnce();
                return;
            }
        }
    }
    
    _state = CharacterState::FindTarget;
    attackTarget = nullptr;
}

void TowerShooterSmall::attackOnce(){
    if (_state == CharacterState::Die){
        return;
    }
    _state = CharacterState::Wait;
    if (attackTarget->getStandTile(this).row == static_cast<Tower *>(this->getParent())->getStandTile(this).row){
        if (_side == Side::Player){
            _state = CharacterState::AttackUp;
            _characterActor->playAttackUpAnimation();
        }else {
            _state = CharacterState::AttackDown;
            _characterActor->playAttackDownAnimation();
        }
    }else if (attackTarget->getStandTile(this).row > static_cast<Tower *>(this->getParent())->getStandTile(this).row){
        _state = CharacterState::AttackUp;
        _characterActor->playAttackUpAnimation();
    }else {
        _state = CharacterState::AttackDown;
        _characterActor->playAttackDownAnimation();
    }
    
    float delay = GameData::getInstance()->getCharacterAnimationDelayPerUnit(_name) * GameData::getInstance()->getCharacterAttackLogicAtFrameNumber(_name, _state);
    
    this->scheduleOnce([&](float dt){
        this->attack();
    }, delay, "AttackLogic");
    
    float finishDelay = GameData::getInstance()->getCharacterAnimationDelayPerUnit(_name) * (GameData::getInstance()->getCharacterAnimationFrameNumber(_name, _state) + 1);
    float attackDelay = GameData::getInstance()->getCharacterAttackDelay(_name);
    
    this->scheduleOnce([&](float dt){
        if (_state != CharacterState::Die){
            _state = CharacterState::FindTarget;
        }
    }, finishDelay + attackDelay, "Attack");
    
}

void TowerShooterSmall::attack(){
//    if (!attackTarget->isCanAttack() || !_isCanShoot()){
//        _state = CharacterState::FindTarget;
//        return;
//    }
//    _battleLayer->addArrowToBattleMap(this, attackTarget, [](){});
    if (_state == CharacterState::Die){
        return;
    }
    Vec2 fromPosition = Vec2(static_cast<Tower *>(this->getParent())->getPosition().x, static_cast<Tower *>(this->getParent())->getPosition().y + 90);
    
    _battleLayer->addArrowToBattleMap(fromPosition, attackTarget->getPosition(), [&](){
        CCLOG("Shoule LoseBlood");
        if (attackTarget){
            attackTarget->loseBlood(GameData::getInstance()->getCharacterAttack(_name, attackTarget->getCharacterName()));
        }
    });
}

void TowerShooterSmall::die(){
    _state = CharacterState::Die;
}

bool TowerShooterSmall::_isCanShoot(){
    if (attackTarget == nullptr || !attackTarget->isCanAttack()){
        return false;
    }
    
    float attackRange = _range * _battleLayer->getTileSize().width;
    float distanceWithTarget = getDistanceWithTowVec2(static_cast<Tower *>(this->getParent())->getCenterPoint(), attackTarget->getPosition());
    
    if (distanceWithTarget <= attackRange){
        return true;
    }
    
    return false;
}

