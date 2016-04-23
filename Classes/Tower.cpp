//
//  Tower.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/4.
//
//

#include "Tower.hpp"
#include "HealthBar.hpp"
#include "BattleLayer.hpp"
#include "TowerShooterBig.hpp"

USING_NS_CC;

Tower *Tower::createTower(const TowerType &type, const Side &side, BattleLayer *battleLayer){
    Tower *tower = new (std::nothrow) Tower(type, side, battleLayer);
    if (tower && tower->init()){
        tower->autorelease();
        return tower;
    }
    delete tower;
    tower = nullptr;
    return nullptr;
}

bool Tower::init(){
    if (!BattleElement::init()){
        return false;
    }
    
    _state = TowerState::Alive;
    
    _initTowerAvatar();
    _initHealthBar();
    _initShooter();
    
    return true;
}

void Tower::onEnter(){
    BattleElement::onEnter();
    holdTile();
}

void Tower::onExit(){
    BattleElement::onExit();
}

void Tower::holdTile(){
    _changeTile(false);
}

void Tower::releaseTile(){
    _changeTile(true);
}

bool Tower::isCanAttack(){
    if (_currentHealthValue <= 0){
        return false;
    }else {
        return true;
    }
}

void Tower::loseBlood(int loseValue){
    if (_currentHealthValue <= 0){
        return;
    }
    if (loseValue >= _currentHealthValue){
        loseValue = _currentHealthValue;
    }
    _currentHealthValue -= loseValue;
    _healthBar->refresh();
    if (_currentHealthValue <= 0){
        this->die();
    }
}

AStarDataNode Tower::getStandTile(BattleElement *battleElement){
    Size tileSize = _battleLayer->getTileSize();
    AStarDataNode commingBattleElementTile = battleElement->getStandTile(this);
    Vec2 commingBattleElementTilePoint = Vec2((commingBattleElementTile.column + 0.5) * tileSize.width, (commingBattleElementTile.row + 0.5) * tileSize.height);
    float distance = getDistanceWithTowVec2(_centerPoint, commingBattleElementTilePoint);
    float cosTheta = (commingBattleElementTilePoint.x - _centerPoint.x) / distance;
    float sinTheta = (commingBattleElementTilePoint.y - _centerPoint.y) / distance;
    
    float scaleValue = 1;
    if (_type == TowerType::King){
        scaleValue = 2.828;
    }else {
        scaleValue = 2.121;
    }
    
    float offsetX = scaleValue * tileSize.width * cosTheta;
    float offsetY = scaleValue * tileSize.height * sinTheta;
    Vec2 finalPoint = Vec2(_centerPoint.x + offsetX, _centerPoint.y + offsetY);
    if (finalPoint.x < 0 || finalPoint.y < 0 || finalPoint.x > _battleLayer->getMapSize().width || finalPoint.y > _battleLayer->getMapSize().height){
        CCLOG("%s, Error!", __func__);
        return AStarDataNode(0, 0, true);
    }
    AStarDataNode finalAStarDataNode = AStarDataNode(static_cast<int>(finalPoint.x / tileSize.width), static_cast<int>(finalPoint.y / tileSize.height), true);
    
    //最后处理一下这个 Tile ，保证不返回一个不可达的 Tile
    int minColumnOffset = 0;
    int midColumnOffset = 0;
    int maxColumnOffset = 0;
    int minRowOffset = 0;
    int midRowOffset = 0;
    int maxRowOffset = 0;
    if (_type == TowerType::King){
        minColumnOffset = 0;
        midColumnOffset = 2;
        maxColumnOffset = 4;
        minRowOffset = 0;
        midRowOffset = 2;
        maxRowOffset = 4;
    }else {
        if (_side == Side::Player){
            minColumnOffset = 0;
            midColumnOffset = 1;
            maxColumnOffset = 3;
            minRowOffset = 0;
            midRowOffset = 1;
            maxRowOffset = 3;
        }else {
            minColumnOffset = 0;
            midColumnOffset = 1;
            maxColumnOffset = 3;
            minRowOffset = 0;
            midRowOffset = 2;
            maxRowOffset = 3;
        }
    }
    
    if (finalAStarDataNode.column - _leftBottomTile.column >= minColumnOffset && finalAStarDataNode.column - _leftBottomTile.column < midRowOffset){
        finalAStarDataNode.column = _leftBottomTile.column - 1;
    }
    if (finalAStarDataNode.column - _leftBottomTile.column >= midColumnOffset && finalAStarDataNode.column - _leftBottomTile.column < maxColumnOffset){
        finalAStarDataNode.column = _leftBottomTile.column + maxColumnOffset;
    }
    
    if (finalAStarDataNode.row - _leftBottomTile.row >= minRowOffset && finalAStarDataNode.row - _leftBottomTile.row < midRowOffset){
        finalAStarDataNode.row = _leftBottomTile.row - 1;
    }
    if (finalAStarDataNode.row - _leftBottomTile.row >= midRowOffset && finalAStarDataNode.row - _leftBottomTile.row < maxRowOffset){
        finalAStarDataNode.row = _leftBottomTile.row + maxRowOffset;
    }
    CCLOG("%s, Tower Target Tile: (%d, %d)", __func__, finalAStarDataNode.column, finalAStarDataNode.row);
    return finalAStarDataNode;
}

void Tower::die(){
    CCLOG("%s, I'm Die! %d, %d", __func__, _type, _side);
    _state = TowerState::Die;
    _shooter->setState(CharacterState::Die);
    this->resetSelfZOrder(0);
    _towerRuinAvatar->setVisible(true);
    _shooter->setVisible(false);
    _healthBar->setVisible(false);
    _towerAvatar->setVisible(false);
    this->releaseTile();
}

void Tower::_initHealthBar(){
    
    _fullHealthValue = GameData::getInstance()->getTowerHp(_type);
    
    _currentHealthValue = _fullHealthValue;
    
    if (_type == TowerType::King){
        _healthBar = HealthBar::createHealthBar(HealthBarType::TowerBig, &_fullHealthValue, &_currentHealthValue);
    }else if (_type == TowerType::Defend){
        _healthBar = HealthBar::createHealthBar(HealthBarType::TowerSmall, &_fullHealthValue, &_currentHealthValue);
    }else {
        CCLOG("%s Type Error!", __func__);
        return;
    }
    
    Size towerAvatarSize = _towerAvatar->getContentSize();
    if (_side == Side::Player){
        _healthBar->setPosition(-towerAvatarSize.width / 2, towerAvatarSize.height / 3);
        this->addChild(_healthBar, 5);
    }else if (_side == Side::NPC){
        _healthBar->setPosition(-towerAvatarSize.width / 2, towerAvatarSize.height);
        this->addChild(_healthBar, 5);
    }else {
        CCLOG("%s Side Error!", __func__);
        return;
    }
}

void Tower::_initTowerAvatar(){
    if (_type == TowerType::King){
        _towerAvatar = Sprite::createWithSpriteFrameName("tower_king.png");
        _towerAvatar->setAnchorPoint(Vec2(0.5, 0));
        this->addChild(_towerAvatar, 1);
        
        _towerRuinAvatar = Sprite::createWithSpriteFrameName("tower_ruin_king.png");
        _towerRuinAvatar->setAnchorPoint(Vec2(0.5, 0));
        this->addChild(_towerRuinAvatar, 1);
        _towerRuinAvatar->setVisible(false);
    }else if (_type == TowerType::Defend){
        _towerAvatar = Sprite::createWithSpriteFrameName("tower_defend.png");
        _towerAvatar->setAnchorPoint(Vec2(0.5, 0));
        this->addChild(_towerAvatar, 1);
        
        _towerRuinAvatar = Sprite::createWithSpriteFrameName("tower_ruin_defend.png");
        _towerRuinAvatar->setAnchorPoint(Vec2(0.5, 0));
        this->addChild(_towerRuinAvatar, 1);
        _towerRuinAvatar->setVisible(false);
    }else {
        CCLOG("%s TowerType Error!", __func__);
    }
}

void Tower::_initShooter(){
    if (_type == TowerType::Defend){
        _shooter = TowerShooterSmall::createTowerShooterSmall(_side, _battleLayer);
        _shooter->setPosition(0, 60);
        this->addChild(_shooter, 2);
    }
    if (_type == TowerType::King){
        _shooter = TowerShooterBig::createTowerShooterBig(_side, _battleLayer);
        _shooter->setPosition(0, 80);
        this->addChild(_shooter, 2);
    }
}

void Tower::_changeTile(bool isWalkable){
    Size tileSize = _battleLayer->getTileSize();
    if (_type == TowerType::King){
        if (_side == Side::Player){
            _centerPoint = Vec2(10 * tileSize.width, 2 * tileSize.height);
            _leftBottomTile = AStarDataNode(8, 0, false);
            for (int column = 8; column < 12; ++column){
                for (int row = 0; row < 4; ++row){
                    if (isWalkable){
                        _battleLayer->releaseAStarDataTile(column, row);
                        _battleLayer->setBattleElement(column, row, nullptr);
                    }else {
                        _battleLayer->holdAStarDataTile(column, row);
                        _battleLayer->setBattleElement(column, row, this);
                    }
                    
                }
            }
        }else {
            _centerPoint = Vec2(10 * tileSize.width, 28 * tileSize.height);
            _leftBottomTile = AStarDataNode(8, 26, false);
            for (int column = 8; column < 12; ++column){
                for (int row = 26; row < 30; ++row){
                    if (isWalkable){
                        _battleLayer->releaseAStarDataTile(column, row);
                        _battleLayer->setBattleElement(column, row, nullptr);
                    }else {
                        _battleLayer->holdAStarDataTile(column, row);
                        _battleLayer->setBattleElement(column, row, this);
                    }
                }
            }
        }
    }else {
        if (_side == Side::Player){
            if (this->getPosition().x < _battleLayer->getMapSize().width / 2){
                _centerPoint = Vec2(3.5 * tileSize.width, 6.5 * tileSize.height);
                _leftBottomTile = AStarDataNode(2, 5, false);
                for (int column = 2; column < 5; ++column){
                    for (int row = 5; row < 8; ++row){
                        if (isWalkable){
                            _battleLayer->releaseAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, nullptr);
                        }else {
                            _battleLayer->holdAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, this);
                        }
                    }
                }
            }else {
                _centerPoint = Vec2(16.5 * tileSize.width, 6.5 * tileSize.height);
                _leftBottomTile = AStarDataNode(15, 5, false);
                for (int column = 15; column < 18; ++column){
                    for (int row = 5; row < 8; ++row){
                        if (isWalkable){
                            _battleLayer->releaseAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, nullptr);
                        }else {
                            _battleLayer->holdAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, this);
                        }
                    }
                }
            }
        }else {
            if (this->getPosition().x < _battleLayer->getMapSize().width / 2){
                _centerPoint = Vec2(3.5 * tileSize.width, 24.5 * tileSize.height);
                _leftBottomTile = AStarDataNode(2, 23, false);
                for (int column = 2; column < 5; ++column){
                    for (int row = 23; row < 26; ++row){
                        if (isWalkable){
                            _battleLayer->releaseAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, nullptr);
                        }else {
                            _battleLayer->holdAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, this);
                        }
                    }
                }
            }else {
                _centerPoint = Vec2(16.5 * tileSize.width, 24.5 * tileSize.height);
                _leftBottomTile = AStarDataNode(15, 23, false);
                for (int column = 15; column < 18; ++column){
                    for (int row = 23; row < 26; ++row){
                        if (isWalkable){
                            _battleLayer->releaseAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, nullptr);
                        }else {
                            _battleLayer->holdAStarDataTile(column, row);
                            _battleLayer->setBattleElement(column, row, this);
                        }
                    }
                }
            }
        }
    }
}
