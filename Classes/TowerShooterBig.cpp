//
//  TowerShooterBig.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/15.
//
//

#include "TowerShooterBig.hpp"

TowerShooterBig *TowerShooterBig::createTowerShooterBig(const Side &side, BattleLayer *battleLayer){
    TowerShooterBig *towerShooterBig = new (std::nothrow) TowerShooterBig(side, battleLayer);
    if (towerShooterBig && towerShooterBig->init()){
        towerShooterBig->autorelease();
        return towerShooterBig;
    }
    
    delete towerShooterBig;
    towerShooterBig = nullptr;
    return nullptr;
}
