//
//  GameLayer.h
//  hengDemo
//
//  Created by sanarara on 15-1-24.
//
//

#ifndef __hengDemo__GameLayer__
#define __hengDemo__GameLayer__

#include "cocos2d.h"

class GameLayer:public cocos2d::Layer{
public:
    GameLayer(void);
    ~GameLayer(void);
    
    virtual bool init();
    
protected:
    cocos2d::TMXTiledMap *_map;
    
private:
    
    
};

#endif /* defined(__hengDemo__GameLayer__) */
