//
//  VideoPlayViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#include "VideoPlayViewController.h"


VideoPlayViewController::VideoPlayViewController() {
    this->getView()->setDisplayRange(false);
}


VideoPlayViewController::~VideoPlayViewController() {
    
}

VideoPlayViewController* VideoPlayViewController::create(int video_id) {
    VideoPlayViewController *view = new VideoPlayViewController();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}

void VideoPlayViewController::viewDidLoad() {
    winSize = this->getView()->getBounds().size;
    CCLog("视频视图片中");
    //av_register_all();
    //CCLog("%s",avcodec_configuration());
    //CAApplication::getApplication()->set
}

void VideoPlayViewController::viewDidUnload() {
    
}