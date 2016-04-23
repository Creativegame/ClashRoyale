//
//  TowerShooterSmall.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/15.
//
//

#ifndef TowerShooterSmall_hpp
#define TowerShooterSmall_hpp

#include <stdio.h>
#include "ToolFunction.hpp"
#include "Character.hpp"

class TowerShooterSmall: public Character{
public:
    
    static TowerShooterSmall *createTowerShooterSmall(const Side &side, BattleLayer *battleLayer);
    
    TowerShooterSmall(const Side &side, BattleLayer *battleLayer):
    Character(CharacterName::TowerShooterSmall, side, battleLayer) {}
    
    TowerShooterSmall(const CharacterName &name, const Side &side, BattleLayer *battleLayer):
    Character(name, side, battleLayer) {}
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    virtual void walk() {}
    virtual void attack();
    virtual void die();
    virtual void checkAttackTarget();
    virtual void findPath() {}
    virtual void attackOnce();
    
private:
    
    bool _isCanShoot();
    
};

#endif /* TowerShooterSmall_hpp */
