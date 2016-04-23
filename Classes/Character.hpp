//
//  Character.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"
#include "BattleElement.hpp"
#include "FindAttackTargetBehavior.hpp"

class BattleLayer;
class CharacterActor;
class HealthBar;
class Tower;

class Character: public BattleElement{
public:
    
    static Character *createCharacter(CharacterName name, Side side, BattleLayer *battleLayer);
    
    Character(const CharacterName &name, const Side &side, BattleLayer *battleLayer):
    BattleElement(battleLayer), _name(name), _side(side) {}
    virtual ~Character() = 0;
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void loseBlood(int loseValue);
    virtual AStarDataNode getStandTile(BattleElement *battleElement);
    virtual bool isCharacter() {return true;}
    virtual CharacterName getCharacterName() { return _name; }
    virtual Side getSide() {return _side;}
    virtual void setState(const CharacterState &state) {_state = state;}
    virtual bool isCanAttack();
    virtual void logMe() { CCLOG("Character::%s, Name:%d, Side:%d, State:%d", __func__, _name, _side, _state); }
    
    
    CharacterState getCharacterState() { return _state; }
    
    virtual void walk();
    virtual void attack();
    virtual void die();
    virtual void checkAttackTarget();
    virtual void attackOnce();
    virtual void findPath();
    
    void findAttackTarget() {
        _findAttackTargetBehavior->findAttackTarget();
        findPath();
    }
    
    AStarDataNode standTile;
    AStarDataNode currentTile;
    AStarDataNode nextTile;
    std::vector<AStarNode *> path;
    int pathIndex = 0;
    
protected:

    CharacterName _name;
    Side _side;
    CharacterState _state;
    
    int _speed = 0;
    int _range = 0;
    int _waterCost = 0;
    void _initProperty();
    
    int _fullHealthValue = 100;
    int _currentHealthValue = 0;
    HealthBar *_healthBar;
    void _initHealthBar();
    
    CharacterActor *_characterActor;
    void _initCharacterActor();
    
    FindAttackTargetBehavior *_findAttackTargetBehavior;
    
    
private:

};

#endif /* Character_hpp */
