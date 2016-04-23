//
//  CharacterCard.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/29.
//
//

#ifndef CharacterCard_hpp
#define CharacterCard_hpp

#include <stdio.h>
#include "ToolFunction.hpp"

class BattleLayer;
class BattleUICardBoard;

class CharacterCard: public cocos2d::Node{
public:
    
    static CharacterCard *createCharacterCard(const CharacterName &name, BattleLayer *battleLayer, BattleUICardBoard *battleUICardBoard);
    
    CharacterCard(const CharacterName &name, BattleLayer *battleLayer, BattleUICardBoard *battleUICardBoard):
    _name(name), _battleLayer(battleLayer), _battleUICardBoard(battleUICardBoard) {}
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    void setID(int id) { _id = id;}
    int getID() {return _id;}
    void becomeReadyCard();
    
private:
    
    CharacterName _name;
    int _id = -1;
    BattleLayer *_battleLayer;
    BattleUICardBoard *_battleUICardBoard;
    CharacterCardState _state;
    bool _isProgress = true;
    bool _isSelected = false;
    int _progressPercentage = 100;
    
    cocos2d::Sprite *_cardBoard;
    cocos2d::Sprite *_characterIcon;
    cocos2d::Label *_waterCostLabel;
    cocos2d::ProgressTimer *_progressMask;
    cocos2d::Sprite *_notEnoughMask;
    cocos2d::EventListenerTouchOneByOne *_touchListenter;
    
    void _initCard();
    void _addTouchListener();
    void _select();
    void _unselect();
    void _progress();
    void _done();
};

#endif /* CharacterCard_hpp */
