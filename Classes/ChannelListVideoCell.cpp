//
//  ChannelListVideoCell.cpp
//  youku
//
//  Created by 卢喜羲 on 15/9/6.
//
//

#include "ChannelListVideoCell.h"

ChannelListVideoCell::ChannelListVideoCell():m_lable(NULL),m_line(NULL) {
    
}

ChannelListVideoCell::~ChannelListVideoCell() {
    
}

ChannelListVideoCell* ChannelListVideoCell::create(const std::string& ident,const CADipRect& _rect) {
    ChannelListVideoCell *cell = new ChannelListVideoCell();
    
    if (cell && cell->initWithReuseIdentifier(ident)) {
        cell->setFrame(_rect);
        return cell;
    }
    
    delete cell;
    cell = NULL;
    return NULL;
}

void ChannelListVideoCell::initCell() {
    CADipSize cellSize = this->getBounds().size;
    m_lable = CALabel::createWithFrame(CADipRect(0,0,cellSize.width,cellSize.height -3));
    //m_lable->setText("先测试");
    m_lable->setTextAlignment(CATextAlignmentCenter);
    m_lable->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    m_lable->setFontSize(_px(32));
    this->addSubview(m_lable);
    
    m_line = CAView::createWithFrame(CADipRect(0,cellSize.height-3,cellSize.width,3));
    
    this->addSubview(m_line);
    
}

void ChannelListVideoCell::setModel(CSJson::Value value) {
    std::string lable = value["title"].asString();
    m_lable->setText(lable);
}

void ChannelListVideoCell::normalListViewCell() {
    this->setBackgroundView(CAView::createWithColor(CAColor_clear));
    CC_RETURN_IF(m_line == NULL);
    m_line->setColor(CAColor_white);
    
    CC_RETURN_IF(m_lable == NULL);
    m_lable->setColor(CAColor_black);
}

void ChannelListVideoCell::highlightedListViewCell() {
    
}

void ChannelListVideoCell::selectedListViewCell() {
    this->setBackgroundView(CAView::createWithColor(CAColor_clear));
    m_line->setColor(CAColor_green);
    m_lable->setColor(CAColor_green);
}

void ChannelListVideoCell::disabledListViewCell() {
    
}
