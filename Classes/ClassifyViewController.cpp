//
//  ClassifyViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#include "ClassifyViewController.h"
#include "ChannelCollectionView.h"

ClassifyViewController::ClassifyViewController() {
    
}


ClassifyViewController::~ClassifyViewController() {
    
}

void ClassifyViewController::viewDidLoad() {
    winSize = this->getView()->getBounds().size;
    this->getView()->setColor(CAColor_white);
    this->loadNavigationItem();
    
    ChannelCollectionView *channel = ChannelCollectionView::createWithFrame(CADipRect(0,130,winSize.width,winSize.height-130));
    
    this->getView()->addSubview(channel);
}


void ClassifyViewController::viewDidUnload() {
    
}


void ClassifyViewController::loadNavigationItem() {
    CAView *view = CAView::createWithFrame(CADipRect(0,0,winSize.width,130));
    view->setColor(ccc4(248, 248, 248, 255));
    this->getView()->addSubview(view);
    
    CADipSize viewSize = view->getBounds().size;
    
    CALabel *title = CALabel::createWithCenter(CADipRect(viewSize.width / 2, viewSize.height / 2 + 15,100,viewSize.height - 10));
    title->setText(UTF8("频道"));
    title->setFontSize(_px(38));
    title->setTextAlignment(CATextAlignmentCenter);
    title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    title->setColor(CAColor_black);
    view->addSubview(title);
    
    CAButton *search = CAButton::create(CAButtonTypeCustom);
    search->setImageForState(CAControlStateNormal,CAImage::create("r/btn_search.png"));
    search->setCenter(CADipRect(winSize.width - 80 * 2,viewSize.height / 2 + 15,80,70));
    search->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_search_selected.png"));
    //search->addTarget(this, CAControl_selector(IndexViewController::onButtonSearch), CAControlEventTouchUpInSide);
    view->addSubview(search);
    
    CAButton *record = CAButton::create(CAButtonTypeCustom);
    record->setImageForState(CAControlStateNormal, CAImage::create("r/myyouku_history.png"));
    record->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_history_selected.png"));
    record->setCenter(CADipRect(winSize.width - 50,viewSize.height / 2 + 15,60,55));
    //record->addTarget(this, CAControl_selector(IndexViewController::onButtonRecord), CAControlEventTouchUpInSide);
    view->addSubview(record);
    
    CAView *line = CAView::createWithFrame(CADipRect(0,viewSize.height - 1,viewSize.width,1),CAColor_gray);
    view->addSubview(line);
    
}