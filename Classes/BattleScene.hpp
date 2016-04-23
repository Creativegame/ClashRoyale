//
//  BattleScene.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleLayer;

class BattleScene: public cocos2d::Scene{
public:
    
    static BattleScene *createBattleScene();
    
    virtual bool init();
    
private:
    
    BattleLayer *_battleLayer;
    
};

#endif /* BattleScene_hpp */
