//
//  HomeTavleViewCell.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#include "HomeTavleViewCell.h"
#include "MemberViewController.h"

HomeTavleViewCell::HomeTavleViewCell() {
    
}

HomeTavleViewCell::~HomeTavleViewCell() {
    
}

HomeTavleViewCell* HomeTavleViewCell::create(const std::string& reuseIdentifier,const CADipRect& _rect = CADipRectZero) {
    HomeTavleViewCell *cell = new HomeTavleViewCell();
    if (cell && cell->init(reuseIdentifier,_rect)) {
        cell->autorelease();
        return cell;
    }
    
    delete cell;
    cell = NULL;
    return NULL;
}

bool HomeTavleViewCell::init(const std::string& reuseIdentifier,const CADipRect& _rect = CADipRectZero) {
    if (!this->initWithReuseIdentifier(reuseIdentifier)) {
        return false;
    }
    this->setFrame(_rect);
    
    cellSize = this->getBounds().size;
    return true;
}

void HomeTavleViewCell::createLike() {
    
    likeView = CAView::createWithFrame(CADipRect(0,0,cellSize.width,cellSize.height),CAColor_white);
    //CAImage::create("r/home_subscribe_icon.png")
    CAImageView *imageView = CAImageView::createWithFrame(CADipRect(20,cellSize.height / 2 - 38 / 2,38,38));
    imageView->setTag(100);
    likeView->addSubview(imageView);
    
    CALabel *content = CALabel::createWithFrame(CADipRect(70,cellSize.height / 2 - 38 / 2,cellSize.width / 1.5,38));
    content->setTag(101);
    content->setFontSize(_px(28));
    content->setTextAlignment(CATextAlignmentLeft);
    content->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    likeView->addSubview(content);
    
    //home_notice_right_arrow.png
    CAImageView *right = CAImageView::createWithFrame(CADipRect(cellSize.width - 30,cellSize.height / 2 - 19 / 2,11, 19));
    right->setTag(102);
    likeView->addSubview(right);
    
    likebtn = CAButton::create(CAButtonTypeCustom);
    likebtn->setFrame(CADipRect(0,0,cellSize.width,cellSize.height));
    likebtn->setBackGroundViewForState(CAControlStateAll, likeView);
    likebtn->addTarget(this, CAControl_selector(HomeTavleViewCell::onLikeClick), CAControlEventTouchUpInSide);
    this->addSubview(likebtn);
    
    //this->setLike();
}

void HomeTavleViewCell::onLikeClick(CAControl *btn,CCPoint point) {
    RootWindow::create()->getTabBarController()->showSelectedViewControllerAtIndex(2);
}

void HomeTavleViewCell::createRecommend(int listSize) {
    //reco = RecommendView::create("homeReco", CADipRect(0,0,cellSize.width,cellSize.height),listSize);
    //this->addSubview(reco);
}

void HomeTavleViewCell::setLike() {
    CAImageView *imageView = (CAImageView*)likeView->getSubviewByTag(100);
    imageView->setImage(CAImage::create("r/home_subscribe_icon.png"));
    
    CALabel *content = (CALabel*)likeView->getSubviewByTag(101);
    content->setText(UTF8("戳一下，你喜欢看的都在这里了"));
    
    CAImageView *right = (CAImageView*)likeView->getSubviewByTag(102);
    right->setImage(CAImage::create("r/home_notice_right_arrow.png"));
}

void HomeTavleViewCell::setRecommend(const CSJson::Value& listData) {
    //reco->setModel(listData);
}










