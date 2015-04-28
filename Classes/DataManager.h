//
//  DataManager.h
//  BreakOut
//
//  Created by Yanxu Zheng on 27/04/2015.
//
//

#ifndef __BreakOut__DataManager__
#define __BreakOut__DataManager__

#include <stdio.h>
#include "BrickBase.h"
USING_NS_CC;

class DataManager
{
public:
    CC_SYNTHESIZE(int, score, Score);
//    CC_SYNTHESIZE(int, highestScore, HighestScore);
    
    Vector<BrickBase*> brickVector;

    DataManager();
    
    static DataManager* getInstance();
    
    void clear();

    
private:
    static DataManager* instance;
    
};

#endif /* defined(__BreakOut__DataManager__) */
