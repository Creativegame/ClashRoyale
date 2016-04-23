//
//  Character.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#include "Character.hpp"
#include "CharacterActor.hpp"
#include "HealthBar.hpp"
#include "BattleLayer.hpp"
#include "Tower.hpp"

USING_NS_CC;

Character::~Character(){
    
}

bool Character::init(){
    if (!BattleElement::init()){
        return false;
    }
    
    _initCharacterActor();
    _initProperty();
    _initHealthBar();
    
    if (_side == Side::Player){
        _state = CharacterState::WalkUp;
    }else {
        _state = CharacterState::WalkDown;
    }
    
    return true;
}

void Character::onEnter(){
    BattleElement::onEnter();
    currentTile = AStarDataNode(static_cast<int>(this->getPosition().x / _battleLayer->getTileSize().width), static_cast<int>(this->getPosition().y / _battleLayer->getTileSize().height), true);
    findAttackTarget();
    walk();
}

void Character::onExit(){
    BattleElement::onExit();
//    _battleLayer = nullptr;
}

void Character::loseBlood(int loseValue){
    if (loseValue >= _currentHealthValue){
        _currentHealthValue = 0;
        _healthBar->refresh();
    }else{
        _currentHealthValue -= loseValue;
        _healthBar->refresh();
    }
    if (_currentHealthValue <= 0){
        _state = CharacterState::Die;
        this->die();
    }
}

AStarDataNode Character::getStandTile(BattleElement *battleElement){
    return currentTile;
}

bool Character::isCanAttack(){
    if (_state == CharacterState::Die){
        return false;
    }
    
    return true;
}

void Character::die(){
    _healthBar->setVisible(false);
    _state = CharacterState::Die;
    _characterActor->playDieAnimation();
    
    this->stopAllActions();
    float delay = GameData::getInstance()->getCharacterAnimationFrameNumber(_name, CharacterState::Die) * GameData::getInstance()->getCharacterAnimationDelayPerUnit(_name);
    
    this->scheduleOnce([&](float dt){
        CCLOG("Remove Me!");
        _battleLayer->removeCharacterFromBattleMap(this);
    }, delay, "die");
}

void Character::walk(){
    if (path.size() == 0){
        CCLOG("%s, No Way!", __func__);
        return;
    }
    
    if (++pathIndex >= path.size()){
        CCLOG("%s, Get Target Tile", __func__);
        this->findAttackTarget();
        this->findPath();
    }
    
    nextTile = AStarDataNode(path[pathIndex]->column, path[pathIndex]->row, true);
    
    float duration = 1;
    
    if (nextTile.row == currentTile.column || nextTile.column == currentTile.column){
        duration = _battleLayer->getTileSize().width / _speed;
    }else {
        duration = (_battleLayer->getTileSize().width * 1.4) / _speed;
    }
    
    CCLOG("%s, Duration:%f", __func__, duration);
    
    int lastPathIndex = static_cast<int>(path.size() - 1);
    
    if (currentTile.row > path[lastPathIndex]->row){
        _state = CharacterState::WalkDown;
    }else {
        _state = CharacterState::WalkUp;
    }
    
    this->runAction(Sequence::create(
                                     MoveTo::create(duration, Vec2(nextTile.column * _battleLayer->getTileSize().width, nextTile.row * _battleLayer->getTileSize().height)),
                                     CallFunc::create([&](){
        this->resetSelfZOrder();
        currentTile = nextTile;
        if (_state == CharacterState::Die){
            return;
        }
        _state = CharacterState::FindTarget;
    }),
                                     NULL));
}

void Character::checkAttackTarget(){
    
}

void Character::attackOnce(){
    _state = CharacterState::Wait;
    if (attackTarget->getStandTile(this).row == currentTile.row){
        if (_side == Side::Player){
            _state = CharacterState::AttackUp;
            _characterActor->playAttackUpAnimation();
        }else {
            _state = CharacterState::AttackDown;
            _characterActor->playAttackDownAnimation();
        }
    }else if (attackTarget->getStandTile(this).row > currentTile.row){
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
        if (_state == CharacterState::Die){
            return;
        }
        _state = CharacterState::FindTarget;
    }, finishDelay + attackDelay, "Attack");
    
}

void Character::attack(){
    CCLOG("%s", __func__);
    if (attackTarget->isCanAttack()){
        if (attackTarget->isTower()){
            attackTarget->loseBlood(GameData::getInstance()->getCharacterAttack(_name, attackTarget->getTowerType()));
        }else {
            attackTarget->loseBlood(GameData::getInstance()->getCharacterAttack(_name, attackTarget->getCharacterName()));
        }
    }
}

void Character::findPath(){
    path.clear();
    pathIndex = 0;
    if (attackTarget){
        astar(_battleLayer->astarData, path, currentTile, attackTarget->getStandTile(this));
    }
    
    //TEST
    for (auto iter = path.begin(); iter != path.end(); ++iter){
        //        CCLOG("(%d, %d)", (*iter)->column, (*iter)->row);
        Sprite *pathNode = Sprite::createWithSpriteFrameName("battle_map_path.png");
        pathNode->setAnchorPoint(Vec2(0, 0));
        pathNode->setPosition((*iter)->column * _battleLayer->getTileSize().width, (*iter)->row * _battleLayer->getTileSize().height);
        _battleLayer->addChildToBattleMap(pathNode);
    }
}

void Character::_initCharacterActor(){
    _characterActor = CharacterActor::createCharacter(_name, _side);
    _characterActor->setAnchorPoint(Vec2(0.5, 0));
    _characterActor->setPosition(GameData::getInstance()->getCharacterActorOffset(_name));
    this->addChild(_characterActor, 1);
}

void Character::_initHealthBar(){
    _healthBar = HealthBar::createHealthBar(HealthBarType::Character, &_fullHealthValue, &_currentHealthValue);
    Size healthBarSize = _healthBar->getHealthBarSize();
    Size characterActorSize = _characterActor->getContentSize();
//    CCLOG("%s, Size Bar:(%f, %f), Actor:(%f, %f)", __func__, healthBarSize.width, healthBarSize.height, characterActorSize.width, characterActorSize.height);
    _healthBar->setPosition(-healthBarSize.width / 2, characterActorSize.height + GameData::getInstance()->getCharacterActorOffset(_name).y);
    this->addChild(_healthBar, 5);
}

void Character::_initProperty(){
    _speed = GameData::getInstance()->getCharacterSpeed(_name);
    _range = GameData::getInstance()->getCharacterRange(_name);
    _fullHealthValue = GameData::getInstance()->getCharacterHp(_name);
    _currentHealthValue = _fullHealthValue;
    _waterCost = GameData::getInstance()->getCharacterWaterCost(_name);
    
//    CCLOG("Speed: %d, Range: %d, HP: %d, WaterCost: %d", _speed, _range, _fullHealthValue, _waterCost);
}
