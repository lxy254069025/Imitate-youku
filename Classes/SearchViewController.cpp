//
//  SearchViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/9/2.
//
//

#include "SearchViewController.h"
#include "IndexViewController.h"

SearchViewController::SearchViewController() {
    
}


SearchViewController::~SearchViewController() {
    
}

void SearchViewController::viewDidLoad() {
    
    CADipSize winSize = this->getView()->getBounds().size;
    
    CAButton *btn = CAButton::createWithCenter(CADipRect(winSize.width / 2,winSize.height / 2,100,100), CAButtonTypeCustom);
    btn->setTitleForState(CAControlStateAll, "点点试试");
    btn->addTarget(this, CAControl_selector(SearchViewController::onBtn), CAControlEventTouchUpInSide);
    this->getView()->addSubview(btn);
}

void SearchViewController::viewDidUnload() {
    
}

void SearchViewController::onBtn(CAControl *btn,CCPoint point) {
    IndexViewController *indexView = new IndexViewController();
    indexView->init();
    RootWindow::create()->getNavigationController()->popViewControllerAnimated(false);
    indexView->release();
}
