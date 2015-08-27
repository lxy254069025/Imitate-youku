//
//  VideoPlayViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#ifndef __youku__VideoPlayViewController__
#define __youku__VideoPlayViewController__

#include "RootWindow.h"

class VideoPlayViewController : public CAViewController {
    
public:
    VideoPlayViewController();
    
    virtual ~VideoPlayViewController();
    
    static VideoPlayViewController* create(int video_id);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
private:
    CADipSize winSize;
};

#endif /* defined(__youku__VideoPlayViewController__) */
