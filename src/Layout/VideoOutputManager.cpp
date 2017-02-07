/*
 *  VideoOutputManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "VideoOutputManager.h"



VideoOutputManager::VideoOutputManager(): Manager(), m_blurScale(0.0)
{
	//Intentionally left empty
}


VideoOutputManager::~VideoOutputManager()
{
    ofLogNotice() <<"VideoOutputManager::Destructor";
}


void VideoOutputManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();
    
    this->setupFbo();
    this->setupSyphon();
    this->setupBlur();
    
    ofLogNotice() <<"VideoOutputManager::initialized";

}

void VideoOutputManager::setupFbo()
{
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth() - AppManager::getInstance().getGuiManager().getWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fboVideoOutput.allocate(width, height);
    m_fboVideoOutput.begin(); ofClear(0); m_fboVideoOutput.end();
}

void VideoOutputManager::setupSyphon()
{
    string name = AppManager::getInstance().getSettingsManager().getSyphonName();
    m_syphonServer.setName(name);
    
    ofLogNotice() <<"VideoOutputManager::setupSyphon << Setting up Syphon server: " << name;
}

void VideoOutputManager::setupBlur()
{
    float radius = 10; float shape = .2; float passes = 1;
    m_blur.setup(m_fboVideoOutput.getWidth(), m_fboVideoOutput.getHeight(), radius, shape, passes);
    m_blur.setScale(m_blurScale);
}

void VideoOutputManager::draw()
{
    m_fboVideoOutput.draw(0,0);
    
    //m_blur.draw();
    
    m_syphonServer.publishTexture(&m_fboVideoOutput.getTexture());
}


void VideoOutputManager::begin()
{
    int brightness = 255*AppManager::getInstance().getAudioManager().getAudioMax();
    
    //ofLogNotice() <<"VideoOutputManager::setupSyphon << brightness: " << brightness;

    
    ofPushStyle();
    m_fboVideoOutput.begin();
    m_blur.begin();
    ofClear(0);
    ofSetColor(brightness);
}

void VideoOutputManager::end()
{
     m_blur.end();
     m_blur.draw();
     m_fboVideoOutput.end();
     ofPopStyle();
    
}

void VideoOutputManager::onBlurScaleChange(float& value)
{
    m_blurScale = value;
    m_blur.setScale(m_blurScale);
}





