#include "app.h"

//--------------------------------------------------------------
void app::setup(){
    
    
    screenMargin = 20; //pixel dimension for layout
    

    
    
    loadSettings();
   
      
    vector<string> idList = vidGrabbers.at(0)->getDeviceIDs();
    for(int i=0;i<idList.size();i++){
        cout << "CAMERA ID: " << i << ": " << idList.at(i) << endl;
    }
    
    // use these for layout
    // camW = cameraModels.at(0).getWidth();
    // camH = cameraModels.at(0).getHeight();

    ofBackground(32,32,32);
    
    drawRect = calculateDrawRect();
    
}

void app::applyModelSettingsToGrabber(ofxLibdc::PointGrey * grabber_ptr, CameraModel model){

     grabber_ptr->setBayerMode(DC1394_COLOR_FILTER_RGGB);
     grabber_ptr->setSize(model.getWidth(),model.getHeight());
     grabber_ptr->setup(model.getGuid()) ? cout << "OK." << endl : cout << "Error." << endl;

}

//--------------------------------------------------------------
void app::update(){
    
    
    for(int i=0;i<vidGrabbers.size();i++){
    
	bool bNewFrame = vidGrabbers.at(i)->grabVideo(curFrames.at(i));
	
	if(bNewFrame) {
        curFrames.at(i).update();
        grayScaleImages.at(i).setFromPixels(curFrames.at(i).getPixels(), cameraModels.at(i).getWidth(), cameraModels.at(i).getHeight(), OF_IMAGE_COLOR);
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

    // assuming both vids have the same height/width:
    int camW = cameraModels.at(0).getWidth();
    int camH = cameraModels.at(0).getHeight();
    
    float aspectRatio = ((float)camW*2.0f)/(float)camH;
    int displayWidth, displayHeight;
    displayWidth = ofGetWidth()/2;
    displayHeight = ofGetHeight();
    float displayRatio = ofGetWidth()/ofGetHeight();
    float imgScale;
    
    if(aspectRatio>displayRatio){
        // stitched images are too wide
        // match the width
        imgScale = ((float)(ofGetWidth()/2.0f-screenMargin*2))/(float)camW;
    } else {
        // too tall (not likely, but tested)
        // match the height
        imgScale = ((float)(ofGetHeight()-screenMargin*2))/(float)camH;
    }
    displayWidth = imgScale*camW;
    displayHeight = imgScale*camH;
    
    int displayY, displayX;
    displayY = ofGetHeight()/2-displayHeight/2;
    displayX = ofGetWidth()/2-displayWidth;
	//
    
    ofRectangle rect;
    rect.set(displayX,displayY,displayWidth,displayHeight);
    return rect;
}

void app::loadSettings(){
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
    // count the camera elems
	int numDragTags = XML.getNumTags("cameras:camera");
    
	//if there is at least one <STROKE> tag we can read the list of points
	//and then try and draw it as a line on the screen
	if(numDragTags > 0){
        
        // traverse the XML
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
                cout << "fps: " << XML.getAttribute("camera", "fps", 30,i) << endl;
                
                cout << endl << "connecting...";
                cameraModels.push_back(CameraModel(XML.getAttribute("camera", "name", "not specified",i),XML.getAttribute("camera", "desc", "not specified",i),XML.getAttribute("camera", "guid", "not specified",i),XML.getAttribute("camera", "fps", 30,i)));
                cameraModels.at(i).setSize(XML.getAttribute("camera", "width", 640,i),XML.getAttribute("camera", "height", 480,i));
                
                vidGrabbers.push_back(new ofxLibdc::PointGrey());
                
                applyModelSettingsToGrabber(vidGrabbers.at(i),cameraModels.at(i));
                
                curFrames.push_back(ofImage());
                curFrames.at(i).allocate(cameraModels.at(i).getWidth(),cameraModels.at(i).getHeight(),OF_IMAGE_COLOR);
                colorImages.push_back(ofImage());
                colorImages.at(i).allocate(cameraModels.at(i).getWidth(), cameraModels.at(i).getHeight() ,OF_IMAGE_COLOR);
                grayScaleImages.push_back(ofImage());
                grayScaleImages.at(i).allocate(cameraModels.at(i).getWidth(), cameraModels.at(i).getHeight() ,OF_IMAGE_COLOR);
                
                
                pointCount++;
            }
        }
        
		XML.popTag();
    }


    /////////////////////////
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