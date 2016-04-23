//
//  BattleUILayer.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/29.
//
//

#ifndef BattleUILayer_hpp
#define BattleUILayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"

class BattleLayer;
class BattleUICardBoard;

class BattleUILayer: public cocos2d::Layer{
public:
    
    static BattleUILayer *createBattleUILayer(BattleLayer *battleLayer);
    
    BattleUILayer(BattleLayer *battleLayer):
    _battleLayer(battleLayer) {}
    
    virtual bool init();
    
private:
    
    BattleLayer *_battleLayer;
    
    BattleUICardBoard *_cardBoard;
    
};

#endif /* BattleUILayer_hpp */
