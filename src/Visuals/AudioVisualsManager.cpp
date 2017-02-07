/*
 *  AudioVisualsManager.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */

#include "ofMain.h"

#include "AudioVisualsManager.h"
#include "AppManager.h"


const int AudioVisualsManager::NUMBER_VISUALS = 3;
const int AudioVisualsManager::FBO_WIDTH = 1030;
const int AudioVisualsManager::FBO_HEIGHT = 524;

AudioVisualsManager::AudioVisualsManager(): Manager(), m_playAudioVisuals(false), m_inputLevel(1.0), m_mode(0)
{
	//Intentionally left empty
}


AudioVisualsManager::~AudioVisualsManager()
{
    ofLogNotice() <<"AudioVisualsManager::Destructor" ;
}


void AudioVisualsManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupBoundingBox();
    this->setupFbo();
    this->setupShader();
    this->setupParticles();
    this->setupRings();
    this->setupStrobe();

    ofLogNotice() <<"AudioVisualsManager::initialized" ;
    
}

void AudioVisualsManager::setupBoundingBox()
{
    m_boundingBox.width = AppManager::getInstance().getVideoOutputManager().getVideoFbo().getWidth();
    m_boundingBox.height = AppManager::getInstance().getVideoOutputManager().getVideoFbo().getHeight();
    
    m_boundingBox.y = 0;
    m_boundingBox.x = 0;
}

void AudioVisualsManager::setupFbo()
{
    m_fbo.allocate(FBO_WIDTH, FBO_HEIGHT,GL_RGBA32F_ARB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void AudioVisualsManager::setupShader()
{
    m_shader.setGeometryInputType(GL_LINES);
    m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    m_shader.setGeometryOutputCount(4);
    m_shader.load("shaders/ThickLineShaderVert.glsl", "shaders/ThickLineShaderFrag.glsl", "shaders/ThickLineShaderGeom.glsl");
}

void AudioVisualsManager::resetPosition()
{
    setupBoundingBox();
}

void AudioVisualsManager::setupParticles()
{
    m_particles.setup();
}

void AudioVisualsManager::setupRings()
{
    m_rings.setup();
}

void AudioVisualsManager::setupStrobe()
{
    m_strobe.setup();
}


void AudioVisualsManager::update()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
    switch (m_mode)
    {
        case 0:
            this->updateStrobe();
            break;
        case 1:
            this->updateParticles();
            break;
        case 2:
            this->updateRings();
            break;
        default:
            break;
    }
    
    this->updateFbo();
}


void AudioVisualsManager::updateParticles()
{
    float audioMax = AppManager::getInstance().getAudioManager().getAudioMax();
    
    m_particles.setParameters(audioMax, audioMax);
    m_particles.update();
}

void AudioVisualsManager::updateRings()
{
    float audioMax = AppManager::getInstance().getAudioManager().getAudioMax();
    
    m_rings.setParameters(audioMax, audioMax);
    m_rings.update();
}


void AudioVisualsManager::updateStrobe()
{
   float audioMax = AppManager::getInstance().getAudioManager().getAudioMax();
    
    m_strobe.setParameters(audioMax);
    m_strobe.update();
}

void AudioVisualsManager::updateFbo()
{
    
    ofEnableAlphaBlending();
    m_fbo.begin();
    
        switch (m_mode)
        {
            case 0:
                this->drawStrobe();
                break;
            case 1:
                this->drawParticles();
                break;
            case 2:
                this->drawRings();
                break;
            default:
                break;
        }
    
    m_fbo.end();
    ofDisableAlphaBlending();
    
    ofPixels pixels;
    m_fbo.readToPixels(pixels);
}

void AudioVisualsManager::drawStrobe()
{
    m_strobe.draw();
}
void AudioVisualsManager::drawParticles()
{
    ofPushStyle();
    ofFill();
    ofSetColor(0,0,0,40);
    ofDrawRectangle(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    
    m_shader.begin();
    m_shader.setUniform1f("thickness", 2);
    
    m_particles.draw();
    
    ofPopStyle();
    m_shader.end();
}

void AudioVisualsManager::drawRings()
{
    ofPushStyle();
    ofFill();
    ofSetColor(0,0,0,12);
    ofDrawRectangle(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    
    m_shader.begin();
    m_shader.setUniform1f("thickness", 6);

    m_rings.draw();
    
    ofPopStyle();
    m_shader.end();

    
}

void AudioVisualsManager::draw()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
    ofSetColor(m_color);
    m_fbo.draw(m_boundingBox);
}

void AudioVisualsManager::onPlayAudioVisualsChange(bool value)
{
    m_playAudioVisuals = value;
}

void AudioVisualsManager::onNextAudiohange()
{
    m_mode = (m_mode + 1) % NUMBER_VISUALS;
}





