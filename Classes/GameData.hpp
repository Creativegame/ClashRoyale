//
//  GameData.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/22.
//
//

#ifndef GameData_hpp
#define GameData_hpp

#include <stdio.h>
#include "ToolClass.hpp"

class GameData{
public:
    
    static GameData *getInstance();
    static const float defaultDelayPerUnit;
    
    static const std::map<CharacterName, std::string> characterNameData;
    static const std::map<CharacterName, int> characterWalkUpAnimationFrameNumberData;
    static const std::map<CharacterName, int> characterWalkDownAnimationFrameNumberData;
    static const std::map<CharacterName, int> characterAttackUpAnimtionFrameNumberData;
    static const std::map<CharacterName, int> characterAttackDownAnimationFrameNumberData;
    static const std::map<CharacterName, int> characterDieAnimationFrameNumberData;
    static const std::map<CharacterName, int> characterAttackUpLogicAtFrameNumberData;
    static const std::map<CharacterName, int> characterAttackDownLogicAtFrameNumberData;
    static const std::map<CharacterName, float> characterAnimationDelayPerUnitData;
    static const std::map<CharacterName, cocos2d::Vec2> characterActorOffsetData;
    static const std::map<CharacterName, int> characterAttackDelay;
    
    static const std::map<CharacterName, int> characterSpeedData;
    static const std::map<CharacterName, int> characterRangeData;
    static const std::map<CharacterName, int> characterHpData;
    static const std::map<CharacterName, int> characterWaterCostData;
    static const std::map<CharacterName, std::map<CharacterName, int>> characterAttackData;
    static const std::map<CharacterName, std::map<TowerType, int>> characterAttackTowerData;
    static const std::map<BattleWeapon, int> battleWeaponSpeed;
    static const std::map<TowerType, int> towerHpData;
    
    static const int maxWater;
    static const float addOneWaterTime;
    
    int getCharacterAnimationFrameNumber(const CharacterName &name, const std::string &animation);
    int getCharacterAnimationFrameNumber(const CharacterName &name, const CharacterState &state);
    float getCharacterAnimationDelayPerUnit(const CharacterName &name);
    cocos2d::Vec2 getCharacterActorOffset(const CharacterName &name);
    int getCharacterAttackDelay(const CharacterName &name);
    int getCharacterAttackLogicAtFrameNumber(const CharacterName &name, const CharacterState &state);
    int getCharacterSpeed(const CharacterName &name);
    int getCharacterRange(const CharacterName &name);
    int getCharacterHp(const CharacterName &name);
    int getCharacterWaterCost(const CharacterName &name);
    int getCharacterAttack(const CharacterName &from, const CharacterName &to);
    int getCharacterAttack(const CharacterName &from, const TowerType &to);
    int getBattleWeaponSpeed(const BattleWeapon &weapon);
    int getTowerHp(const TowerType &type);
    float getAddOneWaterTime();
    int getMaxWater();
    
    
private:
    
    static GameData *_gameData;
    GameData() = default;
    ~GameData() = default;
    
};

#endif /* GameData_hpp */
