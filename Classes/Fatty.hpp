//
//  Fatty.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/4.
//
//

#ifndef Fatty_hpp
#define Fatty_hpp

#include <stdio.h>
#include "ToolFunction.hpp"
#include "Character.hpp"

class Fatty: public Character{
public:
    
    static Fatty *createFatty(const Side &side, BattleLayer *battleLayer);
    
    Fatty(const Side &side, BattleLayer *battleLayer):
    Character(CharacterName::Fatty, side, battleLayer) {}
    
    virtual void checkAttackTarget();
//    virtual void attackOnce();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
private:
};

#endif /* Fatty_hpp */
