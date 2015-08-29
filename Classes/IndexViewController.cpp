//  IndexViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/28.
//
//

#include "IndexViewController.h"
#include "CacheView.h"
#include "MemberViewController.h"
#include "VideoPlayViewController.h"
#include "TableViewHeaderView.h"
#include "DataCollectionView.h"


#define MORESELECTED 100000
#define PAGELINKTAG 1000

IndexViewController::IndexViewController() {
    
}

IndexViewController::~IndexViewController() {
    
}


void IndexViewController::viewDidLoad() {
    winSize = this->getView()->getBounds().size;
    
    this->parseJson();
    
    this->loadNavigationItem();
    
    this->loadPageView();
}

void IndexViewController::viewDidUnload() {
    
}

void IndexViewController::parseJson() {
    std::string json_file = CCFileUtils::sharedFileUtils()->fullPathForFilename("r/data/HomeData.json");
    CCString *jsonData = CCString::createWithContentsOfFile(json_file.c_str());
    
    CSJson::Reader reader;
    if (reader.parse(jsonData->getCString(), value)) {
        //OK
        this->loadCollectionView();
    } else {
        //初始化失败。
    }
}

void IndexViewController::loadNavigationItem() {
    CAView *view = CAView::createWithFrame(CADipRect(0,0,winSize.width,130));
    view->setColor(CAColor_white);
    this->getView()->addSubview(view);
    
    CAImageView *logo = CAImageView::createWithFrame(CADipRect(30,60,76,50));
    logo->setImage(CAImage::create("r/icon_youku.png"));
    view->addSubview(logo);
    
    CAButton *search = CAButton::create(CAButtonTypeCustom);
    search->setImageForState(CAControlStateNormal,CAImage::create("r/btn_search.png"));
    search->setFrame(CADipRect(winSize.width / 2 - 70 * 1.6,55,80,70));
    search->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_search_selected.png"));
    search->addTarget(this, CAControl_selector(IndexViewController::onButtonSearch), CAControlEventTouchUpInSide);
    view->addSubview(search);
    
    CAButton *member = CAButton::create(CAButtonTypeCustom);
    member->setImageForState(CAControlStateNormal, CAImage::create("r/btn_vip.png"));
    member->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_vip_selected.png"));
    member->setFrame(CADipRect(winSize.width / 2 - 10 ,55,80,70));
    member->addTarget(this, CAControl_selector(IndexViewController::onButtonMenber), CAControlEventTouchUpInSide);
    view->addSubview(member);
    
    CAButton *record = CAButton::create(CAButtonTypeCustom);
    record->setImageForState(CAControlStateNormal, CAImage::create("r/myyouku_history.png"));
    record->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_history_selected.png"));
    record->setFrame(CADipRect(winSize.width / 2 + 92,55,80,70));
    record->addTarget(this, CAControl_selector(IndexViewController::onButtonRecord), CAControlEventTouchUpInSide);
    view->addSubview(record);
    
    CAButton *upload = CAButton::create(CAButtonTypeCustom);
    upload->setImageForState(CAControlStateNormal, CAImage::create("r/btn_upload.png"));
    upload->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_upload_selected.png"));
    upload->setFrame(CADipRect(winSize.width / 2 + 194,55,80,70));
    upload->addTarget(this, CAControl_selector(IndexViewController::onButtonUpload), CAControlEventTouchUpInSide);
    view->addSubview(upload);
    
    CAButton *more = CAButton::create(CAButtonTypeCustom);
    more->setImageForState(CAControlStateNormal, CAImage::create("r/btn_more.png"));
    more->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_more_selected.png"));
    more->setFrame(CADipRect(winSize.width / 2 + 296,55,80,70));
    more->addTarget(this, CAControl_selector(IndexViewController::onButtonMore), CAControlEventTouchUpInSide);
    view->addSubview(more);
}

void IndexViewController::loadPageView() {
    
}

void IndexViewController::loadCollectionView() {
    DataCollectionView *view = DataCollectionView::createWithFrame(CADipRect(0,131,winSize.width,winSize.height-130.5));
    view->setValue(value);
    view->initCollection();
    
    this->getView()->addSubview(view);
}

//搜索
void IndexViewController::onButtonSearch(CAControl *btn, CCPoint point) {
    CCLog("搜索");
}
//会员中心
void IndexViewController::onButtonMenber(CAControl *btn, CCPoint point) {
    this->getNavigationController()->presentModalViewController(MemberViewController::create(), true);
}
//用户记录
void IndexViewController::onButtonRecord(CAControl *btn, CCPoint point) {
    
}
//上传
void IndexViewController::onButtonUpload(CAControl *btn, CCPoint point) {
    
}
//更多
void IndexViewController::onButtonMore(CAControl *btn, CCPoint point) {
    CacheView *more_selected = (CacheView*)this->getView()->getSubviewByTag(MORESELECTED);
    if (more_selected) {
        if (more_selected->isVisible()) {
            more_selected->setVisible(false);
        } else {
            more_selected->setVisible(true);
        }
        
    } else {
        more_selected = CacheView::create(CADipRect(0,130.5,winSize.width,winSize.height-130.5));
        more_selected->setTag(MORESELECTED);
        more_selected->addCacheTarget(this, CAControl_selector(IndexViewController::onButtonCache), CAControlEventTouchUpInSide);
        this->getView()->addSubview(more_selected);
    }
    
}

void IndexViewController::onButtonCache(CAControl *btn, CCPoint point) {
    CCLog("缓存触发");
    btn->getSuperview();
}





