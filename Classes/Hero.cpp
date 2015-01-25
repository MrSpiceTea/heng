//
//  Hero.cpp
//  hengDemo
//
//  Created by Zhantu Xie on 15/1/19.
//
//

#include "Hero.h"

USING_NS_CC;

Hero::Hero(void){
    IsRunning=false;
    IsJunping=false;
    HeroDirecton=false;//right
    hero_img_name=NULL;
    IsRight=true;
}
Hero::~Hero(void)
{
    
}
void Hero::InitHeroSprite(char *img_name){
    herosprite=Sprite::create(img_name);
    hero_img_name=img_name;
    this->addChild(herosprite);
}
void Hero::SetAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_directon){
    if(HeroDirecton!=run_directon)
    {   HeroDirecton=run_directon;
        herosprite->setFlippedX(run_directon);
    }
    if (IsRunning) {
        SpriteFrameCache *frameCache=SpriteFrameCache::getInstance();
        frameCache->addSpriteFramesWithFile(name_plist,name_png);
//        CCArray* frameArray= CCArray::createWithCapacity(num);
        Vector<SpriteFrame*> frameArray(num);
        unsigned int i;
        for (i=1;i<=num;i++) {
//            SpriteFrame* frame=frameCache->spriteFrameByName(CCString::createWithFormat("%s%d.png",name_each,i)->getCString());
            SpriteFrame *frame=frameCache->getSpriteFrameByName(CCString::createWithFormat("%s%d.png",name_each,i)->getCString());
           
            frameArray.pushBack(frame);
        }
        
        //使用SpriteFrame列表创建动画对象
        auto animation=Animation::createWithSpriteFrames(frameArray);
        animation->setLoops(-1);//一直
        animation->setDelayPerUnit(0.1f);//两张图片替换间隔
        
        //封装成一个动作
        auto action=Animate::create(animation);
        
        herosprite->runAction(action);
        IsRunning=true;
    }
}
void Hero::StopAnimation(){
    if (!IsRunning||IsJunping) return;
    herosprite->stopAllActions();//停止所有动画
    
    //恢复原来贴图
//    this->removeChild(herosprite,true);//把原来的精灵删除掉
//    herosprite=CCSprite::create(hero_img_name);//恢复精灵原来的贴图样子
//    herosprite->setFlippedX(HeroDirecton);
//    this->addChild(herosprite);
    //直接修改贴图
    herosprite->setTexture(hero_img_name);
    IsRunning=false;
    IsJunping=false;

    
    
}
void Hero::walkto(cocos2d::Vec2 dest){
    auto pos=herosprite->getPosition();

    if (dest.x>110&&dest.x<230&&dest.y<100) {
        IsRight=false;
        IsRunning=true;
        SetAnimation("taigelist.plist", "taigelist.png","taga",8,false);
        pos.x+=1000;
        auto move=MoveTo::create(3, pos);
        herosprite->runAction(move);
    }else if(dest.x<110&&dest.y<100){
         IsRight=true;
        IsRunning=true;
        SetAnimation("taigelist.plist", "taigelist.png","taga",8,true);
        pos.x-=1000;
        auto move=MoveTo::create(3, pos);
        herosprite->runAction(move);
    }else if(dest.x>600&&dest.y<100){
        IsRunning=true;
        if (!IsJunping) {
            IsJunping=true;
            if (IsRight) {
                 SetAnimation("taigajumplist.plist", "taigajumplist.png","taigajump",6,true);
            }else{
                 SetAnimation("taigajumplist.plist", "taigajumplist.png","taigajump",6,false);
            }
           
            auto jump=JumpTo::create(0.5,pos, 100, 1);
            auto func=[&](){
                IsJunping=false;
                this->StopAnimation();
            };
            auto callback=CallFunc::create(func);
            Sequence *seq=Sequence::create(jump, callback, nullptr);
            herosprite->runAction(seq);
        }
        
    }
  
    
//    auto move=MoveTo::create(1, dest);
//    //定义回调,结束停止人物动画
//    auto func=[&](){
////        log("stop");
//    };
//    auto callback=CallFunc::create(func);
//    Sequence *seq=Sequence::create(move, callback, nullptr);
//    herosprite->runAction(seq);
    
}