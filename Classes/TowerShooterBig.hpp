//
//  TowerShooterBig.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/15.
//
//

#ifndef TowerShooterBig_hpp
#define TowerShooterBig_hpp

#include <stdio.h>
#include "TowerShooterSmall.hpp"

class TowerShooterBig: public TowerShooterSmall{
public:
    
    static TowerShooterBig *createTowerShooterBig(const Side &side, BattleLayer *battleLayer);
    
    TowerShooterBig(const Side &side, BattleLayer *battleLayer):
    TowerShooterSmall(CharacterName::TowerShooterBig, side, battleLayer) {}
    
    
private:
    
};

#endif /* TowerShooterBig_hpp */
