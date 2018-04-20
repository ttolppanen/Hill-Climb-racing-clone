#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

namespace hillclimb {

    class AppDelegate : private cocos2d::Application {
    public:
        virtual void initGLContextAttrs();
        virtual bool applicationDidFinishLaunching();
        virtual void applicationDidEnterBackground();
        virtual void applicationWillEnterForeground();
    };
}
   
#endif

