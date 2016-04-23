//
//  HealthBar.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/26.
//
//

#ifndef HealthBar_hpp
#define HealthBar_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"

class HealthBar: public cocos2d::Node{
public:
    
    static HealthBar *createHealthBar(const HealthBarType &type);
    static HealthBar *createHealthBar(const HealthBarType &type, const int *fullValuePointer, const int *currentValuePointer);
    
    HealthBar(const HealthBarType &type):
    _type(type) {}
    HealthBar(const HealthBarType &type, const int *fullValuePointer, const int *currentValuePointer):
    _type(type), _fullValuePointer(fullValuePointer), _currentValuePointer(currentValuePointer) {}
    
    virtual bool init();
    
    cocos2d::Size getHealthBarSize();
    void refresh();
    
private:
    
    HealthBarType _type;
    
    cocos2d::Sprite *_barBackground;
    cocos2d::Sprite *_bar;
    cocos2d::Label *_valueLabel;
    void _initHealthBar();
    
    const int *_fullValuePointer;
    const int *_currentValuePointer;
    
};

#endif /* HealthBar_hpp */
