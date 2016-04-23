//
//  GameData.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/22.
//
//

#include "GameData.hpp"

GameData *GameData::_gameData = nullptr;
const float GameData::defaultDelayPerUnit = 0.05;

const std::map<CharacterName, std::string> GameData::characterNameData = {
    {CharacterName::Knight, "knight"}, {CharacterName::Fatty, "fatty"}, {CharacterName::Ghost, "ghost"}, {CharacterName::Goblin, "goblin"}, {CharacterName::Gunner, "gunner"},
    {CharacterName::TowerShooterSmall, "towerShooterSmall"}, {CharacterName::TowerShooterBig, "towerShooterBig"}
};

const std::map<CharacterName, int> GameData::characterWalkUpAnimationFrameNumberData = {
    {CharacterName::Knight, 12}, {CharacterName::Fatty, 12}, {CharacterName::TowerShooterSmall, 0}, {CharacterName::TowerShooterBig, 0}
};

const std::map<CharacterName, int> GameData::characterWalkDownAnimationFrameNumberData = {
    {CharacterName::Knight, 12}, {CharacterName::Fatty, 12}, {CharacterName::TowerShooterSmall, 0}, {CharacterName::TowerShooterBig, 0}
};

const std::map<CharacterName, int> GameData::characterAttackUpAnimtionFrameNumberData = {
    {CharacterName::Knight, 0}, {CharacterName::Fatty, 7}, {CharacterName::TowerShooterSmall, 9}, {CharacterName::TowerShooterBig, 8}
};

const std::map<CharacterName, int> GameData::characterAttackDownAnimationFrameNumberData = {
    {CharacterName::Knight, 0}, {CharacterName::Fatty, 9}, {CharacterName::TowerShooterSmall, 9}, {CharacterName::TowerShooterBig, 8}
};

const std::map<CharacterName, int> GameData::characterDieAnimationFrameNumberData = {
    {CharacterName::Knight, 10}, {CharacterName::Fatty, 10}, {CharacterName::TowerShooterSmall, 0}, {CharacterName::TowerShooterBig, 0}
};

const std::map<CharacterName, float> GameData::characterAnimationDelayPerUnitData = {
    {CharacterName::Knight, 0.05}, {CharacterName::Fatty, 0.09}, {CharacterName::TowerShooterSmall, 0.06}, {CharacterName::TowerShooterBig, 0.06}
};

const std::map<CharacterName, cocos2d::Vec2> GameData::characterActorOffsetData = {
    {CharacterName::Knight, cocos2d::Vec2(0, 0)}, {CharacterName::Fatty, cocos2d::Vec2(15, -41)}, {CharacterName::TowerShooterSmall, cocos2d::Vec2(0, 0)}, {CharacterName::TowerShooterBig, cocos2d::Vec2(0, 0)}
};

const std::map<CharacterName, int> GameData::characterAttackUpLogicAtFrameNumberData = {
    {CharacterName::Knight, 0}, {CharacterName::Fatty, 5}, {CharacterName::TowerShooterSmall, 8}, {CharacterName::TowerShooterBig, 7}
};

const std::map<CharacterName, int> GameData::characterAttackDownLogicAtFrameNumberData = {
    {CharacterName::Knight, 0}, {CharacterName::Fatty, 4}, {CharacterName::TowerShooterSmall, 8}, {CharacterName::TowerShooterBig, 7}
};

const std::map<CharacterName, int> GameData::characterAttackDelay = {
    {CharacterName::Knight, 0}, {CharacterName::Fatty, 0}, {CharacterName::TowerShooterSmall, 1}, {CharacterName::TowerShooterBig, 1}
};

const std::map<CharacterName, int> GameData::characterSpeedData = {
    {CharacterName::Knight, 1}, {CharacterName::Fatty, 30}, {CharacterName::TowerShooterSmall, 0}, {CharacterName::TowerShooterBig, 0}
};

const std::map<CharacterName, int> GameData::characterRangeData = {
    {CharacterName::Knight, 1}, {CharacterName::Fatty, 1}, {CharacterName::TowerShooterSmall, 8}, {CharacterName::TowerShooterBig, 8}
};

const std::map<CharacterName, int> GameData::characterHpData = {
    {CharacterName::Knight, 100}, {CharacterName::Fatty, 100}, {CharacterName::TowerShooterSmall, 100}, {CharacterName::TowerShooterBig, 100}
};

const std::map<CharacterName, int> GameData::characterWaterCostData = {
    {CharacterName::Knight, 3}, {CharacterName::Fatty, 5}, {CharacterName::Ghost, 3}, {CharacterName::Goblin, 2}, {CharacterName::Gunner, 4}, {CharacterName::TowerShooterSmall, 0}, {CharacterName::TowerShooterBig, 0}
};

const std::map<CharacterName, std::map<CharacterName, int>> GameData::characterAttackData = {
    {CharacterName::Knight,
        {{CharacterName::Fatty, 10}, {CharacterName::Ghost, 0}, {CharacterName::Goblin, 10}, {CharacterName::Gunner, 10}, {CharacterName::Knight, 10}}
    },
    
    {CharacterName::Fatty,
        {{CharacterName::Fatty, 0}, {CharacterName::Ghost, 0}, {CharacterName::Goblin, 0}, {CharacterName::Gunner, 0}, {CharacterName::Knight, 0}}
    },
    
    {CharacterName::TowerShooterSmall,
        {{CharacterName::Fatty, 10}, {CharacterName::Ghost, 10}, {CharacterName::Goblin, 10}, {CharacterName::Gunner, 10}, {CharacterName::Knight, 10}}
    },
    
    {CharacterName::TowerShooterBig,
        {{CharacterName::Fatty, 10}, {CharacterName::Ghost, 10}, {CharacterName::Goblin, 10}, {CharacterName::Gunner, 10}, {CharacterName::Knight, 10}}
    }
};

const std::map<CharacterName, std::map<TowerType, int>> GameData::characterAttackTowerData = {
    {CharacterName::Fatty,
        {{TowerType::King, 5}, {TowerType::Defend, 10}}
    },
    
    {CharacterName::TowerShooterSmall,
        {{TowerType::King, 0}, {TowerType::Defend, 0}}
    },
    
    {CharacterName::TowerShooterSmall,
        {{TowerType::King, 0}, {TowerType::Defend, 0}}
    }
};

const std::map<BattleWeapon, int> GameData::battleWeaponSpeed = {
    {BattleWeapon::Arrow, 1000}
};

const std::map<TowerType, int> GameData::towerHpData = {
    {TowerType::King, 100}, {TowerType::Defend, 100}
};

const float GameData::addOneWaterTime = 2;

const int GameData::maxWater = 10;

GameData *GameData::getInstance(){
    if (_gameData == nullptr){
        _gameData = new (std::nothrow) GameData();
        if (_gameData){
            return _gameData;
        }else {
            CCLOG("GameData Constructor Fail!");
            delete _gameData;
            _gameData = nullptr;
            return nullptr;
        }
    }
    return _gameData;
}

int GameData::getCharacterAnimationFrameNumber(const CharacterName &name, const std::string &animation){
    if (animation == "walkUp"){
        if (characterWalkUpAnimationFrameNumberData.find(name) != characterWalkUpAnimationFrameNumberData.end()){
            return characterWalkUpAnimationFrameNumberData.at(name);
        }
        CCLOG("%s, WalkUp Error %d", __func__, name);
        return 0;
    }else if (animation == "walkDown"){
        if (characterWalkDownAnimationFrameNumberData.find(name) != characterWalkDownAnimationFrameNumberData.end()){
            return characterWalkDownAnimationFrameNumberData.at(name);
        }
        CCLOG("%s, WalkDown Error %d", __func__, name);
        return 0;
    }else if (animation == "attackUp"){
        if (characterAttackUpAnimtionFrameNumberData.find(name) != characterAttackUpAnimtionFrameNumberData.end()){
            return characterAttackUpAnimtionFrameNumberData.at(name);
        }
        CCLOG("%s, AttackUp Error %d", __func__, name);
        return 0;
    }else if (animation == "attackDown"){
        if (characterAttackDownAnimationFrameNumberData.find(name) != characterAttackDownAnimationFrameNumberData.end()){
            return characterAttackDownAnimationFrameNumberData.at(name);
        }
        CCLOG("%s, AttackDown Error %d", __func__, name);
        return 0;
    }else if (animation == "die"){
        if (characterDieAnimationFrameNumberData.find(name) != characterDieAnimationFrameNumberData.end()){
            return characterDieAnimationFrameNumberData.at(name);
        }
        CCLOG("%s, Die Error %d", __func__, name);
        return 0;
    }
    
    CCLOG("%s, Error %d %s", __func__, name, animation.c_str());
    return 0;
}

int GameData::getCharacterAnimationFrameNumber(const CharacterName &name, const CharacterState &state){
    if (state == CharacterState::WalkUp){
        return getCharacterAnimationFrameNumber(name, "walkUp");
    }else if (state == CharacterState::WalkDown){
        return getCharacterAnimationFrameNumber(name, "walkDown");
    }else if (state == CharacterState::AttackUp){
        return getCharacterAnimationFrameNumber(name, "attackUp");
    }else if (state == CharacterState::AttackDown){
        return getCharacterAnimationFrameNumber(name, "attackDown");
    }else if (state == CharacterState::Die){
        return getCharacterAnimationFrameNumber(name, "die");
    }else {
        CCLOG("%s, Error!", __func__);
        return 0;
    }
}

float GameData::getCharacterAnimationDelayPerUnit(const CharacterName &name){
    if (characterAnimationDelayPerUnitData.find(name) != characterAnimationDelayPerUnitData.end()){
        return characterAnimationDelayPerUnitData.at(name);
    }else {
        CCLOG("%s, Error!", __func__);
        return defaultDelayPerUnit;
    }
}

cocos2d::Vec2 GameData::getCharacterActorOffset(const CharacterName &name){
    if (characterActorOffsetData.find(name) != characterActorOffsetData.end()){
        return characterActorOffsetData.at(name);
    }else {
        CCLOG("%s, Error!", __func__);
        return cocos2d::Vec2(0, 0);
    }
}

int GameData::getCharacterAttackDelay(const CharacterName &name){
    if (characterAttackDelay.find(name) != characterAttackDelay.end()){
        return characterAttackDelay.at(name);
    }
    CCLOG("%s, Error!", __func__);
    return 0;
}

int GameData::getCharacterAttackLogicAtFrameNumber(const CharacterName &name, const CharacterState &state){
    if (state == CharacterState::AttackDown){
        if (characterAttackDownLogicAtFrameNumberData.find(name) != characterAttackDownLogicAtFrameNumberData.end()){
            return characterAttackDownLogicAtFrameNumberData.at(name);
        }else {
            CCLOG("%s, Name Error!", __func__);
            return 0;
        }
    }else if (state == CharacterState::AttackUp){
        if (characterAttackUpLogicAtFrameNumberData.find(name) != characterAttackUpLogicAtFrameNumberData.end()){
            return characterAttackUpLogicAtFrameNumberData.at(name);
        }else {
            CCLOG("%s, Name Error!", __func__);
            return 0;
        }
    }else {
        CCLOG("%s, State Error", __func__);
    }
    return 0;
}

int GameData::getCharacterSpeed(const CharacterName &name){
    if (characterSpeedData.find(name) != characterSpeedData.end()){
        return characterSpeedData.at(name);
    }
    
    CCLOG("%s, Error", __func__);
    return 0;
}

int GameData::getCharacterRange(const CharacterName &name){
    if (characterRangeData.find(name) != characterRangeData.end()){
        return characterRangeData.at(name);
    }
    CCLOG("%s, Error", __func__);
    return 0;
}

int GameData::getCharacterHp(const CharacterName &name){
    if (characterHpData.find(name) != characterHpData.end()){
        return characterHpData.at(name);
    }
    CCLOG("%s, Error", __func__);
    return 0;
}

int GameData::getCharacterWaterCost(const CharacterName &name){
    if (characterWaterCostData.find(name) != characterWaterCostData.end()){
        return characterWaterCostData.at(name);
    }
    CCLOG("%s, Error", __func__);
    return 0;
}

int GameData::getCharacterAttack(const CharacterName &from, const CharacterName &to){
    if (characterAttackData.find(from) != characterAttackData.end()){
        const std::map<CharacterName, int> &attackData = characterAttackData.at(from);
        if (attackData.find(to) != attackData.end()){
            return attackData.at(to);
        }
        CCLOG("%s, To Error!", __func__);
        return 0;
    }
    CCLOG("%s, From Error!", __func__);
    return 0;
}

int GameData::getCharacterAttack(const CharacterName &from, const TowerType &to){
    if (characterAttackTowerData.find(from) != characterAttackTowerData.end()){
        const std::map<TowerType, int> &attackData = characterAttackTowerData.at(from);
        if (attackData.find(to) != attackData.end()){
            return attackData.at(to);
        }else {
            CCLOG("%s, TowerType Error!", __func__);
            return 0;
        }
    }
    CCLOG("%s, CharacterName Error!", __func__);
    return 0;
}

int GameData::getTowerHp(const TowerType &type){
    if (towerHpData.find(type) != towerHpData.end()){
        return towerHpData.at(type);
    }else {
        CCLOG("%s Error!", __func__);
        return 0;
    }
}

int GameData::getBattleWeaponSpeed(const BattleWeapon &weapon){
    if (battleWeaponSpeed.find(weapon) != battleWeaponSpeed.end()){
        return battleWeaponSpeed.at(weapon);
    }
    CCLOG("%s, Error!", __func__);
    return 1;
}

float GameData::getAddOneWaterTime(){
    return addOneWaterTime;
}

int GameData::getMaxWater(){
    return maxWater;
}



