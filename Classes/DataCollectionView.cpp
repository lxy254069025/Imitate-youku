//
//  DataCollectionView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/28.
//
//

#include "DataCollectionView.h"
#include "VideoPlayViewController.h"
#include "TableViewHeaderView.h"
#include "FirstCollectionHeaderView.h"
#include "HttpImageView.h"
//#include "WebSocket.h"

#define PAGELINKTAG 1000

DataCollectionView::DataCollectionView():m_pageViewIndex(0) {
    
}

DataCollectionView::~DataCollectionView() {
    
}

DataCollectionView* DataCollectionView::createWithFrame(const CADipRect& _ret) {
    DataCollectionView *view = new DataCollectionView();
    if (view && view->init(_ret)) {
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}

bool DataCollectionView::init(const CADipRect& _ret) {
    if (!CAView::init()) {
        return false;
    }
    
    this->setFrame(_ret);
    winSize = this->getBounds().size;
    this->setColor(CAColor_gray);
    
    return true;
}

void DataCollectionView::setValue(CSJson::Value value) {
    m_value = value;
}

void DataCollectionView::loadPageView() {
    m_header = CAView::createWithFrame(CADipRect(0,0,winSize.width,350),CAColor_clear);
    m_pageView = CAPageView::createWithFrame(CADipRect(0,0,winSize.width,350), CAPageViewDirectionHorizontal);
    m_pageView->setCurrPage(0, true);
    m_pageView->setPageViewDelegate(this);
    m_pageView->setSpacing(0);
    
    CADipSize headerSize = m_header->getBounds().size;
    
    CSJson::Value pageValue = m_value["header"];
    
    CAVector<CAView*> vec;
    for (int i = 0; i < pageValue.size(); i++) {
        std::string path = pageValue[i]["img"].asString();
        std::string js_title = pageValue[i]["title"].asString();
        int js_id = pageValue[i]["id"].asInt();
        
        HttpImageView *image = HttpImageView::createWithFrame(CADipRect(0,0,headerSize.width,headerSize.height));
        image->setUrl(path);
        
        CALabel *title = CALabel::createWithFrame(CADipRect(20,headerSize.height / 1.25,headerSize.width,50));
        title->setText(js_title);
        title->setFontSize(_px(28));
        title->setColor(CAColor_white);
        image->addSubview(title);
        
        CAButton *btn = CAButton::create(CAButtonTypeCustom);
        btn->setFrame(CADipRect(0,0,headerSize.width,headerSize.height));
        btn->setBackGroundViewForState(CAControlStateAll, image);
        btn->setTag(js_id);
        btn->addTarget(this, CAControl_selector(DataCollectionView::pageClick), CAControlEventTouchUpInSide);
        vec.pushBack(btn);
    }
    m_pageView->setViews(vec);
    m_header->addSubview(m_pageView);
    CAScheduler::schedule(schedule_selector(DataCollectionView::changePageViewIndex), this, 3, false);
    
    for (int j = 0; j < vec.size(); j++) {
        CAView *pageLink = CAView::createWithFrame(CADipRect(20 + 118 * j,headerSize.height / 1.35,118,1),CAColor_gray);
        pageLink->setZOrder(100);
        if (j == 0) {
            pageLink->setFrame(CADipRect(20 + 118 * j,headerSize.height / 1.35 - 2,118,3));
            pageLink->setColor(CAColor_white);
        }
        pageLink->setTag(PAGELINKTAG+j);
        m_header->addSubview(pageLink);
    }
}

void DataCollectionView::initCollection() {
    this->loadPageView();
    //this->addSubview(m_header);
    m_collection = CACollectionView::createWithFrame(CADipRect(0,0,winSize.width,winSize.height));
    m_collection->setAllowsSelection(true);
    m_collection->setCollectionViewDataSource(this);
    m_collection->setCollectionViewDelegate(this);
    m_collection->setScrollViewDelegate(this);
    m_collection->setCollectionHeaderHeight(350);
    m_collection->setCollectionHeaderView(m_header);
    
    //m_collection->setBackGroundColor(CAColor_black);
    m_collection->setAlwaysTopSectionHeader(false);
    m_collection->setAlwaysBottomSectionFooter(false);
    
    CAPullToRefreshView *refreshDiscount1 = CAPullToRefreshView::create(CAPullToRefreshView::CAPullToRefreshTypeHeader);
    refreshDiscount1->setLabelColor(CAColor_black);
    refreshDiscount1->setPullToRefreshText(UTF8("下拉可以刷新"));
    refreshDiscount1->setLabelColor(CAColor_gray);
    refreshDiscount1->setRefreshingText(UTF8("正在刷新..."));
    m_collection->setHeaderRefreshView(refreshDiscount1);
    this->addSubview(m_collection);
}



CACollectionViewCell* DataCollectionView::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item) {
    int index = row * 2 + item;
    
    CSJson::Value data = m_value["data"][section]["list"];
    
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
        
        HttpImageView *imageView = HttpImageView::createWithFrame(CADipRect(0,0,itemSize.width,itemSize.height - 100));
        
        imageView->setTag(101);
        //imageView->setImage(BaseImage::createUrl(data[index]["img"].asString()));
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
    
    HttpImageView *imageView = (HttpImageView*)p_Cell->getSubviewByTag(99)->getSubviewByTag(101);
    imageView->setUrl(data[index]["img"].asString());
    
    //设置itme文本显示
    CALabel* itemText = (CALabel*)p_Cell->getSubviewByTag(99)->getSubviewByTag(100);
    string title = data[index]["title"].asString();
    itemText->setText(title);
    
    CALabel* tagText = (CALabel*)p_Cell->getSubviewByTag(99)->getSubviewByTag(102);
    string tag = data[index]["tag"].asString();
    tagText->setText(tag);
    
    return p_Cell;
}

//Necessary
unsigned int DataCollectionView::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row) {
    return _px(311);
}

//Necessary
unsigned int DataCollectionView::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row) {
    return 2;
}

//Necessary
unsigned int DataCollectionView::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section) {
    CSJson::Value data = m_value["data"][section]["list"];
    int listSize = data.size();
    return listSize % 2 != 0?(listSize - 1) / 2:listSize / 2;
}

unsigned int DataCollectionView::numberOfSections(CACollectionView *collectionView) {
    return m_value["data"].size();
}

CAView* DataCollectionView::collectionViewSectionViewForHeaderInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section) {
    //TableViewHeaderView *view = NULL;
    
    CSJson::Value data = m_value["data"];
    CSJson::Value currHeader = data[section]["header"];
    
    switch (section) {
        case 0:
        {
            FirstCollectionHeaderView *view = FirstCollectionHeaderView::createWithFrame(CADipRect(0,0,viewSize.width,viewSize.height));
            return view;
        }
            
        default:
        {
            TableViewHeaderView *view = TableViewHeaderView::createWithFrame(CADipRect(0,0,viewSize.width,viewSize.height));
            view->setModel(currHeader);
            return view;
        }
    }
}

unsigned int DataCollectionView::collectionViewHeightForHeaderInSection(CACollectionView *collectionView, unsigned int section) {
    
    return _px(115);
}

CAView* DataCollectionView::collectionViewSectionViewForFooterInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section) {
    return CAView::createWithFrame(CADipRect(0,0,viewSize.width,viewSize.height), CAColor_green);
}

unsigned int DataCollectionView::collectionViewHeightForFooterInSection(CACollectionView *collectionView, unsigned int section) {
    return 0;
}


void DataCollectionView::pageClick(CAControl *btn,CCPoint point) {
    int v_id = btn->getTag();
    CCLog("page 点中%d",v_id);
    RootWindow::create()->getNavigationController()->pushViewController(VideoPlayViewController::create(v_id), true);
}

void DataCollectionView::changePageViewIndex(float t) {
    int num = m_pageView->getPageCount();
    int curr = m_pageView->getCurrPage();
    if (curr < num - 1) {
        m_pageView->setCurrPage(curr+1, true);
    } else {
        m_pageView->setCurrPage(0, true);
    }
    
    curr = m_pageView->getCurrPage();
    
    if (curr == m_pageViewIndex) {
        return;
    }
    
    CADipSize headerSize = m_header->getBounds().size;
    
    CAView *link1 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+m_pageViewIndex);
    link1->setFrame(CADipRect(20 + 118 * m_pageViewIndex,headerSize.height / 1.35,118,1));
    link1->setColor(CAColor_gray);
    
    m_pageViewIndex = curr;
    
    CAView *link2 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+curr);
    link2->setFrame(CADipRect(20 + 118 * curr,headerSize.height / 1.35 - 2,118,3));
    link2->setColor(CAColor_white);
    
}

void DataCollectionView::scrollViewHeaderBeginRefreshing(CAScrollView* view) {
    CAScheduler::schedule(schedule_selector(DataCollectionView::onRefresing), this, 2, false);
}

void DataCollectionView::scrollViewFooterBeginRefreshing(CAScrollView* view) {
    
}

void DataCollectionView::onRefresing(float t) {
    m_collection->reloadData();
}

void DataCollectionView::pageViewDidBeginTurning(CAPageView* pageView) {
    CCLog("点点点1");
}

void DataCollectionView::pageViewDidEndTurning(CAPageView* pageView) {
    if (pageView->getCurrPage() == m_pageViewIndex) {
        return;
    }
    
    int curr = pageView->getCurrPage();
    CADipSize headerSize = m_header->getBounds().size;
    
    CAView *link1 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+m_pageViewIndex);
    link1->setFrame(CADipRect(20 + 118 * m_pageViewIndex,headerSize.height / 1.35,118,1));
    link1->setColor(CAColor_gray);
    
    m_pageViewIndex = curr;
    
    CAView *link2 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+curr);
    link2->setFrame(CADipRect(20 + 118 * curr,headerSize.height / 1.35 - 2,118,3));
    link2->setColor(CAColor_white);
}

void DataCollectionView::pageViewDidSelectedPageAtIndex(CAPageView* pageView, unsigned int index, const CCPoint& point) {
    CCLog("点点点2");
}

void DataCollectionView::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
    int index = row * 2 + item;
    CSJson::Value data = m_value["data"];
    CSJson::Value currData = data[section]["list"];
    int v_id = currData[index]["id"].asInt();
    RootWindow::create()->getNavigationController()->pushViewController(VideoPlayViewController::create(v_id), true);
    //RootWindow::create()->getNavigationController()->pushViewController(CAVideoPlayerController::createWithPath("r/data.mp4", "asdf"), true);
}

void DataCollectionView::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item) {
}

void DataCollectionView::collectionViewWillDisplayCellAtIndex(CACollectionView* table, CACollectionViewCell* cell, unsigned int section, unsigned int row, unsigned int item) {
    CCLog("试试就试试%d",row*2 + item);
}
