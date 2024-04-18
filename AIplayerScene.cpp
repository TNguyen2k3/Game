// AIPlayerScene.cpp
#include "AIPlayerScene.h"

USING_NS_CC;

Scene* AIPlayerScene::createScene()
{
    return AIPlayerScene::create();
}

bool AIPlayerScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Add your initialization code for AI player mode here

    return true;
}