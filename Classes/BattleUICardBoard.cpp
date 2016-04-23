//
//  BattleUICardBoard.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/18.
//
//

#include "BattleUICardBoard.hpp"
#include "BattleLayer.hpp"
#include "CharacterCard.hpp"
#include "BattleUIWaterBar.hpp"

USING_NS_CC;

BattleUICardBoard *BattleUICardBoard::createBattleUICardBoard(std::vector<CharacterName> characterNameList, BattleLayer *battleLayer){
    BattleUICardBoard *battleUICardBoard = new (std::nothrow) BattleUICardBoard(characterNameList, battleLayer);
    if (battleUICardBoard && battleUICardBoard->init()){
        battleUICardBoard->autorelease();
        return battleUICardBoard;
    }
    delete battleUICardBoard;
    battleUICardBoard = nullptr;
    return battleUICardBoard;
}

bool BattleUICardBoard::init(){
    if (!Node::init()){
        return false;
    }
    
    _backgroundBoard = Sprite::createWithSpriteFrameName("battle_ui_cardBoard.png");
    _backgroundBoard->setAnchorPoint(Vec2(0, 0));
    _backgroundBoard->setPosition(0, 0);
    this->addChild(_backgroundBoard, 0);
    
    _nextCardLabel = Label::createWithSystemFont("下一个：", "Arial", 28);
    _nextCardLabel->enableOutline(Color4B(0, 0, 0, 255), 2);
    _nextCardLabel->setPosition(-55, 100);
    this->addChild(_nextCardLabel, 1);
    
    _battleWaterBar = BattleUIWaterBar::createBattleUIWaterBar(_battleLayer);
    _battleWaterBar->setPosition(15, 3);
    _backgroundBoard->addChild(_battleWaterBar, 1);
    
    _characterNameList = _battleLayer->getCharacterNameList();
    for (int characterNameIndex = 0; characterNameIndex < _characterNameList.size(); ++characterNameIndex){
        _characterNames.push(_characterNameList[characterNameIndex]);
    }
    
    for (int cardIndex = 0; cardIndex < 4; ++cardIndex){
        CharacterCard *card = CharacterCard::createCharacterCard(_characterNames.getNext(), _battleLayer, this);
        card->setPosition(_cardPosition[cardIndex]);
        this->addChild(card, 1);
        card->becomeReadyCard();
        card->setID(cardIndex);
        _readyCards.push_back(card);
    }
    
    _addNewNextCard();
    
    return true;
}

void BattleUICardBoard::useCard(CharacterCard *card){
    for (int cardIndex = 0; cardIndex < _readyCards.size(); ++cardIndex){
        if (card->getID() == _readyCards[cardIndex]->getID()){
            int id = card->getID();
            _readyCards[cardIndex]->removeFromParent();
            
            _nextCard->runAction(Spawn::create(MoveTo::create(0.1, _cardPosition[id]), ScaleTo::create(0.1, 1), NULL));
            _nextCard->setID(id);
            _readyCards[cardIndex] = _nextCard;
            _readyCards[cardIndex]->becomeReadyCard();
            
            _addNewNextCard();
            
            break;
        }
    }
}

void BattleUICardBoard::_addNewNextCard(){
    
    this->scheduleOnce([&](float dt){
        _nextCard = CharacterCard::createCharacterCard(_characterNames.getNext(), _battleLayer, this);
        _nextCard->setPosition(-100, 50);
        _nextCard->setScale(0.6);
        this->addChild(_nextCard, 1);
        
        _nextCard->runAction(MoveTo::create(0.1, Vec2(-65, 50)));
    }, 0.2, "AddNewNextCard");
    
}
