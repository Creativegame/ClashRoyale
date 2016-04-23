//
//  BattleElement.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/12.
//
//

#ifndef BattleElement_hpp
#define BattleElement_hpp

#include <stdio.h>
#include "ToolFunction.hpp"

class BattleLayer;

class BattleElement: public cocos2d::Node{
public:
    
    BattleElement(BattleLayer *battleLayer):
    _battleLayer(battleLayer) {}
    ~BattleElement() = 0;
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void loseBlood(int loseValue) = 0;
    virtual Side getSide() = 0;
    virtual void logMe() = 0;
    
    virtual AStarDataNode getStandTile(BattleElement *battleElement) = 0;
    
    virtual bool isCanAttack() {return false;}
    virtual bool isTower() {return false;}
    virtual bool isCharacter() {return false;}
    virtual CharacterName getCharacterName() {return CharacterName::NoName;}
    virtual TowerType getTowerType() {return TowerType::NoType;}
    virtual void resetSelfZOrder();
    virtual void resetSelfZOrder(int zorder);
    virtual void setState(const CharacterState &state) {}
    virtual void setState(const TowerState &state) {}
    
    void setID(int id) {_id = id;}
    int getID() {return _id;}
    int getAttackTargetID(){
        if (attackTarget){
            return attackTarget->getID();
        }
        return -1;
    }
    
    BattleElement *attackTarget = nullptr;
    
protected:
    
    BattleLayer *_battleLayer;
    int _id = -1;
    
private:
    
};

#endif /* BattleElement_hpp */
