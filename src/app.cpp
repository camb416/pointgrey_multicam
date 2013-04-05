#include "app.h"

//--------------------------------------------------------------
void app::setup(){
    
    
    screenMargin = 20; //pixel dimension for layout
    
    width = 1280;
	height = 960;
    
    
    ////////////////////////
    // load XML... refactor later
    ////////////////////////
    
    
    string message = "";

	if( XML.loadFile("camera_settings.xml") ){
		message = "camera_settings.xml loaded!";
	}else{
		message = "unable to load mySettings.xml check data/ folder";
	}
    
    cout << message << endl;
    
    int pointCount = 0;
    //lets see how many <STROKE> </STROKE> tags there are in the xml file
	int numDragTags = XML.getNumTags("cameras:camera");
    
	//if there is at least one <STROKE> tag we can read the list of points
	//and then try and draw it as a line on the screen
	if(numDragTags > 0){
        
		//we push into the last STROKE tag
		//this temporarirly treats the tag as
		//the document root.
		XML.pushTag("cameras", numDragTags-1);
        
        //we see how many points we have stored in <PT> tags
        int numPtTags = XML.getNumTags("camera");
        
        if(numPtTags > 0){
            
            //We then read those x y values into our
            //array - so that we can then draw the points as
            //a line on the screen
            
            //we have only allocated a certan amount of space for our array
            //so we don't want to read more than that amount of points
            int totalToRead = numPtTags;
            
            for(int i = 0; i < totalToRead; i++){
                //the last argument of getValue can be used to specify
                //which tag out of multiple tags you are refering to.
               // int x = XML.getValue("PT:X", 0, i);
               // int y = XML.getValue("PT:Y", 0, i);
                cout << "CAMERA: " << endl;
                cout << "name: " << XML.getAttribute("camera", "name", "not specified",i) << endl;
                cout << "desc: " << XML.getAttribute("camera", "desc", "not specified",i) << endl;
                cout << "guid: " << XML.getAttribute("camera", "guid", "not specified",i) << endl;
                
                cout << endl << "connecting...";
                vidGrabbers.push_back(new ofxLibdc::PointGrey());
                vidGrabbers.at(i)->setBayerMode(DC1394_COLOR_FILTER_RGGB);
                
                vidGrabbers.at(i)->setSize(width,height);
                vidGrabbers.at(i)->setup(XML.getAttribute("camera", "guid", "not specified",i)) ? cout << "OK." << endl : cout << "Error." << endl;

                curFrames.push_back(ofImage());
                curFrames.at(i).allocate(width,height,OF_IMAGE_COLOR);
                colorImages.push_back(ofImage());
                colorImages.at(i).allocate(width, height,OF_IMAGE_COLOR);
                grayScaleImages.push_back(ofImage());
                grayScaleImages.at(i).allocate(width, height,OF_IMAGE_COLOR);
            
                
                pointCount++;
            }
        }

		XML.popTag();
    }
    
    
    /////////////////////////
    
    
    
    
    

    
    
    vector<string> idList = vidGrabbers.at(0)->getDeviceIDs();
    for(int i=0;i<idList.size();i++){
        cout << "CAMERA ID: " << i << ": " << idList.at(i) << endl;
    }
    /*
	curFrames.at(i).allocate(width, height,OF_IMAGE_COLOR);
	colorImage.allocate(width, height,OF_IMAGE_COLOR);
    
	curFrame2.allocate(width, height,OF_IMAGE_COLOR);
	colorImage2.allocate(width, height,OF_IMAGE_COLOR);
    */
    ofBackground(32,32,32);
    
    drawRect = calculateDrawRect();
    
}

//--------------------------------------------------------------
void app::update(){
    
    
    for(int i=0;i<vidGrabbers.size();i++){
    
	bool bNewFrame = vidGrabbers.at(i)->grabVideo(curFrames.at(i));
	
	if(bNewFrame) {
        curFrames.at(i).update();
		//colorImages.at(i).setFromPixels(curFrames.at(i).getPixels(), width,height,OF_IMAGE_COLOR);
        grayScaleImages.at(i).setFromPixels(curFrames.at(i).getPixels(), width, height, OF_IMAGE_COLOR);
        grayScaleImages.at(i).setImageType(OF_IMAGE_GRAYSCALE);
	}
    
    
        
    }
    
    
}

//--------------------------------------------------------------
void app::draw(){

	ofSetHexColor(0xffffff);
    

   
    grayScaleImages.at(0).draw(drawRect);
    grayScaleImages.at(1).draw(drawRect.x+drawRect.width, drawRect.y,drawRect.width,drawRect.height);
    
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
		for(int i=0;i<vidGrabbers.size();i++){
            vidGrabbers.at(i)->printFeatures();
        }
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