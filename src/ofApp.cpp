#include "ofApp.h"
/*
 
 Adapted by Francisco Bernardo for the new BITalino SDK and of_v0.10.1_osx
 from https://gitlab.doc.gold.ac.uk/rapid-mix/BITalino-OSC-OSX by Mick Grierson
 
*/


BITalino::VFrame frames(20); // initialize the a vector of frames with 20 frames

//--------------------------------------------------------------
void ofApp::setup(){

    
    
    ofTrueTypeFont::setGlobalDpi(72);
    myfont.load("verdana.ttf", 14, true, true);
    
    if(!xml.load("address.xml")){
        ofLogError() << "Couldn't load file";
    }
    
    ofBackground(40, 100, 40);
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    
    cout << "Connected to device. Press Enter to exit.";

    auto bitalino_config = xml.findFirst("//bitalino");
    
    string address = bitalino_config.getChild("address").getValue();
    
    
    
    // Check your BITalino port in the file system on the /dev
//    dev = new BITalino("/dev/tty.BITalino-49-80-DevB");
    
    dev = new BITalino((char*) address.c_str());
    
    std::string ver = dev->version();    // get device version string
    printf("BITalino version: %s\n", ver.c_str());
    
    dev->start(1000, {0, 1, 2, 3, 4, 5});   // start acquisition of all channels at 1000 Hz
    
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(50);
}

//--------------------------------------------------------------
void ofApp::update(){

    try {
        
        //this method attempts to send 20 OSC messages containing BITalino frames, every 50 times a second
        dev->read(frames);
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

    myfont.drawString("Sending 6 inputs to port 6448\nusing OSC message /wek/inputs", 10, 20);
    myfont.drawString("Inputs are:", 10, 70); // \nEMG, ECG, EDA, EEG, ACC, LUX

    
    char emgString[255]; // an array of chars
    sprintf(emgString, "EMG: %.2f", emg);
    myfont.drawString(emgString, 10, 125);

    char ecgString[255]; // an array of chars
    sprintf(ecgString, "ECG: %.2f", ecg);
    myfont.drawString(ecgString, 10, 175);

    char edaString[255]; // an array of chars
    sprintf(edaString, "EDA: %.2f", eda);
    myfont.drawString(edaString, 10, 225);

    char eegString[255]; // an array of chars
    sprintf(eegString, "EEG: %.2f", eeg);
    myfont.drawString(eegString, 10, 275);
    
    char accString[255]; // an array of chars
    sprintf(accString, "ACC: %.2f", acc);
    myfont.drawString(accString, 10, 325);

    char luxString[255]; // an array of chars
    sprintf(luxString, "LUX: %.2f", lux);
    myfont.drawString(luxString, 10, 375);
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
