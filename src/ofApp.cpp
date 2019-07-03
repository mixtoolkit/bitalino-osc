#include "ofApp.h"

BITalino::VFrame frames(20); // initialize the a vector of frames with 20 frames

//--------------------------------------------------------------
void ofApp::setup(){

    ofTrueTypeFont::setGlobalDpi(72);
    myfont.load("verdana.ttf", 14, true, true);
    
    ofBackground(40, 100, 40);
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    
    cout << "Connected to device. Press Enter to exit.";
    
    dev = new BITalino("/dev/tty.BITalino-52-29-DevB");

    std::string ver = dev->version();    // get device version string
    printf("BITalino version: %s\n", ver.c_str());
    
    dev->start(1000, {0, 1, 2, 3, 4, 5});   // start acquisition of all channels at 1000 Hz
    
    /*
     BITalino::Vint chans;
     chans.push_back(0);
     chans.push_back(1);
     chans.push_back(2);
     chans.push_back(3);
     chans.push_back(4);
     chans.push_back(5);
     dev->start(1000, chans);
     
     
     //    dev.trigger({false, false, true, false});
     
     
     BITalino::Vbool outputs;
     outputs.push_back(false);
     outputs.push_back(false);
     outputs.push_back(true);
     outputs.push_back(false);
     dev->trigger(outputs);
     */
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(50);
    


}

//--------------------------------------------------------------
void ofApp::update(){

    try {
        
        //this method attempts to send 20 frames at once, 50 times a second over OSC
        dev->read(frames); // get 100 frames from device
        ofxOscMessage m[20];
        
        for (int i = 0;i<20;i++) {
            const BITalino::Frame &f = frames[i];  // get a reference to the first frame of each 100 frames block
            m[i].setAddress("/wek/inputs");

            m[i].addFloatArg(f.analog[0]);
//            m[i].addFloatArg(myFilter.lopass(f.analog[0],0.125));
            m[i].addFloatArg(f.analog[1]);
            m[i].addFloatArg(f.analog[2]);
            m[i].addFloatArg(f.analog[3]);
            m[i].addFloatArg(f.analog[4]);
            m[i].addFloatArg(f.analog[5]);
            sender.sendMessage(m[i]);
            
            if (i==0) {
                emg = f.analog[0];
                ecg = f.analog[1];
                eda = f.analog[2];
                eeg = f.analog[3];
                acc = f.analog[4];
                lux = f.analog[5];
                cout << emg << " " << eda << " " << ecg << " " << acc << " " << lux << endl;
            }
        }
    }
    catch(BITalino::Exception &e)
    {
        printf("BITalino exception: %s\n", e.getDescription());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    myfont.drawString("Sending 6 inputs to port 6448\nusing /wek/inputs", 10, 20);
    myfont.drawString("Inputs are:\nEMG, ECG, EDA, EEG, ACC, LUX", 10, 70);

    
    char emgString[255]; // an array of chars
    sprintf(emgString, "EMG: %.2f", emg);
    myfont.drawString(emgString, 10, 125);

    char ecgString[255]; // an array of chars
    sprintf(ecgString, "ECG: %.2f", ecg);
    myfont.drawString(ecgString, 10, 200);

    
    char edaString[255]; // an array of chars
    sprintf(edaString, "EDA: %.2f", eda);
    myfont.drawString(edaString, 10, 250);

    char eegString[255]; // an array of chars
    sprintf(eegString, "EEG: %.2f", eeg);
    myfont.drawString(eegString, 10, 300);
    
    char accString[255]; // an array of chars
    sprintf(accString, "ACC: %.2f", acc);
    myfont.drawString(accString, 10, 350);

    char luxString[255]; // an array of chars
    sprintf(luxString, "LUX: %.2f", lux);
    myfont.drawString(luxString, 10, 400);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
