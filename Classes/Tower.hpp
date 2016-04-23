//
//  Tower.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/4.
//
//

#ifndef Tower_hpp
#define Tower_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"
#include "BattleElement.hpp"

class BattleLayer;
class HealthBar;

class Tower: public BattleElement{
public:
    
    static Tower *createTower(const TowerType &type, const Side &side, BattleLayer *battleLayer);
    
    Tower(const TowerType &type, const Side &side, BattleLayer *battleLayer):
    BattleElement(battleLayer), _type(type), _side(side) {}
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void holdTile();
    void releaseTile();
    
    virtual AStarDataNode getStandTile(BattleElement *battleElement);
    virtual bool isTower() {return true;}
    virtual TowerType getTowerType() { return _type; }
    virtual Side getSide() {return _side;}
    virtual void setState(const TowerState &state) {_state = state;}
    virtual void logMe() { CCLOG("Tower::%s Type:%d, Side:%d, State:%d", __func__, _type, _side, _state); }
    
    virtual bool isCanAttack();
    virtual void loseBlood(int loseValue);
    void die();
    
    TowerState getTowerState() { return _state; }
    Side getTowerSide() { return _side; }
    BattleElement *getShooter() {return _shooter;}
    cocos2d::Vec2 getCenterPoint() {return _centerPoint;}
    
    AStarDataNode standTile;
    
private:
    
    TowerType _type;
    Side _side;
    TowerState _state;
    
    BattleElement *_shooter;
    void _initShooter();
    
    int _fullHealthValue = 100;
    int _currentHealthValue = 0;
    
    HealthBar *_healthBar;
    cocos2d::Sprite *_towerAvatar;
    cocos2d::Sprite *_towerRuinAvatar;
    
    void _initHealthBar();
    void _initTowerAvatar();
    
    cocos2d::Vec2 _centerPoint;
    AStarDataNode _leftBottomTile;
    void _changeTile(bool isWalkable);
};

#endif /* Tower_hpp */
