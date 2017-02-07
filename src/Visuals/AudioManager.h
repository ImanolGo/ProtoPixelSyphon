/*
 *  AudioManager.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 06/02/17.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"

#include "TextVisual.h"
#include "RectangleVisual.h"

#include "ofxFFTLive.h"

//========================== class AudioManager ==============================
//============================================================================
/** \class AudioManager AudioManager.h
 *	\brief Class managing the audio input
 *	\details It reads from the input microphone and calculates the energy.
 */


class AudioManager: public Manager
{
    
public:
    
    //! Constructor
    AudioManager();
    
    //! Destructor
    ~AudioManager();
    
    //! Setup the Audio Manager
    void setup();
    
    //! Update the Audio Manager
    void update();
    
    //! Draw the Audio Manager
    void draw();
    
    float getAudioMax();
    
    void onChangeVolume(float& value);
    
    void onChangeAudioOn(bool& value);
    
    void setAudioMax(float audioMax);
    
    
private:
    
    void setupFFT();
    
    void drawCircle();
    
    
private:
    
    float           m_volume;
    ofxFFTLive      m_fft;
    bool            m_audioOn;
    float           m_audioMax;
    ofPoint         m_circlePosition;
    
    ofPtr<TextVisual>        m_audioText;
    ofPtr<RectangleVisual>   m_audioRect;
    
};


