//
//  BattleLayer.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#include "BattleLayer.hpp"
#include "BattleUILayer.hpp"
#include "CharacterCreator.hpp"
#include "TowerCreator.hpp"
#include "BattleElement.hpp"
#include "Arrow.hpp"

USING_NS_CC;

BattleLayer *BattleLayer::createBattleLayer(){
    BattleLayer *battleLayer = new (std::nothrow) BattleLayer();
    if (battleLayer && battleLayer->init()){
        battleLayer->autorelease();
        return battleLayer;
    }
    
    delete battleLayer;
    battleLayer = nullptr;
    return nullptr;
}

bool BattleLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    _dealMap();
    _makeAStarData();
    _initBattleUILayer();
    
    return true;
}

void BattleLayer::onEnter(){
    Layer::onEnter();
    _addBattleMapTouchListener();
    _startAddWater();
}

void BattleLayer::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    
    _initTower();
    
    _testCode();
}

void BattleLayer::onExit(){
    Layer::onExit();
    _stopAddWater();
}

bool BattleLayer::addCharacterToBattleMap(const cocos2d::Vec2 &position){
    int tileCoordX = static_cast<int>(position.x) / static_cast<int>(_battleTileSize.width);
    int tileCoordY = static_cast<int>(position.y) / static_cast<int>(_battleTileSize.height);
    Vec2 characterPosition = Vec2(tileCoordX * _battleTileSize.width + _battleTileSize.width / 2, tileCoordY * _battleTileSize.height + _battleTileSize.height / 2);
    
    Character *testFatty = createCharacter(CharacterName::Fatty, Side::Player, this);
    testFatty->setPosition(characterPosition);
    _battleMap->addChild(testFatty, getBattleElementZOrderOnBattleMap(testFatty));
    
    playerCharacters.push_back(testFatty);
    return true;
}

bool BattleLayer::addCharacterToBattleMap(const CharacterName &name, const cocos2d::Vec2 &worldPosition){
    Vec2 positionInBattleMap = _battleMap->convertToNodeSpace(worldPosition);
    Rect battleRect = Rect(0, 0, _battleMapSize.width, _battleMapSize.height);
    if (battleRect.containsPoint(positionInBattleMap)){
        CCLOG("%s, %s, (%.2f, %.2f)", __func__, getCharacterNameString(name).c_str(), worldPosition.x, worldPosition.y);
        Character *newCharacter = createCharacter(name, Side::Player, this);
        newCharacter->setPosition(positionInBattleMap);
        _battleMap->addChild(newCharacter, getBattleElementZOrderOnBattleMap(newCharacter));
        playerCharacters.push_back(newCharacter);
        newCharacter->setID(_characterID++);
        _playerWater -= GameData::getInstance()->getCharacterWaterCost(name);
        return true;
    }
    return false;
}

void BattleLayer::removeCharacterFromBattleMap(Character *character){
    
    if (character->getSide() == Side::Player){
        
        for (auto iter = npcCharacters.begin(); iter != npcCharacters.end(); ++iter){
            if ((*iter)->getAttackTargetID() == character->getID()){
                (*iter)->attackTarget = nullptr;
            }
        }
        
        for (auto iter = npcTowers.begin(); iter != npcTowers.end(); ++iter){
            BattleElement *shooter = (*(iter))->getShooter();
            if (shooter->getAttackTargetID() == character->getID()){
                shooter->attackTarget = nullptr;
            }
        }
        
        for (auto iter = playerCharacters.begin(); iter != playerCharacters.end(); ++iter){
            if ((*iter)->getID() == character->getID()){
                playerCharacters.erase(iter);
                BattleElement *battleElement = dynamic_cast<BattleElement *>(character);
                battleElement->removeFromParent();
                return;
            }
        }
    }
    if (character->getSide() == Side::NPC){
        
        for (auto iter = playerCharacters.begin(); iter != playerCharacters.end(); ++iter){
            if ((*iter)->getAttackTargetID() == character->getID()){
                (*iter)->attackTarget = nullptr;
            }
        }
        
        for (auto iter = playerTowers.begin(); iter != playerTowers.end(); ++iter){
            BattleElement *shooter = (*iter)->getShooter();
            if ( shooter->getAttackTargetID() == character->getID()){
                shooter->attackTarget = nullptr;
            }
        }
        
        for (auto iter = npcCharacters.begin(); iter != npcCharacters.end(); ++iter){
            if ((*iter)->getID() == character->getID()){
                npcCharacters.erase(iter);
                BattleElement *battleElement = dynamic_cast<BattleElement *>(character);
                battleElement->removeFromParent();
                return;
            }
        }
    }
    
    CCLOG("%s, Can't Find Character! %d", __func__, character->getID());
}

void BattleLayer::addArrowToBattleMap(BattleElement *from, BattleElement *to, const std::function<void ()> &callback){
    CCLOG("%s, ", __func__);
}

void BattleLayer::addArrowToBattleMap(const cocos2d::Vec2 &fromPoint, const cocos2d::Vec2 &toPoint, const std::function<void ()> &callback){
    CCLOG("%s, ", __func__);
    Arrow *arrow = Arrow::createArrow(fromPoint, toPoint, this);
    arrow->setPosition(fromPoint);
    _battleMap->addChild(arrow, 10000);
    
    float duration = getDistanceWithTowVec2(fromPoint, toPoint) / GameData::getInstance()->getBattleWeaponSpeed(BattleWeapon::Arrow);
    
    arrow->runAction(Sequence::create(MoveTo::create(duration, toPoint), CallFunc::create([=](){
        callback();
        arrow->removeFromParent();
    }), NULL));
}

void BattleLayer::holdAStarDataTile(int column, int row){
    if (column < 0 || column >= _battleMapTileSize.width || row < 0 || row >= _battleMapTileSize.height){
        return;
    }
    
    astarData[column][row].walkable = false;
}

void BattleLayer::releaseAStarDataTile(int column, int row){
    if (column < 0 || column >= _battleMapTileSize.width || row < 0 || row >= _battleMapTileSize.height){
        return;
    }
    
    astarData[column][row].walkable = true;
}

void BattleLayer::setBattleElement(int column, int row, BattleElement *battleElement){
    if (column < 0 || column >= _battleMapTileSize.width || row < 0 || row >= _battleMapTileSize.height){
        return;
    }
    
    battleElements[column][row] = battleElement;

}

void BattleLayer::addChildToBattleMap(cocos2d::Node *child){
    _battleMap->addChild(child, 1);
}

int BattleLayer::getBattleElementZOrderOnBattleMap(BattleElement *battleElement){
    int coordY = static_cast<int>(battleElement->getPosition().y) / _battleTileSize.height;
    int zorder = (_battleMapTileSize.height - coordY) + 10;
    return zorder;
}

std::vector<CharacterName> BattleLayer::getCharacterNameList(){
    //TODO: Will Done
    std::vector<CharacterName> characterNameList = {CharacterName::Fatty, CharacterName::Fatty, CharacterName::Fatty, CharacterName::Fatty, CharacterName::Fatty};
    return characterNameList;
}

void BattleLayer::_startAddWater(){
    float delayTime = 0.01;
    float waterStep = 1.0 / (static_cast<float>(GameData::getInstance()->getAddOneWaterTime()) / delayTime);
    this->schedule([&, waterStep](float dt){
        if (_playerWater < GameData::getInstance()->getMaxWater()){
            if (_playerCurrentWaterProgress >= 1){
                _playerWater += 1;
                _playerCurrentWaterProgress = 0;
            }else {
                _playerCurrentWaterProgress += waterStep;
            }
        }else {
            _playerCurrentWaterProgress = 0;
        }
        
        if (_npcWater < GameData::getInstance()->getMaxWater()){
            if (_npcCurrentWaterProgress >= 1){
                _npcWater += 1;
                _npcCurrentWaterProgress = 0;
            }else {
                _npcCurrentWaterProgress += waterStep;
            }
        }else {
            _npcCurrentWaterProgress = 0;
        }
    }, delayTime, "WaterLogic");
}

void BattleLayer::_stopAddWater(){
    this->unschedule("WaterLogic");
}

void BattleLayer::_dealMap(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _battleMapBackground = LayerColor::create(Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height);
    _battleMapBackground->setPosition(0, 0);
    this->addChild(_battleMapBackground, 0);
    
    TMXTiledMap *tiledMap = TMXTiledMap::create("res/map/battle_map.tmx");
    TMXLayer *backgroundLayer = tiledMap->getLayer("background");
    TMXLayer *walkableLayer = tiledMap->getLayer("walkable");
    
    walkableLayer->setAnchorPoint(Vec2(0.5, 0.5));
    walkableLayer->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 90);
    _battleMapBackground->addChild(walkableLayer, 1);
    
    backgroundLayer->setAnchorPoint(Vec2(0.5, 0.5));
    backgroundLayer->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 90);
    _battleMapBackground->addChild(backgroundLayer, 1);
    
    Size mapSize = walkableLayer->getLayerSize();
    _battleMapTileSize = Size(20, 30);
    _battleTileSize = walkableLayer->getMapTileSize();
    
    _battleMapSize = Size(20 * _battleTileSize.width, 30 * _battleTileSize.height);
    _battleMap = LayerColor::create(Color4B(255, 255, 255, 150), _battleMapSize.width, _battleMapSize.height);
    _battleMap->ignoreAnchorPointForPosition(false);
    _battleMap->setAnchorPoint(Vec2(0.5, 0.5));
    _battleMap->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 90);
    _battleMapBackground->addChild(_battleMap, 5);
    
}

void BattleLayer::_makeAStarData(){
    TMXTiledMap *tiledMap = TMXTiledMap::create("res/map/battle_map.tmx");
    TMXLayer *walkableLayer = tiledMap->getLayer("walkable");
    Size mapSize = walkableLayer->getLayerSize();
//    CCLOG("MapSize: (%f, %f)", mapSize.width, mapSize.height);
    
    AStarDataNode astarDataVec[20][30];
    
    for (int column = 0; column < _battleMapTileSize.width; ++column){
        for (int row = 0; row < _battleMapTileSize.height; ++row){
            Vec2 tileCoord = Vec2(column + 5, mapSize.height - (row + 5) - 1);
            int tileGID = walkableLayer->getTileGIDAt(tileCoord);
            
            if (tileGID > 0){
                Value value = tiledMap->getPropertiesForGID(tileGID);
                ValueMap valueMap = value.asValueMap();
                int walkable = valueMap["walkable"].asInt();
//                CCLOG("Column: %d, Row: %d, Walkable: %d", column, row, walkable);
                
                astarDataVec[column][row].column = column;
                astarDataVec[column][row].row = row;
                astarDataVec[column][row].walkable = (walkable == 0) ? false : true;
                
            }
        }
    }
    
    for (int column = 0; column < _battleMapTileSize.width; ++column){
        std::vector<AStarDataNode> oneList;
        std::vector<BattleElement *> oneBattleElementList;
        for (int row = 0; row < _battleMapTileSize.height; ++row){
            AStarDataNode astarDataNode = AStarDataNode(column, row, astarDataVec[column][row].walkable);
            oneList.push_back(astarDataNode);
            oneBattleElementList.push_back(nullptr);
        }
        astarData.push_back(oneList);
        battleElements.push_back(oneBattleElementList);
    }
    
//    for (int row = 0; row < _battleMapTileSize.height; ++row){
//        for (int column = 0; column < _battleMapTileSize.width; ++column){
//            printf("%d", astarData[column][row].walkable);
//        }
//        printf("\n");
//    }
}

void BattleLayer::_addBattleMapTouchListener(){
    _battleMapTouchListener = EventListenerTouchOneByOne::create();
    _battleMapTouchListener->setSwallowTouches(true);
    _battleMapTouchListener->onTouchBegan = [](Touch *touch, Event *event){
        return true;
    };
    _battleMapTouchListener->onTouchMoved = [](Touch *touch, Event *event){
        Vec2 delta = touch->getDelta();
        if (fabsf(delta.x) > 5 || fabsf(delta.y) > 5){
        }
    };
    _battleMapTouchListener->onTouchEnded = [&](Touch *touch, Event *event){
        Vec2 locationInBattleMap = _battleMap->convertToNodeSpace(touch->getLocation());
        if (locationInBattleMap.x < 0 || locationInBattleMap.y < 0 || locationInBattleMap.x > _battleMapSize.width || locationInBattleMap.y > _battleMapSize.height){
            return;
        }
//        addCharacterToBattleMap(locationInBattleMap);
//        int tileCoordX = static_cast<int>(locationInBattleMap.x) / static_cast<int>(_battleTileSize.width);
//        int tileCoordY = static_cast<int>(locationInBattleMap.y) / static_cast<int>(_battleTileSize.height);
//        CCLOG("Touch (%.2f, %.2f), (%d, %d)", locationInBattleMap.x, locationInBattleMap.y, tileCoordX, tileCoordY);
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_battleMapTouchListener, _battleMap);
}

void BattleLayer::_initBattleUILayer(){
    _battleUILayer = BattleUILayer::createBattleUILayer(this);
    this->addChild(_battleUILayer, 10);
}

void BattleLayer::_initTower(){
    TMXTiledMap *tiledMap = TMXTiledMap::create("res/map/battle_map.tmx");
    TMXObjectGroup *towerObjectData = tiledMap->getObjectGroup("tower");
    auto &towersData = towerObjectData->getObjects();
    for (auto &towerDataItem : towersData){
        ValueMap &towerData = towerDataItem.asValueMap();
        
//        CCLOG("%s, %s", towerData["side"].asString().c_str(), towerData["type"].asString().c_str());
        
        if (towerData["side"].asString() == "player"){
            if (towerData["type"].asString() == "king"){
//                _playerKingTower = Tower::createTower(TowerType::King, Side::Player, this);
                playerKingTower = createTower(TowerType::King, Side::Player, this);
                playerKingTower->setPosition(_battleMapSize.width / 2, 0);
                _battleMap->addChild(playerKingTower, getBattleElementZOrderOnBattleMap(playerKingTower));
                playerTowers.push_back(playerKingTower);
            }else {
                if (towerData["road"].asString() == "left"){
//                    _playerDefendLeftTower = Tower::createTower(TowerType::Defend, Side::Player, this);
                    playerDefendLeftTower = createTower(TowerType::Defend, Side::Player, this);
                    playerDefendLeftTower->setPosition(_battleTileSize.width * 3.5, _battleTileSize.height * 5);
                    _battleMap->addChild(playerDefendLeftTower, getBattleElementZOrderOnBattleMap(playerDefendLeftTower));
                    playerTowers.push_back(playerDefendLeftTower);
                }
                if (towerData["road"].asString() == "right"){
//                    _playerDefendRightTower = Tower::createTower(TowerType::Defend, Side::Player, this);
                    playerDefendRightTower = createTower(TowerType::Defend, Side::Player, this);
                    playerDefendRightTower->setPosition(_battleTileSize.width * 16.5, _battleTileSize.height * 5);
                    _battleMap->addChild(playerDefendRightTower, getBattleElementZOrderOnBattleMap(playerDefendRightTower));
                    playerTowers.push_back(playerDefendRightTower);
                }
            }
        }else {
            if (towerData["type"].asString() == "king"){
//                _npcKingTower = Tower::createTower(TowerType::King, Side::NPC, this);
                npcKingTower = createTower(TowerType::King, Side::NPC, this);
                npcKingTower->setPosition(_battleMapSize.width / 2, _battleTileSize.height * 26);
                _battleMap->addChild(npcKingTower, getBattleElementZOrderOnBattleMap(npcKingTower));
                npcTowers.push_back(npcKingTower);
            }else {
                if (towerData["road"].asString() == "left"){
//                    _npcDefendLeftTower = Tower::createTower(TowerType::Defend, Side::NPC, this);
                    npcDefendLeftTower = createTower(TowerType::Defend, Side::NPC, this);
                    npcDefendLeftTower->setPosition(_battleTileSize.width * 3.5, _battleTileSize.height * 23);
                    _battleMap->addChild(npcDefendLeftTower, getBattleElementZOrderOnBattleMap(npcDefendLeftTower));
                    npcTowers.push_back(npcDefendLeftTower);
                }
                if (towerData["road"].asString() == "right"){
//                    _npcDefendRightTower = Tower::createTower(TowerType::Defend, Side::NPC, this);
                    npcDefendRightTower = createTower(TowerType::Defend, Side::NPC, this);
                    npcDefendRightTower->setPosition(_battleTileSize.width * 16.5, _battleTileSize.height * 23);
                    _battleMap->addChild(npcDefendRightTower, getBattleElementZOrderOnBattleMap(npcDefendRightTower));
                    npcTowers.push_back(npcDefendRightTower);
                }
            }
        }
        
    }
}

void BattleLayer::_testCode(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //Add Tile Label
    for (int column = 0; column < astarData.size(); ++column){
        for (int row = 0; row < astarData[column].size(); ++row){
            std::string labelString = int2String(column) + "," + int2String(row);
            Label *tileLabel = Label::createWithSystemFont(labelString, "Arial", 10);
            tileLabel->setColor(Color3B(0, 0, 0));
            tileLabel->setPosition(column * _battleTileSize.width + _battleTileSize.width / 2, row * _battleTileSize.height + _battleTileSize.height / 2);
            _battleMap->addChild(tileLabel, 1);
        }
    }
    
//    this->schedule([&](float dt){
//        CCLOG("Test Water");
//        _playerWater = 2;
//    }, 20, "TestWater");
    
    //Find Path Test
//    std::vector<AStarNode *> path;
//    AStarDataNode beginNode = AStarDataNode(3, 0, true);
//    AStarDataNode targetNode = AStarDataNode(3, 29, true);
//    astar(astarData, path, beginNode, targetNode);
//    for (auto iter = path.begin(); iter != path.end(); ++iter){
////        CCLOG("(%d, %d)", (*iter)->column, (*iter)->row);
//        Sprite *pathNode = Sprite::createWithSpriteFrameName("battle_map_path.png");
//        pathNode->setAnchorPoint(Vec2(0, 0));
//        pathNode->setPosition((*iter)->column * _battleTileSize.width, (*iter)->row * _battleTileSize.height);
//        _battleMap->addChild(pathNode, 1);
//    }
    
//    this->schedule([&](float deltaTime){
//        playerKingTower->loseBlood(5);
//        playerDefendLeftTower->loseBlood(8);
//        npcKingTower->loseBlood(7);
//        npcDefendRightTower->loseBlood(10);
//    }, 1, "Test");
    
    //Tower Test
//    Tower *tower1 = Tower::createTower(TowerType::King, Side::Player);
//    tower1->setPosition(_battleMapSize.width / 2, 0);
//    _battleMap->addChild(tower1, getBattleElementZOrderOnBattleMap(tower1));
//    
//    Tower *tower2 = Tower::createTower(TowerType::Defend, Side::Player);
//    tower2->setPosition(_battleMapSize.width / 2, _battleMapSize.height / 4);
//    _battleMap->addChild(tower2, getBattleElementZOrderOnBattleMap(tower2));
//    
//    Tower *tower3 = Tower::createTower(TowerType::King, Side::NPC);
//    tower3->setPosition(_battleMapSize.width / 2, _battleMapSize.height / 2);
//    _battleMap->addChild(tower3, getBattleElementZOrderOnBattleMap(tower3));
//    
//    Tower *tower4 = Tower::createTower(TowerType::Defend, Side::NPC);
//    tower4->setPosition(_battleMapSize.width / 2, _battleMapSize.height / 4 * 3);
//    _battleMap->addChild(tower4, getBattleElementZOrderOnBattleMap(tower4));
    
}
