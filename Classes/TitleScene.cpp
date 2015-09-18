#include "TitleScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Title::createScene() {
	auto scene = Scene::create();
	auto layer = Title::create();
	scene->addChild(layer);
	return scene;
}

bool Title::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �w�i�F�ݒ�
	auto layer2 = LayerColor::create(Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height);
	layer2->ignoreAnchorPointForPosition(false);
	layer2->setTouchEnabled(false);
	layer2->setAnchorPoint(Vec2(0.5f, 0.5f));
	layer2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(layer2);

	auto layer = LayerColor::create(Color4B(51, 75, 112, 255), visibleSize.width * 0.8, visibleSize.height * 0.8);
	layer->ignoreAnchorPointForPosition(false);
	layer->setTouchEnabled(false);
	layer->setAnchorPoint(Vec2(0.5f, 0.5f));
	layer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(layer);

	// Enter
	auto enterLabel = LabelTTF::create("Enter", "Arial", 40);
	enterLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	enterLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));
	this->addChild(enterLabel);

	// �A�N�V�����쐬
//	Vector<cocos2d::FiniteTimeAction*> actions;
//	actions.pushBack(RotateBy::create(1, 10));
////	auto sequence = Sequence::create(actions);
//	auto repeat1 = Repeat::create(actions);
//	enterLabel->runAction(sequence);

	// �W�����v�̃A�N�V����
	auto jumpAction = JumpBy::create(2, Vec2(0, 0), 10, 1);
	// �傫���ω�
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions1;
	actions1.pushBack(cocos2d::ScaleBy::create(1, 1.2));
	actions1.pushBack(cocos2d::ScaleBy::create(1, 0.8));
	auto sequence1 = cocos2d::Sequence::create(actions1);

	// �F�ω�
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::TintTo::create(1, 255, 150, 150));
	actions.pushBack(cocos2d::TintTo::create(1, 255, 255, 255));
	auto sequence = cocos2d::Sequence::create(actions);

	//�A�N�V�������쐬
	auto spawn = Spawn::create(jumpAction, sequence1, sequence, NULL);

	//���s�[�g
	auto repeatForever = RepeatForever::create(spawn);

	//�J�n�I
	enterLabel->runAction(repeatForever);

	// ���X�i�[�쐬
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		// �Փ˔���
		Point p = touch->getLocation();
		Rect r = enterLabel->boundingBox();
		if (r.containsPoint(p))
		{
			auto transition = TransitionFadeUp::create(1.0f, HelloWorld::createScene());
			Director::getInstance()->replaceScene(transition);
		}
		return true;
	};

	// ���X�i�[�ǉ�
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ���x���ǉ�
	auto label = LabelTTF::create("BoxPazzle", "Arial", 40);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1.5f / 2));
	this->addChild(label);

	return true;
}