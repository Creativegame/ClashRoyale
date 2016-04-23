//
//  CharacterCard.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/29.
//
//

#include "CharacterCard.hpp"
#include "BattleLayer.hpp"
#include "BattleUICardBoard.hpp"

USING_NS_CC;

CharacterCard *CharacterCard::createCharacterCard(const CharacterName &name, BattleLayer *battleLayer, BattleUICardBoard *battleUICardBoard){
    CharacterCard *characterCard = new (std::nothrow) CharacterCard(name, battleLayer, battleUICardBoard);
    if (characterCard && characterCard->init()){
        characterCard->autorelease();
        return characterCard;
    }
    delete characterCard;
    characterCard = nullptr;
    return nullptr;
}

bool CharacterCard::init(){
    if (!Node::init()){
        return false;
    }
    
    _initCard();
    
    return true;
}

void CharacterCard::onEnter(){
    Node::onEnter();
}

void CharacterCard::onExit(){
    Node::onExit();
    this->unscheduleUpdate();
    if (_touchListenter){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListenter);
        _touchListenter = nullptr;
    }
}

void CharacterCard::update(float dt){
    
    if (GameData::getInstance()->getCharacterWaterCost(_name) <= _battleLayer->getPlayerWater()){
        _state = CharacterCardState::Done;
        _done();
    }else {
        _state = CharacterCardState::Progress;
        _progress();
    }
}

void CharacterCard::becomeReadyCard(){
    this->scheduleUpdate();
    _addTouchListener();
}

void CharacterCard::_initCard(){
    _cardBoard = Sprite::createWithSpriteFrameName("battle_ui_cardBackground.png");
//    _cardBoard->setAnchorPoint(Vec2(0, 0));
    this->addChild(_cardBoard, 0);
    
    Size cardBoardSize = _cardBoard->getContentSize();
    
    _characterIcon = Sprite::createWithSpriteFrameName(getCharacterIconFrameName(_name));
    _characterIcon->setPosition(cardBoardSize.width / 2, cardBoardSize.height / 2 + 20);
    _cardBoard->addChild(_characterIcon, 1);
    
    _waterCostLabel = createLabel(int2String(GameData::getInstance()->getCharacterWaterCost(_name)), 25, Color3B(255, 255, 255));
    _waterCostLabel->enableOutline(Color4B(0, 0, 0, 255), 2);
    _waterCostLabel->setPosition(cardBoardSize.width / 2 - 3, 17);
    _cardBoard->addChild(_waterCostLabel, 1);
    
    Sprite *progressSprite = Sprite::createWithSpriteFrameName("battle_ui_cardBackground.png");
    _progressMask = ProgressTimer::create(progressSprite);
    _progressMask->setColor(Color3B(0, 0, 0));
    _progressMask->setOpacity(100);
    _progressMask->setType(ProgressTimer::Type::RADIAL);
    _progressMask->setReverseProgress(true);
    _progressMask->setPercentage(80);
    _progressMask->setAnchorPoint(Vec2(0, 0));
    _progressMask->setPosition(0, 0);
    _progressMask->setVisible(false);
    _cardBoard->addChild(_progressMask, 5);
    
//    _state = CharacterCardState::Wait;
    
//    _notEnoughMask = Sprite::createWithSpriteFrameName("battle_ui_cardBackground.png");
//    _notEnoughMask->setColor(Color3B(0, 0, 0));
//    _notEnoughMask->setOpacity(100);
//    _notEnoughMask->setAnchorPoint(Vec2(0, 0));
//    _notEnoughMask->setPosition(0, 0);
//    _cardBoard->addChild(_notEnoughMask, 4);
}

void CharacterCard::_addTouchListener(){
    _touchListenter = EventListenerTouchOneByOne::create();
    _touchListenter->setSwallowTouches(false);
    _touchListenter->onTouchBegan = [](Touch *touch, Event *event){
        return true;
    };
    _touchListenter->onTouchMoved = [&](Touch *touch, Event *event){
    };
    _touchListenter->onTouchEnded = [&](Touch *touch, Event *event){
        Rect touchSelectedRect = Rect(-60, -75, 120, 150);
        Vec2 touchLocation = this->convertToNodeSpace(touch->getLocation());
        if (touchSelectedRect.containsPoint(touchLocation)){
            this->_select();
        }else {
            if (_isSelected){
                if (_state == CharacterCardState::Done){
                    if (_battleLayer->addCharacterToBattleMap(_name, touch->getLocation())){
                        _battleUICardBoard->useCard(this);
                    }else {
                        this->_unselect();
                    }
                }else {
                    this->_unselect();
                }
            }
        }
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListenter, this);
}

void CharacterCard::_select(){
    _cardBoard->runAction(Sequence::create(ScaleTo::create(0.05, 1.1), ScaleTo::create(0.05, 1), NULL));
    if (_isSelected){
        return;
    }
    _isSelected = true;
    _cardBoard->runAction(EaseIn::create(MoveBy::create(0.1, Vec2(0, 25)), 5));
}

void CharacterCard::_unselect(){
//    _cardBoard->runAction(Sequence::create(ScaleTo::create(0.05, 1.1), ScaleTo::create(0.05, 1), NULL));
    if (!_isSelected){
        return;
    }
    _isSelected = false;
    _cardBoard->runAction(EaseIn::create(MoveBy::create(0.1, Vec2(0, -25)), 5));
}

void CharacterCard::_progress(){
    _isProgress = true;
    _progressMask->setVisible(true);
    float sumProgress = GameData::getInstance()->getCharacterWaterCost(_name) * 100;
    float currentProgress = (static_cast<float>(_battleLayer->getPlayerWater()) + _battleLayer->getPlayerCurrentWaterProgress()) * 100;
    float percentage = 100 - currentProgress / sumProgress * 100;
//    CCLOG("%s, %f, %f, %f", __func__, sumProgress, currentProgress, percentage);
    _progressMask->setPercentage(percentage);
    
}

void CharacterCard::_done(){
    if (!_isProgress){
        return;
    }
    _isProgress = false;
    _cardBoard->runAction(Sequence::create(ScaleTo::create(0.03, 1.1), ScaleTo::create(0.03, 1), NULL));
    _progressMask->setVisible(false);
}
