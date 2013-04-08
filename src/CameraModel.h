//
//  CameraModel.h
//  multicam_imgrec
//
//  Created by Cameron Browning on 4/8/13.
//
//

#ifndef __multicam_imgrec__CameraModel__
#define __multicam_imgrec__CameraModel__

#include "ofxXmlSettings.h"
#include <iostream>

using namespace std;

class CameraModel{
    
public:
    
    CameraModel(string name_in="no name.", string desc_in="no description.", string guid_in="X", int fps_in=30);
    ~CameraModel();
    
    void setup();
    void setName(string name_in);
    void setDesc(string desc_in);
    void setGuid(string guid_in);
    void setFPS(int fps_in);
    void setSize(int w_in=640,int h_in=480);

    string getName();
    string getDesc();
    string getGuid();
    int getFPS();
    int getWidth();
    int getHeight();
    
    void load();
    
private:
    string name;
    string desc;
    string guid;
    int fps;
    int w;
    int h;
    ofxXmlSettings XML;
};

#endif /* defined(__multicam_imgrec__CameraModel__) */
