#pragma once

#include "ofMain.h"
#include "bitalino.h"
#include "ofxOsc.h"
#include <sys/select.h>
#include <stdio.h>

#define HOST "localhost"
#define PORT 6448

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxOscSender sender;
    
        ofTrueTypeFont myfont;
    
//        ofxMaxiFilter myFilter;
    
        BITalino *dev;
        float emg, ecg, eda, eeg, acc, lux;
        ofXml xml;
};
