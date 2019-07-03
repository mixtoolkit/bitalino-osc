//
//  myThread.h

//  bitalinoOSC
//
//  Created by Mick Grierson on 14/05/2015.
//
//

#ifndef __bitalinoOSC__myThread__
#define __bitalinoOSC__myThread__

#include <stdio.h>
#include "ofMain.h"

class MyThread : public ofThread {
    
public:
    
    // the thread function
    void MyThread::threadedFunction() {
        
        // start
        
        while(isThreadRunning()) {
            
            
            
            
        }
        
        // done
    }
    
};


#endif /* defined(__bitalinoOSC__myThread__) */

