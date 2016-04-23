//
//  FindAttackTargetBehavior.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/7.
//
//

#ifndef FindAttackTargetBehavior_hpp
#define FindAttackTargetBehavior_hpp

#include <stdio.h>
#include "ToolFunction.hpp"

class Character;
class BattleLayer;

class FindAttackTargetBehavior: public cocos2d::Node{
public:
    
    FindAttackTargetBehavior(Character *character, BattleLayer *battleLayer):
    _character(character), _battleLayer(battleLayer) {}
    virtual ~FindAttackTargetBehavior() = 0;
    
    virtual void findAttackTarget() = 0;
    
protected:
    Character *_character;
    BattleLayer *_battleLayer;
};


class FindAttackTargetBehaviorEmpty: public FindAttackTargetBehavior{
public:
    
    static FindAttackTargetBehaviorEmpty *createFindAttackTargetBehaviorEmpty(Character *character, BattleLayer *battleLayer);
    
    FindAttackTargetBehaviorEmpty(Character *character, BattleLayer *battleLayer):
    FindAttackTargetBehavior(character, battleLayer) {}
    
    virtual void findAttackTarget() {}
    
private:
};



class FindAttackTargetBehaviorOnlyFindTower: public FindAttackTargetBehavior{
public:
    
    static FindAttackTargetBehaviorOnlyFindTower *createFindAttackTargetBehaviorOnlyFindTower(Character *character, BattleLayer *battleLayer);
    
    FindAttackTargetBehaviorOnlyFindTower(Character *character, BattleLayer *battleLayer):
    FindAttackTargetBehavior(character, battleLayer) {}
    
    virtual bool init();
    
    virtual void findAttackTarget();
    
private:
    
};



class FindAttackTargetBehaviorFlyCharacterPriority: public FindAttackTargetBehavior{
public:
    
private:
    
};



class FindAttackTargetBehaviorGroundCharacterPriority: public FindAttackTargetBehavior{
public:
    
private:
};

#endif /* FindAttackTargetBehavior_hpp */
