//
//  HttpImageView.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/29.
//
//

#include "HttpImageView.h"

HttpImageView::HttpImageView() {
    
}
HttpImageView::~HttpImageView() {
    
}

HttpImageView* HttpImageView::createWithFrame(const CCRect& _rect) {
    HttpImageView *view = new HttpImageView();
    if (view && view->init()) {
        view->setFrame(_rect);
        view->autorelease();
        return view;
    }
    
    delete view;
    view = NULL;
    return NULL;
}


void HttpImageView::setUrl(std::string url) {
    m_key = MD5(url).md5() + ".png";
    
    std::string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "image/";
    CCFileUtils::sharedFileUtils()->createDirectory(imagePath.c_str());
    imagePath = imagePath + m_key;
    
    CAImage* image = CAImage::create(imagePath);
    if (image) {
        CCLog("you拉");
        this->setImage(image);
        return;
    } else {
        CCLog("meiyou");
        this->setImage(CAImage::create("r/video_default.png"));//先占个位置
    }
    CAHttpRequest *httpRequest = new CAHttpRequest();
    httpRequest->setUrl(url.c_str());
    httpRequest->setRequestType(CAHttpRequest::kHttpGet);
    httpRequest->setResponseCallback(this, httpresponse_selector(HttpImageView::onHttpImage));
    CAHttpClient::getInstance()->send(httpRequest);
    httpRequest->release();

}

//void setImage(CAImage* image);

void HttpImageView::onHttpImage(CAHttpClient* send,CAHttpResponse* response) {
    if (!response) {
        return;
    }
    
    if (!response->isSucceed()) {
        return;
    }
    
    std::vector<char> *buffer = response->getResponseData();
    unsigned char* pData = ((unsigned char*)(const_cast<char*>(buffer->data())));
    std::string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "image/";
    CCFileUtils::sharedFileUtils()->createDirectory(imagePath.c_str());
    imagePath = imagePath + m_key;
    
    FILE *fp = fopen(imagePath.c_str(), "wb+");
    if (fp) {
        fwrite(pData, sizeof(unsigned char), buffer->size(), fp);
        fclose(fp);
    }
    
    CAImage *texture = new CAImage();
    texture->initWithImageData((unsigned char*)buffer->data(), buffer->size());
    texture->autorelease();
    this->setImage(texture);
    CCLog("加载了");
}


