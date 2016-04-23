//
//  BattleLayer.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#ifndef BattleLayer_hpp
#define BattleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"

class BattleUILayer;
class BattleElement;
class Character;
class Tower;

class BattleLayer: public cocos2d::Layer{
public:
    
    static BattleLayer *createBattleLayer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    std::vector<std::vector<AStarDataNode>> astarData;
    std::vector<std::vector<BattleElement *>> battleElements;
    
    bool addCharacterToBattleMap(const cocos2d::Vec2 &position);
    bool addCharacterToBattleMap(const CharacterName &name, const cocos2d::Vec2 &worldPosition);
    void removeCharacterFromBattleMap(Character *character);
    void removeCharacterFromBattleMap(BattleElement *battleElement);
    void addArrowToBattleMap(BattleElement *from, BattleElement *to, const std::function<void ()> &callback);
    void addArrowToBattleMap(const cocos2d::Vec2 &fromPoint, const cocos2d::Vec2 &toPoint, const std::function<void ()> &callback);
    void holdAStarDataTile(int column, int row);
    void releaseAStarDataTile(int column, int row);
    void setBattleElement(int column, int row, BattleElement *battleElement);
    cocos2d::Size &getMapSize() { return _battleMapSize; }
    cocos2d::Size &getTileSize() { return _battleTileSize; }
    cocos2d::Size &getMapTileSize() {return _battleMapTileSize; }
    
    Tower *playerKingTower;
    Tower *playerDefendLeftTower;
    Tower *playerDefendRightTower;
    Tower *npcKingTower;
    Tower *npcDefendLeftTower;
    Tower *npcDefendRightTower;
    
    std::vector<Character *> playerCharacters;
    std::vector<Character *> npcCharacters;
    
    std::vector<Tower *> playerTowers;
    std::vector<Tower *> npcTowers;
    
    void addChildToBattleMap(Node *child);
    int getBattleElementZOrderOnBattleMap(BattleElement *battleElement);
    
    std::vector<CharacterName> getCharacterNameList();
    int getPlayerWater() {return _playerWater;}
    float getPlayerCurrentWaterProgress() {return _playerCurrentWaterProgress;}
    int getNpcWater(){return _npcWater;}
    
private:
    
    int _characterID = 0;
    
    BattleUILayer *_battleUILayer;
    void _initBattleUILayer();
    
    cocos2d::LayerColor *_battleMapBackground;
    cocos2d::LayerColor *_battleMap;
    cocos2d::Size _battleMapSize;
    cocos2d::Size _battleTileSize;
    cocos2d::Size _battleMapTileSize;
    cocos2d::EventListenerTouchOneByOne *_battleMapTouchListener;
    
    std::vector<CharacterName> _playerCharacterNameList;
    std::vector<CharacterName> _npcCharacterNameList;
    
    int _playerWater = 5;
    float _playerCurrentWaterProgress = 0;
    int _npcWater = 5;
    float _npcCurrentWaterProgress = 0;
    void _startAddWater();
    void _stopAddWater();
    
    void _dealMap();
    void _makeAStarData();
    void _addBattleMapTouchListener();
    
    void _initTower();
    
    void _testCode();
};

#endif /* BattleLayer_hpp */
