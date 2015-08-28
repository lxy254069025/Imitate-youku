//
//  FirstCollectionHeaderView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/29.
//
//

#include "FirstCollectionHeaderView.h"

FirstCollectionHeaderView::FirstCollectionHeaderView() {
    
}

FirstCollectionHeaderView::~FirstCollectionHeaderView() {
    
}

FirstCollectionHeaderView* FirstCollectionHeaderView::createWithFrame(const CADipRect& _ret) {
    FirstCollectionHeaderView *view = new FirstCollectionHeaderView();
    if (view && view->init(_ret)) {
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
    
}

bool FirstCollectionHeaderView::init(const CADipRect& _ret) {
    if (!CAView::init()) {
        return false;
    }
    this->setFrame(_ret);
    
    winSize = this->getBounds().size;
    
    CAView *topView = CAView::createWithFrame(CADipRect(0,0,winSize.width,winSize.height),CAColor_white);
    
    CAImageView *imageView = CAImageView::createWithFrame(CADipRect(20,(winSize.height - 15) / 2 - 38 / 2,38,38));
    imageView->setImage(CAImage::create("r/home_subscribe_icon.png"));
    topView->addSubview(imageView);
    
    CALabel *content = CALabel::createWithFrame(CADipRect(70,(winSize.height - 15) / 2 - 38 / 2,winSize.width / 1.5,38));
    content->setText(UTF8("戳一下，你喜欢看的都在这里了"));
    content->setFontSize(_px(28));
    content->setTextAlignment(CATextAlignmentLeft);
    content->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    topView->addSubview(content);
    
    //home_notice_right_arrow.png
    CAImageView *right = CAImageView::createWithFrame(CADipRect(winSize.width - 30,(winSize.height - 15) / 2 - 19 / 2,11, 19));
    right->setImage(CAImage::create("r/home_notice_right_arrow.png"));
    topView->addSubview(right);
    
    CAButton *topBtn = CAButton::create(CAButtonTypeCustom);
    topBtn->setFrame(CADipRect(0,0,winSize.width,winSize.height));
    topBtn->setBackGroundViewForState(CAControlStateAll, topView);
    topBtn->addTarget(this, CAControl_selector(FirstCollectionHeaderView::onTopHeaderClick), CAControlEventTouchUpInSide);
    this->addSubview(topBtn);
    
    CAView *belowView = CAView::createWithFrame(CADipRect(0,winSize.height - 15,winSize.width,15),ccc4(216,216,216, 255));
    this->addSubview(belowView);
    return true;
}

void FirstCollectionHeaderView::onTopHeaderClick(CAControl *btn,CCPoint point) {
    RootWindow::create()->getTabBarController()->showSelectedViewControllerAtIndex(2);
}