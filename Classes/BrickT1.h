//
//  BrickT1.h
//  BreakOut
//
//  Created by Yanxu Zheng on 20/04/2015.
//
//

#ifndef __BreakOut__BrickT1__
#define __BreakOut__BrickT1__

#include <stdio.h>

#include "BrickBase.h"

class BrickT1 : public BrickBase
{
public:
    BrickT1();
    
    static BrickT1* create();
};

#endif /* defined(__BreakOut__BrickT1__) */
