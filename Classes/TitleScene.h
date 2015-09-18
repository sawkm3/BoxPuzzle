#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
private:
	cocos2d::LabelTTF* _label;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Title);
};

#endif // INCLUDED_TITLE_SCENE_H