//
//  Arrow.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/15.
//
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include <stdio.h>
#include "ToolFunction.hpp"

class BattleLayer;
class BattleElement;

class Arrow: public cocos2d::Sprite{
public:
    
    static Arrow *createArrow(BattleElement *from, BattleElement *to, BattleLayer *battleLayer);
    static Arrow *createArrow(const cocos2d::Vec2 &fromPoint, const cocos2d::Vec2 &toPoint, BattleLayer *battleLayer);
    
    Arrow(BattleElement *from, BattleElement *to, BattleLayer *battleLayer):
    _from(from), _to(to), _battleLayer(battleLayer) {}
    Arrow(const cocos2d::Vec2 &fromPoint, const cocos2d::Vec2 &toPoint, BattleLayer *battleLayer):
    _fromPoint(fromPoint), _toPoint(toPoint), _battleLayer(battleLayer) {}
    
    virtual bool init();
    
private:
    
    BattleLayer *_battleLayer;
    cocos2d::Vec2 _fromPoint;
    cocos2d::Vec2 _toPoint;
    BattleElement *_from;
    BattleElement *_to;
};

#endif /* Arrow_hpp */
