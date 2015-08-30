//
//  ChannelCollectionView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/31.
//
//

#include "ChannelCollectionView.h"
#include <math.h>

ChannelCollectionView::ChannelCollectionView() {
    
}
ChannelCollectionView::~ChannelCollectionView() {
    
}

ChannelCollectionView* ChannelCollectionView::createWithFrame(const CADipRect& _ret) {
    ChannelCollectionView *view = new ChannelCollectionView();
    if (view && view->init(_ret)) {
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}

bool ChannelCollectionView::init(const CADipRect& _ret) {
    if (!CAView::init()) {
        return false;
    }
    
    this->setFrame(_ret);
    winSize = this->getBounds().size;
    
    this->parseJson();
    
    
    return true;
}


void ChannelCollectionView::parseJson() {
    std::string json_file = CCFileUtils::sharedFileUtils()->fullPathForFilename("r/icon/IconJson.json");
    CCString *jsonData = CCString::createWithContentsOfFile(json_file.c_str());
    
    CSJson::Reader reader;
    if (reader.parse(jsonData->getCString(), m_value)) {
        //OK
        this->loadCollectionView();
    } else {
        //初始化失败。
    }
}

void ChannelCollectionView::loadCollectionView() {
    m_collection = CACollectionView::createWithFrame(CADipRect(0,0,winSize.width,winSize.height));
    m_collection->setCollectionViewDataSource(this);
    m_collection->setCollectionViewDelegate(this);
    m_collection->setAllowsSelection(true);
    m_collection->setAllowsMultipleSelection(false);
    m_collection->setAlwaysTopSectionHeader(false);
    this->addSubview(m_collection);
} 

//Necessary
CACollectionViewCell* ChannelCollectionView::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item) {
    CACollectionViewCell *cell = collectionView->dequeueReusableCellWithIdentifier("channel");
    char classify[10];
    int index = row * 4 + item;
    sprintf(classify, "classify%d",section + 1);
    CSJson::Value currValue = m_value[classify][index];
    CCLog("-- %d",index);
    if (cell == NULL) {
        cell = CACollectionViewCell::create("channel");
        
        CAImageView *imageView = CAImageView::createWithFrame(CADipRect(30,50,84,60));
        imageView->setImageViewScaleType(CAImageViewScaleTypeFitImageInside);
        imageView->setTag(100);
        cell->addSubview(imageView);
        CALabel *title = CALabel::createWithFrame(CADipRect(30,130,84,32));
        
        title->setFontSize(_px(28));
        title->setColor(ccc4(144, 144, 144, 255));
        title->setTextAlignment(CATextAlignmentCenter);
        title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        title->setTag(101);
        cell->addSubview(title);
    }
    
    CAImageView *imageView = (CAImageView*)cell->getSubviewByTag(100);
    imageView->setImage(CAImage::create(currValue["img"].asString()));
    
    CALabel *title = (CALabel*)cell->getSubviewByTag(101);
    title->setText(currValue["title"].asString());
    return cell;
}

//Necessary
unsigned int ChannelCollectionView::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row) {
    return _px(190);
}

//Necessary
unsigned int ChannelCollectionView::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row) {
    return 4;
}

//Necessary
unsigned int ChannelCollectionView::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section) {
    char classify[10];
    
    sprintf(classify, "classify%d",section + 1);
    CSJson::Value currValue = m_value[classify];
    long _size = ceil(currValue.size() / 4.f);
    return _size;
}

unsigned int ChannelCollectionView::numberOfSections(CACollectionView *collectionView) {
    return 2;
}

CAView* ChannelCollectionView::collectionViewSectionViewForHeaderInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section) {
    if (section == 0) {
        return NULL;
    }
    
    CAView *view = CAView::createWithFrame(CADipRect(0,0,viewSize.width,viewSize.height));
    
    CAView *topView = CAView::createWithFrame(CADipRect(0,0,viewSize.width,13),ccc4(216,216,216, 255));
    view->addSubview(topView);
    
    CALabel *title = CALabel::createWithCenter(CADipRect(viewSize.width / 2,(viewSize.height + 20) / 2,viewSize.width,viewSize.height - 10));
    title->setTextAlignment(CATextAlignmentCenter);
    title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    title->setText("仿优酷频道");
    title->setColor(ccc4(144, 144, 144, 255));
    title->setFontSize(_px(32));
    view->addSubview(title);
    
    CAView *line = CAView::createWithFrame(CADipRect(0,viewSize.height - 1,viewSize.width,1),ccc4(216,216,216, 255));
    view->addSubview(line);
    return view;
}

unsigned int ChannelCollectionView::collectionViewHeightForHeaderInSection(CACollectionView *collectionView, unsigned int section) {
    if (section == 0) {
        return 0;
    }
    return _px(110);
}

void ChannelCollectionView::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
}

void ChannelCollectionView::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
}











