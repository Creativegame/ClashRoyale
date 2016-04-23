//
//  ToolFunction.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/21.
//
//

#ifndef ToolFunction_hpp
#define ToolFunction_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "GameData.hpp"

inline std::string int2String(int number){
    int numberToConver = number;
    int size = 0;
    do {
        ++size;
    }while (numberToConver /= 10);
    
    size *= 2;
    
    char str[size];
    int len = snprintf(str, sizeof(str), "%d", number);
    if (len > sizeof(str) - 1){
        std::cout << __func__ << "缓冲区溢出！！！！" << std::endl;
    }
    
    std::string string(str);
    return string;
}

inline std::string getCharacterAnimationFrameName(const std::string &characterName, const std::string &characterAnimation, int frameIndex){
    std::string frameName;
    if (frameIndex < 10){
        frameName = characterName + "_" + characterAnimation + "_0" + int2String(frameIndex) + ".png";
    }else {
        frameName = characterName + "_" + characterAnimation + "_" + int2String(frameIndex) + ".png";
    }
//    CCLOG("%s, %s", __func__, frameName.c_str());
    return frameName;
}

inline void makeCharacterAnimationFrameArray(cocos2d::Vector<cocos2d::SpriteFrame *> *spriteFrameArray, const std::string &characterName, const std::string &characterAnimation, int frameNumber){
    for (int frameIndex = 0; frameIndex < frameNumber; ++frameIndex){
        spriteFrameArray->pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(getCharacterAnimationFrameName(characterName, characterAnimation, frameIndex)));
    }
}

inline cocos2d::Label *createLabel(const std::string &string, float size, const cocos2d::Color3B &color){
    cocos2d::Label *label = cocos2d::Label::createWithTTF(string, "res/front/Comic_Book.ttf", size);
    label->setColor(color);
    return label;
}

inline std::string getCharacterNameString(CharacterName name){
    if (GameData::getInstance()->characterNameData.find(name) != GameData::getInstance()->characterNameData.end()){
        return GameData::getInstance()->characterNameData.at(name);
    }
    
    CCLOG("%s, Error!", __func__);
    return "";
}

inline std::string getCharacterIconFrameName(const CharacterName &name){
    return getCharacterNameString(name) + "_down.png";
}

inline float getDistanceWithTowVec2(const cocos2d::Vec2 &lhs, const cocos2d::Vec2 &rhs){
    return sqrtf((lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y));
}

#pragma mark - AStar ---------------------------------------------------------------------------------------------------------------------------------------------

int calculateGValue(int column, int row, AStarNode *currentNode);
int calculateHValue(int column, int row, const AStarDataNode &targetNode);

void astarDealNeighborNode(
                           const std::vector<std::vector<AStarDataNode>> &astarData,
                           AStarNode *currentNode,
                           const AStarDataNode &beginNode,
                           const AStarDataNode &targetNode,
                           std::vector<AStarNode *> &openList,
                           const std::vector<AStarNode *> &closeList
                           );

void astar(
           const std::vector<std::vector<AStarDataNode>> &astarData,
           std::vector<AStarNode *> &path,
           const AStarDataNode &beginNode,
           const AStarDataNode &targetNode
           );




#endif /* ToolFunction_*hpp */
