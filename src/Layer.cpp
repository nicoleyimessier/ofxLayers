//
//  Layer.cpp
//  LayerSystem
//
//  Created by Nicole Messier on 3/25/19.
//
//

#include "Layer.h"

Layer::Layer()
{
    
}

Layer::~Layer()
{
    
}

void Layer::setup()
{
    
}

void Layer::update(float dt)
{
    
}

void Layer::draw(){
    
    if(hasBgImage)
    {
        //Draw BackgroundImage
        bgImage->draw(0.0f, 0.0f);
    }

    
    // Draw media Objects
    for(auto &obj : mediaObjects)
    {
        obj->draw();
        obj->drawDebug();
    }
}

#pragma mark VISIBILITY
void Layer::setIsVisble(bool visible)
{
    
}

#pragma mark MEDIA OBJECTS

void Layer::addBgImage(string imgPath)
{
    if(hasBgImage) return;
    
    ofLogNotice("Layer::addBgImage") << "Adding static bg image " << imgPath;
    
    bgImage = new ofImage();
    bgImage->load(imgPath);
    hasBgImage = true;
}

void Layer::addMediaObject(string UID,
                           ofVec2f pos,
                           int zone,
                           int layer)
{
    
    ofLogNotice("Layer::addMediaObject") << "Adding MediaObject-" << UID << " layer: " << layer;
    
    MediaObject * temp = new MediaObject();
    temp->setup(UID, pos, zone, layer);
    mediaObjects.push_back(temp);
    
}
