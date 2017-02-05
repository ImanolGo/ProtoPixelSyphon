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


const int AudioVisualsManager::NUMBER_VISUALS = 2;
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
    this->setupFft();
    this->setupShader();
    this->setupParticles();
    this->setupRings();

    ofLogNotice() <<"AudioVisualsManager::initialized" ;
    
}

void AudioVisualsManager::setupBoundingBox()
{
    float ratio = ((float)ofGetWidth())/ofGetHeight();
    
    m_boundingBox.width = AppManager::getInstance().getGuiManager().getWidth();
    m_boundingBox.height = m_boundingBox.width/ratio;
    
    
    m_boundingBox.y = AppManager::getInstance().getGuiManager().getPosition().y + AppManager::getInstance().getGuiManager().getHeight() + 20;
    m_boundingBox.x = AppManager::getInstance().getGuiManager().getPosition().x;
}


void AudioVisualsManager::setupFft()
{
    m_fftLive.setMirrorData(false);
    m_fftLive.setup();
    m_fftLive.setThreshold(1.01);
    m_fftLive.setPeakDecay(0.915);
    m_fftLive.setMaxDecay(0.995);

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


void AudioVisualsManager::update()
{
    if (!m_playAudioVisuals) {
        return;
    }
    
    
    this->updateFft();
    
    switch (m_mode)
    {
        case 0:
            this->updateRings();
            break;
        case 1:
            this->updateParticles();
            break;
        default:
            break;
    }
    
    this->updateFbo();
}

void AudioVisualsManager::updateFft()
{
    m_fftLive.update();
}

void AudioVisualsManager::updateParticles()
{
    int numOfVerts = 3;
    
    float * audioData = new float[numOfVerts];
    m_fftLive.getFftPeakData(audioData, numOfVerts);
    
    m_particles.setParameters(audioData[0], audioData[2]);
    m_particles.update();
    
    delete[] audioData;
}

void AudioVisualsManager::updateRings()
{
    int numOfVerts = 3;
    float * audioData = new float[numOfVerts];
    m_fftLive.getFftPeakData(audioData, numOfVerts);
    
    m_rings.setParameters(audioData[0], audioData[2]);
    m_rings.update();
    
    delete[] audioData;
}


void AudioVisualsManager::updateFbo()
{
    
    ofEnableAlphaBlending();
    m_fbo.begin();
    
        switch (m_mode)
        {
            case 0:
                this->drawRings();
                break;
            case 1:
                this->drawParticles();
                break;            
            default:
                break;
        }
    
    m_fbo.end();
    ofDisableAlphaBlending();
    
    ofPixels pixels;
    m_fbo.readToPixels(pixels);
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





