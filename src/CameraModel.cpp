//
//  CameraModel.cpp
//  multicam_imgrec
//
//  Created by Cameron Browning on 4/8/13.
//
//

#include "CameraModel.h"


CameraModel::CameraModel(string name_in, string desc_in, string guid_in, int fps_in){
    name = name_in;
    desc = desc_in;
    guid = guid_in;
    fps = fps_in;
}
CameraModel::~CameraModel(){
    
}

void setup(){ };

void CameraModel::setName(string name_in){ name = name_in; }
void CameraModel::setDesc(string desc_in){ desc=desc_in; }
void CameraModel::setGuid(string guid_in){ guid = guid_in; }
void CameraModel::setFPS(int fps_in){ fps = fps_in; }
void CameraModel::setSize(int w_in,int h_in){ w = w_in; h = h_in; }

string CameraModel::getName(){ return name; }
string CameraModel::getDesc(){ return desc; }
string CameraModel::getGuid(){ return guid; }
int CameraModel::getFPS(){ return fps; }
int CameraModel::getWidth(){ return w; }
int CameraModel::getHeight(){ return h; }

void CameraModel::load(){
    
}
