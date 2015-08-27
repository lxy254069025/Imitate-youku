//
//  ClassifyViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#ifndef __youku__ClassifyViewController__
#define __youku__ClassifyViewController__

#include "RootWindow.h"

class ClassifyViewController: public CAViewController {
    
public:
    ClassifyViewController();
    
    virtual ~ClassifyViewController();
    
    CREATE_FUNC(ClassifyViewController);
    
protected:
    void viewDidLoad();
    
    void viewDidUnload();
    
private:
    CADipSize winSize;
};

#endif /* defined(__youku__ClassifyViewController__) */
