//
//  RecommendView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#include "RecommendView.h"
#include "VideoPlayViewController.h"


RecommendView::RecommendView() {
    
}

RecommendView::~RecommendView() {
    
}

RecommendView* RecommendView::create(const CADipRect& _ret) {
    RecommendView *recommend = new RecommendView();
    if (recommend && recommend->init(_ret)) {
        recommend->autorelease();
        return recommend;
    }
    
    delete recommend;
    recommend = NULL;
    return NULL;
}

bool RecommendView::init(const CADipRect& _ret) {
    if (!CAView::init()) {
        return false;
    }
    this->setFrame(_ret);
    winSize = this->getBounds().size;
    
    return true;
}

void RecommendView::setlistSize(const int listSize) {
    m_listSize = (listSize % 2) != 0?((listSize-1) / 2):(listSize / 2);
}

void RecommendView::setListData(const CSJson::Value& listData) {
    m_listData = listData;
}

void RecommendView::initCollection() {
    
    m_collection = CACollectionView::createWithFrame(this->getBounds());
    m_collection->setAllowsSelection(true);
    m_collection->setCollectionViewDataSource(this);
    m_collection->setCollectionViewDelegate(this);
    m_collection->setScrollEnabled(false);
    
    this->addSubview(m_collection);
}

//Necessary
CACollectionViewCell* RecommendView::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item) {
    
    int index = row * 2 + item;
    
    CADipSize _size = cellSize;
    //根据标识获得CACollectionViewCell
    CACollectionViewCell* p_Cell = collectionView->dequeueReusableCellWithIdentifier("homelistdata");
    //如果没有找到相应的CACollectionViewCell则新建一个
    if (p_Cell == NULL)
    {
        p_Cell = CACollectionViewCell::create("homelistdata");
        //生成Item背景
        CAView* view = CAView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
        view->setTag(99);
        p_Cell->addSubview(view);
        
        CADipSize itemSize = view->getBounds().size;
        
        CAImageView *imageView = CAImageView::create();
        imageView->setFrame(CADipRect(0,0,itemSize.width,itemSize.height - 100));
        imageView->setTag(101);
        view->addSubview(imageView);
        //生成itemCALabel
        CALabel* itemText = CALabel::createWithFrame(CADipRect(20, itemSize.height - 95, itemSize.width, 40));
        itemText->setTag(100);
        itemText->setFontSize(_px(28));
        itemText->setTextAlignment(CATextAlignmentLeft);
        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        view->addSubview(itemText);
        
        CALabel *tag = CALabel::createWithFrame(CADipRect(20,itemSize.height - 55,itemSize.width,30));
        tag->setTag(102);
        tag->setFontSize(_px(22));
        tag->setTextAlignment(CATextAlignmentLeft);
        tag->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
        tag->setColor(CAColor_gray);
        view->addSubview(tag);
    }
    
    //设置Item背景颜色
    CAView* itemImageView = p_Cell->getSubviewByTag(99);
    itemImageView->setColor(CAColor_white);

    CAImageView *imageView = (CAImageView*)p_Cell->getSubviewByTag(99)->getSubviewByTag(101);
    imageView->setImage(CAImage::create(m_listData[index]["img"].asString()));

    //设置itme文本显示
    CALabel* itemText = (CALabel*)p_Cell->getSubviewByTag(99)->getSubviewByTag(100);
    string title = m_listData[index]["title"].asString();
    itemText->setText(title);

    CALabel* tagText = (CALabel*)p_Cell->getSubviewByTag(99)->getSubviewByTag(102);
    string tag = m_listData[index]["tag"].asString();
    tagText->setText(tag);
    
    return p_Cell;
}

void RecommendView::setReload(const CSJson::Value& listData) {
    if (m_listData == listData) {
        return;
    }
    
    m_collection->reloadData();
}
//Necessary
unsigned int RecommendView::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row) {
    
    //CCLog("%d ----", winSize.width);
    
    return _px(winSize.height / m_listSize);
}

//Necessary
unsigned int RecommendView::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row) {
    return 2;
}

//Necessary
unsigned int RecommendView::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section) {
    return m_listSize;
}

void RecommendView::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    int index = row * 2 + item;
    int v_id = m_listData[index]["id"].asInt();
    CCLog("list video id: %d",v_id);
    RootWindow::create()->getNavigationController()->pushViewController(VideoPlayViewController::create(v_id), true);
}

void RecommendView::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    
}










