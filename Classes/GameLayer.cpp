//
//  GameLayer.cpp
//  hengDemo
//
//  Created by sanarara on 15-1-24.
//
//

#include "GameLayer.h"
USING_NS_CC;

bool GameLayer::init(){
    
    _map=TMXTiledMap::create("test.tmx");
    addChild(_map);

    return true;
}