#pragma once

#include "ofxLibdc.h"
#include "ofxXmlSettings.h"
#include "CameraModel.h"
#include "ofxARToolkitPlus.h"

#include "ofMain.h"


// Uncomment this to use a camera instead of a video file
#define CAMERA_CONNECTED

class app : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofRectangle drawRect;
    ofRectangle calculateDrawRect();
    	
    int screenMargin;   // pixel dimension for layout
    
    ofxXmlSettings XML;
    void loadSettings();
    
    vector<CameraModel> cameraModels;
    vector<ofxLibdc::PointGrey*> vidGrabbers;

    vector<ofImage> curFrames;
    vector<ofImage> colorImages;
    vector<ofImage> grayScaleImages;
    
private:
    
    void applyModelSettingsToGrabber(ofxLibdc::PointGrey * grabber_ptr, CameraModel model);


		
};
