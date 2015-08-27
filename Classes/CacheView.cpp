//
//  CacheView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#include "CacheView.h"

CacheView::CacheView() {
    
}

CacheView::~CacheView() {
    
}

CacheView* CacheView::create(CADipRect _ret) {
    CacheView *view = new CacheView();
    if (view->init(_ret)) {
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}

bool CacheView::init(CADipRect _ret) {
    if (!CAView::init()) {
        return false;
    }
    
    this->setFrame(_ret);
    this->setColor(CAColor_clear);
    
    CADipSize winSize = this->getBounds().size;
    CCLog("cacheView%f",winSize.height);
    CAView *cacheView = CAView::createWithFrame(CADipRect(winSize.width - 230,0,230,80),CAColor_white);
    this->addSubview(cacheView);
    
    cache1 = CAButton::create(CAButtonTypeCustom);
    cache1->setImageForState(CAControlStateNormal, CAImage::create("r/btn_downloading.png"));
    cache1->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_downloading_selected.png"));
    cache1->setFrame(CADipRect(50,0 + 10 / 2,80,70));
    cache1->setZOrder(100);
    //cache1->addTarget(this, CAControl_selector(FirstViewController::onButtonCache), CAControlEventTouchUpInSide);
    cacheView->addSubview(cache1);
    
    cache2 = CAButton::create(CAButtonTypeCustom);
    cache2->setTitleForState(CAControlStateAll, UTF8("缓存"));
    cache2->setTitleColorForState(CAControlStateAll, CAColor_gray);
    //cache2->addTarget(this, CAControl_selector(FirstViewController::onButtonCache), CAControlEventTouchUpInSide);
    cache2->setFrame(CADipRect(120,0 + 10 / 2,80,70));
    cacheView->addSubview(cache2);
    
    return true;
}

void CacheView::addCacheTarget(CAObject *target, SEL_CAControl selector, CAControlEvents event){
    cache1->addTarget(target, selector, event);
    cache2->addTarget(target, selector, event);
}

bool CacheView::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent) {
    CCLog("开始摸了");
    if (this->isVisible()) {
        this->setVisible(false);
    }
    
    return true;
}

void CacheView::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent) {
    CCLog("移动了");
    
}

void CacheView::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent) {
    CCLog("把手松开了");
    
}



