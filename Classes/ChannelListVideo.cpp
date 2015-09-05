//
//  ChannelListVideo.cpp
//  youku
//
//  Created by 卢喜羲 on 15/9/5.
//
//

#include "ChannelListVideo.h"
#include "ChannelListVideoCell.h"

ChannelListVideo::ChannelListVideo() {
    
}

ChannelListVideo::~ChannelListVideo() {
    
}

ChannelListVideo* ChannelListVideo::createWithFrame(const CADipRect& _rect) {
    ChannelListVideo *view = new ChannelListVideo();
    
    if (view && view->init()) {
        view->setFrame(_rect);
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}

void ChannelListVideo::initListVideo(int channel_id) {
    m_channel_id = channel_id;
    
    CACollectionView *collect = CACollectionView::createWithFrame(this->getBounds());
    collect->setCollectionViewDataSource(this);
    collect->setCollectionViewDelegate(this);
    collect->setAllowsSelection(true);
    collect->setAllowsMultipleSelection(false);
    
    this->addSubview(collect);
}

void ChannelListVideo::initListView(CSJson::Value value) {
    m_value = value;
    CADipSize winSize = this->getBounds().size;
    
    CAListView *listView = CAListView::createWithFrame(CADipRect(0,0,winSize.width,80));
    listView->setListViewDataSource(this);
    listView->setListViewDelegate(this);
    listView->setAllowsSelection(true);
    listView->setListViewOrientation(CAListViewOrientationHorizontal);
    listView->setShowsScrollIndicators(false);
    listView->setSeparatorColor(CAColor_clear);
    listView->setScrollEnabled(true);
    this->addSubview(listView);
    
}

//-----------------------------------------------listView------------------------------------------------------------
unsigned int ChannelListVideo::numberOfIndex(CAListView *listView) {
    return 20;
}

unsigned int ChannelListVideo::listViewHeightForIndex(CAListView *listView, unsigned int index) {
    return _px(150);
}

CAListViewCell* ChannelListVideo::listViewCellAtIndex(CAListView *listView, const CCSize& cellSize, unsigned int index) {
    ChannelListVideoCell *cell = (ChannelListVideoCell*)listView->dequeueReusableCellWithIdentifier("listView");
    if (cell == NULL) {
        cell = ChannelListVideoCell::create("listView",CADipRect(0,0,cellSize.width,cellSize.height));
        cell->initCell();
        
        listView->setSelectAtIndex(0);
    }
    
    cell->setModel(m_value[index]);
    
    CCLog("listView");
    return cell;
}



//---------------------------------------------collectionView---------------------------------------------------------
CACollectionViewCell* ChannelListVideo::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item) {
    CACollectionViewCell *cell = collectionView->dequeueReusableCellWithIdentifier("channelListView");
    if (cell == NULL) {
        cell = CACollectionViewCell::create("channelListView");
        CALabel *la = CALabel::createWithFrame(CADipRect(0,0,cellSize.width,cellSize.height));
        
        la->setText("sadfasfdsdf");
        cell->addSubview(la);
        
        
        
    }
    
    
    return cell;
}

//Necessary
unsigned int ChannelListVideo::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row) {
    return _px(200);
}

//Necessary
unsigned int ChannelListVideo::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row) {
    return 3;
}

//Necessary
unsigned int ChannelListVideo::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section) {
    return 10;
}

void ChannelListVideo::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
}

void ChannelListVideo::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
}

