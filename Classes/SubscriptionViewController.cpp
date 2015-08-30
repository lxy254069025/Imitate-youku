//
//  SubscriptionViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#include "SubscriptionViewController.h"

SubscriptionViewController::SubscriptionViewController() {
    
}


SubscriptionViewController::~SubscriptionViewController() {
    
}


void SubscriptionViewController::viewDidLoad() {
    winSize = this->getView()->getBounds().size;
    this->getView()->setColor(CAColor_gray);
    
    this->loadNavigationItem();
    
    this->loadWeb();
}

void SubscriptionViewController::viewDidUnload() {
    
}

void SubscriptionViewController::loadNavigationItem() {
    CAView *view = CAView::createWithFrame(CADipRect(0,0,winSize.width,130));
    view->setColor(ccc4(248, 248, 248, 255));
    this->getView()->addSubview(view);
    
    CADipSize viewSize = view->getBounds().size;
    
    CALabel *title = CALabel::createWithCenter(CADipRect(viewSize.width / 2, viewSize.height / 2 + 15,100,viewSize.height - 10));
    title->setText(UTF8("订阅"));
    title->setFontSize(_px(38));
    title->setTextAlignment(CATextAlignmentCenter);
    title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    title->setColor(CAColor_black);
    view->addSubview(title);
    
}

void SubscriptionViewController::loadWeb() {
    
    CAWebView *web = CAWebView::createWithFrame(CADipRect(0,130.5,winSize.width,winSize.height-130));
    web->loadURL("http://i.youku.com/u/subscribeUpdate");
    this->getView()->addSubview(web);
}

