//
//  ToolFunction.cpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/3/21.
//
//

#include "ToolFunction.hpp"

int calculateGValue(int column, int row, AStarNode *currentNode){
    if (column == currentNode->column || row == currentNode->row){
        return 10 + currentNode->GValue;
    }else {
        return 14 + currentNode->GValue;
    }
}

int calculateHValue(int column, int row, const AStarDataNode &targetNode){
    return (abs(column - targetNode.column) + abs(row - targetNode.row)) * 10;
}

void astarDealNeighborNode(
                           const std::vector<std::vector<AStarDataNode>> &astarData,
                           AStarNode *currentNode,
                           const AStarDataNode &beginNode,
                           const AStarDataNode &targetNode,
                           std::vector<AStarNode *> &openList,
                           const std::vector<AStarNode *> &closeList
                           ){
    int maxColmun = static_cast<int>(astarData.size());
    int maxRow = static_cast<int>(astarData[0].size());
    
    for (int column = currentNode->column - 1; column < currentNode->column + 2; ++column){
        for (int row = currentNode->row - 1; row < currentNode->row + 2; ++row){
            
            if (column < 0 || column >= maxColmun || row < 0 || row >= maxRow){
                continue;
            }
            
            if (!astarData[column][row].walkable){
                continue;
            }
            
            bool isInCloseList = false;
            for (auto iter = closeList.begin(); iter != closeList.end(); ++iter){
                if ((*iter)->column == column && (*iter)->row == row){
                    isInCloseList = true;
                    break;
                }
            }
            if (isInCloseList){
                continue;
            }
            
            bool isInOpenList = false;
            AStarNode *nodeInOpenList;
            for (auto iter = openList.begin(); iter != openList.end(); ++iter){
                if ((*iter)->column == column && (*iter)->row == row){
                    isInOpenList = true;
                    nodeInOpenList = (*iter);
                    break;
                }
            }
            
            int GValue = calculateGValue(column, row, currentNode);
            int HValue = calculateHValue(column, row, targetNode);
            int FValue = GValue + HValue;
            
            if (isInOpenList){
                
                if (nodeInOpenList->FValue > FValue){
                    nodeInOpenList->GValue = GValue;
                    nodeInOpenList->HValue = HValue;
                    nodeInOpenList->FValue = FValue;
                    nodeInOpenList->parentNode = currentNode;
                }
                
            }else {
                AStarNode *newNode = new (std::nothrow) AStarNode(column, row, true, FValue, GValue, HValue, currentNode);
                openList.push_back(newNode);
            }
        }
    }
}

void astar(
           const std::vector<std::vector<AStarDataNode>> &astarData,
           std::vector<AStarNode *> &path,
           const AStarDataNode &beginNode,
           const AStarDataNode &targetNode
           ){
    
    std::vector<AStarNode *> openList;
    std::vector<AStarNode *> closeList;
    AStarNode *astarBeginNode = new (std::nothrow) AStarNode(beginNode.column, beginNode.row, beginNode.walkable, 0, 0, 0, nullptr);
    openList.push_back(astarBeginNode);
    
    while (openList.size() != 0){
        
        AStarNode *currentNode = openList[0];
        for (auto iter = openList.begin(); iter != openList.end(); ++iter){
            if ((*iter)->FValue < currentNode->FValue){
                currentNode = (*iter);
            }
        }
        
        for (auto iter = openList.begin(); iter != openList.end(); ++iter){
            if ((*iter)->column == currentNode->column && (*iter)->row == currentNode->row){
                openList.erase(iter);
                break;
            }
        }
        
//        currentNode->print();
        
        if (currentNode->column == targetNode.column && currentNode->row == targetNode.row){
            CCLOG("找到路径了");
            AStarNode *pathNode = currentNode;
            while (pathNode) {
                path.push_back(pathNode);
                pathNode = pathNode->parentNode;
            }
            std::reverse(path.begin(), path.end());
            return;
        }
        
        closeList.push_back(currentNode);
        
        astarDealNeighborNode(astarData, currentNode, beginNode, targetNode, openList, closeList);
        
    }
    
    CCLOG("竟然没找到路径！");
    
}

