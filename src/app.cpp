#include "app.h"

//--------------------------------------------------------------
void app::setup(){
    
    screenMargin = 20; //pixel dimension for layout
    
    width = 1280;
	height = 960;
    
    vidGrabber.setBayerMode(DC1394_COLOR_FILTER_RGGB);
    vidGrabber.setSize(width,height);
    vidGrabber.setup(0);
    vidGrabber.printFeatures();
    
    vidGrabber2.setBayerMode(DC1394_COLOR_FILTER_RGGB);
    vidGrabber2.setSize(width,height);
    vidGrabber2.setup(1);
    vidGrabber2.printFeatures();
    
	curFrame.allocate(width, height,OF_IMAGE_COLOR);
	colorImage.allocate(width, height,OF_IMAGE_COLOR);
    
	curFrame2.allocate(width, height,OF_IMAGE_COLOR);
	colorImage2.allocate(width, height,OF_IMAGE_COLOR);
    
    ofBackground(32,32,32);
    
    drawRect = calculateDrawRect();
    
}

//--------------------------------------------------------------
void app::update(){
    
	bool bNewFrame = vidGrabber.grabVideo(curFrame);
	
	if(bNewFrame) {
        curFrame.update();
		colorImage.setFromPixels(curFrame.getPixels(), width,height,OF_IMAGE_COLOR);
	}
    
    bNewFrame = vidGrabber2.grabVideo(curFrame2);
	
	if(bNewFrame) {
        curFrame2.update();
        colorImage2.setFromPixels(curFrame2.getPixels(), width,height,OF_IMAGE_COLOR);
	}
    
    
}

//--------------------------------------------------------------
void app::draw(){

	ofSetHexColor(0xffffff);
    

   
    colorImage.draw(drawRect);
    colorImage2.draw(drawRect.x+drawRect.width, drawRect.y,drawRect.width,drawRect.height);
    
	ofSetHexColor(0x666666);
}

ofRectangle app::calculateDrawRect(){

    float aspectRatio = ((float)width*2.0f)/(float)height;
    int displayWidth, displayHeight;
    displayWidth = ofGetWidth()/2;
    displayHeight = ofGetHeight();
    float displayRatio = ofGetWidth()/ofGetHeight();
    float imgScale;
    
    if(aspectRatio>displayRatio){
        // stitched images are too wide
        // match the width
        imgScale = ((float)(ofGetWidth()/2.0f-screenMargin*2))/(float)width;
    } else {
        // too tall (not likely, but tested)
        // match the height
        imgScale = ((float)(ofGetHeight()-screenMargin*2))/(float)height;
    }
    displayWidth = imgScale*width;
    displayHeight = imgScale*height;
    
    int displayY, displayX;
    displayY = ofGetHeight()/2-displayHeight/2;
    displayX = ofGetWidth()/2-displayWidth;
	//
    
    ofRectangle rect;
    rect.set(displayX,displayY,displayWidth,displayHeight);
    return rect;
}


//--------------------------------------------------------------
void app::keyPressed(int key){
    
#ifdef CAMERA_CONNECTED
	if(key == 's') {
		//vidGrabber.videoSettings();
        vidGrabber.printFeatures();
	}
#endif
    
}

//--------------------------------------------------------------
void app::keyReleased(int key){
    
}

//--------------------------------------------------------------
void app::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void app::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void app::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void app::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void app::windowResized(int w, int h){
    drawRect = calculateDrawRect();
}

//--------------------------------------------------------------
void app::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void app::dragEvent(ofDragInfo dragInfo){ 
    
}