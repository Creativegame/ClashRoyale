//
//  CharacterActor.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#include "CharacterActor.hpp"

USING_NS_CC;

CharacterActor *CharacterActor::createCharacter(const CharacterName &name, const Side &side){
    CharacterActor *characterActor = new (std::nothrow) CharacterActor(name, side);
    if (characterActor && characterActor->init()){
        characterActor->autorelease();
        return characterActor;
    }
    
    delete characterActor;
    characterActor = nullptr;
    return nullptr;
}

bool CharacterActor::init(){
    if (!Sprite::initWithSpriteFrameName(_getCharacterNormalSpriteFrame())){
        return false;
    }
    _faceTo = FaceTo::Right;
    
    _prepareAnimation();
    
    return true;
}

void CharacterActor::playWalkDownAnimation(){
    _playAnimation(CharacterAnimationType::WalkDown);
}

void CharacterActor::playWalkUpAnimation(){
    _playAnimation(CharacterAnimationType::WalkUp);
}

void CharacterActor::playAttackUpAnimation(){
    this->stopAllActions();
    _isPlaying = false;
    _playAnimation(CharacterAnimationType::AttackUp);
}

void CharacterActor::playAttackDownAnimation(){
    this->stopAllActions();
    _isPlaying = false;
    _playAnimation(CharacterAnimationType::AttackDown);
}

void CharacterActor::playDieAnimation(){
    this->stopAllActions();
    _isPlaying = false;
    _playAnimation(CharacterAnimationType::Die);
}

void CharacterActor::_playAnimation(const CharacterAnimationType &type){
    if (_isPlaying){
        return;
    }
    _isPlaying = true;
    auto animate = _createAnimate(type);
    this->runAction(Sequence::create(
                                     animate,
                                     CallFunc::create([&](){
        this->stopAllActions();
        _isPlaying = false;
    }),
                                     NULL));
}

Animate *CharacterActor::_createAnimate(const CharacterAnimationType &type){
    cocos2d::Vector<cocos2d::SpriteFrame *> *animationFrameArray = nullptr;
    if (type == CharacterAnimationType::WalkUp){
        animationFrameArray = &_walkUpAnimationFrameArray;
    }else if (type == CharacterAnimationType::WalkDown){
        animationFrameArray = &_walkDownAnimationFrameArray;
    }else if (type == CharacterAnimationType::AttackUp){
        animationFrameArray = &_attackUpAnimationFrameArray;
    }else if (type == CharacterAnimationType::AttackDown){
        animationFrameArray = &_attackDownAnimationFrameArray;
    }else if (type == CharacterAnimationType::Die){
        animationFrameArray = &_dieAnimationFrameArray;
    }else {
        CCLOG("%s, Error!", __func__);
    }
    
    Animation *animation = cocos2d::Animation::createWithSpriteFrames(*animationFrameArray);
    animation->setDelayPerUnit(GameData::getInstance()->getCharacterAnimationDelayPerUnit(_name));
    animation->setRestoreOriginalFrame(_isRestore);
    Animate *animate = cocos2d::Animate::create(animation);
    return animate;
}

void CharacterActor::_turnAround(const FaceTo &faceTo){
    if (_faceTo == faceTo){
        return;
    }else {
        if (faceTo == FaceTo::Left){
            _faceTo = FaceTo::Left;
            this->setFlippedX(true);
        }else {
            _faceTo = FaceTo::Right;
            this->setFlippedX(false);
        }
    }
}

std::string CharacterActor::_getCharacterNormalSpriteFrame(){
    if (_side == Side::Player){
//        CCLOG("%s, %s", __func__, std::string(getCharacterNameString(_name) + "_up.png").c_str());
        return std::string(getCharacterNameString(_name) + "_up.png");
    }else if (_side == Side::NPC){
//        CCLOG("%s, %s", __func__, std::string(getCharacterNameString(_name) + "_down.png").c_str());
        return std::string(getCharacterNameString(_name) + "_down.png");
    }else {
        CCLOG("%s, _side Wrong!", __func__);
        return "";
    }
}

void CharacterActor::_prepareAnimation(){
    makeCharacterAnimationFrameArray(&_walkUpAnimationFrameArray, getCharacterNameString(_name), "walkUp", GameData::getInstance()->getCharacterAnimationFrameNumber(_name, "walkUp"));
    makeCharacterAnimationFrameArray(&_walkDownAnimationFrameArray, getCharacterNameString(_name), "walkDown", GameData::getInstance()->getCharacterAnimationFrameNumber(_name, "walkDown"));
    makeCharacterAnimationFrameArray(&_attackUpAnimationFrameArray, getCharacterNameString(_name), "attackUp", GameData::getInstance()->getCharacterAnimationFrameNumber(_name, "attackUp"));
    makeCharacterAnimationFrameArray(&_attackDownAnimationFrameArray, getCharacterNameString(_name), "attackDown", GameData::getInstance()->getCharacterAnimationFrameNumber(_name, "attackDown"));
//    makeCharacterAnimationFrameArray(&_attackAnimationFrameArray, getCharacterNameString(_name), "attack", GameData::getInstance()->getCharacterAnimationFrameNumber(_name, "attack"));
    makeCharacterAnimationFrameArray(&_dieAnimationFrameArray, "character", "die", GameData::getInstance()->getCharacterAnimationFrameNumber(_name, "die"));
}
