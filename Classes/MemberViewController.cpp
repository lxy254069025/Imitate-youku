//
//  MemberViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#include "MemberViewController.h"

MemberViewController::MemberViewController() {
    
}

MemberViewController::~MemberViewController() {
    
    
}

void MemberViewController::viewDidLoad() {
    winSize = this->getView()->getBounds().size;
    
    this->getView()->setColor(CAColor_gray);
    this->loadNavigationItem();
}


void MemberViewController::viewDidUnload() {
    
}


void MemberViewController::loadNavigationItem() {
    CAView *view = CAView::createWithFrame(CADipRect(0,0,winSize.width,130));
    view->setColor(ccc4(248, 248, 248, 255));
    this->getView()->addSubview(view);
    
    CAView *btnView = CAView::createWithFrame(CCRect(0,0,(40),(30)), CAColor_clear);
    CAImageView *fanhui = CAImageView::createWithFrame(CCRect(20,12,_px(23),_px(35)));
    fanhui->setImage(CAImage::create("r/fanhui.png"));
    btnView->addSubview(fanhui);
    
    CAButton *btnfangui = CAButton::createWithFrame(CADipRect(20,60,80,50), CAButtonTypeCustom);
    btnfangui->setBackGroundViewForState(CAControlStateAll, btnView);
    btnfangui->addTarget(this, CAControl_selector(MemberViewController::onBtnFanhui), CAControlEventTouchDown);
    view->addSubview(btnfangui);
    
    CALabel *title = CALabel::createWithCenter(CADipRect(winSize.width / 1.89,130 / 2 + 70 / 2 ,winSize.width/4,70));
    title->setFontSize(_px(40));
    title->setText(UTF8("优酷会员"));
    view->addSubview(title);
    
    CAView *line = CAView::createWithFrame(CADipRect(0,130,winSize.width,1),CAColor_gray);
    this->getView()->addSubview(line);
    
}

void MemberViewController::onBtnFanhui(CAControl *btn,CCPoint point) {
    this->getNavigationController()->dismissModalViewController(true);
}