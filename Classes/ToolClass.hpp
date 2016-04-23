//
//  ToolClass.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/21.
//
//

#ifndef ToolClass_hpp
#define ToolClass_hpp

#include <stdio.h>
#include "cocos2d.h"

enum class Side {
    Player = 0,
    NPC
};

enum class FaceTo{
    Left = 0,
    Right
};

enum class HealthBarType{
    TowerBig = 0,
    TowerSmall,
    Character,
};

enum class CharacterName{
    Knight = 0,
    Gunner,
    Fatty,
    Goblin,
    Ghost,
    TowerShooterSmall,
    TowerShooterBig,
    NoName
};

enum class CharacterState{
    WalkUp = 0,
    WalkDown,
    AttackUp,
    AttackDown,
    FindTarget,
    Die,
    Wait
};

enum class CharacterCardState{
    Progress = 0,
    Done,
    Wait
};

enum CharacterAnimationType{
    WalkUp = 0,
    WalkDown,
    AttackUp,
    AttackDown,
    Die
};

enum class TowerType{
    King = 0,
    Defend,
    NoType
};

enum class TowerState{
    Alive = 0,
    Die
};

enum class BattleWeapon{
    Arrow = 0
};

class AStarDataNode{
public:
    
    AStarDataNode() {};
    
    AStarDataNode(int argumentColumn, int argumentRow, bool argumentWalkable):
    column(argumentColumn), row(argumentRow), walkable(argumentWalkable) {}
    
    void print(){
        CCLOG("AStarDataNode, (%d, %d), W: %d", column, row, walkable);
    }
    
    int column = 0;
    int row = 0;
    bool walkable = false;
};

class AStarNode{
public:
    
    AStarNode(int argumentColumn, int argumentRow, bool argumentWalkable, int argumentFValue, int argumentGValue, int argumentHValue, AStarNode *argumentParentNode):
    column(argumentColumn), row(argumentRow), walkable(argumentWalkable), FValue(argumentFValue), GValue(argumentGValue), HValue(argumentHValue), parentNode(argumentParentNode) {}
    
    void print(){
        if (parentNode){
            CCLOG("AStarNode, (%d, %d), F: %d, G: %d, H %d Parent: (%d, %d)", column, row, FValue, GValue, HValue, parentNode->column, parentNode->row);
        }else {
            CCLOG("AStarNode, (%d, %d), F: %d, G: %d, H %d ", column, row, FValue, GValue, HValue);
        }
        
    }
    
    int column = 0;
    int row = 0;
    bool walkable = false;
    
    int FValue = 0;
    int GValue = 0;
    int HValue = 0;
    
    AStarNode *parentNode;
};



#endif /* ToolClass_hpp */
