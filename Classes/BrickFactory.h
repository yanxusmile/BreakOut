//
//  BrickFactory.h
//  BreakOut
//
//  Created by Yanxu Zheng on 20/04/2015.
//
//

#ifndef __BreakOut__BrickFactory__
#define __BreakOut__BrickFactory__

#include <stdio.h>
#include "BrickT1.h"


class BrickFactory : public Layer
{
public:
    BrickFactory(Layer* gameLayer);
    
    static BrickFactory* create(Layer* gameLayer);
    
    BrickBase* createBrick(int brickTier);
    
    Vector <BrickBase*> bricks;
    Layer *gameLayer;
};
#endif /* defined(__BreakOut__BrickFactory__) */
