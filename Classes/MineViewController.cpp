//
//  MineViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#include "MineViewController.h"

MineViewController::MineViewController() {
    
}

MineViewController::~MineViewController() {
    
}

void MineViewController::viewDidLoad() {
    //CADevice::openCamera(this);
    this->getView()->setDisplayRange(true);
    
}


void MineViewController::viewDidUnload() {
    
}

void MineViewController::getSelectedImage(CAImage *image) {
    CAImageView *imgView = CAImageView::createWithFrame(this->getView()->getBounds());
    imgView->setImage(image);
    this->getView()->addSubview(imgView);
}