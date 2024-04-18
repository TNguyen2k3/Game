#ifndef __AI_PLAYER_SCENE_H__
#define __AI_PLAYER_SCENE_H__

#include "cocos2d.h"

class AIPlayerScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(AIPlayerScene);

private:
    // Add any necessary variables or methods for AI player mode
};

#endif // __AI_PLAYER_SCENE_H__