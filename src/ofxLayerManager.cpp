//
//  ofxLayerManager.cpp
//  LayerSystem
//
//  Created by Nicole Messier on 3/25/19.
//
//

#include "ofxLayerManager.h"

ofxLayerManager::ofxLayerManager()
{
    
}

ofxLayerManager::~ofxLayerManager()
{
    
}

void ofxLayerManager::setup()
{
    /*
     Parse Json
     */
    
    bool parsingJson = jsonRef.open(jsonFilePath);
    
    if(parsingJson)
    {
        ofLogNotice("ofxLayerManager::setup") << "Succesfully initial parse of " << jsonFilePath << " with data: " << jsonRef.getRawString();
        
        /*
         1. Set up initial layers
         */
        
        const ofxJSONElement & totalLayers = jsonRef["totalLayers"];
        int numLayers = totalLayers.asInt();
        
        for(int i = 0; i < numLayers; i++)
        {
            Layer* temp = new Layer();
            temp->setup();
            layers.push_back(temp);
        }
        
        /*
         2. Parse zones and individual objects
         */
        const ofxJSONElement & zones = jsonRef["zones"];
        
        for(int i = 0; i < zones.size(); i++)
        {
            const ofxJSONElement & zoneNum = zones[i]["zone-number"];
            const ofxJSONElement & zoneUID = zones[i]["zone-uid"];
            const ofxJSONElement & animations = zones[i]["animations"];
            
            zoneNames.push_back(zoneUID.asString());
            
            for(int j = 0; j < animations.size(); j++)
            {
                const ofxJSONElement & newMediaObj = animations[j];
                const ofxJSONElement & layer = newMediaObj["layer"];
                
                if(layer.asInt() < layers.size())
                {
                    const ofxJSONElement & name = newMediaObj["name"];
                    const ofxJSONElement & fps = newMediaObj["fps"];
                    const ofxJSONElement & loadType = newMediaObj["load-type"];
                    const ofxJSONElement & _animType = newMediaObj["animation-type"];
                    
                    //App::LoadType loadType,
                    //App::AnimationType animType,
                    
                    //const ofxJSONElement & path = newMediaObj["path"];
                    const ofxJSONElement & pos = newMediaObj["position"];
                    
                    
                    //const ofxJSONElement & width = newMediaObj["width"];
                    //const ofxJSONElement & height = newMediaObj["height"];
                    
                    const ofxJSONElement & next = newMediaObj["next"];
                    
                    /*
                     
                    temp->setup(UID, pos, zone, layer);
                     
                     */
                    
                    /*
                   addMediaObject (string UID,
                     ofVec2f pos,
                     int zoneOrder,
                     string zoneUID,
                     int layer,
                     LayerData::AnimationType animType)
                    */
                    LayerData::AnimationType animType = static_cast<LayerData::AnimationType>(_animType.asInt());
                    string uid = ofToUpper(name.asString());
                    
                    layers[layer.asInt()]->addMediaObject(uid,
                                                          ofVec2f(pos[0].asFloat(), pos[1].asFloat()),
                                                          zoneNum.asInt(),
                                                          zoneUID.asString(),
                                                          layer.asInt(),
                                                          animType); //zone
                    
                    switch(animType)
                    {
                        case LayerData::IMAGE_SEQUENCE: { break; }
                        case LayerData::TRAVERSING: {
                            
                            const ofxJSONElement & _endPos = newMediaObj["endPosition"];
                            ofVec2f endPos = ofVec2f(_endPos[0].asFloat(), _endPos[1].asFloat());
                            layers[layer.asInt()]->getMediaObject(uid)->setEndPos(endPos);
                                                                                                        
                            break;
                        }
                        case LayerData::ROTATING: { break; }
                        case LayerData::WIGGLING: { break; }
                        case LayerData::BOBBING: { break; }
                        default: break;
                    }
                                                                                              
                    
                    
                    animationsByZone.insert(pair<string, string>(ofToUpper(name.asString()), ofToUpper(zoneUID.asString()) ));
                }
                else
                {
                    ofLogError("ofxLayerManager::setup") << "Object layer, " << layer.asInt() << ", is out of bounds!";
                }
            }
        }
        
        
        /*
         3.  Parse Image layers
         */
        
        const ofxJSONElement & imageLayers = jsonRef["image-layers"];
        
        for(int i = 0; i < imageLayers.size(); i++)
        {
            const ofxJSONElement & newImage = imageLayers[i];
            const ofxJSONElement & name = newImage["name"];
            const ofxJSONElement & path = newImage["path"];
            const ofxJSONElement & layer = newImage["layer"];
            
            if(layer.asInt() < layers.size())
            {
                layers[layer.asInt()]->addBgImage(path.asString());
            }
            else
            {
                ofLogError("ofxLayerManager::setup") << "Object layer, " << layer.asInt() << ", is out of bounds!";
            }
            
        }
    }
    else
    {
        ofLogError("ofxLayerManager::setup") << "Unable to parse json";
    }
}

void ofxLayerManager::update(float dt)
{
    for( auto & layer : layers)
    {
        layer->update(dt);
    }
}

void ofxLayerManager::draw()
{
    for( auto & layer : layers)
    {
        layer->draw();
    }
}

#pragma mark LAYERS
int ofxLayerManager::getNumLayers()
{
    return layers.size();
}

Layer* ofxLayerManager::getLayer(int index)
{
    if(index >= layers.size())
        return nullptr;
    
    return layers[index];
}

