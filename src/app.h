#pragma once

#include "ofxLibdc.h"
#include "ofxOpenCv.h"
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
    
    /* Size of the image */
    int width, height;
	
    /* Use either camera or a video file */

    int screenMargin;   // pixel dimension for layout
    
    ofxLibdc::PointGrey vidGrabber;
    ofxLibdc::PointGrey vidGrabber2;
    ofImage curFrame;
    ofImage curFrame2;

   	
    /* OpenCV images */
    ofImage colorImage;
    ofImage colorImage2;
    //ofImage grayImage;
    //ofImage	grayThres;
	
    /* Image to distort on to the marker */
    //ofImage displayImage;
    /* The four corners of the image */
    //vector<ofPoint> displayImageCorners;
		
};
