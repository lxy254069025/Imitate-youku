//
//  ChannelDropDownView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/9/1.
//
//

#include "ChannelDropDownView.h"
#include <math.h>

ChannelDropDownViewCell::ChannelDropDownViewCell():m_title(NULL) {
    
}
ChannelDropDownViewCell::~ChannelDropDownViewCell() {
    
}

ChannelDropDownViewCell* ChannelDropDownViewCell::create(const std::string& identifier, const CADipRect& _rect) {
    ChannelDropDownViewCell *cell = new ChannelDropDownViewCell();
    
    if (cell && cell->init(identifier,_rect)) {
        cell->autorelease();
        
        return cell;
    }
    
    delete cell;
    cell = NULL;
    return NULL;
}

bool ChannelDropDownViewCell::init(const std::string& identifier, const CADipRect& _rect) {
    if (!CACollectionViewCell::initWithReuseIdentifier(identifier)) {
        return false;
    }
    
    this->setFrame(_rect);
    
    m_winSize = this->getBounds().size;
    
    m_title = CALabel::createWithFrame(CADipRect(0,0,m_winSize.width,m_winSize.height));
    m_title->setTextAlignment(CATextAlignmentCenter);
    m_title->setTag(100);
    m_title->setFontSize(_px(30));
    m_title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    
    this->addSubview(m_title);
    return true;
}

void ChannelDropDownViewCell::normalCollectionViewCell() {
    CC_RETURN_IF(m_title == NULL);
    m_title->setColor(CAColor_black);
}

void ChannelDropDownViewCell::highlightedCollectionViewCell() {
    this->setBackgroundView(CAView::createWithColor(CAColor_white));
    
    
    
}

void ChannelDropDownViewCell::selectedCollectionViewCell() {
    m_title->setColor(CAColor_green);
}

void ChannelDropDownViewCell::disabledTableViewCell() {
    CCLog("取消选择");
}

void ChannelDropDownViewCell::setModel(CSJson::Value value,int default_id) {
    m_title->setText(value["title"].asString());
    
    if (default_id == 0 && value["title"].asString() == "全部") {
        m_title->setColor(CAColor_green);
    } else if (value["id"].asInt() == default_id) {
        m_title->setColor(CAColor_green);
    }
}


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
    this->setColor(CAColor_clear);
    winSize = this->getBounds().size;
    
    //this->loadCollectionView();
    return true;
}

// 0是全部
void ChannelDropDownView::setDefaultChannel(int default_id) {
    m_DefaultId = default_id;
}

void ChannelDropDownView::setCallBack(CAObject *target, Channel_Control selector) {
    m_target = target;
    m_selector = selector;
}


void ChannelDropDownView::loadCollectionView() {
    CACollectionView *collectView = CACollectionView::createWithFrame(CADipRect(0,0,winSize.width,(int)ceil(m__size / 4.f) * 100));
    collectView->setTag(1);
    collectView->setBackGroundColor(ccc4(248, 248, 248, 255));
    collectView->setScrollEnabled(false);
    collectView->setCollectionViewDataSource(this);
    collectView->setCollectionViewDelegate(this);
    collectView->setHoriInterval(_px(1));
    collectView->setVertInterval(_px(1));
    collectView->setAllowsSelection(true);
    this->addSubview(collectView);
    
    CCLog("--- %d",(int)ceil(m__size / 4.0f));
}

CACollectionViewCell* ChannelDropDownView::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item) {
    ChannelDropDownViewCell *cell = (ChannelDropDownViewCell*)collectionView->dequeueReusableCellWithIdentifier("ChanelDropDown");
    int index = row * 4 + item;
    CSJson::Value currValue;
    
    if (index < 8) {
        currValue = m_value["classify1"][index];
    } else {
        currValue = m_value["classify2"][index - 8];
    }
    
    if (cell == NULL) {
        cell = ChannelDropDownViewCell::create("ChanelDropDown",CADipRect(0,0,cellSize.width,cellSize.height));
        
//        CAView *view = CAView::createWithFrame(CADipRect(0,0,cellSize.width,cellSize.height),CAColor_white);
//        view->setTag(99);
//        CALabel *la = CALabel::createWithFrame(CADipRect(0,0,cellSize.width,cellSize.height));
//        la->setTextAlignment(CATextAlignmentCenter);
//        la->setTag(100);
//        la->setFontSize(_px(30));
//        la->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//        view->addSubview(la);
//        cell->addSubview(view);
        
    }
    cell->setModel(currValue,m_DefaultId);
    
    //CALabel *la = (CALabel*)cell->getSubviewByTag(99)->getSubviewByTag(100);
//    if (m_DefaultId == 0 && currValue["title"].asString() == "全部") {
//        cell->setModel(currValue);
//    } else if (m_DefaultId == currValue["id"].asInt()) {
//        cell->setModel(currValue);
//    }
    
    //la->setText(currValue["title"].asString());
    
    return cell;
}

//Necessary
unsigned int ChannelDropDownView::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row) {
    return _px(100);
}

//Necessary
unsigned int ChannelDropDownView::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row) {
    return 4;
}


//Necessary
unsigned int ChannelDropDownView::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section) {
    
    return (int)ceil(m__size / 4.f);
}

void ChannelDropDownView::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
    int index = row * 4 + item;
    CSJson::Value currValue;
    
    if (index < 8) {
        currValue = m_value["classify1"][index];
    } else {
        currValue = m_value["classify2"][index - 8];
    }
    
    
    (m_target->*m_selector)(currValue["title"].asString(),currValue["id"].asInt());
}

void ChannelDropDownView::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
}




