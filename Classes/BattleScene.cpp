//
//  BattleScene.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/20.
//
//

#include "BattleScene.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

BattleScene *BattleScene::createBattleScene(){
    BattleScene *battleScene = new (std::nothrow) BattleScene();
    if (battleScene && battleScene->init()){
        battleScene->autorelease();
        return battleScene;
    }
    
    delete battleScene;
    battleScene = nullptr;
    return nullptr;
}

bool BattleScene::init(){
    if (!Scene::init()){
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/character/character.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/tower/tower.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/map/battle_map_ui.plist");
    
    _battleLayer = BattleLayer::createBattleLayer();
    this->addChild(_battleLayer, 1);
    
    return true;
}
