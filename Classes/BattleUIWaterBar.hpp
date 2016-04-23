//
//  BattleUIWaterBar.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/20.
//
//

#ifndef BattleUIWaterBar_hpp
#define BattleUIWaterBar_hpp

#include <stdio.h>
#include "ToolFunction.hpp"

class BattleLayer;

class BattleUIWaterBar: public cocos2d::Node{
public:
    
    static BattleUIWaterBar *createBattleUIWaterBar(BattleLayer *battleLayer);
    
    BattleUIWaterBar(BattleLayer *battleLayer):
    _battleLayer(battleLayer) {}
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
private:
    
    BattleLayer *_battleLayer;
    cocos2d::Sprite *_waterBar;
    cocos2d::Label *_waterNumberLabel;
    std::vector<cocos2d::Sprite *> _waters;
    
};

#endif /* BattleUIWaterBar_hpp */
