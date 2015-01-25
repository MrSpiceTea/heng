//
//  Hero.h
//  hengDemo
//
//  Created by Zhantu Xie on 15/1/19.
//
//

#include "cocos2d.h"
#include "cocos-ext.h"

class Hero:public cocos2d::Node {
    
public:
    Hero(void);
    ~Hero(void);
    //图片加载
    void InitHeroSprite(char *img_name);
    bool IsRunning;
    bool IsJunping;
    bool IsRight;
    //运动的方向
    bool HeroDirecton;
    void SetAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,bool run_directon);
    void StopAnimation();
    void walkto(cocos2d::Vec2 dest);
    CREATE_FUNC(Hero);
private:
    cocos2d::Sprite *herosprite;
    char *hero_img_name;
};