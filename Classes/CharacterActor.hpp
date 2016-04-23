//
//  CharacterActor.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#ifndef CharacterActor_hpp
#define CharacterActor_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"

class CharacterActor: public cocos2d::Sprite{
public:
    
    static CharacterActor *createCharacter(const CharacterName &name, const Side &side);
    CharacterActor(const CharacterName &name, const Side &side):
    _name(name), _side(side) {}
    
    virtual bool init();
    
    void playWalkUpAnimation();
    void playWalkDownAnimation();
    void playAttackUpAnimation();
    void playAttackDownAnimation();
    void playDieAnimation();
    
    void setActorRestoreOriginalFrame(bool isRestroe) {_isRestore = isRestroe;}
    
private:
    
    CharacterName _name;
    Side _side;
    FaceTo _faceTo;
    
    bool _isPlaying = false;
    bool _isRestore = false;
    
    std::string _getCharacterNormalSpriteFrame();
    void _prepareAnimation();
    
    void _playAnimation(const CharacterAnimationType &type);
    cocos2d::Animate *_createAnimate(const CharacterAnimationType &type);
    
    void _turnAround(const FaceTo &faceTo);
    
    cocos2d::Vector<cocos2d::SpriteFrame *> _walkUpAnimationFrameArray;
    cocos2d::Vector<cocos2d::SpriteFrame *> _walkDownAnimationFrameArray;
    cocos2d::Vector<cocos2d::SpriteFrame *> _attackUpAnimationFrameArray;
    cocos2d::Vector<cocos2d::SpriteFrame *> _attackDownAnimationFrameArray;
    cocos2d::Vector<cocos2d::SpriteFrame *> _dieAnimationFrameArray;
    
};

#endif /* CharacterActor_hpp */
