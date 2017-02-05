/*
 *  VideoManager.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#pragma once

#include "Manager.h"


//========================== class VideoManager ==============================
//============================================================================
/** \class VideoManager VideoManager.h
 *	\brief Class managing the video player visuals
 *	\details it creates and updates the video player
 */

class VideoManager: public Manager
{
    
    static const string VIDEO_PATH;
    
public:
    
    //! Constructor
    VideoManager();
    
    //! Destructor
    ~VideoManager();
    
    //! Setup the Video Manager
    void setup();
    
    //! Update the Video Manager
    void update();
    
    //! Draw the Video Manager
    void draw();
    
    void  onPlayVideoChange(bool value);
    
    void  onNextVideoChange();
    
    void onRecordVideoLoopsChange(bool& value);
    
    void onVideoTrailChange(bool& value);
    
    void resetPosition();
    
    void onHueChange(float& value) {m_color.setHue(value);}
    
    void onBrightnessChange(float& value) {m_color.setBrightness(value);}
    
    void onSaturationChange(float& value) {m_color.setSaturation(value);}
    
    void onVideoSpeedChange(float& value) {m_videoPlayer.setSpeed(value);}
    
private:
    
    void setupFbo();
    
    void loadVideos();
    
    void setupBoundingBox();
    
    
private:
    
    typedef vector <string> Videos;
    
    ofVideoPlayer 	m_videoPlayer;
    Videos          m_videos;
    string          m_currentVideo;
    
    bool            m_playVideo;
    bool            m_recordVideoLoops;
    bool            m_trail;
    ofRectangle     m_boundingBox;
    
    ofFbo           m_fbo;
    ofColor         m_color;
    int             m_frameNumber;
    
};



