//
//  CharacterCreator.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/7.
//
//

#ifndef CharacterCreator_hpp
#define CharacterCreator_hpp

#include <stdio.h>
#include "Knight.hpp"
#include "Fatty.hpp"

inline Character *createCharacter(const CharacterName &name, const Side &side, BattleLayer *battleLayer){
    if (name == CharacterName::Knight){
        Knight *knight = Knight::createKnight(side, battleLayer);
        return knight;
    }else if (name == CharacterName::Fatty){
        Fatty *fatty = Fatty::createFatty(side, battleLayer);
        return fatty;
    }else{
        CCLOG("%s, No Name!", __func__);
        return nullptr;
    }
}

#endif /* CharacterCreator_hpp */
