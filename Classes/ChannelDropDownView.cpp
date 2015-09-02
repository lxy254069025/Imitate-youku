//
//  ChannelDropDownView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/9/1.
//
//

#include "ChannelDropDownView.h"

ChannelDropDownView::ChannelDropDownView() {
    
}



ChannelDropDownView::~ChannelDropDownView() {
    
}

ChannelDropDownView* ChannelDropDownView::createWithFrame(const CADipRect& _rect) {
    ChannelDropDownView *view = new ChannelDropDownView();
    if (view && view->init(_rect)) {
        view->autorelease();
        
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
    
}


bool ChannelDropDownView::init(const CADipRect& _rect) {
    if (!CAView::init()) {
        return false;
    }
    
    this->setFrame(_rect);
    this->setColor(CAColor_green);
    return true;
}

// 0是全部
void ChannelDropDownView::setDefaultChannel(int default_id) {
    
}

void ChannelDropDownView::loadCollectionView() {
    CACollectionView *collectView = CACollectionView::createWithFrame(CADipRect(0,0,winSize.width,winSize.height));
    collectView->setTag(1);
    this->addSubview(collectView);
    
    
}




