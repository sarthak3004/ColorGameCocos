//
//  GameOverScene.hpp
//  ColorGame-mobile
//
//  Created by SarthakR on 21/02/23.
//

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <ui/CocosGUI.h>

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(GameOver);

    cocos2d::Size visibleSize;
};
#endif /* GameOverScene_hpp */
