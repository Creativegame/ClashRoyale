//
//  TowerCreator.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/5.
//
//

#ifndef TowerCreator_hpp
#define TowerCreator_hpp

#include <stdio.h>
#include "Tower.hpp"

inline Tower *createTower(const TowerType &type, const Side &side, BattleLayer *battleLayer){
    Tower *newTower = Tower::createTower(type, side, battleLayer);
    return newTower;
}


#endif /* TowerCreator_hpp */
