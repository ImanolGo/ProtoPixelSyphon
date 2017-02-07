/*
 *  AudioManager.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 06/02/17.
 *
 */


#include "AudioManager.h"
#include "AppManager.h"


AudioManager::AudioManager(): m_volume(0.5), m_audioMax(1.0)
{
    //Intentionaly left empty
}


AudioManager::~AudioManager()
{
    ofLogNotice() <<"AudioManager::Destructor" ;
}


void AudioManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"AudioManager::initialized" ;
    
    this->setupFFT();
}


void AudioManager::setupFFT()
{
    m_fft.setup();
    m_fft.setMirrorData(false);
    m_fft.setPeakDecay(0.915);
    m_fft.setMaxDecay(0.995);
    m_fft.setThreshold(1.0);
}


void AudioManager::update()
{
    if (!m_audioOn) {
        return;
    }
    
    m_fft.update();
    m_audioMax = ofMap(m_fft.getAveragePeak(), 0.0, 0.2, 0.0, 1.0, true);
    
    //ofLogNotice() <<"AudioManager::update: " << m_fft.getAveragePeak();
    //ofLogNotice() <<"AudioManager::update2: " << m_fft.getLoudBand();
}

void AudioManager::draw()
{
    //m_fft.draw(340,600);
    this->drawCircle();
}

void AudioManager::drawCircle()
{
    int mainWindowIndex = 0;
    
    float radius = ofMap(m_audioMax, 0.0, 1.0, 10, 200, true);
    
    //ofColor color = AppManager::getInstance().getSettingsManager().getColor("GUI1");
    
    ofPushStyle();
    ofSetCircleResolution(100);
    ofSetColor(ofColor::white);
        ofDrawCircle(m_circlePosition, radius);
    ofPopStyle();
    
  
}


void AudioManager::onChangeVolume(float& value)
{
    m_volume = value;
    //m_fft.setVolume(m_volume);
}

void AudioManager::setAudioMax(float audioMax)
{
    if(m_audioOn){
        return;
    }
    
    m_audioMax = audioMax;
}

void AudioManager::onChangeAudioOn(bool& value)
{
    m_audioOn = value;
    if(!m_audioOn){
        m_audioMax = 1.0;
    }
    
}


float AudioManager::getAudioMax()
{
    return m_audioMax;
}

