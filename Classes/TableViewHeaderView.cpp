//
//  TableViewHeaderView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#include "TableViewHeaderView.h"

TableViewHeaderView::TableViewHeaderView() {
    
}

TableViewHeaderView::~TableViewHeaderView() {
    
}

TableViewHeaderView* TableViewHeaderView::createWithFrame(const CADipRect& _ret) {
    TableViewHeaderView *view = new TableViewHeaderView();
    
    if (view && view->init(_ret)) {
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}

bool TableViewHeaderView::init(const CADipRect& _ret) {
    if (!CAView::init()) {
        return false;
    }
    this->setFrame(_ret);
    this->setColor(CAColor_white);
    winSize = this->getBounds().size;
    
    CAImageView *imageView = CAImageView::createWithCenter(CADipRect(3,winSize.height / 2,6,winSize.height/3));
    imageView->setImage(CAImage::create("r/box_title_left.png"));
    this->addSubview(imageView);
    
    
    m_btn = CAButton::create(CAButtonTypeCustom);
    m_btnView = CAView::create();
    m_btnView->setColor(CAColor_clear);
    
    m_title = CALabel::createWithFrame(m_btnView->getBounds());
    m_title->setFontSize(_px(winSize.height/3));
    m_title->setColor(CAColor_black);
    m_title->setTextAlignment(CATextAlignmentLeft);
    m_title->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    m_btnView->addSubview(m_title);
    
    m_right = CAImageView::create();
    m_btnView->addSubview(m_right);
    
    m_btn->setBackGroundViewForState(CAControlStateAll, m_btnView);
    this->addSubview(m_btn);
    
    m_rightView = CAView::create();
    m_rightView->setColor(CAColor_clear);
    
    m_rightBtn1 = CAButton::create(CAButtonTypeCustom);
    m_rightBtn1->setTitleFontSize(_px(22));
    m_rightBtn1->setTitleColorForState(CAControlStateAll, CAColor_gray);
    m_rightView->addSubview(m_rightBtn1);
    
    m_rightBtn2 = CAButton::create(CAButtonTypeCustom);
    m_rightBtn2->setTitleFontSize(_px(22));
    m_rightBtn2->setTitleColorForState(CAControlStateAll, CAColor_gray);
    m_rightView->addSubview(m_rightBtn2);
    
    m_rightBtn3 = CAButton::create(CAButtonTypeCustom);
    m_rightBtn3->setTitleFontSize(_px(22));
    m_rightBtn3->setTitleColorForState(CAControlStateAll, CAColor_gray);
    m_rightView->addSubview(m_rightBtn3);
    
    this->addSubview(m_rightView);
    return true;
}
//home_notice_right_arrow.png
void TableViewHeaderView::setModel(const CSJson::Value chan) {
    
    if (chan.size() == 0) {
        return;
    }
    
    long titleLen = cc_utf8_strlen(chan["left"]["title"].asCString());
    float btnW = titleLen * (winSize.height/3) + 20;
    
    m_btn->setFrame(CADipRect(20,winSize.height/3,btnW,40));
    m_btn->addTarget(this, CAControl_selector(TableViewHeaderView::onClick), CAControlEventTouchUpInSide);
    m_btn->setTag(chan["left"]["id"].asInt());
    
    m_btnView->setFrame(m_btn->getBounds());
    
    m_title->setFrame(m_btnView->getBounds());
    //std::string t = chan.aliases.empty()?chan.aliases:" ";
    m_title->setText(chan["left"]["title"].asString());
    
    m_right->setCenter(CADipRect(btnW-10,(winSize.height/3) / 2,11,19));
    m_right->setImage(CAImage::create("r/home_notice_right_arrow.png"));
    
    int classify_num = chan["right"].size();
    int classify_string_len = 0;
    for (int i = 0; i < classify_num; i++) {
        CSJson::Value classify = chan["right"][i];
        classify_string_len += cc_utf8_strlen(classify["title"].asCString());
        classify_string_len++;
    }
    
    float rightViewWidth = classify_string_len * (22);
    m_rightView->setCenter(CADipRect(winSize.width - rightViewWidth / 2, winSize.height / 2,rightViewWidth,winSize.height / 3));
    
    CADipSize m_rightViewSize = m_rightView->getBounds().size;
    
    std::string bt1 = chan["right"][0]["title"].asString();
    float bt1_width = cc_utf8_strlen(bt1.c_str()) * 26;
    m_rightBtn1->setFrame(CADipRect(0,0,bt1_width,m_rightViewSize.height));
    m_rightBtn1->setTitleForState(CAControlStateAll, bt1+"•");
    
    std::string bt2 = chan["right"][1]["title"].asString();
    float bt2_width = cc_utf8_strlen(bt2.c_str()) * 26;
    m_rightBtn2->setFrame(CADipRect(bt1_width + 10,0,bt2_width,m_rightViewSize.height));
    m_rightBtn2->setTitleForState(CAControlStateAll, bt2+"•");
    
    std::string bt3 = chan["right"][2]["title"].asString();
    float bt3_width = cc_utf8_strlen(bt3.c_str()) * 26;
    m_rightBtn3->setFrame(CADipRect(bt1_width + bt2_width + 10,0,bt3_width,m_rightViewSize.height));
    m_rightBtn3->setTitleForState(CAControlStateAll, bt3);
}

void TableViewHeaderView::onClick(CAControl *btn , CCPoint point) {
    CCLog("分类id：%d",m_btn->getTag());
}

