//
//  Knight.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/23.
//
//

#ifndef Knight_hpp
#define Knight_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"
#include "Character.hpp"

class Knight: public Character{
public:
    
    static Knight *createKnight(const Side &side, BattleLayer *battleLayer);
    
    Knight(const Side &side, BattleLayer *battleLayer):
    Character(CharacterName::Knight, side, battleLayer) {}
    
    virtual bool init();
    virtual void onEnter();
    
private:
    
};

#endif /* Knight_hpp */
