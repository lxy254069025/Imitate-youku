//
//  HttpImageView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/29.
//
//

#ifndef __youku__HttpImageView__
#define __youku__HttpImageView__

#include "RootWindow.h"

class HttpImageView : public CAImageView {
public:
    HttpImageView();
    virtual ~HttpImageView();
    
    static HttpImageView* createWithFrame(const CCRect& _rect);
    void setUrl(std::string url);
    
    //void setImage(CAImage* image);
    
    void onHttpImage(CAHttpClient* send,CAHttpResponse* response);
    
private:
    std::string m_key;
};

#endif /* defined(__youku__HttpImageView__) */
