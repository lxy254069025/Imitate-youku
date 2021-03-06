//
//  ChannelDetailedViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/9/1.
//
//

#include "ChannelDetailedViewController.h"
#include "ChannelListVideo.h"


ChannelDetailedViewController::ChannelDetailedViewController():m_cDropDownView(NULL) {
    this->parseJson();
}

ChannelDetailedViewController::~ChannelDetailedViewController() {
    
}

ChannelDetailedViewController* ChannelDetailedViewController::create(const int channel_id,const int channel_s_id) {
    ChannelDetailedViewController *_viewController = new ChannelDetailedViewController();
    
    if (_viewController && _viewController->init(channel_id,channel_s_id)) {
        _viewController->autorelease();
        return _viewController;
    }
    
    delete _viewController;
    _viewController = NULL;
    return NULL;
    
}

bool ChannelDetailedViewController::init(const int channel_id,const int channel_s_id) {
    if (!CAViewController::init()) {
        return false;
    }
    
    this->m_channel_id = channel_id;
    
    this->m_channel_s_id = channel_s_id;
    
    
    return true;
}


void ChannelDetailedViewController::viewDidLoad() {
    winSize = this->getView()->getBounds().size;
    
    this->loadNavigationIemt();
    
    this->getView()->setColor(CAColor_black);
    
    this->loadTitleList();
    
}

void ChannelDetailedViewController::viewDidUnload() {
    
}

void ChannelDetailedViewController::parseJson() {
    std::string json_file = CCFileUtils::sharedFileUtils()->fullPathForFilename("r/icon/IconJson.json");
    CCString *jsonData = CCString::createWithContentsOfFile(json_file.c_str());
    
    CSJson::Reader reader;
    if (reader.parse(jsonData->getCString(), m_channel_value)) {
        //OK
        //this->loadCollectionView();
        m_channelSize = m_channel_value["classify1"].size() + m_channel_value["classify2"].size();
    } else {
        //初始化失败。
    }
}

void ChannelDetailedViewController::loadNavigationIemt() {
    CAView *view = CAView::createWithFrame(CADipRect(0,0,winSize.width,130));
    view->setColor(ccc4(248, 248, 248, 255));
    view->setZOrder(100);
    view->setTag(99);
    this->getView()->addSubview(view);
    
    CADipSize viewSize = view->getBounds().size;
    
    CAImageView *fanhui = CAImageView::createWithFrame(CADipRect(0,0,50,50));
    fanhui->setImageViewScaleType(CAImageViewScaleTypeFitImageInside);
    fanhui->setImage(CAImage::create("r/topbar_icon_back_normal@2x.png"));
    
    CAButton *fanhuiBtn = CAButton::createWithCenter(CADipRect(50,(viewSize.height + 40) / 2,50,50), CAButtonTypeCustom);
    fanhuiBtn->setBackGroundViewForState(CAControlStateAll, fanhui);
    fanhuiBtn->addTarget(this, CAControl_selector(ChannelDetailedViewController::onFanHui), CAControlEventTouchUpInSide);
    view->addSubview(fanhuiBtn);
    
    long titleLen = StringUtils::getCharacterCountInUTF8String(reustChannelTitle());
    
    m_dropDownBtn = CAButton::createWithCenter(CADipRect(viewSize.width / 2,(viewSize.height + 40) / 2,38*(titleLen+1),50), CAButtonTypeCustom);
    
    CADipSize btnSize = m_dropDownBtn->getBounds().size;
    
    
    m_dropDownView = CAView::createWithFrame(CADipRect(0,0,btnSize.width,btnSize.height),CAColor_clear);


    CALabel *title = CALabel::createWithFrame(CADipRect(0,0,btnSize.width - 38,btnSize.height));
    title->setText(reustChannelTitle());
    title->setTextAlignment(CATextAlignmentLeft);
    title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    title->setFontSize(_px(38));
    title->setTag(100);
    
    m_dropDownView->addSubview(title);
    
    CAImageView *drop = CAImageView::createWithFrame(CADipRect(btnSize.width - 38,0,38,btnSize.height));
    drop->setImage(CAImage::create("r/topbar_icon_open_clicked@2x.png"));
    drop->setImageViewScaleType(CAImageViewScaleTypeFitImageInside);
    drop->setRotation(0);
    drop->setTag(101);
    
    m_dropDownView->addSubview(drop);
    
    m_dropDownBtn->setBackGroundViewForState(CAControlStateAll, m_dropDownView);
    m_dropDownBtn->addTarget(this, CAControl_selector(ChannelDetailedViewController::onDropDwon), CAControlEventTouchUpInSide);
    view->addSubview(m_dropDownBtn);
    
    CAView *line = CAView::createWithFrame(CADipRect(0,viewSize.height - 1,viewSize.width,1),CAColor_gray);
    view->addSubview(line);
}

void ChannelDetailedViewController::onFanHui(CAControl *btn, CCPoint point) {
    RootWindow::create()->getNavigationController()->popViewControllerAnimated(true);
}

std::string ChannelDetailedViewController::reustChannelTitle() {
    CSJson::Value value1 = m_channel_value["classify1"];
    CSJson::Value value2 = m_channel_value["classify2"];
    for (int i = 0; i < value1.size(); i++) {
        if (value1[i]["id"].asInt() == m_channel_id) {
            return value1[i]["title"].asString();
        }
    }
    
    for (int j = 0; j < value2.size(); j++) {
        if (value2[j]["id"].asInt() == m_channel_id) {
            return value2[j]["title"].asString();
        }
    }
    return "全部";
}

void ChannelDetailedViewController::onDropDwon(CAControl *btn,CCPoint point) {
    
    CAImageView *drop =  (CAImageView*)m_dropDownView->getSubviewByTag(101);
    if (drop->getRotation() == 0) {
        drop->setRotation(180);
    } else {
        drop->setRotation(0);
    }
    
    if (m_cDropDownView != NULL) {
        if (m_cDropDownView->getFrameOrigin().y >= 130) {
            CAViewAnimation::beginAnimations("111", NULL);
            m_cDropDownView->setFrame(CADipRect(0,-winSize.height + - 130,winSize.width,winSize.height));
            CAViewAnimation::commitAnimations();
            return;
        } else {
            CAViewAnimation::beginAnimations("111", NULL);
            m_cDropDownView->setFrame(CADipRect(0,130,winSize.width,winSize.height));
            CAViewAnimation::commitAnimations();
            return;
        }
        
    }
    
    
    m_cDropDownView = ChannelDropDownView::createWithFrame(CADipRect(0,-winSize.height + - 130,winSize.width,winSize.height));
    m_cDropDownView->setDataSize(m_channelSize);
    m_cDropDownView->initCollectionView();
    m_cDropDownView->setZOrder(99);
    m_cDropDownView->setDefaultChannel(0);
    m_cDropDownView->setValue(m_channel_value);
    m_cDropDownView->setCallBack(this,CAView_selector(ChannelDetailedViewController::setDorDwonAttr));
    
    this->getView()->addSubview(m_cDropDownView);
    CAViewAnimation::beginAnimations("111", NULL);
    m_cDropDownView->setFrame(CADipRect(0,130,winSize.width,winSize.height));
    CAViewAnimation::commitAnimations();
}

void ChannelDetailedViewController::setDorDwonAttr(std::string title,int channel_id) {
    
    CALabel *currTitle = (CALabel*)m_dropDownView->getSubviewByTag(100);
    
    CAView *view = (CAView*)this->getView()->getSubviewByTag(99);
    
    CAViewAnimation::beginAnimations("111", NULL);
    m_cDropDownView->setFrame(CADipRect(0,-winSize.height + - 130,winSize.width,winSize.height));
    CAViewAnimation::commitAnimations();
    
    long titleLen = StringUtils::getCharacterCountInUTF8String(title);
    
    CADipSize viewSize = view->getBounds().size;
    
    m_dropDownBtn->setCenter(CADipRect(viewSize.width / 2,(viewSize.height + 40) / 2,38*(titleLen+1),50));
    CADipSize btnSize = m_dropDownBtn->getBounds().size;
    
    
    m_dropDownView->setFrame(CADipRect(0,0,btnSize.width,btnSize.height));
    
    CAImageView *drop = (CAImageView*)m_dropDownView->getSubviewByTag(101);
    drop->setFrame(CADipRect(btnSize.width - 38,0,38,btnSize.height));
    if (drop->getRotation() == 0) {
        drop->setRotation(180);
    } else {
        drop->setRotation(0);
    }
    
    currTitle->setFrame(CADipRect(0,0,btnSize.width - 38,btnSize.height));
    currTitle->setText(title);
    
    
}


void ChannelDetailedViewController::loadTitleList() {
    
    CSJson::Value value1 = m_channel_value["classify1"];
    CSJson::Value value2 = m_channel_value["classify2"];
    
    CSJson::Value currValue;
    
    for (int i = 0; i < value1.size(); i++) {
        if (value1[i]["id"].asInt() == m_channel_id) {
            currValue = value1;
            break;
        }
    }
    
    for (int j = 0; j < value2.size(); j++) {
        if (value2[j]["id"].asInt() == m_channel_id) {
            currValue = value2;
            break;
        }
    }
    
    ChannelListVideo *titleList = ChannelListVideo::createWithFrame(CADipRect(0,130,winSize.width,winSize.height - 130));
    titleList->initListView(currValue);
    this->getView()->addSubview(titleList);
}

