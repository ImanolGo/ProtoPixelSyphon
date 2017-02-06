/*
 *  VideoManager.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */

#include "ofMain.h"

#include "VideoManager.h"
#include "AppManager.h"
#include "ofQTKitPlayer.h"


const string VideoManager::VIDEO_PATH = "videos/";

VideoManager::VideoManager(): Manager(), m_playVideo(false), m_recordVideoLoops(false), m_trail(false), m_frameNumber(-1)
{
    //Intentionally left empty
}


VideoManager::~VideoManager()
{
    ofLogNotice() <<"VideoManager::Destructor" ;
}


void VideoManager::setup()
{
    if(m_initialized)
        return;
    
    
    Manager::setup();
    
    this->loadVideos();
    this->setupBoundingBox();
    this->setupFbo();
    
    ofLogNotice() <<"VideoManager::initialized" ;
    
}


void VideoManager::loadVideos()
{

    //shared_ptr<ofQTKitPlayer> videoPlayer = shared_ptr<ofQTKitPlayer>(new ofQTKitPlayer()) ;
    //m_videoPlayer.setPlayer(videoPlayer);
    
    //string path = VIDEO_PATH;
    string path = "/Users/imanolgo/MEGA/Video/ProtoPixelVideos";
    ofLogNotice()<< "VideoManager::loadVideos->loading samples from \""<<path<<"\"";
    ofDirectory dir(path);
    dir.allowExt("mp4");
    dir.allowExt("mov");
    dir.allowExt("avi");
    //populate the directory object
    if(dir.listDir()==0){
        ofLogNotice()<< "VideoManager::loadVideos-> No samples found in \""<<path<<"\"";
    }
    
    //go through and print out all the paths
    for(int i = 0; i < dir.size(); i++)
    {
        string videoPath = dir.getPath(i);
        m_videos.push_back(videoPath);
        ofLogNotice()<< "VideoManager::loadVideos-> Loaded: \""<<videoPath<<"\"";
    }
    
    m_currentVideo = m_videos.front();
    m_videoPlayer.load(m_currentVideo);
    //m_videoPlayer.setLoopState(OF_LOOP_NONE);
    m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
}

void VideoManager::setupBoundingBox()
{
    m_boundingBox.width = AppManager::getInstance().getVideoOutputManager().getVideoFbo().getWidth();
    m_boundingBox.height = AppManager::getInstance().getVideoOutputManager().getVideoFbo().getHeight();
    
    m_boundingBox.y = 0;
    m_boundingBox.x = 0;
}

void VideoManager::setupFbo()
{
    m_fbo.allocate(m_videoPlayer.getPixels().getWidth(), m_videoPlayer.getPixels().getHeight(),GL_RGBA);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void VideoManager::resetPosition()
{
    setupBoundingBox();
}

void VideoManager::update()
{
    if (!m_playVideo) {
        return;
    }
    
    
    m_videoPlayer.update();
    
}


void VideoManager::draw()
{
    if (!m_playVideo) {
        return;
    }
    
    
    m_fbo.begin();
    ofPushStyle();
    
    if(m_trail){
        ofEnableAlphaBlending();
        ofFill();
        ofSetColor(0,0,0, 5);
        ofDrawRectangle(0,0,m_fbo.getWidth(),m_fbo.getHeight());
        ofSetColor(m_color, 12);;
    }
    else{
        ofClear(0);
        ofSetColor(m_color);
    }
    
    
    m_videoPlayer.draw(0,0);
    ofPopStyle();
    m_fbo.end();
    
    m_fbo.draw(m_boundingBox);
    
    //m_videoPlayer.draw(0,0);
    
}

void VideoManager::onPlayVideoChange(bool value)
{
    ofLogNotice()<< "VideoManager::onPlayVideoChange: " << value;
    
    if(value){
        m_playVideo = true;
        m_videoPlayer.play();
    }
    else{
        m_playVideo = false;
        m_videoPlayer.stop();
    }
}

void VideoManager::onRecordVideoLoopsChange(bool& value) {
    
    m_recordVideoLoops = value;
    
    if(m_recordVideoLoops){
        m_videoPlayer.setLoopState(OF_LOOP_NONE);
    }
    else{
        m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
    }
    
}

void VideoManager::onVideoTrailChange(bool& value) {
    
    m_trail = value;
}

void VideoManager::onNextVideoChange()
{
    for (int i = 0; i < m_videos.size(); i++) {
        if(m_videos[i] == m_currentVideo){
            int index = (i+1)%m_videos.size();
            m_currentVideo = m_videos[index];
            break;
        }
    }
    
   // m_videoPlayer.close();
    
    m_videoPlayer.load(m_currentVideo);
    
    m_videoPlayer.stop();
    
    if(m_playVideo){
        
        m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
        
        if(m_recordVideoLoops){
            m_videoPlayer.setLoopState(OF_LOOP_NONE);
        }
        
        m_videoPlayer.play();
        
    }
    
    this->setupFbo();
}



