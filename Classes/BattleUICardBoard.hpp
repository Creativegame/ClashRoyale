//
//  BattleUICardBoard.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/18.
//
//

#ifndef BattleUICardBoard_hpp
#define BattleUICardBoard_hpp

#include <stdio.h>
#include "ToolFunction.hpp"
#include "CycleList.hpp"

class BattleLayer;
class BattleUIWaterBar;
class CharacterCard;

class BattleUICardBoard: public cocos2d::Node{
public:
    
    static BattleUICardBoard *createBattleUICardBoard(std::vector<CharacterName> characterNameList, BattleLayer *battleLayer);
    
    BattleUICardBoard(std::vector<CharacterName> characterNameList, BattleLayer *battleLayer):
    _characterNameList(characterNameList), _battleLayer(battleLayer) {}
    
    virtual bool init();
    
    void useCard(CharacterCard *card);
    
private:
    
    std::vector<cocos2d::Vec2> _cardPosition = {cocos2d::Vec2(88, 126), cocos2d::Vec2(209, 126), cocos2d::Vec2(329, 126), cocos2d::Vec2(450, 126)};
    std::vector<CharacterName> _characterNameList;
    CycleList<CharacterName> _characterNames;
    std::vector<CharacterCard *> _readyCards;
    CharacterCard *_nextCard;
    BattleLayer *_battleLayer;
    
    BattleUIWaterBar *_battleWaterBar;
    
    cocos2d::Sprite *_backgroundBoard;
    cocos2d::Label *_nextCardLabel;
    
    void _onGameStart();
    void _addNewNextCard();
    
};

#endif /* BattleUICardBoard_hpp */
